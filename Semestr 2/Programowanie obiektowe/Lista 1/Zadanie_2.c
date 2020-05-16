#include <stdio.h>
#include <stdlib.h>

typedef struct ulamek
{
    int p;
    unsigned int q;
}Ulamek;

int gcd(int n, int m)
{
    if(m==0)
        return n;
    else
        return gcd(m, n%m);
}

int sgn(int a)
{
    if(a==0)
        return 0;
    if(a>0)
        return 1;
    return -1;
}

Ulamek * suma(Ulamek *w1, Ulamek *w2)
{
    int nwd=gcd(w1->q, w2->q);
    int mianownik=(w1->q/nwd)*w2->q;
    int licznik=(w1->p)*(w2->q/nwd) + (w2->p)*(w1->q/nwd);
    int znak=sgn(licznik);
    if(znak==0)
    {
        Ulamek * nowy=malloc(sizeof(Ulamek));
        nowy->p=0;
        nowy->q=1;
        return nowy;
    }
    if(licznik<0) licznik=licznik*(-1);
    nwd=gcd(licznik, mianownik);
    licznik=licznik/nwd * znak;
    mianownik=mianownik/nwd;
    Ulamek * nowy=malloc(sizeof(Ulamek));
    nowy->p=licznik;
    nowy->q=mianownik;
    return nowy;
}

Ulamek * roznica(Ulamek *w1, Ulamek *w2)
{
    Ulamek * pom=malloc(sizeof(Ulamek));
    pom->p=w2->p *(-1);
    pom->q=w2->q;
    Ulamek * wynik=suma(w1, pom);
    free(pom);
    return wynik;
}

Ulamek * iloczyn(Ulamek *w1, Ulamek *w2)
{
    if(w1->p==0 || w2->p==0)
    {
        Ulamek * nowy=malloc(sizeof(Ulamek));
        nowy->p=0;
        nowy->q=1;
        return nowy;
    }
    int znak=sgn(w1->p)*sgn(w2->p);
    int a=w1->p;
    if(a<0) a=a*(-1);
    int b=w2->p;
    if(b<0) b=b*(-1);
    int nwd1=gcd(a, w2->q);
    int nwd2=gcd(b, w1->q);
    Ulamek * nowy=malloc(sizeof(Ulamek));
    nowy->p=(a/nwd1)*(b/nwd2)*znak;
    nowy->q=(w1->q/nwd2)*(w2->q/nwd1);
    return nowy;
}

Ulamek * iloraz(Ulamek *w1, Ulamek *w2)
{
    if(w2->p==0)
        return NULL;
    Ulamek * pom=malloc(sizeof(Ulamek));
    pom->p=w2->q;
    pom->q=w2->p;
    Ulamek * wynik=iloczyn(w1, pom);
    free(pom);
    return wynik;
}

Ulamek * tworzenie(int licznik, int mianownik)
{
    if(mianownik==0)
        return NULL;
    if(licznik==0)
    {
        Ulamek * nowy=malloc(sizeof(Ulamek));
        nowy->p=0;
        nowy->q=1;
        return nowy;
    }
    int znak=sgn(licznik)*sgn(mianownik);
    if(licznik<0) licznik=licznik*(-1);
    if(mianownik<0) mianownik=mianownik*(-1);
    int nwd=gcd(licznik, mianownik);
    Ulamek * nowy=malloc(sizeof(Ulamek));
    nowy->p=licznik/nwd * znak;
    nowy->q=mianownik/nwd;
    return nowy;
}

void suma2(Ulamek *w1, Ulamek *w2)
{
    int nwd=gcd(w1->q, w2->q);
    int mianownik=(w1->q/nwd)*w2->q;
    int licznik=(w1->p)*(w2->q/nwd) + (w2->p)*(w1->q/nwd);
    int znak=sgn(licznik);
    if(znak==0)
    {
        w2->p=0;
        w2->q=1;
    }
    else
    {
        if(licznik<0) licznik=licznik*(-1);
        nwd=gcd(licznik, mianownik);
        licznik=licznik/nwd * znak;
        mianownik=mianownik/nwd;
        w2->p=licznik;
        w2->q=mianownik;
    }
}

void roznica2(Ulamek *w1, Ulamek *w2)
{
    w2->p=w2->p *(-1);
    suma2(w1, w2);
}

void iloczyn2(Ulamek *w1, Ulamek *w2)
{
    if(w1->p==0 || w2->p==0)
    {
        w2->p=0;
        w2->q=1;
    }
    else
    {
        int znak=sgn(w1->p)*sgn(w2->p);
        int a=w1->p;
        if(a<0) a=a*(-1);
        int b=w2->p;
        if(b<0) b=b*(-1);
        int nwd1=gcd(a, w2->q);
        int nwd2=gcd(b, w1->q);
        w2->p=(a/nwd1)*(b/nwd2)*znak;
        w2->q=(w1->q/nwd2)*(w2->q/nwd1);
    }
}
void iloraz2(Ulamek *w1, Ulamek *w2)
{
    if(w2->p!=0)
    {   
        int pom=w2->q;
        w2->q=w2->p;
        w2->p=pom;
        iloczyn2(w1, w2);
    }
}

int main()
{
    Ulamek * w1=tworzenie(-4, -6);
    Ulamek * w2=tworzenie(-9, 2);
    Ulamek * wynik=iloczyn(w1, w2);
    printf("%d %d\n", wynik->p, wynik->q);
    return 0;
}