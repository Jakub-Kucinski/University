#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Lista6zad2.h"

/*Jakub Kuciński, nr indeksu 309881, Lista zadań 6, zadanie 2., 27.11.2018, grupa środa 10-12, wstęp do programowania w C */

void generator(int n, double t[n])
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        t[i]=(((double) rand()) / ((double) rand())) * ((double)rand());
    }
}

//Funkcja porownywania uzywana w funkcji qsort
int porownaj(const void * a, const void * b)
{
    double a1=*(double*)a;
    double b1=*(double*)b;
    if(a1>b1) return 1;
    if(a1==b1) return 0;
    return -1;
}

void quicksort(int n, double t[n])
{
    qsort(t, n, sizeof(double), porownaj);
}

//Moja wersja quicksorta
void mojsort(int n, double t[n])
{
    szybkisort(t, 0, n-1);
}

int szybki(double t[], int p, int k)
{
    int i=p, j=k;
    double piwot=(t[p]+t[k]+t[(p+k)/2])/3;
    //double piwot=t[p];
    while(true)
    {
        while(t[j]>piwot)
            j--;
        while(t[i]<piwot)
            i++;
        if(i<j)
        {
            double x=t[i];
            t[i]=t[j];
            t[j]=x;
            i++;
            j--;
        }
        else
        {
            return j;
        }
    }
}
void szybkisort(double t[], int p, int k)
{
    int pom;
    if(p<k)
    {
        pom=szybki(t, p, k);
        szybkisort(t, p, pom);
        szybkisort(t, pom+1, k);
    }
}

void czas_dzialania(int ile, int rozmiar, clock_t * minimalny, clock_t * sredni, clock_t * maksymalny, void (* sortowanie)(int, double []))
{
    double t[rozmiar];
    clock_t pocz;
    pocz=clock();

    generator(rozmiar, t);
    sortowanie(rozmiar, t);
    *minimalny=clock()-pocz;
    *maksymalny=*minimalny;

    clock_t wczesniejszy=clock();
    for(int i=1; i<ile; i++)
    {
        generator(rozmiar, t);
        sortowanie(rozmiar, t);
        clock_t aktulany=clock();
        if(*minimalny>aktulany-wczesniejszy)
            *minimalny=aktulany-wczesniejszy;
        if(*maksymalny<aktulany-wczesniejszy)
            *maksymalny=aktulany-wczesniejszy;
        wczesniejszy=aktulany;
    }
    *sredni= ((double) (clock()-pocz)) / ((double) ile);
}


int ibinarysearch(double tab[], double value, int left, int right)
{
    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (tab[middle] == value)
            return middle;
        else if (tab[middle] > value)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}

//Tablica t powinna być początkową nieposortowaną tablicą, a tablica posortowana tablicą posortowaną
bool czy_poprawny(int n, double t[n], double posortowana[n])
{
    //Sprawdzanie czy niemalejący
    for(int i=0; i<n-1; i++)
    {
        if(posortowana[i]>posortowana[i+1])
        {
            return 0;
        }
    }

    //Sprawdzanie czy permutacja
    //Stworze tablice pomocnicza pom, w ktorej beda znajdowaly sie wszystkie elementy posortowanej
    //w porzadku niemalejacym bez powtorzen
    //W tablicy "ile" bede trzymal informacje o liczbie wystapien liczby o tym samym indeksie co w pom
    double pom[n];
    int ile[n];
    for(int i=0; i<n; i++)
    {
        ile[i]=0;
    }
    pom[0]=posortowana[0];
    ile[0]++;
    int k=0;
    for(int i=1; i<n; i++)
    {
        if(posortowana[i]==posortowana[i-1])
        {
            ile[k]++;
        }
        else
        {
            k++;
            pom[k]=posortowana[i];
            ile[k]++;
        }
    }
    for(int i=0; i<n; i++)
    {
        //Szukamy w tablicy pom wystąpień kolejnych elementów tablicy początkowej
        int gdzie=ibinarysearch(pom, t[i], 0, k);
        //Nie znaleziono elementu
        if(gdzie==-1)
        {
            return 0;
        }
        else
        {
            //Jesli znaleziono, ale wszystkie wystąpienia elementu o wartości pom[gdzie] (t[i]) zostaly wykorzystane
            if(ile[gdzie]==0)
            {
                return 0;
            }
            //Jesli sa jeszcze wolne wystapienia to zmniejsz ich liczbe o 1
            else
            {
                ile[gdzie]--;
            }
        }
    }
    return 1;
}




