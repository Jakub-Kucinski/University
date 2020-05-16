CC = gcc
CFLAGS = -std=gnu99 -Wextra -Wall

TARGET = transport

SRCS = send_and_get_udp.c update_arrays.c transport.c  
OBJS = send_and_get_udp.o update_arrays.o transport.o

.PHONY: all clean distclean

all = $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
		$(RM) $(OBJS) 

distclean:
		$(RM) $(OBJS) $(TARGET)