#include <stdio.h>
#include <stdlib.h>

int pot(int n, int m)
{
    int i=0;
    int iloczyn=n;
    while(iloczyn<m)
    {
        iloczyn=iloczyn*iloczyn;
        i++;
    }
    int t[i];
    int pot[i];
    i=0; iloczyn=n; t[0]=n; int wyk=1; pot[0]=1;
    while(iloczyn<m)
    {
        iloczyn=iloczyn*iloczyn;
        wyk=wyk*2;
        i++;
        t[i]=iloczyn;
        pot[i]=wyk;
    }

    if(iloczyn==m) return pot[i];
    if(iloczyn/n < m) return pot[i];
    int suma=1;
    wyk=0;
    for(int j=i-1; j>=0; j--)
    {
        suma=suma*t[j];
        wyk=wyk+pot[j];
        if(suma>=m)
        {
            if(suma/n < m)
                return wyk;
            else
            {
                suma=suma/t[j];
                wyk=wyk-pot[j];
            }
        }
    }
    return wyk;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int wynik=pot(n, m);
    printf("%d", wynik);
    return 0;
}
