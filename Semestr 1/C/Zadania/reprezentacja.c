#include<stdio.h>

char t[36]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

unsigned long long int zamianaodw(unsigned long long int n, int b)
{
    unsigned long long int k=0;
    unsigned long long int pot=10;
    if(b>10)
            pot=pot*10;
    while(n>0)
    {
        k=k*pot+(n%b);
        n=n/b;
    }
    return k;
}

void wypisz(unsigned long long int n, int p)
{
    unsigned long long int pot=10;
    if(p>10)
        pot=pot*10;
    if(n==0)
        printf("0");
    while(n>0)
    {
        printf("%c", t[n%pot]);
        n=n/pot;
    }
}

int main(void)
{
    double x;
    int p;
    int d;
    scanf("%lf %i %i", &x, &p, &d);
    unsigned long long int n=x;
    unsigned long long int np=zamianaodw(n, p);
    wypisz(np, p);
    x=x-n;
    if(d>0)
    {
        int k=0;
        printf(",");
        for(int i=0; i<d; i++)
        {
            x=x*p;
            k=x;
            k=k%p;
            printf("%c", t[k]);
            x=x-k;
        }
    }

    return 0;
}
