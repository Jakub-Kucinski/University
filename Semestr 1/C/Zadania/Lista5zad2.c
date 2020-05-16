#include<stdio.h>
#include<stdbool.h>


void nast_perm(int n, int s, int p[n], bool t[n])
{
    if(s==(n-1))
    {
        for(int i=0; i<n; i++)
        {
            printf("%d ", p[i]);
        }
        printf("\n");
    }
    else
    {
        for(int i=s; i<n; i++)
        {
            int pom=p[s];
            p[s]=p[i];
            p[i]=pom;
            nast_perm(n, s+1, p, t);
            p[i]=p[s];
            p[s]=pom;
        }
    }

}

void kwadraty(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok])
{
    if(s==n-1)
    {
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            przek=przek+p[i*(bok+1)];
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
                przek=przek+p[(i+1)*(bok-1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
        for(int i=0; i<n; i++)
        {
            printf("%d ", p[i]);
        }
        printf("\n");}
    }
    else
    {
        for(int i=s; i<n; i++)
        {
            int pom=p[s];
            p[s]=p[i];
            p[i]=pom;
            int k=1;
            wiersz[s/bok]=wiersz[s/bok]+p[s];
            kolumna[s%bok]=kolumna[s%bok]+p[s];
            if(suma<wiersz[s/bok] || suma<kolumna[s%bok])
            {
                k=0;
                wiersz[s/bok]=wiersz[s/bok]-p[s];
                kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            else
            {
                if(s%bok==bok-1 && suma!=wiersz[s/bok])
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    if(s/bok==bok-1 && suma!=kolumna[s%bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                }
            }
            if(k==1)
            {

            kwadraty(n, s+1, p, t, suma, bok, kolumna, wiersz);

            wiersz[s/bok]=wiersz[s/bok]-p[s];
            kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            p[i]=p[s];
            p[s]=pom;
        }
    }
}

void perm2(int n, int s, int p[n], bool t[n+1])
{
    for(int i=1; i<=n; i++)
    {
        if(t[i]==0)
        {
            t[i]=1;
            p[s]=i;
            perm2(n, s+1, p, t);
            t[i]=0;
        }
    }
    if(s==n-1)
    {
        for(int i=0; i<n; i++)
        {
            printf("%d ", p[i]);
        }
        printf("\n");
    }
}

void kwadraty2(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok])
{
    if(s<n)
    {
    for(int i=0; i<n; i++)
    {
        if(t[i]==0)
        {
            t[i]=1;
            p[s]=i+1;

            int k=1;
            wiersz[s/bok]=wiersz[s/bok]+p[s];
            kolumna[s%bok]=kolumna[s%bok]+p[s];
            if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[s%bok] && s/bok<bok-1))
            {
                //if(suma<wiersz[s/bok] || suma<kolumna[s%bok] )
                //if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[s%bok] && s/bok<bok-1))
                k=0;
                wiersz[s/bok]=wiersz[s/bok]-p[s];
                kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            else
            {
                if((s%bok)==(bok-1) && suma!=wiersz[s/bok])
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    if((s/bok)==(bok-1) && suma!=kolumna[s%bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                }
            }
            if(k==1)
                {kwadraty2(n, s+1, p, t, suma, bok, kolumna, wiersz);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];}
            t[i]=0;
        }
    }
    }
    if(s==n-1)
    {
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            przek=przek+p[i*(bok+1)];
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
                przek=przek+p[(i+1)*(bok-1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
        for(int i=0; i<n; i++)
        {
            printf("%d ", p[i]);
        }
        printf("\n");}
    }
}

void kwadratytest(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok], int *ile)
{
    if((*ile)!=0)
  {
    if(s<n)
   {
    for(int i=0; i<n; i++)
    {
        if(t[i]==0)
        {
            t[i]=1;
            p[s]=i+1;

            int k=1;
            wiersz[s/bok]=wiersz[s/bok]+p[s];
            kolumna[s%bok]=kolumna[s%bok]+p[s];
            if((suma<=wiersz[s/bok] && s%bok<bok-1) || (suma<=kolumna[s%bok] && s/bok<bok-1))
            {
                k=0;
                wiersz[s/bok]=wiersz[s/bok]-p[s];
                kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            else
            {
                if((s%bok)==(bok-1) && suma!=wiersz[s/bok])
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    if((s/bok)==(bok-1) && suma!=kolumna[s%bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                }
            }
            if(k==1)
                {kwadratytest(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];}
            t[i]=0;
        }
    }
   }
    if(s==n-1)
    {
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            przek=przek+p[i*(bok+1)];
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
                przek=przek+p[(i+1)*(bok-1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
            (*ile)--;
            for(int i=0; i<bok; i++)
            {
                for(int j=0; j<bok; j++)
                {
                    printf("%d ", p[i*bok + j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
  }
}

void kwadratypiertest(int n, int s, int p[n], bool t[n], int suma, int bok, int kolumna[bok], int wiersz[bok], int *ile)
{
if((*ile)!=0)
{
    if(s==n-1)
    {
        int k=1;
        int przek=0;
        for(int i=0; i<bok; i++)
        {
            przek=przek+p[i*(bok+1)];
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
                przek=przek+p[(i+1)*(bok-1)];
            }
            if(przek!=suma)
            {
                k=0;
            }
        }
        if(k==1)
        {
        (*ile)--;
        for(int i=0; i<n; i++)
        {
            printf("%d ", p[i]);
        }
        printf("\n");}
    }
    else
    {
        for(int i=s; i<n; i++)
        {
            int pom=p[s];
            p[s]=p[i];
            p[i]=pom;
            int k=1;
            wiersz[s/bok]=wiersz[s/bok]+p[s];
            kolumna[s%bok]=kolumna[s%bok]+p[s];
            if(suma<wiersz[s/bok] || suma<kolumna[s%bok])
            {
                k=0;
                wiersz[s/bok]=wiersz[s/bok]-p[s];
                kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            else
            {
                if(s%bok==bok-1 && suma!=wiersz[s/bok])
                {
                    k=0;
                    wiersz[s/bok]=wiersz[s/bok]-p[s];
                    kolumna[s%bok]=kolumna[s%bok]-p[s];
                }
                else
                {
                    if(s/bok==bok-1 && suma!=kolumna[s%bok])
                    {
                        k=0;
                        wiersz[s/bok]=wiersz[s/bok]-p[s];
                        kolumna[s%bok]=kolumna[s%bok]-p[s];
                    }
                }
            }
            if(k==1)
            {

            kwadratypiertest(n, s+1, p, t, suma, bok, kolumna, wiersz, ile);

            wiersz[s/bok]=wiersz[s/bok]-p[s];
            kolumna[s%bok]=kolumna[s%bok]-p[s];
            }
            p[i]=p[s];
            p[s]=pom;
        }
    }
}
}


int main(void)
{
    int n;
    scanf("%d", &n);
    int p[n*n];
    bool t[n*n];
    int kolumna[n];
    int wiersz[n];
    for(int i=0; i<n*n; i++)
        {
        p[i]=i+1;
        t[i]=0;}
    for(int i=0; i<n; i++)
        {kolumna[i]=0; wiersz[i]=0;}


    int ile=0;
    scanf("%d", &ile);

    kwadratypiertest(n*n, 0, p, t, ((n*n+1)*n)/2, n, kolumna, wiersz, &ile);

    return 0;
}
