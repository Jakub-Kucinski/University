#include<stdio.h>
#include<string.h>
/*Jakub Kuciński, nr indeksu 309881, Lista zadań 2, zadanie 2., 23.10.2018, grupa środa 10-12, wstęp do programowania w C */

char wiersz[500];//Bedziemy wczytywac do tablicy "wiersz" kolejne znaki z biezacego wiersza pliku
int t[50]={0};//Gdy element "p" tablicy bedzie mial wartosc 1, to mamy wypisac wyrazy o numerze "p" z kazdego wiersza
int main(int argc, char *argv[])
{


    if(argc<=1) {printf("Brak argumentow \n"); return 1;}//Sprawdzamy czy podane zostaly argumenty
    for(int i=1; i<argc; i++)
    {
        int p,k;//p - poczatek przedzialu, k - koniec
        if(sscanf(argv[i], "%d-%d", &p, &k)==1)//Wczytujemy kolejne przedzialy
            k=p;//Gdy nie podano drugiego argumentu, to mamy pojedynczy wyraz zadany do wypisania i ustawiamy koniec przedzialu na wartosc poczatku p
        for(int j=p; j<=k; j++)
            t[j]=1;//Zaznaczam w tablicy "t" wyrazy, ktore maja zostac wypisane
    }
    char c;//Bedziemy uzywac tej zmiennej do wczytywania kolejnych znakow z pliku
    while(1)
    {
        int i=0;//Bedzie przechowywac liczbe znakow (w tym bialych) w aktualnym wierszu
        while((c =getchar())!= EOF && c!='\n')//Pobieramy chary do momentu az skoncza sie dane lub natrafimy na znak nowej lini
        {
            wiersz[i]=c;
            i++;
        }
        int czypierw=1;//Zmienna przechowuje informacje czy wyraz ktorego pierwszy znak chcemy wypisac jest pierszym wyrazem do wypisania w wierszu (nie wypisujemy wtedy spacji)
        int numer=0;//Przechowuje wartosc mowiaca o numerze wyrazu, w ktorym znajdujemy sie obecnie
        if(wiersz[0]!=' ' && wiersz[0]!='\t' && i>0)//Sprawdzanie pierwszego indeksu w wierszu (czy nie jest znakiem bialym), bo w pętli będziemy odwaoływać się do aktualnego i poprzedniego indeksu
        {
            if(t[0]==1)//Jesli mamy wypisac pierwszy wyraz z wiersza to wypisujemy pierwszy znak wiersza
            {
                putchar(wiersz[0]);
            }
            numer=1;//Aktualny wyraz ma numer 1
            czypierw=0;//Wypisano pierwszy znak pierwszego wyrazu do wypisania
        }
        int n=1;//Kolejne indeksy znakow w wierszu
        while(n<i)
        {
            if(wiersz[n]!=' ' && wiersz[n]!='\t')//Jesli aktualny indeks jest znakiem to
            {
                if(wiersz[n-1]!=' ' && wiersz[n-1]!='\t')//Jesli poprzedni indeks jest znakiem to znaczy ze aktualny indeks jest kontynuacja wyrazu
                {
                    if(t[numer]==1)//Jesli wyraz o numerze "numer" ma byc wyswietlony to wypisz aktualny znak
                    {
                        putchar(wiersz[n]);
                    }
                }
                else//Jesli poprzedni indeks to znak bialy to oznacza ze zaczyna sie nowy wyraz
                {
                    numer++; //Zwieksz numer aktualnego wyrazu (bo zaczyna sie nowy)
                    if(t[numer]==1)//Jesli wyraz o numerze "numer" ma byc wyswietlony to wypisz aktualny znak
                    {
                        if(czypierw==1)//Jesli jest to pierwszy wypisywany wyraz w wierszu to zmien wartosc czypierw
                        {czypierw=0;}
                        else//Jesli nie jest to pierwszy wypisywany wyraz to wypisz spacje
                        {putchar(' ');}
                        putchar(wiersz[n]);//Wypisz aktualny znak
                    }

                }
            }//Jezeli aktualny indeks jest znakiem bialym to nie chcemy wypisywac ani zmieniac zadnych wartosci
            n++;//Zwiększamy numer sprawdzanego indeksu
        }
        if(c==EOF)//Jesli ostatni z wczytanych do zmiennej c znakow jest "EOF" to znaczy ze nie ma wiecej wierszy
            break;
        putchar('\n');//Koniec wypisywania wyrazow z aktualnego wiersza, wypisujemy znak nowej linii
    }
    return 0;
    }


