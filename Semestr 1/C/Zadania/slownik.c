#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct wezel{
    int index;
    struct wezel * lewo;
    struct wezel * prawo;
} *Kolejka, Wezel;


void wczytaj(int n, char slownik[n][33], int dlugosc[n]);
void uzupelnij(int n, Kolejka poczatek[n], Kolejka koniec[n], char slownik[n][33], int dlugosc[n]);
int krok(int i, int j, int n, char slownik[n][33], int dlugosc[n]);
void wypisz_slownik(int n, char slownik[n][33], int dlugosc[n]);
int znajdz(char a[33], int da, int n, char slownik[n][33], int dlugosc[n]);
int porownaj(char a[33], int da, int j, int n, char slownik[n][33], int dlugosc[n]);
int slowo(char slowo1[33]);
int BFS(int i, int j, int n, Kolejka poczatek[n]);

Kolejka utworz();
int czy_pusta(Kolejka t);
Kolejka dodaj_na_koniec(Kolejka t, double x);
void wypisz(Kolejka t);

void wczytajstring(int n, char slownik[n][33]);
int krok2(int i, int j, int n, char slownik[n][33], int dlugosc);
void uzupelnij2(int n, Kolejka poczatek[n], Kolejka koniec[n], char slownik[n][33], int dlugosc);
int znajdz2(char a[33], int n, char slownik[n][33]);

int main()
{
    int n;
    scanf("%d", &n);
    char slownik[n][33];
    //int dlugosc[n];
    //wczytaj(n, slownik, dlugosc);
    wczytajstring(n, slownik);

    Kolejka poczatek[n];
    Kolejka koniec[n];

    //uzupelnij(n, poczatek, koniec, slownik, dlugosc);
    int d=strlen(slownik[0]);
    uzupelnij2(n, poczatek, koniec, slownik, d);

    /*for(int i=0; i<n; i++)
    {
        printf("%d: ", i);
        wypisz(poczatek[i]);
    }*/
    char a[33], b[33];
    //int da=slowo(a);
    //int db=slowo(b);
    scanf("%s", a);
    scanf("%s", b);
    //int i=znajdz(a, da, n, slownik, dlugosc);
    //int j=znajdz(b, db, n, slownik, dlugosc);
    int i=znajdz2(a, n, slownik);
    int j=znajdz2(b, n, slownik);
    //printf("%d %d\n", i, j);
    int wynik=BFS(i, j, n, poczatek);
    printf("%d", wynik);

    return 0;
}

int slowo(char slowo1[33])
{
    char c;
    int i=0;
    while(!isspace(c=getchar()) && c!=EOF)
    {
        slowo1[i]=c;
        i++;
    }
    return i;
}

int porownaj(char a[33], int da, int j, int n, char slownik[n][33], int dlugosc[n])
{
    if(da!=dlugosc[j])
        return 0;
    for(int i=0; i<da; i++)
    {
        if(a[i]!=slownik[j][i])
            return 0;
    }
    return 1;
}

int znajdz(char a[33], int da, int n, char slownik[n][33], int dlugosc[n])
{
    for(int i=0; i<n; i++)
    {
        if(porownaj(a, da, i, n, slownik, dlugosc))
            return i;
    }
    return -1;
}

int znajdz2(char a[33], int n, char slownik[n][33])
{
    for(int i=0; i<n; i++)
    {
        if(strcmp(a, slownik[i])==0)
            return i;
    }
    return -1;
}

void wczytaj(int n, char slownik[n][33], int dlugosc[n])
{
    char c;
    scanf("%c", &c);
    for(int i=0; i<n; i++)
    {
        c=getchar();
        int j=0;
        while(!isspace(c))
        {
            slownik[i][j]=c;
            c=getchar();
            j++;
        }
        dlugosc[i]=j;
    }
}

void wczytajstring(int n, char slownik[n][33])
{
    for(int g=0;g<n;g++)
		scanf("%s",&slownik[g][0]);
}

void wypisz_slownik(int n, char slownik[n][33], int dlugosc[n])
{
    for(int i=0; i<n; i++)
    {
        int d=dlugosc[i];
        for(int j=0; j<d; j++)
            printf("%c", slownik[i][j]);
        printf(" ");
    }
}

//Zalozenie: moga byc roznej dlugosci, ale moga sie roznic tylko na dokladnie jednej POZYCJI, nie sa permutacjami z roznica jednego znaku
int krok(int i, int j, int n, char slownik[n][33], int dlugosc[n])
{
    if(dlugosc[i]-dlugosc[j]>1 || dlugosc[j]-dlugosc[i]>1)
        return 0;
    if(dlugosc[i]==dlugosc[j])
    {
        int d=dlugosc[i];
        int czy=0;
        for(int k=0; k<d; k++)
        {
            if(slownik[i][k]!=slownik[j][k])
            {
                if(czy==1)
                    return 0;
                czy=1;
            }
        }
        return 1;
    }
    if(dlugosc[i]>dlugosc[j])
    {
        int d=dlugosc[j];
        for(int k=0; k<d; k++)
        {
            if(slownik[i][k]!=slownik[j][k])
                return 0;
        }
        return 1;
    }
    else
    {
        int d=dlugosc[i];
        for(int k=0; k<d; k++)
        {
            if(slownik[i][k]!=slownik[j][k])
                return 0;
        }
        return 1;
    }
}

int krok2(int i, int j, int n, char slownik[n][33], int dlugosc)
{
    int czy=0;
        for(int k=0; k<dlugosc; k++)
        {
            if(slownik[i][k]!=slownik[j][k])
            {
                if(czy==1)
                    return 0;
                czy=1;
            }
        }
        return 1;
}

void uzupelnij(int n, Kolejka poczatek[n], Kolejka koniec[n], char slownik[n][33], int dlugosc[n])
{
    for(int i=0; i<n; i++)
    {
        poczatek[i]=NULL;
        koniec[i]=NULL;
    }
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(krok(i, j, n, slownik, dlugosc))
            {
                koniec[i]=dodaj_na_koniec(koniec[i], j);
                if(poczatek[i]==NULL)
                    poczatek[i]=koniec[i];
                koniec[j]=dodaj_na_koniec(koniec[j], i);
                if(poczatek[j]==NULL)
                    poczatek[j]=koniec[j];
            }
        }
    }
}

void uzupelnij2(int n, Kolejka poczatek[n], Kolejka koniec[n], char slownik[n][33], int dlugosc)
{
    for(int i=0; i<n; i++)
    {
        poczatek[i]=NULL;
        koniec[i]=NULL;
    }
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(krok2(i, j, n, slownik, dlugosc))
            {
                koniec[i]=dodaj_na_koniec(koniec[i], j);
                if(poczatek[i]==NULL)
                    poczatek[i]=koniec[i];
                koniec[j]=dodaj_na_koniec(koniec[j], i);
                if(poczatek[j]==NULL)
                    poczatek[j]=koniec[j];
            }
        }
    }
}

int BFS(int i, int j, int n, Kolejka poczatek[n])
{
    int odwiedzone[n];
    for(int o=0; o<n; o++) odwiedzone[o]=0;
    int skad[n];
    for(int o=0; o<n; o++) skad[o]=-1;

    Wezel *p=malloc(sizeof(Wezel));
    Kolejka start;
    Kolejka end;
    p->prawo=NULL;
    p->lewo=NULL;
    p->index=i;
    start=p;
    end=start;
    odwiedzone[i]=1;
    while(start)
    {
        int k=start->index;
        //printf("k: %d ", k);
        for(Wezel *wsk=poczatek[k]; wsk!=NULL; wsk=wsk->prawo)
        {
            if(odwiedzone[wsk->index]==0)
            {
                end=dodaj_na_koniec(end, wsk->index);
                odwiedzone[wsk->index]=1;
                skad[wsk->index]=k;
            }

        }
        start=start->prawo;
    }
    if(i==j)
        return 0;
    if(skad[j]==-1)
        return -1;
    int pom=skad[j];
    int ile=1;
    while(skad[pom]!=-1)
    {
        pom=skad[pom];
        ile++;
    }
    return ile;
}

Kolejka utworz()
{
    return NULL;
}

int czy_pusta(Kolejka t)
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
        nowy->prawo=NULL;
        nowy->lewo=NULL;
        nowy->index=x;
        return nowy;
    }
    else
    {
        Wezel *nowy=malloc(sizeof(Wezel));
        nowy->prawo=NULL;
        nowy->index=x;
        nowy->lewo=t;
        t->prawo=nowy;
        return nowy;
    }
}

void wypisz(Kolejka t)
{
    Kolejka wsk=t;
    while(wsk!=NULL)
    {
        printf("%d ", wsk->index);
        wsk=wsk->prawo;
    }
    printf("\n");
}
