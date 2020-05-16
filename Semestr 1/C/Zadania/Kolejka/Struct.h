#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*Jakub Kuciński, nr indeksu 309881, Lista zadań 7, zadanie 2., 04.12.2018, grupa środa 10-12, wstęp do programowania w C */

typedef struct wezel
{
    double info;
    struct wezel* nast;

}* Kolejka, Wezel;

Kolejka utworz();
Kolejka dodaj_na_pocz(Kolejka t, double x);
Kolejka dodaj_na_koniec(Kolejka t, double x);
double zwroc_wart_z_pocz(Kolejka t);
double usun_i_zwroc(Kolejka *t);
bool czy_pusta(Kolejka t);
int dlugosc(Kolejka t);
void wypisz(Kolejka t);
Kolejka polacz_kolejki(Kolejka t1, Kolejka t2);
Kolejka skopiuj(Kolejka t);
Kolejka wstaw(Kolejka t, double x);
Kolejka insertsort(Kolejka t);
Kolejka quicksort(Kolejka* t);
