#include<stdio.h>
#include<string.h>
/*Jakub Kuciński, nr indeksu 309881, Lista zadań 2, zadanie 3., 22.10.2018, grupa środa 10-12 wstęp do programowania w C */


int main(void)
{
    char o;
    int x;
    int y;
    scanf("%c %d %d", &o, &x, &y);
    char c;
    while ((c = getchar()) != EOF && c != '\n');
    char t[x*y];
    if(o=='K')
    {

        int n=x*y;
        int i=0;
        while((c=getchar())!=EOF)
        {
            t[i]=c;
            i=i+1;
            if(i==n)
            {
                for(int l=0; l<x; l++)
                {
                    for(int k=0; k<y; k++)
                    {
                        putchar(t[k*x+l]);
                    }
                }
                i=0;
            }
        }
        if(i>0)
        {
            for(int l=0; l<x; l++)
                {
                    for(int k=0; k<y; k++)
                    {
                        if(k*x+l<i){putchar(t[k*x+l]);}
                    }
                }
        }
    }
    if(o=='D')
    {
        int n=x*y;
        int i=0;
        int zam=x; x=y; y=zam;
        while((c=getchar())!=EOF)
        {
            t[i]=c;
            i=i+1;
            if(i==n)
            {
                for(int l=0; l<x; l++)
                {
                    for(int k=0; k<y; k++)
                    {
                        putchar(t[k*x+l]);
                    }
                }
                i=0;
            }
        }
        if(i>0)
        {
            for(int l=0; l<x; l++)
                {
                    for(int k=0; k<y; k++)
                    {
                        if(k*x+l<i){putchar(t[k*x+l]);}
                    }
                }
/*
            zam=x; x=y; y=zam;
            int b=i%x;
            int czy[i];
            for(int k=0; k<i; k++)czy[k]=0;
            int a=i/x;
            if(b!=0)
            {a++;}
            for(int k=0; k<a; k++)
            {
            int l=0;
            int indeks=k;
            putchar(t[indeks]);
            while(l<=b)
            {
            indeks=indeks+a;
            putchar(t[indeks]);
            l++;
            czy[indeks]=1;
            }
            while(l<n)
            {
            indeks=indeks+a-1;
            putchar(t[indeks]);
            l++;
            czy[indeks]=1;
            }
            }
            for(int k=0; k<i; k++)
            {
            if(czy[k]==0)
            {putchar(t[k]);}
            }
*/
        }
    }

    return 0;
}
