//wersja poprawiona
#include<stdio.h>
#include<stdbool.h>
//Jakub Kuciński, Wstęp do programowania w C, Lista 3 zadanie 2, nr indeksu 309881, grupa środa 10-12, 6-11-2018
void wczytywanie(const int a, const int b, bool t[a][b]);
void wypisywanie(const int a, const int b, const bool t[a][b]);
void obroc(const int a, const int b, const bool t[a][b], const int x, const int y, bool wynik[x][y], const int p);
void sprawdzarka(const int a, const int b);

int main()
{
    int a=5;
    int b=4;
    sprawdzarka(a, b);


    return 0;
}

//Funkcja wczytuje obrazek o rozmaiarach a na b, gdy napotyka na znak X to wpisuje true (czarny piksel), a gdy spację false (biały piksel)
void wczytywanie(const int a, const int b, bool t[a][b])
{
    char c;
    for(int i=0; i<b; i++)
    {
        for(int j=0; j<a;j++)
        {
            c=getchar();
            if(c=='X')
            {t[j][i]=true;}
            else
            {t[j][i]=false;}
        }
        c=getchar();//wczytywanie znaku nowej lini na koncu wiersza
    }
}

//Funkcja wypisuje obrazek o rozmaiarach a na b, gdy napotyka na true to wpisuje X (czarny piksel), a gdy false spację(biały piksel)
void wypisywanie(const int a, const int b, const bool t[a][b])
{
    for(int i=0; i<b; i++)
    {
        for(int j=0; j<a;j++)
        {
            if(t[j][i]==true)
            {putchar('X');}
            else
            {putchar(' ');}
        }
        if(i<b-1)
            putchar('\n');
    }
}

//Funckcja obraza obrazek o wymiarach a b o 90 (p=1), 180 (p=2) lub 270 (p=3) stopni
//Obrocony obrazek zapisywany jest w podanej przez argument tabeli wynik
//Uzytkownik podaje wymiary x y tabelki wynikowej tak by obrocony obrazek zmiescil sie w niej
//W przypdaku podania zlych rozmiarow tabeli wynikowej pewne dane wynikowe moga zostac utracone
void obroc(const int a, const int b, const bool t[a][b], const int x, const int y, bool wynik[x][y], const int p)
{
    if(p==1)//90 stopni
    {
        for(int i=0; i<a && i<y; i++)
        {
            for(int j=0; j<b && j<x; j++)
            {
                wynik[j][i]=t[i][b-j-1];
            }
        }
    }
    else
    {
        if(p==2)//180 stopni
        {
            for(int i=0; i<b && i<y; i++)
            {
                for(int j=0; j<a && j<x; j++)
                {
                    wynik[j][i]=t[a-j-1][b-i-1];
                }
            }
        }
        else//270 stopni
        {
            if(p==3)
            {
                for(int i=0; i<a && i<y; i++)
                {
                    for(int j=0; j<b && j<x; j++)
                    {
                        wynik[j][i]=t[a-i-1][j];
                    }
                }
            }

        }
    }
}

//Funckcja wczytuje obrazek o rozmiarach a na b i wypisuje go oraz nastepnie jego obrocne o 90, 180, 270 stopni wersje
void sprawdzarka(const int a, const int b)
{
    bool t[a][b];
    wczytywanie(a, b, t);
    wypisywanie(a, b, t);
    putchar('\n');
    putchar('\n');

    bool t2[b][a];
    bool t3[a][b];

    obroc(a, b, t, b, a, t2, 1);
    wypisywanie(b, a, t2);
    putchar('\n');
    putchar('\n');

    obroc(a, b, t, a, b, t3, 2);
    wypisywanie(a, b, t3);
    putchar('\n');
    putchar('\n');

    obroc(a, b, t, b, a, t2, 3);
    wypisywanie(b, a, t2);
}
