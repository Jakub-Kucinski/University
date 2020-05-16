#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct wezel
{
    double info;
    struct wezel * nast;

}*Kolejka, Wezel;

Kolejka uwtorz();
Kolejka dodaj_na_pocz(Kolejka t, double x);
Kolejka dodaj_na_koniec(Kolejka t, double x);
double zwroc_wart_z_pocz(Kolejka t);
double usun_i_zwroc(Kolejka t);
bool czy_pusta(Kolejka t);
int dlugosc(Kolejka t);
void wypisz(Kolejka t);
