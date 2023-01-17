CC=gcc

CFLAGS= -Og -std=gnu11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function
# ogolne flagi kompilacji dla modulow

LDFLAGS= -lpthread
# ogolne flagi konsolidacji programu

DEPS = zad1.h
NAME = zad2
NAME2 = zad3

$(NAME): zad2.c zad1.o $(DEPS)
	$(CC) $(CFLAGS) zad2.c zad1.o -o $(NAME) $(LDFLAGS)

zad1.o: zad1.c $(DEPS)
	$(CC) -c $(CFLAGS) zad1.c -o zad1.o

clean:
	rm *.o zad2