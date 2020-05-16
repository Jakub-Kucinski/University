#include "wymierne.h"
//Jakub Kuciński, grupa środa 10-12, Lista 4 zadanie 2, nr indeksu 309881, 13.11.2018, Wstęp do programowania w C
int gcc(int n, int m)
{
    if(m==0)
        return n;
    else
        return gcc(m, n%m);
}

Wymierna tworzenie(int n, int m)
{
    if(m<0)
    {m=m*(-1); n=n*(-1);}
    int nwd=0;
    if(n!=0)
    {
        if(n<0)
            nwd=gcc(n*(-1), m);
        else
            nwd=gcc(n, m);
        n=n/nwd; m=m/nwd;
    }

    long long int l=n;
    Wymierna wynik=0;
    wynik=wynik | m;
    wynik=wynik | (l<<32);
    return wynik;
}

int wyodrebnij_licznik(Wymierna n)
{
    unsigned int pom=0;
    int licznik=0;
    licznik=(n>>32) & (~pom);
    return licznik;
}

unsigned int wyodrebnij_mianownik(Wymierna n)
{
    unsigned int pom=0;
    unsigned int mianownik=0;
    mianownik=n & (~pom);
    return mianownik;
}

Wymierna wczytywanie()
{
    int n=0;
    int m=1;
    scanf("%d/%d", &n, &m);
    if(m==0) m=1;
    if(n==0) m=1;
    Wymierna a=tworzenie(n, m);
    return a;
}

void wypisywanie(Wymierna n)
{
    unsigned int mianownik=wyodrebnij_mianownik(n);
    int licznik=wyodrebnij_licznik(n);
    printf("%d/%u", licznik, mianownik);
}

Wymierna iloczyn(Wymierna a, Wymierna b)
{
    Wymierna wynik=0;
    int l1=wyodrebnij_licznik(a);
    int l2=wyodrebnij_licznik(b);
    unsigned int m1=wyodrebnij_mianownik(a);
    unsigned int m2=wyodrebnij_mianownik(b);
    if(l1==0 || l2==0)
    {
        wynik=wynik + 1;
        return wynik;
    }
    long long int la=l1;
    long long int lb=l2;
    long long unsigned int ma=m1;
    long long unsigned int mb=m2;
    la=la*lb;
    ma=ma*mb;
    int nwd=0;
    if(la<0)
        nwd=gcc(la*(-1), ma);
    else
        nwd=gcc(la, ma);
    la=la/nwd;
    ma=ma/nwd;
    wynik=tworzenie(la, ma);
    return wynik;
}

Wymierna odwrotnosc(Wymierna a)
{
    int l1=wyodrebnij_licznik(a);
    int m1=wyodrebnij_mianownik(a);
    if(l1<0)
    {l1=l1*(-1); m1=m1*(-1);}
    Wymierna wynik;
    wynik=tworzenie(m1, l1);
    return wynik;
}

Wymierna iloraz(Wymierna a, Wymierna b)
{
    if(wyodrebnij_licznik(b)==0)
        return 0;
    Wymierna odwrotnab=odwrotnosc(b);
    Wymierna wynik=iloczyn(a, odwrotnab);
    return wynik;
}

Wymierna suma(Wymierna a, Wymierna b)
{
    int l1=wyodrebnij_licznik(a);
    int l2=wyodrebnij_licznik(b);
    unsigned int m1=wyodrebnij_mianownik(a);
    unsigned int m2=wyodrebnij_mianownik(b);
    long long int la=l1;
    long long int lb=l2;
    long long unsigned int ma=m1;
    long long unsigned int mb=m2;
    long long unsigned int nwd=gcc(ma, mb);
    long long unsigned int mw=ma*(mb/nwd);
    long long int lw=la*(mb/nwd) + lb*(ma/nwd);
    if(lw<0)
        nwd=gcc(lw*(-1), mw);
    else
        nwd=gcc(lw, mw);
    lw=lw/nwd;
    mw=mw/nwd;
    Wymierna wynik=tworzenie(lw, mw);
    return wynik;
}

Wymierna roznica(Wymierna a, Wymierna b)
{
    int l2=wyodrebnij_licznik(b);
    unsigned int m2=wyodrebnij_mianownik(b);
    l2=l2*(-1);
    Wymierna przeciwnab=tworzenie(l2, m2);
    Wymierna wynik=suma(a, przeciwnab);
    return wynik;
}

