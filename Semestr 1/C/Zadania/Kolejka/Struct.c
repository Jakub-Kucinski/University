#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Struct.h"

/*Jakub Kuciński, nr indeksu 309881, Lista zadań 7, zadanie 2., 04.12.2018, grupa środa 10-12, wstęp do programowania w C */

Kolejka utworz()
{
    return NULL;
}

bool czy_pusta(Kolejka t)
{
    if(t==NULL)
        return 1;
    return 0;
}

Kolejka dodaj_na_koniec(Kolejka t, double x)
{
    if(czy_pusta(t))
    {
        Wezel *nowy=malloc(sizeof(Wezel));
        nowy->nast=nowy;
        nowy->info=x;
        return nowy;
    }
    else
    {
        Wezel *nowy=malloc(sizeof(Wezel));
        nowy->nast=t->nast;
        nowy->info=x;
        t->nast=nowy;
        return nowy;
    }
}

Kolejka dodaj_na_pocz(Kolejka t, double x)
{
    if(czy_pusta(t))
    {
        Wezel *nowy=malloc(sizeof(Wezel));
        nowy->nast=nowy;
        nowy->info=x;
        return nowy;
    }
    else
    {
        Wezel *nowy=malloc(sizeof(Wezel));
        nowy->nast=t->nast;
        nowy->info=x;
        t->nast=nowy;
        return t;
    }
}

double zwroc_wart_z_pocz(Kolejka t)
{
    if(czy_pusta(t))
    {
        return NAN;
    }
    return (t->nast)->info;
}

double usun_i_zwroc(Kolejka *t)
{
    if(czy_pusta(*t))
    {
        printf("Kolejka pusta - nie mozna usunac elementu");
        exit(1);
    }
    if((*t)->nast==(*t))
    {
        double x=(*t)->info;
        (*t)=NULL;
        return x;
    }
    Wezel* wsk=(*t)->nast->nast;
    double x=((*t)->nast)->info;
    free((*t)->nast);
    (*t)->nast=wsk;
    return x;
}

int dlugosc(Kolejka t)
{
    if(czy_pusta(t))
        return 0;
    int ile=1;
    Wezel* wsk=t->nast;

    while(wsk!=t)
    {
        ile++;
        wsk=wsk->nast;
    }
    return ile;
}

void wypisz(Kolejka t)
{
    if(czy_pusta(t)==0)
    {
        int ile=1;
        Wezel* wsk=t->nast;

        while(wsk!=t)
        {
            printf("%lf ", wsk->info);
            ile++;
            wsk=wsk->nast;
        }
        printf("%lf ", t->info);
    }
}

Kolejka polacz_kolejki(Kolejka t1, Kolejka t2)
{
    if(czy_pusta(t1))
    {
        free(t1);
        return t2;
    }
    if(czy_pusta(t2))
    {
        free(t2);
        return t1;
    }
    Wezel* wsk=t1->nast;
    t1->nast=t2->nast;
    t2->nast=wsk;
    return t2;
}

Kolejka skopiuj(Kolejka t)
{
    if(czy_pusta(t))
        return NULL;

    Wezel* wsk=t->nast;
    Kolejka kopia=utworz();
    while(wsk!=t)
    {
        kopia=dodaj_na_koniec(kopia, wsk->info);
        wsk=wsk->nast;
    }
    kopia=dodaj_na_koniec(kopia, t->info);
    return kopia;
}

Kolejka wstaw(Kolejka t, double x)
{
    if(czy_pusta(t))
    {
        return dodaj_na_pocz(t, x);
    }
    if(x>(t->info))
    {
        return dodaj_na_koniec(t, x);
    }
    Wezel* wsk=t;
    if(x<=((wsk->nast)->info))
    {
        dodaj_na_pocz(wsk, x);
        return t;
    }
    wsk=wsk->nast;
    while(wsk!=t)
    {
        if(x<=((wsk->nast)->info))
        {
            dodaj_na_pocz(wsk, x);
            break;
        }
        wsk=wsk->nast;
    }
    return t;
}


Kolejka insertsort(Kolejka t)
{
    if(czy_pusta(t))
    {
        return t;
    }
    Kolejka posortowana=utworz();
    Wezel* wsk=t->nast;
    posortowana=wstaw(posortowana, t->info);
    while(wsk!=t)
    {
        posortowana=wstaw(posortowana, wsk->info);
        wsk=wsk->nast;
    }
    return posortowana;
}


Kolejka quicksort(Kolejka* t)
{
    if(czy_pusta((*t)))
    {
        return (*t);
    }
    if((*t)->nast==(*t))
    {
        return (*t);
    }
    double piwot=((*t)->nast)->info;
    usun_i_zwroc(t);

    Kolejka mniejszarowna=utworz();
    Kolejka wieksza=utworz();
    double pom;
    while(czy_pusta((*t))==0)
    {
        pom=usun_i_zwroc(t);
        if(pom>piwot)
        {
            wieksza=dodaj_na_pocz(wieksza, pom);
        }
        else
        {
            mniejszarowna=dodaj_na_pocz(mniejszarowna, pom);
        }
    }
    mniejszarowna=quicksort(&mniejszarowna);
    mniejszarowna=dodaj_na_koniec(mniejszarowna, piwot);
    wieksza=quicksort(&wieksza);
    return polacz_kolejki(mniejszarowna, wieksza);
}
