#include <stdio.h>
#include <stdlib.h>
#include "Wielomian2.h"

#include <stdbool.h>
#include <ctype.h>



typedef struct wezel{
    char op;
    Wielomian t;
    struct wezel * poprzedni;
} Wezel, *Stos;

Stos utworz();
bool czy_pusty(Stos t);
Stos dodaj_na_koniec(Stos glowny, Stos nowy);
Stos zwroc_strukt_z_gory(Stos t);
Stos usun_i_zwroc(Stos *t);


int main()
{
    char s[82];
    //scanf("%[^\n]s",&s);
    //for(int i=0; s[i]!='\n'; i++){scanf("%c ",&s[i]);}
    fgets(s, 82, stdin);

    //printf("Wczytalem!\n");
    //printf("%lu", sizeof(Wezel));
    Stos operatory=utworz();
    Stos wyjscie=utworz();
    int i=0;
    Wezel *nowy;

    while(s[i]!='\0')
    {
        //printf("W srodku");
        //printf("%d\n", s[i]);
        if(s[i]=='+')
        {
            //printf("Plus\n");
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='('))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op='+';
            operatory=dodaj_na_koniec(operatory, nowy);
        }
        if(s[i]=='-')
        {
            //Wolny minus
            if(isspace(s[i+1]))
            {
                //printf("Minus wolny\n");
                i++;
                while((czy_pusty(operatory)==0) && (operatory->op!='('))
                {
                    wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
                }
                nowy=malloc(sizeof(Wezel));
                nowy->op='-';
                operatory=dodaj_na_koniec(operatory, nowy);
            }
            //Minus w liczbie
            else
            {
                //printf("Minus zwiazany\n");
                lli wspolcz=0;
                i++;
                if(isdigit(s[i])==0)
                    wspolcz=1;
                while(isdigit(s[i]))
                {
                    wspolcz=10 * wspolcz + (s[i]-'0');
                    i++;
                }
                wspolcz=wspolcz*(-1);
                lli wyk=0;
                nowy=malloc(sizeof(Wezel));

                if(s[i]=='x')
                {
                    i++;
                    if(s[i]=='^')
                    {
                        i++;
                        while(isdigit(s[i]))
                        {
                            wyk=10 * wyk + (s[i]-'0');
                            i++;
                        }
                    }
                    else
                    {
                        wyk=1;
                    }
                }
                wyzeruj(nowy->t);
                dodajwspolcz(nowy->t, wyk, wspolcz);
                nowy->op=0;
                wyjscie=dodaj_na_koniec(wyjscie, nowy);
            }
        }
        if(s[i]=='*')
        {
            //printf("Razy\n");
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op='*';
            operatory=dodaj_na_koniec(operatory, nowy);
        }
        if(isdigit(s[i]))
        {
            //printf("Liczba\n");
            lli wspolcz=0;
            while(isdigit(s[i]))
            {
                wspolcz=10 * wspolcz + (s[i]-'0');
                i++;
            }
            lli wyk=0;
            nowy=malloc(sizeof(Wezel));
            if(s[i]=='x')
            {
                i++;
                if(s[i]=='^')
                {
                    i++;
                    while(isdigit(s[i]))
                    {
                        wyk=10 * wyk + (s[i]-'0');
                        i++;
                    }
                }
                else
                {
                    wyk=1;
                }
            }
            wyzeruj(nowy->t);
            dodajwspolcz(nowy->t, wyk, wspolcz);
            nowy->op=0;
            wyjscie=dodaj_na_koniec(wyjscie, nowy);
        }
        if(isspace(s[i]))
        {
            //printf("%d", i);
            //printf("Bialy znak");
            //printf("%d\n", s[i]);
            if(s[i]=='\n' || s[i]=='\0') break;
            i++;
        }
        if(s[i]=='(')
        {
            i++;
            //printf("Lewy okragly\n");
            nowy=malloc(sizeof(Wezel));
            nowy->op='(';
            operatory=dodaj_na_koniec(operatory, nowy);
        }
        if(s[i]==')')
        {
            //printf("Prawy okragly\n");
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='('))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            usun_i_zwroc(&operatory);
        }
        if(s[i]=='[')
        {
            //printf("Lewy kwadratowy\n");
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+') && (operatory->op!='*'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op='/';
            operatory=dodaj_na_koniec(operatory, nowy);

            nowy=malloc(sizeof(Wezel));
            nowy->op='(';
            operatory=dodaj_na_koniec(operatory, nowy);

            while(s[i]!='/')
            {
                if(s[i]=='+')
            {
                i++;
                while((czy_pusty(operatory)==0) && (operatory->op!='('))
                {
                    wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
                }
                nowy=malloc(sizeof(Wezel));
                nowy->op='+';
                operatory=dodaj_na_koniec(operatory, nowy);
            }
            if(s[i]=='-')
            {
                //Wolny minus
                if(isspace(s[i+1]))
                {
                i++;
                while((czy_pusty(operatory)==0) && (operatory->op!='('))
                {
                    wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
                }
                nowy=malloc(sizeof(Wezel));
                nowy->op='-';
                operatory=dodaj_na_koniec(operatory, nowy);
            }
            //Minus w liczbie
            else
            {
                lli wspolcz=0;
                i++;
                while(isdigit(s[i]))
                {
                    wspolcz=10 * wspolcz + (s[i]-'0');
                    i++;
                }
                wspolcz=wspolcz*(-1);
                lli wyk=0;
                nowy=malloc(sizeof(Wezel));

                if(s[i]=='x')
                {
                    i++;
                    if(s[i]=='^')
                    {
                        i++;
                        while(isdigit(s[i]))
                        {
                            wyk=10 * wyk + (s[i]-'0');
                            i++;
                        }
                    }
                    else
                    {
                        wyk=1;
                    }
                }
                wyzeruj(nowy->t);
                dodajwspolcz(nowy->t, wyk, wspolcz);
                nowy->op=0;
                wyjscie=dodaj_na_koniec(wyjscie, nowy);
            }
        }
        if(s[i]=='*')
        {
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op='*';
            operatory=dodaj_na_koniec(operatory, nowy);
        }
        if(isdigit(s[i]))
        {
            lli wspolcz=0;
            while(isdigit(s[i]))
            {
                wspolcz=10 * wspolcz + (s[i]-'0');
                i++;
            }
            lli wyk=0;
            nowy=malloc(sizeof(Wezel));
            if(s[i]=='x')
            {
                i++;
                if(s[i]=='^')
                {
                    i++;
                    while(isdigit(s[i]))
                    {
                        wyk=10 * wyk + (s[i]-'0');
                        i++;
                    }
                }
                else
                {
                    wyk=1;
                }
            }
            wyzeruj(nowy->t);
            dodajwspolcz(nowy->t, wyk, wspolcz);
            nowy->op=0;
            wyjscie=dodaj_na_koniec(wyjscie, nowy);
        }
        if(isspace(s[i]))
        {
            i++;
        }
        if(s[i]=='(')
        {
            nowy=malloc(sizeof(Wezel));
            nowy->op='(';
            operatory=dodaj_na_koniec(operatory, nowy);
        }
        if(s[i]==')')
        {
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='('))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            usun_i_zwroc(&operatory);
        }
        if(s[i]=='[')
        {
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+') && (operatory->op!='*'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op='/';
            operatory=dodaj_na_koniec(operatory, nowy);

            nowy=malloc(sizeof(Wezel));
            nowy->op='(';
            operatory=dodaj_na_koniec(operatory, nowy);

            while(s[i]!='/')
            {

            }
        }
        if(s[i]=='x')
        {
            nowy=malloc(sizeof(Wezel));
            lli wspolcz=1;
            i++;
            lli wyk=0;
            if(s[i]=='^')
            {
                i++;
                while(isdigit(s[i]))
                {
                    wyk=10 * wyk + (s[i]-'0');
                    i++;
                }
            }
            else
            {
                wyk=1;
            }
            wyzeruj(nowy->t);
            dodajwspolcz(nowy->t, wyk, wspolcz);
            nowy->op=0;
            wyjscie=dodaj_na_koniec(wyjscie, nowy);
        }
        if(s[i]==39)
        {
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+') && (operatory->op!='*'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op=39;
            operatory=dodaj_na_koniec(operatory, nowy);
        }

            }

            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='('))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            usun_i_zwroc(&operatory);

            while(s[i]!=']')
            {
                i++;
            }
            i++;

        }
        if(s[i]=='x')
        {
            //printf("Iks bez wspolczynnika\n");
            nowy=malloc(sizeof(Wezel));
            lli wspolcz=1;
            i++;
            lli wyk=0;
            if(s[i]=='^')
            {
                i++;
                while(isdigit(s[i]))
                {
                    wyk=10 * wyk + (s[i]-'0');
                    i++;
                }
            }
            else
            {
                wyk=1;
            }
            wyzeruj(nowy->t);
            dodajwspolcz(nowy->t, wyk, wspolcz);
            nowy->op=0;
            wyjscie=dodaj_na_koniec(wyjscie, nowy);
        }
        if(s[i]==39)
        {
            //printf("Pochodna\n");
            i++;
            while((czy_pusty(operatory)==0) && (operatory->op!='(') && (operatory->op!='-') && (operatory->op!='+') && (operatory->op!='*'))
            {
                wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
            }
            nowy=malloc(sizeof(Wezel));
            nowy->op=39;
            operatory=dodaj_na_koniec(operatory, nowy);
        }
    }
    while(czy_pusty(operatory)==0)
    {
        wyjscie=dodaj_na_koniec(wyjscie, usun_i_zwroc(&operatory));
    }

    /*int k=0;
    while(wyjscie!=NULL)
    {
        k++;
        if(wyjscie->op==0)
        {
            printf("\n");
            wypiszwiel(wyjscie->t);
        }
        else
        {
            printf("\n");
            printf("%c", wyjscie->op);
        }
        wyjscie=wyjscie->poprzedni;
    }*/

    Stos odwrocony;
    while(czy_pusty(wyjscie)==0)
    {
        odwrocony=dodaj_na_koniec(odwrocony, usun_i_zwroc(&wyjscie));
    }
    Wielomian pomocniczy;
    Stos wiel1;
    Stos wiel2;
    while(czy_pusty(odwrocony)==0)
    {
        nowy=usun_i_zwroc(&odwrocony);
        if(nowy->op==0)
        {
            wyjscie=dodaj_na_koniec(wyjscie, nowy);
        }
        else
        {
            if(nowy->op=='+')
            {
                wiel1=usun_i_zwroc(&wyjscie);
                wiel2=usun_i_zwroc(&wyjscie);
                wyzeruj(pomocniczy);
                sumawiel(wiel1->t, wiel2->t, pomocniczy);
                przepisz(pomocniczy, wiel2->t);
                wyjscie=dodaj_na_koniec(wyjscie, wiel2);
            }
            if(nowy->op=='-')
            {
                wiel1=usun_i_zwroc(&wyjscie);
                wiel2=usun_i_zwroc(&wyjscie);
                wyzeruj(pomocniczy);
                roznicawiel(wiel2->t, wiel1->t, pomocniczy);
                przepisz(pomocniczy, wiel2->t);
                wyjscie=dodaj_na_koniec(wyjscie, wiel2);
            }
            if(nowy->op=='*')
            {
                wiel1=usun_i_zwroc(&wyjscie);
                wiel2=usun_i_zwroc(&wyjscie);
                wyzeruj(pomocniczy);
                iloczynwiel(wiel2->t, wiel1->t, pomocniczy);
                przepisz(pomocniczy, wiel2->t);
                wyjscie=dodaj_na_koniec(wyjscie, wiel2);
            }
            if(nowy->op=='/')
            {
                wiel1=usun_i_zwroc(&wyjscie);
                wiel2=usun_i_zwroc(&wyjscie);
                wyzeruj(pomocniczy);
                podstawwiel(wiel2->t, wiel1->t, pomocniczy);
                przepisz(pomocniczy, wiel2->t);
                wyjscie=dodaj_na_koniec(wyjscie, wiel2);
            }
            if(nowy->op==39)
            {
                wiel1=usun_i_zwroc(&wyjscie);
                wyzeruj(pomocniczy);
                pochodnawiel(wiel1->t, pomocniczy);
                przepisz(pomocniczy, wiel1->t);
                wyjscie=dodaj_na_koniec(wyjscie, wiel1);
            }
        }
    }
    wypiszwiel(wyjscie->t);

    return 0;
}


Stos utworz()
{
    return NULL;
}

bool czy_pusty(Stos t)
{
    if(t==NULL)
        return 1;
    return 0;
}

Stos dodaj_na_koniec(Stos glowny, Stos nowy)
{
    if(czy_pusty(glowny))
    {
        nowy->poprzedni=NULL;
        glowny=nowy;
        return glowny;
    }
    else
    {
        nowy->poprzedni=glowny;
        glowny=nowy;
        return glowny;
    }
}

Stos zwroc_strukt_z_gory(Stos t)
{
    if(czy_pusty(t))
    {
        return NULL;
    }
    return t;
}

Stos usun_i_zwroc(Stos *t)
{
    if(czy_pusty(*t))
    {
        printf("Kolejka pusta - nie mozna usunac elementu");
        exit(1);
    }
    if((*t)->poprzedni==NULL)
    {
        Stos pom=*t;
        (*t)=NULL;
        return pom;
    }
    Stos wsk=(*t);
    (*t)=(*t)->poprzedni;
    return wsk;
}


