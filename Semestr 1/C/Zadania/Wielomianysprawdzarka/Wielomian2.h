#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR 1000
#define STOPIEN ROZMIAR+1
typedef long long int lli;
typedef lli Wielomian[ROZMIAR+2];

void wyzeruj(Wielomian t);
void dodajwspolcz(Wielomian t, int n, lli wspolczynnik);
void pomnozprzezstala(Wielomian t, lli n);
void wypiszwiel(Wielomian t);
void przepisz(Wielomian kopiowany, Wielomian docelowy);
void sumawiel(Wielomian a, Wielomian b, Wielomian wynik);
void roznicawiel(Wielomian a, Wielomian b, Wielomian wynik);
void iloczynwiel(Wielomian a, Wielomian b, Wielomian wynik);
void pochodnawiel(Wielomian a, Wielomian wynik);
void podstawwiel(Wielomian a, Wielomian podstawiany, Wielomian wynik);
