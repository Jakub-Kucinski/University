#include <stdio.h>
#include <stdlib.h>
#include "wyrazenie.h"

NaWezel utworz(double x)
{
    Wezel * nowy=malloc(sizeof(Wezel));
    nowy->arg=x;
    nowy->prawy=NULL;
    nowy->lewy=NULL;
    nowy->op=' ';
    return nowy;
}

NaWezel polacz(NaWezel a, NaWezel b, char znak)
{
    Wezel * nowy=malloc(sizeof(Wezel));
    nowy->lewy=a;
    nowy->prawy=b;
    nowy->op=znak;
    return nowy;
}

int czy_arg(NaWezel t)
{
    if(t->op==' ')
        return 1;
    return 0;
}

int priorytet(NaWezel t)
{
    if(t->op=='*' || t->op=='/')
        return 1;
    return 0;
}

int czy_przemienny(NaWezel t)
{
    if(t->op=='*' || t->op=='+')
        return 1;
    return 0;
}

void wypisz(NaWezel t)
{
    if(czy_arg(t))
    {
        printf("%lf", t->arg);
    }
    else
    {
        if(czy_arg(t->lewy))
        {
            wypisz(t->lewy);
        }
        else
        {
            if(priorytet(t)>priorytet(t->lewy))
            {
                printf("(");
                wypisz(t->lewy);
                printf(")");
            }
            else
            {
                wypisz(t->lewy);
            }
        }

        printf("%c", t->op);

        if(czy_arg(t->prawy))
        {
            wypisz(t->prawy);
        }
        else
        {
            if(priorytet(t)>priorytet(t->prawy))
            {
                printf("(");
                wypisz(t->prawy);
                printf(")");
            }
            else
            {
                if(priorytet(t)<priorytet(t->prawy))
                {
                    wypisz(t->prawy);
                }
                else
                {
                    if()
                }
            }
        }

    }
}

/*void wypisz(NaWezel t)
{
    if(czy_arg(t))
    {
        printf("%lf", t->arg);
    }
    else
    {
        wypisz(t->lewy);
        printf("%c", t->op);
        wypisz(t->prawy);
    }
}*/

