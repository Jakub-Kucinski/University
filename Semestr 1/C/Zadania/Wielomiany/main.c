#include <stdio.h>
#include <stdlib.h>
#include "wymierne.h"
#include "wielomiany.h"
//Jakub Kuciński, grupa środa 10-12, Lista 4 zadanie 2, nr indeksu 309881, 13.11.2018, Wstęp do programowania w C

void sprawdzanie();
int main()
{
    sprawdzanie();

    return 0;
}

void sprawdzanie()
{
    printf("Podaj stopien pierwszego wielomianu (liczba naturalna)\n");
    int s1=0;
    scanf("%d", &s1);
    Wielomian a;
    printf("Podaj wspolczynniki pierwszego wielomianu (liczby wymierne po spacjach)\n");
    czytajwiel(s1, a);

    printf("Podaj stopien drugiego wielomianu (liczba naturalna)\n");
    int s2=0;
    scanf("%d", &s2);
    Wielomian b;
    printf("Podaj wspolczynniki drugiego wielomianu (liczby wymierne po spacjach)\n");
    czytajwiel(s2, b);

    printf("Podaj punkt wymierny, w ktorym chcesz obliczyc wartosc wielomianow\n");
    Wymierna n=wczytywanie();

    printf("\nPierwszy wielomian\n");
    wypiszwiel(a);
    printf("\nWartosc w podanym punkcie: ");
    Wymierna p=wartosc(n, a);
    wypisywanie(p);
    printf("\n");

    printf("\nDrugi wielomian\n");
    wypiszwiel(b);
    printf("\nWartosc w podanym punkcie: ");
    p=wartosc(n, b);
    wypisywanie(p);
    printf("\n");

    printf("\nSuma wielomianow\n");
    Wielomian wielsum;
    sumawiel(a, b, wielsum);
    wypiszwiel(wielsum);
    printf("\n");

    printf("\nRoznica wielomianow\n");
    Wielomian wielroz;
    roznicawiel(a, b, wielroz);
    wypiszwiel(wielroz);
    printf("\n");

    printf("\nIloczyn wielomianow\n");
    Wielomian wynik;
    iloczynwiel(a, b, wynik);
    wypiszwiel(wynik);
    printf("\n");

}
