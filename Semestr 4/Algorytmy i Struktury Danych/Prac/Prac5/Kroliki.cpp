#include <cstdio>
#include <algorithm>

struct Punkt
{
    int x;
    int y;
    int liczba_marchewek;
};

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

long long brut(int k, int m, int n, Punkt Punkty[], long long W[], int last[])
{
    for (int i = 0; i < k; i++)
    {
        long long maxi = 0;
        int l = -1;
        for (int j = 0; j < i; j++)
        {
            if(Punkty[j].x <= Punkty[i].x && W[j] > maxi)
            {
                maxi = W[j];
                l = j;
            }
        }
        last[i] = l;
        W[i] = Punkty[i].liczba_marchewek + maxi;
    }
    return W[k-1];
}

void wypisz_droge(int i, int n, Punkt Punkty[], int last[])
{
    if(last[i] == -1)
    {
        printf("%d\n", n);
        printf("%d %d\n", Punkty[i].x, Punkty[i].y);
        return;
    }
    wypisz_droge(last[i], n + 1, Punkt Punkty[], int last[]);
    printf("%d %d\n", Punkty[i].x, Punkty[i].y);
}

int main()
{
    int m, n;
    scanf("%d %d\n", &m, &n);
    int k;
    scanf("%d\n", &k);
    Punkt Punkty[k + 1];
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %d\n", &Punkty[i].x, &Punkty[i].y, &Punkty[i].liczba_marchewek);
    }
    
    std::sort(Punkty, Punkty+k, wierszowo);

    if(Punkty[k-1].x != m || Punkty[k-1].y != n)
    {
        Punkty[k].x = m;
        Punkty[k].y = n;
        Punkty[k].liczba_marchewek = 0;
        k = k + 1;
    }
    for (int i = 0; i < k; i++)
    {
        printf("%d %d %d\n", Punkty[i].x, Punkty[i].y, Punkty[i].liczba_marchewek);
    }
    long long W[k] = {0};
    int last[k] = {0};
    long long wynik = brut(k, m, n, Punkty, W, last);
    printf("%lld\n", wynik);

    return 0;
}