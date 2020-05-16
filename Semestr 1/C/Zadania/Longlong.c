#include<stdio.h>
long long int det2(long long int wx, long long int wy, long long int vx, long long int vy);
long long int det(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y);
long long int sgn(long long int x);
long long int strona(long long int pax, long long int pay, long long int pbx, long long int pby, long long int ppx, long long int ppy, long long int pqx, long long int pqy);
long long int nalezy(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y);
long long int min(long long int a, long long int b);
long long int max(long long int a, long long int b);
void wczytaj(long long int n, long long int t[n][4]);
long long int nadrzednosc(long long int n, long long int t[n][4], long long int nadrzedny[n]);
long long int liczebsklad(long long int n, long long int nadrzedny[n], long long int ilesklad[n]);
long long int makssklad(long long int n, long long int ilesklad[n]);
long long int testowanadrzednosc(long long int n, long long int t[n][4], long long int nadrzedny[n]);
long long int testowanadrzednosc2(long long int n, long long int t[n][4], long long int nadrzedny[n]);

int main()
{
    long long int n;
    scanf("%lld", &n);
    long long int dane[n][4];
    wczytaj(n, dane);
    long long int nadrzedny[n];
    long long int ilesklad[n];
    long long int przeciecia=nadrzednosc(n, dane, nadrzedny);
    long long int roznychskladowych=liczebsklad(n, nadrzedny, ilesklad);
    long long int najwskladowa=makssklad(n, ilesklad);
    printf("%lld %lld %lld", przeciecia, roznychskladowych, najwskladowa);
    return 0;
}

long long int testowanadrzednosc2(long long int n, long long int t[n][4], long long int nadrzedny[n])
{
    for(int i=1; i<n; i++) nadrzedny[i]=-1;
    long long int ile=0;
    nadrzedny[0]=0;
    for(int i=1; i<n; i++)
    {
        int k=0;
        for(int j=0; j<i; j++)
        {
                if(strona(t[i][0], t[i][1], t[i][2], t[i][3], t[j][0], t[j][1], t[j][2], t[j][3])<=0 && strona(t[j][0], t[j][1], t[j][2], t[j][3], t[i][0], t[i][1], t[i][2], t[i][3])<=0)
                {
                    ile++;
                    if(k==0)
                    {
                        nadrzedny[i]=nadrzedny[j];
                        k=1;
                    }
                    else
                    {

                    }
                }
        }
        if(nadrzedny[i]==-1)
            nadrzedny[i]=i;
    }
    return ile;
}

long long int makssklad(long long int n, long long int ilesklad[n])
{
    long long int maks=0;
    for(int i=0; i<n; i++)
    {
        if(ilesklad[i]>maks)
        {
            maks=ilesklad[i];
        }
    }
    return maks;
}

long long int liczebsklad(long long int n, long long int nadrzedny[n], long long int ilesklad[n])
{
    for(int i=0; i<n; i++)
    {ilesklad[i]=0;}
    for(int i=0; i<n; i++)
    {ilesklad[nadrzedny[i]]++;}
    long long int ile=0;
    for(int i=0; i<n; i++)
    {
        if(ilesklad[i]>0)
        {
            ile++;
        }
    }
    return ile;
}

long long int testowanadrzednosc(long long int n, long long int t[n][4], long long int nadrzedny[n])
{
    for(int i=1; i<n; i++) nadrzedny[i]=-1;
    long long int ile=0;
    nadrzedny[0]=0;
    for(int i=1; i<n; i++)
    {
        int k=0;
        for(int j=0; j<i; j++)
        {
            if(nalezy(t[i][0], t[i][1], t[i][2], t[i][3], t[j][0], t[j][1])==1 || nalezy(t[i][0], t[i][1], t[i][2], t[i][3], t[j][2], t[j][3])==1 || nalezy(t[j][0], t[j][1], t[j][2], t[j][3], t[i][0], t[i][1])==1 || nalezy(t[j][0], t[j][1], t[j][2], t[j][3], t[i][2], t[i][3])==1)
            {
                ile++;
                if(k==0)
                {
                    nadrzedny[i]=nadrzedny[j];
                    k=1;
                }
                else
                {

                }
            }
            else
            {
                if(strona(t[i][0], t[i][1], t[i][2], t[i][3], t[j][0], t[j][1], t[j][2], t[j][3])<0 && strona(t[j][0], t[j][1], t[j][2], t[j][3], t[i][0], t[i][1], t[i][2], t[i][3])<0)
                {
                    ile++;
                    if(k==0)
                    {
                        nadrzedny[i]=nadrzedny[j];
                        k=1;
                    }
                    else
                    {

                    }
                }
            }
        }
        if(nadrzedny[i]==-1)
            nadrzedny[i]=i;
    }
    return ile;
}

long long int nadrzednosc(long long int n, long long int t[n][4], long long int nadrzedny[n])
{
    for(int i=1; i<n; i++) nadrzedny[i]=-1;
    long long int ile=0;
    nadrzedny[0]=0;
    for(int i=1; i<n; i++)
    {
        int k=0;
        for(int j=0; j<i; j++)
        {
            if(nalezy(t[i][0], t[i][1], t[i][2], t[i][3], t[j][0], t[j][1])==1 || nalezy(t[i][0], t[i][1], t[i][2], t[i][3], t[j][2], t[j][3])==1 || nalezy(t[j][0], t[j][1], t[j][2], t[j][3], t[i][0], t[i][1])==1 || nalezy(t[j][0], t[j][1], t[j][2], t[j][3], t[i][2], t[i][3])==1)
            {
                ile++;
                if(k==0)
                {
                    nadrzedny[i]=nadrzedny[j];
                    k=1;
                }
                else
                {
                    if(nadrzedny[i]!=nadrzedny[j])
                    {
                        long long int zmienna=nadrzedny[j];
                        for(int l=0; l<i; l++)
                        {
                            if(nadrzedny[l]==zmienna)
                                nadrzedny[l]=nadrzedny[i];
                        }
                    }
                }
            }
            else
            {
                if(strona(t[i][0], t[i][1], t[i][2], t[i][3], t[j][0], t[j][1], t[j][2], t[j][3])<0 && strona(t[j][0], t[j][1], t[j][2], t[j][3], t[i][0], t[i][1], t[i][2], t[i][3])<0)
                {
                    ile++;
                    if(k==0)
                    {
                        nadrzedny[i]=nadrzedny[j];
                        k=1;
                    }
                    else
                    {
                        if(nadrzedny[i]!=nadrzedny[j])
                        {
                            long long int zmienna=nadrzedny[j];
                            for(int l=0; l<i; l++)
                            {
                                if(nadrzedny[l]==zmienna)
                                    nadrzedny[l]=nadrzedny[i];
                            }
                        }
                    }
                }
            }
        }
        if(nadrzedny[i]==-1)
            nadrzedny[i]=i;
    }
    return ile;
}

void wczytaj(long long int n, long long int t[n][4])
{
    for(int i=0; i<n; i++)
    {
        scanf("%lld %lld %lld %lld", &t[i][0], &t[i][1], &t[i][2], &t[i][3]);
    }
}

long long int det2(long long int wx, long long int wy, long long int vx, long long int vy)
{
    return wx*vy-wy*vx;
}

long long int det(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y)
{
    long long int wx=p1x-p0x;
    long long int wy=p1y-p0y;
    long long int vx=p2x-p0x;
    long long int vy=p2y-p0y;
    return det2(wx, wy, vx, vy);
}

long long int sgn(long long int x)
{
	if (x==0) return 0;
	if (x>0) return 1;
	return -1;
}

long long int strona(long long int pax, long long int pay, long long int pbx, long long int pby, long long int ppx, long long int ppy, long long int pqx, long long int pqy)
{
    if(sgn(det(pax, pay, pbx, pby, ppx, ppy))*sgn(det(pax, pay, pbx, pby, pqx, pqy))<0)
        return -1;
    if(sgn(det(pax, pay, pbx, pby, ppx, ppy))*sgn(det(pax, pay, pbx, pby, pqx, pqy))==0)
        return 0;
    return 1;
}

long long int min(long long int a, long long int b)
{
    if(a>b) return b;
    return a;
}

long long int max(long long int a, long long int b)
{
    if(a>b) return a;
    return b;
}

long long int nalezy(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y)
{
    if(det(p0x, p0y, p1x, p1y, p2x, p2y)==0 && p2x>=min(p0x, p1x) && p2x<=max(p0x, p1x) && p2y>=min(p0y, p1y) && p2y<=max(p0y, p1y))
        return 1;
    return 0;
}
