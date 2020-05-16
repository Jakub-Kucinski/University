#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int liczbaznakow(FILE *zrodlo);
int liczbalini(FILE *zrodlo);
void stworzb(FILE *zrodlo, int ktory, int dlugosc, char *baza, char *rozsz);
//tworzy plik z odpowiednia liczba bajtow
void podzielb(FILE *zrodlo, char *baza, char *rozsz, int ile, int n);
void stworzt(FILE *zrodlo, int ktory, int dlugosc, char *baza, char *rozsz);
//tworzy plik z odpowiednia liczba wierszy
void podzielt(FILE *zrodlo, char *baza, char *rozsz, int ile, int n);
//nieprawidlowa flaga "-t"
void nawp(void);

int main(int argc, char *argv[])
{
    int n;
    int iplik;
    if(argc==3)
    {
        n=atoi(argv[2]);
        iplik=1;
    }
    else
    {
        if(argc==4)
        {
            if((int)strlen(argv[1])!=2)
            {
                nawp();
            }
            else
            {
                if(argv[1][0]!='-')
                {
                    nawp();
                }
                else
                {
                    if(argv[1][1]!='t')
                    {
                        nawp();
                    }
                }
            }
            n=atoi(argv[3]);
            iplik=2;
        }
        else
        {
            nawp();
        }
    }
    FILE *zrodlo;
    zrodlo=fopen(argv[iplik], "r");
    if(zrodlo==NULL)
    {
        printf("Nie ma takiego pliku");
        exit(1);
    }
    char *kropka=strrchr(argv[iplik], '.');
    char rozsz[200];
    strcpy(rozsz, kropka);
    char baza[200];
    strncpy(baza, argv[iplik], kropka-argv[iplik]);
    int ile;

    if(argc==3)
    {
        ile=liczbaznakow(zrodlo);
        podzielb(zrodlo, baza, rozsz, ile, n);
    }
    else
    {
        ile=liczbalini(zrodlo);
        podzielt(zrodlo, baza, rozsz, ile, n);
    }
    fclose(zrodlo);
    return 0;
}

int liczbaznakow(FILE *zrodlo)
{
    int liczba=0;
    int a=getc(zrodlo);
    while(a!=EOF)
    {
        liczba++;
        a=getc(zrodlo);
    }
    rewind(zrodlo);
    return liczba;
}

int liczbalini(FILE *zrodlo)
{
    int liczba=0;
    int a=getc(zrodlo);
    while(a!=EOF)
    {
        if(a=='\n')
        {
            liczba++;
        }
        a=getc(zrodlo);
    }
    rewind(zrodlo);
    return liczba-1;
}

void stworzb(FILE *zrodlo, int ktory, int dlugosc, char *baza, char *rozsz)
{
    char nazwa[200];
    sprintf(nazwa, "%s-%03d%s", baza, ktory+1, rozsz);
    FILE *wyjscie;
    wyjscie=fopen(nazwa, "w");
    while(dlugosc!=0)
    {
        int a=getc(zrodlo);
        putc(a, wyjscie);
        dlugosc--;
    }
    fclose(wyjscie);
}

void podzielb(FILE *zrodlo, char *baza, char *rozsz, int ile, int n)
{
    for(int i=0; i<n; i++)
    {
        int dlugosc=ile/n;
        if(i<ile%n)
        {
            dlugosc++;
        }
        stworzb(zrodlo, i, dlugosc, baza, rozsz);
    }
}

void stworzt(FILE *zrodlo, int ktory, int dlugosc, char *baza, char *rozsz)
{
    char nazwa[200];
    sprintf(nazwa, "%s-%03d%s", baza, ktory+1, rozsz);
    FILE *wyjscie;
    wyjscie=fopen(nazwa, "w");
    while(dlugosc!=0)
    {
        int a=getc(zrodlo);
        putc(a, wyjscie);
        if(a=='\n')
        {
            dlugosc--;
        }
    }
    fclose(wyjscie);
}

void podzielt(FILE *zrodlo, char *baza, char *rozsz, int ile, int n)
{
    for(int i=0; i<n; i++)
    {
        int dlugosc=ile/n;
        if(i<ile%n)
        {
            dlugosc++;
        }
        stworzt(zrodlo, i, dlugosc, baza, rozsz);
    }
}

void nawp(void)
{
    printf("Nieprawidłowe argumenty wywołania programu.");
    exit(1);
}
