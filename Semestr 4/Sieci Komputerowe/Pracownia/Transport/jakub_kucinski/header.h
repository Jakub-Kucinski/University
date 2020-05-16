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

void send_request(int sockfd, char *ip_addr, int port, int start, int length);
void copy_to(char *destiny, char *source, int n);
int get_reply(int sockfd, char *ip_addr, int port, char *write_to, int length);
void update_times_and_resend_expired(int sockfd, char *ip_addr, int port, int start, int length, int size, 
                                     int frame_size, char received[], struct timeval times[], suseconds_t usec_passed);
int write_to_file_and_update_arrays(int sockfd, char *ip_addr, int port, int start, int length, int size, int frame_size,
                                    char datagrams[], char received[], struct timeval times[], suseconds_t usec_passed, FILE *fp);