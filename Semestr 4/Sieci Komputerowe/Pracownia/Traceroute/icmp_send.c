#include "header.h"


void icmp_create_and_send(char * ip_addr, u_int8_t current_ttl, int sockfd)
{
    for(int k = 0; k < 3; k++)
    {
        struct icmp header;
        header.icmp_type = ICMP_ECHO;
        header.icmp_code = 0;
        header.icmp_hun.ih_idseq.icd_id = (u_int16_t) getpid();
        header.icmp_hun.ih_idseq.icd_seq = (u_int16_t) (current_ttl * 3 + k);
        header.icmp_cksum = 0;
        header.icmp_cksum = compute_icmp_checksum (
            (u_int16_t*)&header, sizeof(header)
            );

        struct sockaddr_in recipient;
        bzero(&recipient, sizeof(recipient));
        recipient.sin_family = AF_INET;
        if(inet_pton(AF_INET, ip_addr, &recipient.sin_addr) <= 0)
        {
            fprintf(stderr, "inet_pton error: %s\n", strerror(errno)); 
            exit(1);
        }

        u_int8_t ttl = current_ttl;
        if(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(u_int8_t)) < 0)
        {
            fprintf(stderr, "setsockopt error: %s\n", strerror(errno)); 
            exit(1);
        }

        ssize_t bytes_sent = sendto(
            sockfd,  
            &header,
            sizeof(header),
            0, 
            (struct sockaddr*)&recipient,
            sizeof(recipient)
            );
        if(bytes_sent < 0) 
        {
            fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
            exit(1);
        }
    }
}

int valid_ip(char * ip_addr)
{
    struct sockaddr_in recipient;
    return inet_pton(AF_INET, ip_addr, &recipient.sin_addr) == 1;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Bad numer of arguments\n"); 
		return EXIT_FAILURE;
    }
    if(!valid_ip(argv[1]))
    {
        fprintf(stderr, "Not a valid IP address\n"); 
		return EXIT_FAILURE;
    }

    char * ip_addr = argv[1];
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 
    {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

    for(u_int8_t ttl = 1; ttl <= 30; ttl++)
    {
        icmp_create_and_send(ip_addr, ttl, sockfd);

        if(icmp_wait_to_receive(ttl, sockfd))
        {
            break;
        }
    }
    return EXIT_SUCCESS;
}