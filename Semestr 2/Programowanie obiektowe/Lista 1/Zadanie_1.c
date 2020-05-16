#include <stdio.h>
#include <stdlib.h>

typedef struct punkt
{
    float x;
    float y;
}Punkt;

typedef struct kwadrat
{
    Punkt p1;
    Punkt p2;
}Kwadrat;

typedef struct trojkat
{
    Punkt p1;
    Punkt p2;
    Punkt p3;
}Trojkat;

typedef struct kolo
{
    Punkt p1;
    float r;  
}Kolo;

enum typ_wyliczeniowy {TROJKAT, KWADRAT, KOLO};

typedef struct figura
{
    enum typ_wyliczeniowy typfig;
    union 
    {
        Kwadrat kw;
        Trojkat tr;
        Kolo kol;
    };   
}Figura;

float pole(Figura *f)
{
    if(f->typfig==TROJKAT)
    {
        float wynik=0.5*((f->tr.p1.x)-(f->tr.p2.x))*((f->tr.p1.y)-(f->tr.p3.y));
        if(wynik<0)
            return wynik*(-1);
        return wynik;
    }
    if(f->typfig==KWADRAT)
    {   
        float wynik=((f->kw.p1.x)-(f->kw.p2.x))*((f->kw.p1.y)-(f->kw.p2.y));
        if(wynik<0)
            return wynik*(-1);
        return wynik;
    }
    if(f->typfig==KOLO)
    {
        return 3.14 * (f->kol.r)*(f->kol.r);
    }
}

void przesun(Figura *f, float x, float y)
{
    if(f->typfig==TROJKAT)
    {
        f->tr.p1.x=f->tr.p1.x+x;
        f->tr.p2.x=f->tr.p2.x+x;
        f->tr.p3.x=f->tr.p3.x+x;
        f->tr.p1.y=f->tr.p1.y+y;
        f->tr.p2.y=f->tr.p2.y+y;
        f->tr.p3.y=f->tr.p3.y+y;
    }
    if(f->typfig==KWADRAT)
    {   
        f->kw.p1.x=f->kw.p1.x+x;
        f->kw.p2.x=f->kw.p2.x+x;
        f->kw.p1.y=f->kw.p1.y+y;
        f->kw.p2.y=f->kw.p2.y+y;
    }
    if(f->typfig==KOLO)
    {
        f->kol.p1.x=f->kol.p1.x+x;
        f->kol.p1.y=f->kol.p1.y+y;
    }
}

float sumapol(Figura *f, int size)
{
    float wynik=0;
    for(int i=0; i<size; i++)
    {
        wynik=wynik+pole(&(f[i]));
    }
}

Figura * inicjuj(int typ, float * t, int size)
{
    if(typ<0 || typ>2)
        return NULL;
    if(typ==0)
    {
        if(size<6 || (t[0]==t[2]) || (t[1]!=t[3]) || (t[5]==t[3]))
            return NULL;
        Figura * nowa=malloc(sizeof(Figura));
        nowa->typfig=TROJKAT;
        nowa->tr.p1.x=t[0];
        nowa->tr.p1.y=t[1];
        nowa->tr.p2.x=t[2];
        nowa->tr.p2.y=t[3];
        nowa->tr.p3.x=t[4];
        nowa->tr.p3.y=t[5];
        return nowa;
    }
    if(typ==1)
    {
        if(size<4)
            return NULL;
        float r1=t[0]-t[2];
        float r2=t[1]-t[3];
        if(r1!=r2 && (-1)*r1!=r2)
            return NULL;
        Figura * nowa=malloc(sizeof(Figura));
        nowa->typfig=KWADRAT;
        nowa->kw.p1.x=t[0];
        nowa->kw.p1.y=t[1];
        nowa->kw.p2.x=t[2];
        nowa->kw.p2.y=t[3];
        return nowa;
    }
    if(size<3 || t[2]<=0)
        return NULL;
    Figura * nowa=malloc(sizeof(Figura));
    nowa->typfig=KOLO;
    nowa->kol.p1.x=t[0];
    nowa->kol.p1.y=t[1];
    return nowa;
}

int main()
{
    Figura tablica[2];
    tablica[0].typfig=KOLO;
    tablica[0].kol.r=5.0;
    tablica[0].kol.p1.x=2.0;
    tablica[0].kol.p1.y=3.0;
    tablica[1].typfig=KWADRAT;
    tablica[1].kw.p1.x=2.0;
    tablica[1].kw.p1.y=2.0;
    tablica[1].kw.p2.x=4.0;
    tablica[1].kw.p2.y=4.0;
    printf("%f\n", sumapol(tablica, 2));

    /*Figura * nowa=malloc(sizeof(Figura));
    nowa->typfig=KOLO;
    nowa->kol.r=5.0;
    nowa->kol.p1.x=2.0;
    nowa->kol.p1.y=3.0;
    printf("%f\n", pole(nowa));
    printf("%f %f\n", nowa->kol.p1.x, nowa->kol.p1.y);
    przesun(nowa, 8.0, 10.0);
    printf("%f %f\n", nowa->kol.p1.x, nowa->kol.p1.y);*/
    return 0;
}