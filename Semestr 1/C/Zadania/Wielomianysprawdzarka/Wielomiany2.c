#include <stdio.h>
#include <stdlib.h>
#include "Wielomian2.h"

void wyzeruj(Wielomian t)
{
    for(int i=0; i<=ROZMIAR+1; i++)
        t[i]=0;
    t[STOPIEN]=0;
}

void dodajwspolcz(Wielomian t, int n, lli wspolczynnik)
{
    t[n]=t[n]+wspolczynnik;
    if(n>t[STOPIEN])
        t[STOPIEN]=n;
}

void pomnozprzezstala(Wielomian t, lli n)
{
    for(int i=0; i<=t[STOPIEN]; i++)
    {
        t[i]=t[i]*n;
    }
}

void przepisz(Wielomian kopiowany, Wielomian docelowy)
{
    wyzeruj(docelowy);
    for(int i=0; i<=kopiowany[STOPIEN]; i++)
    {
        docelowy[i]=kopiowany[i];
    }
    docelowy[STOPIEN]=kopiowany[STOPIEN];
}

void wypiszwiel(Wielomian t)
{
    int n=t[STOPIEN];
    if(n==0)
    {
        printf("%lli", t[n]);
    }
    else
    {
        if(n==1)
        {
            if(t[n]!=1 && t[n]!=-1) printf("%lli", t[n]);
            if(t[n]==-1) printf("-");
            printf("x");
            if(t[0]<0)
            {
                printf(" - %lli", (-1)*t[0]);
            }
            else
            {
                if(t[0]>0)
                {
                    printf(" + %lli", t[0]);
                }
            }
        }
        else
        {
            if(t[n]!=1 && t[n]!=-1) printf("%lli", t[n]);
            if(t[n]==-1) printf("-");
            printf("x^%d", n);
            for(int i=n-1; i>1; i--)
            {
                if(t[i]<0)
                {
                    printf(" - ");
                    if(t[i]!=-1) printf("%lli", (-1)*t[i]);
                    printf("x^%d", i);
                }
                else
                {
                    if(t[i]>0)
                    {
                        printf(" + ");
                        if(t[i]!=1) printf("%lli", t[i]);
                        printf("x^%d", i);
                    }
                }
            }
            if(t[1]<0)
            {
                printf(" - ");
                if(t[1]!=-1) printf("%lli", (-1)*t[1]);
                printf("x");
            }
            else
            {
                if(t[1]>0)
                {
                    printf(" + ");
                    if(t[1]!=1) printf("%lli", t[1]);
                    printf("x");
                }
            }
            if(t[0]<0)
            {
                printf(" - %lli", (-1)*t[0]);
            }
            else
            {
                if(t[0]>0)
                {
                    printf(" + %lli", t[0]);
                }
            }
        }
    }

}


void sumawiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=a[STOPIEN];
    int lb=b[STOPIEN];
    //Ustalanie wiekszego ze stopni wielomianow a i b
    int wieksza=lb;
    if(la>lb)
    {
        wieksza=la;
    }
    //Zerowanie wielomianu wynikowego
    //for(int i=0; i<=ROZMIAR+1; i++)
    //    wynik[i]=0;
    //Sumowanie poszczegolnych wspolczynnikow
    for(int i=0; i<=wieksza; i++)
    {
        wynik[i]=a[i]+b[i];
    }
    //Ustalanie stopnia wielomianu wynik
    wynik[STOPIEN]=0;
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=0)
        {
            wynik[STOPIEN]=i;
            break;
        }
    }
}


//Roznica dziala analogicznie do sumy
void roznicawiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=a[STOPIEN];
    int lb=b[STOPIEN];
    int wieksza=lb;
    if(la>lb)
    {
        wieksza=la;
    }
    //for(int i=0; i<=ROZMIAR+1; i++)
    //   wynik[i]=0;
    for(int i=0; i<=wieksza; i++)
    {
        wynik[i]=a[i]-b[i];
    }
    wynik[STOPIEN]=0;
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=0)
        {
            wynik[STOPIEN]=i;
            break;
        }
    }
}

void iloczynwiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=a[STOPIEN];
    int lb=b[STOPIEN];
    //Zerowanie wielomianu wynikowego
    //for(int i=0; i<=ROZMIAR+1; i++)
    //    wynik[i]=0;
    //Wyliczanie wspolczynnikow przy poszczegolnych potegach
    for(int k=0; k<=la; k++)
    {
        for(int j=0; j<=lb; j++)
        {
            wynik[k+j]=wynik[k+j] + (a[k] * b[j]);
        }
    }
    //Ustalanie stopnia wielomianu wynik
    wynik[STOPIEN]=0;
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=0)
        {
            wynik[STOPIEN]=i;
            break;
        }
    }
}

void pochodnawiel(Wielomian a, Wielomian wynik)
{
    for(int i=0; i<a[STOPIEN]; i++)
    {
        wynik[i]=a[i+1]*(i+1);
    }
    wynik[STOPIEN]=a[STOPIEN]-1;
}


void podstawwiel(Wielomian a, Wielomian podstawiany, Wielomian wynik)
{
    Wielomian pom;
    wynik[0]=a[a[STOPIEN]];
    for(int i=a[STOPIEN]-1; i>=0; i--)
    {
        wyzeruj(pom);
        iloczynwiel(wynik, podstawiany, pom);
        przepisz(pom, wynik);
        dodajwspolcz(wynik, 0, a[i]);
    }
}


