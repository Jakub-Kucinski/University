CC = gcc
CFLAGS = -std=gnu99 -Wextra -Wall

TARGET = traceroute

SRCS = icmp_checksum.c icmp_receive.c icmp_send.c
OBJS = icmp_checksum.o icmp_receive.o icmp_send.o

.PHONY: all clean distclean

all = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
		$(RM) $(OBJS) 

distclean:
		$(RM) $(OBJS) $(TARGET)