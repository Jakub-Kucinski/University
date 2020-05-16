#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "drzewo.h"

/*Jakub Kuciński, Lista 8 zadanie 1., 5.12.2018, Wstęp do programowania w C, nr indeksu 309881, grupa środa 10-12 */

int main()
{
    NaWezel stos[MAX];
    int gora=0;
    double x;
    char znak;
    while(1)
    {
        znak=getchar();
        if(isdigit(znak))
        {
            ungetc(znak, stdin);
            scanf("%lf", &x);
            stos[gora]=utworz(x);
            gora++;
        }
        else
        {
            if(znak=='=')
                break;
            if(isspace(znak)){;}
            else
            {
                if(gora<2)
                {
                    printf("Brak argumentow");
                    exit(1);
                }
                stos[gora-2]=polacz(stos[gora-2],stos[gora-1], znak);
                gora--;
            }
        }
    }
    wypisz(stos[0]);
    return 0;
}
