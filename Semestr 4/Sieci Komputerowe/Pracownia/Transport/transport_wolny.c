#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>

// 0 jeśli poprawne argumenty
// -1 w.p.p
int check_argv(char *argv[])
{
    struct sockaddr_in recipient;
    if(inet_pton(AF_INET, argv[1], &recipient.sin_addr) != 1)
        return -1;
    
    int len = strlen(argv[2]);
    for (int i = 0; i < len; i++)
        if(isdigit(argv[2][i]) == 0)
            return -1;
    
    len = strlen(argv[4]);
    for (int i = 0; i < len; i++)
        if(isdigit(argv[4][i]) == 0)
            return -1;
    
    return 0;
}

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

// 0 nagłówek się zgadza
// -1 nie zgadza
int check_is_proper_datagram(char *oncoming_datagram, int start, int length)
{
    char message[50];
    if(sprintf(message, "DATA %d %d", start, length) < 0)
    {
        fprintf(stderr, "sprintf error: %s", strerror(errno)); 
		exit(1);
    }
    if(strcmp(oncoming_datagram, message) != 0)
        return -1;
    return 0;
}


// 0 to nasz
// -1 to nie nasz lub stary
int get_reply(int sockfd, char *file_name,  char *ip_addr, int port, int start, int length, char *write_to)
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
    
    char *pointer_newline = strchr(buffer, '\n');
    char *data = &(pointer_newline[1]);
    pointer_newline[0] = 0;
    
    if (check_is_proper_datagram(buffer, start, length) == -1)
        return -1;

    for (int i = 0; i < length; i++)
    {
        write_to[i] = data[i];
    }
    // printf("%d\n", (int)strcmp(write_to, data));
    // printf ("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));

    // buffer[datagram_len] = 0;
    // printf("%ld-byte head: \n+%s+\n", (long int)datagram_len - length, buffer);
    // printf("%ld-byte message: \n", strlen(data));
    // printf("+%s+\n", data);
    return 0;
}

void get_file(int sockfd, char *file_name, char *ip_addr, int port, int length, int size)
{
    FILE *fp;
    int len = strlen(file_name);
    char path[len + 3];
    if(sprintf(path, "./%s", file_name) < 0)
    {
        fprintf(stderr, "sprintf error: %s", strerror(errno)); 
		exit(1);
    }
    fp = fopen(path, "w");
    if(fp == NULL)
    {
        fprintf(stderr, "fopen error: %s", strerror(errno)); 
		exit(1);
    }

    char write_to[length + 1];
    int start = 0;
    while (start < size)
    {
        fd_set descriptors;
	    FD_ZERO(&descriptors);
	    FD_SET(sockfd, &descriptors);
	    struct timeval tv; 
	    tv.tv_sec = 0;  // 2
	    tv.tv_usec = 500000;

        if (start + length <= size)
            send_request(sockfd, ip_addr, port, start, length);
        else
        {
            send_request(sockfd, ip_addr, port, start, size - start);
        }

        for (;;)
        {
            // printf("start: %d\n", start);
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
            if(ready < 0)
            {
                fprintf(stderr, "select error: %s\n", strerror(errno)); 
                exit(1);
            }
            // Mamy jakąś odpowiedź. Musimy sprawdzić czy dotyczy aktualnego zapytania
            if(ready > 0)
            {
                int n = length;
                if (start + length > size)
                    n = size - start;
                int k = get_reply(sockfd, file_name, ip_addr, port, start, n, write_to);
                // Odpowiedź do naszego requesta
                if(k == 0)
                {
                    start += length;
                    //Wpisz do pliku
                    fwrite(write_to, n, sizeof(char), fp);
                    break;
                }
                // W przeciwnym przypadku czekamy dalej (select)
            }
            // Upłynął czas na odpowiedź, trzeba wysłać jeszcze raz.
            if(ready == 0)
            {
                break;
            }
        }
    }
    // Zamknij plik 
    if(fclose(fp) == EOF)
    {
        fprintf(stderr, "fclose error: %s", strerror(errno)); 
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        fprintf(stderr, "Bad numer of arguments"); 
		return EXIT_FAILURE;
    }
    if(check_argv(argv) == -1)
    {
        fprintf(stderr, "Not valid arguments"); 
		return EXIT_FAILURE;
    }
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *file_name = argv[3];
    int size = atoi(argv[4]);
    // start in [0,10 000 000]
    int start = 0;
    // length in [1,1000]
    int length = 1000;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    get_file(sockfd, file_name, ip_addr, port, length, size);

    close(sockfd);

	return EXIT_SUCCESS;
}
	
