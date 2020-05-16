#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
/*Jakub Kuciński, nr indeksu 309881, Lista zadań 6, zadanie 2., 27.11.2018, grupa środa 10-12, wstęp do programowania w C */


void generator(int n, double t[n]);
int ibinarysearch(double tab[], double value, int left, int right);
bool czy_poprawny(int n, double t[n], double posortowana[n]);
void quicksort(int n, double t[n]);
int porownaj(const void * a, const void * b);
void mojsort(int n, double t[n]);
int szybki(double t[], int p, int k);
void szybkisort(double t[], int p, int k);
void czas_dzialania(int ile, int rozmiar, clock_t * minimalny, clock_t * sredni, clock_t * maksymalny, void (* sortowanie)(int, double []));
