#include "wielomiany.h"
//Jakub Kuciński, grupa środa 10-12, Lista 4 zadanie 2, nr indeksu 309881, 13.11.2018, Wstęp do programowania w C

int czytajwiel(int n, Wielomian t)
{
    //Zerowanie wspolczynnikow wielomianu t
    for(int i=0; i<=ROZMIAR+1; i++)
        t[i]=1;
    int k=1;
    //Jesli podany stopien wielomianu jest wiekszy niz maksymalny rozmiar to wpisz do n maksymalny rozmiar
    if(n>ROZMIAR)
    {
        k=0;
        n=ROZMIAR;
    }
    //Wpisanie stopnia wielomianu do elementu STOPIEN (101. element)
    t[STOPIEN]=tworzenie(n, 1);
    //Wczytywanie kolejnych wspolczynnikow od najwyzszych poteg
    for(int i=n; i>=0; i--)
    {
        t[i]=wczytywanie();
    }
    return k;
}

//Procedura wypisuje wielomian t w postaci (an)*x^n + (an-1)*x^n-1 + ... + (a0), gdzie {an} to liczby wymierne
void wypiszwiel(Wielomian t)
{
    int n=wyodrebnij_licznik(t[STOPIEN]);
    for(int i=n; i>0; i--)
    {
        printf("(");
        wypisywanie(t[i]);
        printf(")*x^%d + ", i);
    }
    printf("(");
    wypisywanie(t[0]);
    printf(")");
}

//Funkcja wylicza wartosc wielomianu t w punkcie wymiernym x i zwraca wartosc wyrazenia typu wymierna
Wymierna wartosc(Wymierna x, Wielomian t)
{
    Wymierna wynik=t[wyodrebnij_licznik(t[STOPIEN])];
    for(int i=wyodrebnij_licznik(t[STOPIEN])-1; i>=0; i--)
    {
        wynik=iloczyn(wynik, x);
        wynik=suma(wynik, t[i]);
    }
    return wynik;
}


void sumawiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=wyodrebnij_licznik(a[STOPIEN]);
    int lb=wyodrebnij_licznik(b[STOPIEN]);
    //Ustalanie wiekszego ze stopni wielomianow a i b
    int wieksza=lb;
    if(la>lb)
    {
        wieksza=la;
    }
    //Zerowanie wielomianu wynikowego
    for(int i=0; i<=ROZMIAR+1; i++)
        wynik[i]=1;
    //Sumowanie poszczegolnych wspolczynnikow
    for(int i=0; i<=wieksza; i++)
    {
        wynik[i]=suma(a[i], b[i]);
    }
    //Ustalanie stopnia wielomianu wynik
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=1)
        {
            wynik[STOPIEN]=tworzenie(i, 1);
            break;
        }
    }
}

//Roznica dziala analogicznie do sumy
void roznicawiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=wyodrebnij_licznik(a[STOPIEN]);
    int lb=wyodrebnij_licznik(b[STOPIEN]);
    int wieksza=lb;
    if(la>lb)
    {
        wieksza=la;
    }
    for(int i=0; i<=ROZMIAR+1; i++)
        wynik[i]=1;
    for(int i=0; i<=wieksza; i++)
    {
        wynik[i]=roznica(a[i], b[i]);
    }
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=1)
        {
            wynik[STOPIEN]=tworzenie(i, 1);
            break;
        }
    }
}


void iloczynwiel(Wielomian a, Wielomian b, Wielomian wynik)
{
    int la=wyodrebnij_licznik(a[STOPIEN]);
    int lb=wyodrebnij_licznik(b[STOPIEN]);
    //Zerowanie wielomianu wynikowego
    for(int i=0; i<=ROZMIAR+1; i++)
        wynik[i]=1;
    //Wyliczanie wspolczynnikow przy poszczegolnych potegach
    for(int k=0; k<=la; k++)
    {
        for(int j=0; j<=lb; j++)
        {
            wynik[k+j]=suma(wynik[k+j], iloczyn(a[k], b[j]));
        }
    }
    //Ustalanie stopnia wielomianu wynik
    for(int i=ROZMIAR; i>=0; i--)
    {
        if(wynik[i]!=1)
        {
            wynik[STOPIEN]=tworzenie(i, 1);
            break;
        }
    }
}


