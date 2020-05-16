#include "header.h"

void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}

// -1 jeśli nie nasz pakiet
// 0 jeśli nasz ale nie docelowe ip
// 1 jeśli nasz i docelowe ip
int icmp_receive(u_int8_t current_ttl, int sockfd, char copy_to[20])
{
	struct sockaddr_in sender;
	socklen_t sender_len = sizeof(sender);
	u_int8_t buffer[IP_MAXPACKET];
	ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
	if (packet_len < 0) {
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
		exit(1);
	}

	struct ip* ip_header = (struct ip*) buffer;

	u_int8_t * icmp_packet = buffer + 4 * ip_header->ip_hl;
	struct icmp* icmp_header = (struct icmp*) icmp_packet;

	u_int8_t type = icmp_header->icmp_type;
	u_int8_t code = icmp_header->icmp_code;

	//echo reply - wtedy dotarliśmy do adresu docelowego
	if(type == 0 && code == 0)
	{

		if(icmp_header->icmp_hun.ih_idseq.icd_id == (u_int16_t) getpid() && (icmp_header->icmp_hun.ih_idseq.icd_seq)/3 == (u_int16_t) current_ttl)
		{
			if(inet_ntop(AF_INET, &(sender.sin_addr), copy_to, 20) == NULL)
			{
				fprintf(stderr, "inet_ntop error: %s\n", strerror(errno)); 
				exit(1);
			}
			return 1;
		}
	}
	
	//time exceeded - wtedy nie jesteśmy w adresie docelowym
	if(type == 11 && code == 0)
	{
		struct ip* ip_header_inner = (struct ip*) ( ((u_int8_t*)icmp_header) + 8);
		u_int8_t * icmp_packet_inner = ((u_int8_t*) ip_header_inner) + 4 * ip_header_inner->ip_hl;
		struct icmp* icmp_header_inner = (struct icmp*) icmp_packet_inner;

		if(icmp_header_inner->icmp_hun.ih_idseq.icd_id == (u_int16_t) getpid() && (icmp_header_inner->icmp_hun.ih_idseq.icd_seq)/3 == (u_int16_t) current_ttl)
		{
			if(inet_ntop(AF_INET, &(sender.sin_addr), copy_to, 20) == NULL)
			{
				fprintf(stderr, "inet_ntop error: %s\n", strerror(errno)); 
				exit(1);
			}
			return 0;
		}
	}

	return -1;
}

void print_next_routers(char ips[3][20], u_int8_t current_ttl, long long time, int i)
{
	printf("%hi. ", (short) current_ttl);
	if(i == 0)
	{
		printf("*\n");
		return;
	}
	if(i == 1)
	{
		printf("%s ???\n", ips[0]);
		return;
	}
	if(i == 2)
	{
		printf("%s ", ips[0]);
		if(strcmp(ips[0], ips[1]) != 0)
		{
			printf("%s ", ips[1]);
		}
		printf("???\n");
		return;
	}
	if(i == 3)
	{
		printf("%s ", ips[0]);
		if(strcmp(ips[0], ips[1]) != 0)
		{
			printf("%s ", ips[1]);
		}
		if(strcmp(ips[0], ips[2]) != 0 && strcmp(ips[1], ips[2]) != 0)
		{
			printf("%s ", ips[2]);
		}
		printf("%lli ms\n", (time/3000));
		return;
	}
}



int icmp_wait_to_receive(u_int8_t current_ttl, int sockfd)
{
	struct timeval tv; 
	tv.tv_sec = 1; 
	tv.tv_usec = 0;
	int ready;
	char ips[3][20];
	int i = 0;
	long long time = 0;
	int is_target = 0;
	for(;;)
	{
		fd_set descriptors;
		FD_ZERO(&descriptors);
		FD_SET(sockfd, &descriptors);
		ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);

		if(ready < 0)
		{
			fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
			exit(1);
		}
		if(ready > 0)
		{
			int k = icmp_receive(current_ttl, sockfd, ips[i]);
			if(k == 0)
			{
				i++;
				time += 1000000 - ((long long) tv.tv_usec);
			}
			if(k == 1)
			{
				is_target = 1;
				i++;
				time += 1000000 - ((long long) tv.tv_usec);
			}
			if(i == 3)
			{
				break;
			}
		}
		if(ready == 0)
		{
			break;
		}
	}
	
	print_next_routers(ips, current_ttl, time, i);

	return is_target;
}
