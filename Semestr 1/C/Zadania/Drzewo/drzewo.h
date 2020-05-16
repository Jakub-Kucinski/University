#include <stdio.h>
#include <stdlib.h>

/*Jakub Kuciński, Lista 8 zadanie 1., 5.12.2018, Wstęp do programowania w C, nr indeksu 309881, grupa środa 10-12 */

#define MAX 100

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


