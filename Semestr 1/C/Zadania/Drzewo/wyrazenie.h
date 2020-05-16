#include <stdio.h>
#include <stdlib.h>

#define MAX 100;

typedef struct wezel{
    char op;
    double arg;
    struct wezel * lewy, * prawy;
} Wezel, *NaWezel;

NaWezel utworz(double x);
NaWezel polacz(NaWezel a, NaWezel b, char znak);
int czy_arg(NaWezel t);
int priorytet(NaWezel t);
int czy_przemienny(NaWezel t);

void wypisz(NaWezel t);

