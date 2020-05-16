#include<stdio.h>
#include "wymierne.h"
//Jakub Kuciński, grupa środa 10-12, Lista 4 zadanie 2, nr indeksu 309881, 13.11.2018, Wstęp do programowania w C

//typ Wielomian może przechowywać wspolczynniki wielomianu maksymalnie stopnia 100
#define ROZMIAR 100
//W elemencie STOPIEN Wielomianu trzymamy informacje o jego stopniu
#define STOPIEN ROZMIAR+1
typedef Wymierna Wielomian[ROZMIAR+2];

//Funcja wczytuje wspolczynniki Wielomianu t o stopniu n
int czytajwiel(int n, Wielomian t);
//Procedura wypisuje dany wielomian
void wypiszwiel(Wielomian t);
//Funkcja zwraca wartosc Wielomianu t w punkcie wymiernym x
Wymierna wartosc(Wymierna x, Wielomian t);
//Funkcja sumuje wielomiany a b i ich wynik zapisuje do Wielomian wynik
void sumawiel(Wielomian a, Wielomian b, Wielomian wynik);
//Funkcja odejmuje wielomian b od wielomianu a i ich wynik zapisuje do Wielomian wynik
void roznicawiel(Wielomian a, Wielomian b, Wielomian wynik);
//Funkcja oblicza iloczyn wielomianow a b i wynik zapisuje do Wielomian wynik
void iloczynwiel(Wielomian a, Wielomian b, Wielomian wynik);

