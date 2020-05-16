// Jakub Kuciński 309881
#include "header.h"

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
    // write_to - aktualnie pobrany datagram, datagrams - datagramy z ramki, 
    // received - czy otrzymano odpowiedni datagram, times - czasy oczekiwania na konkretny datagram
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
                    start = write_to_file_and_update_arrays(sockfd, ip_addr, port, start, length, size, 
                    frame_size, datagrams, received, times, start_tv.tv_usec - tv.tv_usec, fp);
                }
                else //Trzeba zupdateować czasy i wysłać ponownie zapytania o nieotrzymane pakiety
                {
                    update_times_and_resend_expired(sockfd, ip_addr, port, start, length, size, 
                    frame_size, received, times, start_tv.tv_usec - tv.tv_usec);
                }
            }
        }
        if(ready == 0) //Trzeba zupdateować czasy i wysłać ponownie zapytania o nieotrzymane pakiety
        {
            update_times_and_resend_expired(sockfd, ip_addr, port, start, length, size, 
            frame_size, received, times, start_tv.tv_usec - tv.tv_usec);
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

    if(close(sockfd) == -1)
    {
        fprintf(stderr, "close error: %s", strerror(errno)); 
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
	
