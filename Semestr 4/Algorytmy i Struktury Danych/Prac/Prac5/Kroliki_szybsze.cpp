#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Punkt
{
    int x;
    int y;
    int liczba_marchewek;
};

Punkt Wierszowe[1000002];

bool kolumnowo(Punkt a, Punkt b)
{
    if(a.x != b.x) return a.x < b.x;
    return a.y <= b.y;
}

bool wierszowo(Punkt a, Punkt b)
{
    if (a.y != b.y) return a.y < b.y;
    return a.x <= b.x;
}

bool kolumnowo_permutacja(int i, int j)
{
    if(Wierszowe[i].x != Wierszowe[j].x) return Wierszowe[i].x < Wierszowe[j].x;
    return Wierszowe[i].y <= Wierszowe[j].y;
}


long long max_z_indeksem_mniejszym_niz_i(long long kopiec[], int numer_punktu[], int i, int* indeks_najw)
{
    int aktualny_max = 0;
    while (i > 1)
    {
        if(i % 2 == 1)
        {
            if(kopiec[i-1] > aktualny_max)
            {
                aktualny_max = kopiec[i - 1];
                *indeks_najw = numer_punktu[i - 1];
            }
        }
        i = i / 2;
    }
    return aktualny_max;
}

void uaktualnij_wartosci_dla_i(long long kopiec[], int numer_punktu[], int i, int numer_obliczanego_punktu, long long wartosc)
{
    while (i >= 1)
    {
        if(kopiec[i] < wartosc)
        {
            kopiec[i] = wartosc;
            numer_punktu[i] = numer_obliczanego_punktu;
        }
        else
        {
            break;
        }
        i = i / 2;
    }
}

long long szybkie(int k, int pochodzenie[], int Kolumnowe[])
{
    int rozmiar = 1;
    int wysokosc = 0;
    while (rozmiar < k)
    {
        rozmiar *= 2;
        wysokosc++;
    }
    rozmiar = 2 * rozmiar;
    long long kopiec[rozmiar] = {0};
    int numer_punktu[rozmiar] = {0};
    long long wynik[k + 1] = {0};
    for (int i = 0; i < k; i++)
    {
        numer_punktu[rozmiar / 2 + i] = i;
    }

    for (int i = 0; i < k; i++)
    {
        int indeks_najwiekszego = -1;
        int maxi = max_z_indeksem_mniejszym_niz_i(kopiec, numer_punktu, rozmiar / 2 + Kolumnowe[i], &indeks_najwiekszego);
        wynik[Kolumnowe[i]] = Wierszowe[Kolumnowe[i]].liczba_marchewek + maxi;
        pochodzenie[Kolumnowe[i]] = indeks_najwiekszego;
        uaktualnij_wartosci_dla_i(kopiec, numer_punktu, rozmiar / 2 + Kolumnowe[i], Kolumnowe[i], wynik[Kolumnowe[i]]);
    }
    // for (int i = 0; i < k; i++)
    // {
    //     printf("%d. %d\n", i, wynik[i]);
    // }
    return wynik[k - 1];
}

void znajdz_droge(int i, int pochodzenie[], vector<int> droga)
{
    while(pochodzenie[i] != -1)
    {
        droga.push_back(pochodzenie[i]);
        i = pochodzenie[i];
    }
}

int main()
{
    int m, n;
    scanf("%d %d\n", &m, &n);
    int k;
    scanf("%d\n", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %d\n", &Wierszowe[i].x, &Wierszowe[i].y, &Wierszowe[i].liczba_marchewek);
    }
    
    sort(Wierszowe, Wierszowe+k, wierszowo);

    if(Wierszowe[k-1].x != m || Wierszowe[k-1].y != n)
    {
        Wierszowe[k].x = m;
        Wierszowe[k].y = n;
        Wierszowe[k].liczba_marchewek = 0;
        k = k + 1;
    }

    int Kolumnowe[k];
    for (int i = 0; i < k; i++)
    {
        Kolumnowe[i] = i;
    }
    sort(Kolumnowe, Kolumnowe+k, kolumnowo_permutacja);

    int pochodzenie[k + 1] = {0};
    long long wynik = szybkie(k, pochodzenie, Kolumnowe);
    printf("%lld\n", wynik);
    // for (int i = 0; i < k; i++)
    // {
    //     printf("%d. %d\n", i, pochodzenie[i]);
    // }

    vector<int> droga;
    if(Wierszowe[k-1].liczba_marchewek != 0)
    {
        droga.push_back(k - 1);
    }
    int i = k - 1;
    while (pochodzenie[i] != -1)
    {
        droga.push_back(pochodzenie[i]);
        i = pochodzenie[i];
    }
    int num = droga.size();
    printf("%d\n", num);
    // for (int i = num-1; i >= 0; i--)
    // {
    //     printf("%d \n", droga[i]);
    // }
    for (int i = num-1; i >= 0; i--)
    {
        printf("%d %d\n", Wierszowe[droga[i]].x, Wierszowe[droga[i]].y);
    }

    return 0;
}