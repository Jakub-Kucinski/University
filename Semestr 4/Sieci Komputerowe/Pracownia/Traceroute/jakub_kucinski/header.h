#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

#include <assert.h>
#include <stdint.h>
#include <netinet/ip_icmp.h>

#include <sys/time.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <unistd.h>

int icmp_wait_to_receive(u_int8_t current_ttl, int sockfd);
u_int16_t compute_icmp_checksum (const void *buff, int length);