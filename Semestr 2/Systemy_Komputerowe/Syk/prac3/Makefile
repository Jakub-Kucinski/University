CC = gcc -ggdb
CFLAGS = -std=gnu11 -Wall -Wextra -Werror 

all: zad1 zad2 zad3 zad4

zad1: zad1.o
zad2: zad2.o
zad3: zad3.o
zad4: zad4.o
	$(CC) $(CFLAGS) -o $@ $^ -ldl -lpthread -lrt -Wl,-rpath,`pwd`

clean:
	rm -f zad1 zad2 zad3 zad4
	rm -f *.o
	rm -f *~
