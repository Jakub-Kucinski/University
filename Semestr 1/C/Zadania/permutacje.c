#include<stdio.h>
#include<stdbool.h>

//Jakub Kuciński, zad 1 lista 5, nr indeksu 309881, grupa środa 10-12, Wstęp do programowania w C

void wypisz(int n, int p[n])
{
    for(int i=0; i<n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
}

bool nast_perm(int n, int p[n])
{
    if(n==1)
        return false;

    if(p[0]==n)
    {
        for(int i=0; i<n-1; i++)
        {
            p[i]=p[i+1];
        }
        p[n-1]=n;
        return nast_perm(n-1, p);
    }
    else
    {
        for(int i=0; i<n-1; i++)
        {
            if(p[i+1]==n)
            {
                p[i+1]=p[i];
                p[i]=n;
            }
        }
        return true;
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    int t[n];
    for(int i=0; i<n; i++)
        t[i]=i+1;

    int ile=0;
    do
    {
        wypisz(n, t);
        ile++;
    }
    while(nast_perm(n, t));
    printf("%d", ile);
    return 0;
}
