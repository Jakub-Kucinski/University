// Jakub Kuciński 309881
#include "header.h"

void send_request(int sockfd, char *ip_addr, int port, int start, int length)
{
    struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(port);
	if(inet_pton(AF_INET, ip_addr, &server_address.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error: %s\n", strerror(errno)); 
        exit(1);
    }
    char message[50];
    if(sprintf(message, "GET %d %d\n", start, length) < 0)
    {
        fprintf(stderr, "sprintf error: %s\n", strerror(errno)); 
		exit(1);
    }
    ssize_t message_len = strlen(message);
	if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address)) != message_len) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno));
        exit(1);
    }
}

void copy_to(char *destiny, char *source, int n)
{
    for (int i = 0; i < n; i++)
    {
        destiny[i] = source[i];
    }
}

// k >=0 to nasz (może stary), k oznacza start
// -1 to nie nasz
int get_reply(int sockfd, char *ip_addr, int port, char *write_to, int length)
{
    struct sockaddr_in  sender;
    socklen_t           sender_len = sizeof(sender);
    u_int8_t            buffer[length + 30 + 1];

    ssize_t datagram_len = recvfrom (sockfd, buffer, length + 30, 0, (struct sockaddr*)&sender, &sender_len);
    if (datagram_len < 0) {
        fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
        exit(1);
    }
    buffer[datagram_len] = 0;

    char sender_ip_str[20]; 
    if(inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str)) == NULL)
    {
        fprintf(stderr, "inet_ntop error: %s\n", strerror(errno)); 
		exit(1);
    }
    if(strcmp(ip_addr, sender_ip_str) != 0 || ntohs(sender.sin_port) != port)
        return -1;
    
    char *pointer_newline = strchr((char*)buffer, '\n');
    char *data = &(pointer_newline[1]);
    pointer_newline[0] = 0;

    int start_received;
    int length_received;
    if(sscanf((char*)buffer, "DATA %d %d", &start_received, &length_received) < 2)
    {
        return -1;
    }

    copy_to(write_to, data, length_received);
    return start_received;
}