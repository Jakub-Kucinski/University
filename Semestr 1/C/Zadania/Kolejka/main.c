#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Struct.h"

/*Jakub Kuciński, nr indeksu 309881, Lista zadań 7, zadanie 2., 04.12.2018, grupa środa 10-12, wstęp do programowania w C */

int main()
{
    Kolejka t=utworz();
    for(double i=0; i<5; i++)
    {
        t=dodaj_na_koniec(t, i);
    }
    wypisz(t); printf("\n");

    for(double i=5; i<10; i++)
    {
        t=dodaj_na_pocz(t, i);
    }
    wypisz(t); printf("\n"); printf("\n");

    /*Kolejka kopia=skopiuj(t);
    wypisz(kopia);printf("\n"); printf("\n");*/

    /*Kolejka pusta=utworz();
    Kolejka nowa=polacz_kolejki(t, pusta);
    wypisz(nowa);*/

    Kolejka nowa=quicksort(&t);
    wypisz(nowa); printf("\n");

    return 0;
}
