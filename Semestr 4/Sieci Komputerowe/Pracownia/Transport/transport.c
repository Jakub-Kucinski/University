// Jakub Kuciński 309881
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



void update_times_and_resend_expired(int sockfd, char *ip_addr, int port, int start, int length, int size, int frame_size, char received[], struct timeval times[], suseconds_t usec_passed)
{
    for (int i = 0; i < frame_size; i++)
    {
        if(start + i * length >= size)
            break;
        int index = (start / length + i) % frame_size;
        if(received[index] == 0)
        {
            if (usec_passed >= times[index].tv_usec)
            {
                if(times[index].tv_sec == 0)
                {
                    times[index].tv_sec = 0;
                    times[index].tv_usec = 100000;
                    send_request(sockfd, ip_addr, port, start + i * length, length);
                }
                else
                {
                    times[index].tv_sec -= 1;
                    times[index].tv_usec = times[index].tv_usec + 1000000 - usec_passed;
                }
            }
            else
            {
                times[index].tv_usec -= usec_passed;
            }
        }
    }
}


int write_to_file_and_update_arrays(int sockfd, char *ip_addr, int port, int start, int length, int size, int frame_size, 
char datagrams[], char received[], struct timeval times[], suseconds_t usec_passed, FILE *fp)
{
    update_times_and_resend_expired(sockfd, ip_addr, port, start, length, size, frame_size, received, times, usec_passed);
    int i = 0;
    for (i = 0; i < frame_size; i++)
    {
        if(start + i * length >= size)
            return start + i * length;
        int index = (start / length + i) % frame_size;
        if(received[index] == 1)
        {
            fwrite(&datagrams[index * length], length, sizeof(char), fp);
            if(start + i * length + length * frame_size < size)
            {
                received[index] = 0;
                times[index].tv_sec = 0;
                times[index].tv_usec = 100000;
                send_request(sockfd, ip_addr, port, start + i * length + length * frame_size, length);
            }
        }
        else
        {
            break;
        }
    }
    printf("%.2f%% done\n", ((float)(start + i * length)) / size * 100);
    return start + i * length;
}

void get_last_datagram(int sockfd, char *ip_addr, int port, int length, int size, FILE *fp)
{
    int start = size - (size % length);
    char write_to[length + 1];
    while (start < size)
    {
        fd_set descriptors;
	    FD_ZERO(&descriptors);
	    FD_SET(sockfd, &descriptors);
	    struct timeval tv; 
	    tv.tv_sec = 0; 
	    tv.tv_usec = 100000;
        send_request(sockfd, ip_addr, port, start, size % length);
        for (;;)
        {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
            if(ready < 0)
            {
                fprintf(stderr, "select error: %s\n", strerror(errno)); 
                exit(1);
            }
            if(ready > 0)
            {
                int k = get_reply(sockfd, ip_addr, port, write_to, size % length);
                // Odpowiedź do naszego requesta
                if(k == start)
                {
                    start += length;
                    fwrite(write_to, size % length, sizeof(char), fp);
                    break;
                }
            }
            if(ready == 0)
            {
                break;
            }
        }
    }
}

void get_file(int sockfd, char *file_name, char *ip_addr, int port, int length, int size, int frame_size)
{
    // Otwieranie pliku
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
    // write_to - aktualnie pobrany datagram, datagrams - datagramy z ramki, received - czy otrzymano odpowiedni datagram, times - czasy oczekiwania na konkretny datagram.
    // tablice datagrams, received i times są wykorzystywane "cyklicznie" poprzez branie indexów modulo frame_size
    char write_to[length + 1];
    char datagrams[length * frame_size];
    char received[frame_size];
    struct timeval times[frame_size];
    for (int i = 0; i < frame_size; i++)
    {
        times[i].tv_sec = 0;
        times[i].tv_usec = 100000;
        received[i] = 0;
    }

    for (int i = 0; i < frame_size && i * length < size; i++)
    {
        send_request(sockfd, ip_addr, port, i * length, length);
    }
    int last_datagram_size = size % length;
    int original_size = size;
    size -= last_datagram_size;
    int start = 0;
    while (start + length < size)
    {
        fd_set descriptors;
        FD_ZERO(&descriptors);
	    FD_SET(sockfd, &descriptors);
	    struct timeval tv; 
	    tv.tv_sec = 0;
	    tv.tv_usec = 10000;
        struct timeval start_tv;
        start_tv.tv_sec = 0;
	    start_tv.tv_usec = 10000;

        int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
        if(ready < 0)
        {
            fprintf(stderr, "select error: %s\n", strerror(errno)); 
            exit(1);
        }
        // Mamy jakąś odpowiedź. Musimy sprawdzić czy dotyczy naszego requesta (może starego)
        if(ready > 0)
        {
            int start_received = get_reply(sockfd, ip_addr, port, write_to, length);
            // Odpowiedź do requesta na którego jeszcze nie mieliśmy odpowiedzi
            if(start_received >= start && received[(start_received/length) % frame_size] == 0)
            {
                // printf("Index of reply: %d\n", (start_received / length) % frame_ssize);
                received[(start_received / length) % frame_size] = 1;
                copy_to(&datagrams[((start_received / length) % frame_size) * length], write_to, length);
                if (start_received == start) //Można wypisać bo pierwszy pakiet z ramki przyszedł
                {
                    start = write_to_file_and_update_arrays(sockfd, ip_addr, port, start, length, size, frame_size, datagrams, received, times, start_tv.tv_usec - tv.tv_usec, fp);
                }
                else //Trzeba zupdateować czasy i wysłać ponownie zapytania o nieotrzymane pakiety
                {
                    update_times_and_resend_expired(sockfd, ip_addr, port, start, length, size, frame_size, received, times, start_tv.tv_usec - tv.tv_usec);
                }
            }
        }
        if(ready == 0) //Trzeba zupdateować czasy i wysłać ponownie zapytania o nieotrzymane pakiety
        {
            update_times_and_resend_expired(sockfd, ip_addr, port, start, length, size, frame_size, received, times, start_tv.tv_usec - tv.tv_usec);
        }
    }

    if(last_datagram_size > 0) // Jeśli ostatni datagram jest niezerowy to należy go pobrać i zapisać
    {
        get_last_datagram(sockfd, ip_addr, port, length, original_size, fp);
    }
    printf("100.00%% done\n");
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
    int length = 1000;
    int frame_size = 2000;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    get_file(sockfd, file_name, ip_addr, port, length, size, frame_size);

    close(sockfd);

	return EXIT_SUCCESS;
}
	
