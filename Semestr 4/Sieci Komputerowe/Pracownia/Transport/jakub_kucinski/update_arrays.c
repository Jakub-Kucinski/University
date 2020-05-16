// Jakub Kuciński 309881
#include "header.h"

void update_times_and_resend_expired(int sockfd, char *ip_addr, int port, int start, int length, int size, 
                                     int frame_size, char received[], struct timeval times[], suseconds_t usec_passed)
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