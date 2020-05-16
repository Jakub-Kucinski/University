CC=gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
CFLAGS += -g -pipe -m64 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS += -I/usr/include/mysql
LFLAGS = -lm
LFLAGS += -lmysqlclient
LFLAGS += -L/usr/lib64 -L/usr/lib/x_86_64-linux-gnu

NAME = System_rejestracji_czasu_nauki
SRC = main.c Interfejs.c Baza_danych.c Zestawienia_interfejs.c Zestawienia_baza.c Admin_interfejs.c Admin_baza.c
DEPS = Interfejs.h Baza_danych.h Zestawienia_interfejs.h Zestawienia_baza.h Admin_interfejs.h Admin_baza.h
OBJS = main.o Interfejs.o Baza_danych.o Zestawienia_interfejs.o Zestawienia_baza.o Admin_interfejs.o Admin_baza.o

YOU : $(SRC) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)
