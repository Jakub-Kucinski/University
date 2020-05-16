#include <cstdio>
#include <algorithm>

int find_min(int F, int n, int p[], int w[])
{
    int wart_dla_wagi[F];
    int dodana_moneta[F];
    for (int i = 0; i <= F; i++)
    {
        wart_dla_wagi[i] = -1;
        dodana_moneta[i] = -1;
    }
    wart_dla_wagi[0] = 0;
    for (int waga = 1; waga <= F; waga++)
    {
        for (int i = 0; i < n; i++)
        {
            if(waga - w[i] >= 0 && wart_dla_wagi[waga - w[i]] != -1)
            {
                if(wart_dla_wagi[waga] != -1)
                {
                    if(wart_dla_wagi[waga] > wart_dla_wagi[waga - w[i]] + p[i])
                    {
                        wart_dla_wagi[waga] = wart_dla_wagi[waga - w[i]] + p[i];
                        dodana_moneta[waga] = i;
                    }
                }
                else
                {
                    wart_dla_wagi[waga] = wart_dla_wagi[waga - w[i]] + p[i];
                    dodana_moneta[waga] = i;
                }
            }
        }
    }
    if(wart_dla_wagi[F] == -1)
    {
        printf("NIE");
        return -1;
    }
    else
    {
        printf("TAK\n%d\n", wart_dla_wagi[F]);
    }

    int histogram[n];
    for (int i = 0; i < n; i++)
    {
        histogram[i] = 0;
    }
    int waga = F;
    while(waga > 0)
    {
        histogram[dodana_moneta[waga]]++;
        waga = waga - w[dodana_moneta[waga]];
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", histogram[i]);
    }
    printf("\n");

    return 0;
}

int find_max(int F, int n, int p[], int w[])
{
    int wart_dla_wagi[F];
    int dodana_moneta[F];
    for (int i = 0; i <= F; i++)
    {
        wart_dla_wagi[i] = -1;
        dodana_moneta[i] = -1;
    }
    wart_dla_wagi[0] = 0;
    for (int waga = 1; waga <= F; waga++)
    {
        for (int i = 0; i < n; i++)
        {
            if(waga - w[i] >= 0 && wart_dla_wagi[waga - w[i]] != -1)
            {
                if(wart_dla_wagi[waga] != -1)
                {
                    if(wart_dla_wagi[waga] < wart_dla_wagi[waga - w[i]] + p[i])
                    {
                        wart_dla_wagi[waga] = wart_dla_wagi[waga - w[i]] + p[i];
                        dodana_moneta[waga] = i;
                    }
                }
                else
                {
                    wart_dla_wagi[waga] = wart_dla_wagi[waga - w[i]] + p[i];
                    dodana_moneta[waga] = i;
                }
            }
        }
    }

    printf("%d\n", wart_dla_wagi[F]);

    int histogram[n];
    for (int i = 0; i < n; i++)
    {
        histogram[i] = 0;
    }
    int waga = F;
    while(waga > 0)
    {
        histogram[dodana_moneta[waga]]++;
        waga = waga - w[dodana_moneta[waga]];
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", histogram[i]);
    }
    printf("\n");

    return 0;
}

int main()
{
    int F;
    scanf("%d\n", &F);

    int n;
    scanf("%d\n", &n);

    int p[n];
    int w[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &p[i], &w[i]);
    }
    if(find_min(F, n, p, w) != -1)
    {
        find_max(F, n, p, w);
    }

    return 0;
}