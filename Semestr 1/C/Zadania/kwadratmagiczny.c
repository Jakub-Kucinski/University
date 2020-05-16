#include<stdio.h>
#include<stdbool.h>
/*Jakub Kuciński, nr indeksu 309881, Lista zadań 5, zadanie 2., 21.11.2018, grupa środa 10-12, wstęp do programowania w C */

void kwadratytest3(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok], int *ile)
{
if((*ile)!=0)
{
    if(s==n-1)
    {
        //Jesli sumy przekatnych beda poprawne to wypiszemy kwadrat magiczny
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            if(i%2==0)
                przek=przek+p[i*(bok+1)];
            else
                przek=przek+p[(i+1)*(bok-1)];
        }
        if(przek!=suma)
        {
            k=0;
        }
        else
        {
            przek=0;
            for(int i=0; i<bok; i++)
            {
                if(i%2==0)
                    przek=przek+p[(i+1)*(bok-1)];
                else
                    przek=przek+p[i*(bok+1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
            //Zmniejszamy liczbe kwadratow do wypisania
            (*ile)--;
            //Wypisujemy kwadrat
            for(int i=0; i<bok; i++)
            {
                if(i%2==0)
                {
                    for(int j=0; j<bok; j++)
                    {
                        printf("%d ", p[i*bok + j]);
                    }
                }
                else
                {
                    for(int j=0; j<bok; j++)
                    {
                        printf("%d ", p[(i+1)*bok -1 -j ]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    else
    {
        for(int i=s; i<n; i++)
        {
            int pom=p[s];
            p[s]=p[i];
            p[i]=pom;
            if((s/bok)%2==0)
            {
                //Jesli k bedzie =1 to wywolamy rekurencje dla tego elementu p[s]
                int k=1;
                //Dodajemy wartosc w p[s] do odpowiednich sum wierszy i kolumn
                wiersz[s/bok]=wiersz[s/bok]+p[s];
                kolumna[s%bok]=kolumna[s%bok]+p[s];
                //Jesli konkretna wartosc sumy w wierszu lub kolumnie jest wieksza rowna sumie ktora mamy otrzymac
                //i nie jest to ostatni element w danym wierszu/kolumnie
                if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[s%bok] && s/bok<bok-1))
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    //Jesli jest to ostatni element w wierszu a suma wiersza nie jest odpowiednia
                    if((s%bok)==(bok-1) && suma!=wiersz[s/bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                    else
                    {
                        //Jesli jest to ostatni element w kolumnie a suma kolumny nie jest odpowiednia
                        if((s/bok)==(bok-1) && suma!=kolumna[s%bok])
                        {
                            k=0;
                            wiersz[s/bok]=wiersz[s/bok]-p[s];
                            kolumna[s%bok]=kolumna[s%bok]-p[s];
                        }
                    }
                }
                //Jesli wstawienie elementu p[s] nie sprawia ze sumy wieszy lub kolumn sa niepoprawne to wywolujemy rekurencje
                if(k==1)
                    {kwadratytest3(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];}
                t[i]=0;
            }
            //Jesli jestesmy w nieparzystym wierszu to interpretujemy ze wpisujemy liczby od prawej
            else
            {
                //Jesli k bedzie =1 to wywolamy rekurencje dla tego elementu p[s]
                int k=1;
                //Dodajemy wartosc w p[s] do odpowiednich sum wierszy i kolumn
                wiersz[s/bok]=wiersz[s/bok]+p[s];
                kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]+p[s];
                //Jesli konkretna wartosc sumy w wierszu lub kolumnie jest wieksza rowna sumie ktora mamy otrzymac
                //i nie jest to ostatni element w danym wierszu/kolumnie
                if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[bok-1-(s%bok)] && s/bok<bok-1))
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                }
                else
                {
                    //Jesli jest to ostatni element w wierszu a suma wiersza nie jest odpowiednia
                    if((s%bok)==bok-1 && suma!=wiersz[s/bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                    }
                    else
                    {
                        //Jesli jest to ostatni element w kolumnie a suma kolumny nie jest odpowiednia
                        if((s/bok)==(bok-1) && suma!=kolumna[bok-1-(s%bok)])
                        {
                            k=0;
                            wiersz[s/bok]=wiersz[s/bok]-p[s];
                            kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                        }
                    }
                }
                //Jesli wstawienie elementu p[s] nie sprawia ze sumy wieszy lub kolumn sa niepoprawne to wywolujemy rekurencje
                if(k==1)
                    {kwadratytest3(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];}
                t[i]=0;
            }
        }
    }
}
}

void kwadratytest2(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok], int *ile)
{
    //Jesli nie wypisalismy jeszcze wymaganej liczby kwadratow magicznych
  if((*ile)!=0)
  {
  //Jesli nie jestesmy w ostatnim elemencie tablicy p
   if(s<n)
   {
    for(int i=0; i<n; i++)
    {
        //Sprawdzamy ktore liczby mozemy wpisac do aktualnego miejsca tablicy p
        if(t[i]==0)
        {
            t[i]=1;
            p[s]=i+1;
            //Jesli jestesmy w parzystym wierszu to interpretujemy ze wpisujemy liczby od lewej
            if((s/bok)%2==0)
            {
                //Jesli k bedzie =1 to wywolamy rekurencje dla tego elementu p[s]
                int k=1;
                //Dodajemy wartosc w p[s] do odpowiednich sum wierszy i kolumn
                wiersz[s/bok]=wiersz[s/bok]+p[s];
                kolumna[s%bok]=kolumna[s%bok]+p[s];
                //Jesli konkretna wartosc sumy w wierszu lub kolumnie jest wieksza rowna sumie ktora mamy otrzymac
                //i nie jest to ostatni element w danym wierszu/kolumnie
                if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[s%bok] && s/bok<bok-1))
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    //Jesli jest to ostatni element w wierszu a suma wiersza nie jest odpowiednia
                    if((s%bok)==(bok-1) && suma!=wiersz[s/bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                    else
                    {
                        //Jesli jest to ostatni element w kolumnie a suma kolumny nie jest odpowiednia
                        if((s/bok)==(bok-1) && suma!=kolumna[s%bok])
                        {
                            k=0;
                            wiersz[s/bok]=wiersz[s/bok]-p[s];
                            kolumna[s%bok]=kolumna[s%bok]-p[s];
                        }
                    }
                }
                //Jesli wstawienie elementu p[s] nie sprawia ze sumy wieszy lub kolumn sa niepoprawne to wywolujemy rekurencje
                if(k==1)
                    {kwadratytest2(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];}
                t[i]=0;
            }
            //Jesli jestesmy w nieparzystym wierszu to interpretujemy ze wpisujemy liczby od prawej
            else
            {
                //Jesli k bedzie =1 to wywolamy rekurencje dla tego elementu p[s]
                int k=1;
                //Dodajemy wartosc w p[s] do odpowiednich sum wierszy i kolumn
                wiersz[s/bok]=wiersz[s/bok]+p[s];
                kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]+p[s];
                //Jesli konkretna wartosc sumy w wierszu lub kolumnie jest wieksza rowna sumie ktora mamy otrzymac
                //i nie jest to ostatni element w danym wierszu/kolumnie
                if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[bok-1-(s%bok)] && s/bok<bok-1))
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                }
                else
                {
                    //Jesli jest to ostatni element w wierszu a suma wiersza nie jest odpowiednia
                    if((s%bok)==bok-1 && suma!=wiersz[s/bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                    }
                    else
                    {
                        //Jesli jest to ostatni element w kolumnie a suma kolumny nie jest odpowiednia
                        if((s/bok)==(bok-1) && suma!=kolumna[bok-1-(s%bok)])
                        {
                            k=0;
                            wiersz[s/bok]=wiersz[s/bok]-p[s];
                            kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];
                        }
                    }
                }
                //Jesli wstawienie elementu p[s] nie sprawia ze sumy wieszy lub kolumn sa niepoprawne to wywolujemy rekurencje
                if(k==1)
                    {kwadratytest2(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[bok-1-(s%bok)]=kolumna[bok-1-(s%bok)]-p[s];}
                t[i]=0;
            }
        }
    }
   }
   //Jesli jest to ostatni element tablicy p
    if(s==n-1)
    {
        //Jesli sumy przekatnych beda poprawne to wypiszemy kwadrat magiczny
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            if(i%2==0)
                przek=przek+p[i*(bok+1)];
            else
                przek=przek+p[(i+1)*(bok-1)];
        }
        if(przek!=suma)
        {
            k=0;
        }
        else
        {
            przek=0;
            for(int i=0; i<bok; i++)
            {
                if(i%2==0)
                    przek=przek+p[(i+1)*(bok-1)];
                else
                    przek=przek+p[i*(bok+1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
            //Zmniejszamy liczbe kwadratow do wypisania
            (*ile)--;
            //Wypisujemy kwadrat
            for(int i=0; i<bok; i++)
            {
                if(i%2==0)
                {
                    for(int j=0; j<bok; j++)
                    {
                        printf("%d ", p[i*bok + j]);
                    }
                }
                else
                {
                    for(int j=0; j<bok; j++)
                    {
                        printf("%d ", p[(i+1)*bok -1 -j ]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
    }
  }
}

int main(void)
{
    int n;
    scanf("%d", &n);//wczytywanie jakiej dlugosci ma byc bok kwadratu magicznego
    int p[n*n];//tablica, w ktorej przechowujemy permutacje
    bool t[n*n];//przechowuje informacje o tym, ktore liczby zostaly juz wykorzystane
    int kolumna[n];//tablica przechowujaca wartosci sum poszczegolnych kolumn
    int wiersz[n];//tablica przechowujaca wartosci sum poszczegolnych wierszy
    for(int i=0; i<n*n; i++)
    {
        p[i]=i+1;
        t[i]=0;
    }
    for(int i=0; i<n; i++)
    {kolumna[i]=0; wiersz[i]=0;}


    int ile=0;
    scanf("%d", &ile);//wczytywanie ile kwadratow magicznych chcemy wypisac

    kwadratytest3(n*n, 0, p, t, ((n*n+1)*n)/2, n, kolumna, wiersz, &ile);

    return 0;
}

