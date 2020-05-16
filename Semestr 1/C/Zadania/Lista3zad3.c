#include<stdio.h>
int det2(int wx, int wy, int vx, int vy);
int det(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y);
int sgn(int x);
int strona(int pax, int pay, int pbx, int pby, int ppx, int ppy, int pqx, int pqy);
int nalezy(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y);
int min(int a, int b);
int max(int a, int b);
void wczytaj(int n, int t[n][4]);
int nadrzednosc(int n, int t[n][4], int nadrzedny[n]);
int liczebsklad(int n, int nadrzedny[n], int ilesklad[n]);
int makssklad(int n, int ilesklad[n]);
int testowanadrzednosc(int n, int t[n][4], int nadrzedny[n]);

int main()
{
    int n;
    scanf("%d", &n);
    int dane[n][4];
    wczytaj(n, dane);
    int nadrzedny[n];
    int ilesklad[n];
    int przeciecia=nadrzednosc(n, dane, nadrzedny);
    int roznychskladowych=liczebsklad(n, nadrzedny, ilesklad);
    int najwskladowa=makssklad(n, ilesklad);
    printf("%d %d %d", przeciecia, roznychskladowych, najwskladowa);
    return 0;
}

int makssklad(int n, int ilesklad[n])
{
    int maks=0;
    for(int i=0; i<n; i++)
    {
        if(ilesklad[i]>maks)
        {
            maks=ilesklad[i];
        }
    }
    return maks;
}

int liczebsklad(int n, int nadrzedny[n], int ilesklad[n])
{
    for(int i=0; i<n; i++)
    {ilesklad[i]=0;}
    for(int i=0; i<n; i++)
    {ilesklad[nadrzedny[i]]++;}
    int ile=0;
    for(int i=0; i<n; i++)
    {
        if(ilesklad[i]>0)
        {
            ile++;
        }
    }
    return ile;
}

int testowanadrzednosc(int n, int t[n][4], int nadrzedny[n])
{
    for(int i=1; i<n; i++) nadrzedny[i]=-1;
    int ile=0;
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

int nadrzednosc(int n, int t[n][4], int nadrzedny[n])
{
    for(int i=1; i<n; i++) nadrzedny[i]=-1;
    int ile=0;
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
                        int zmienna=nadrzedny[j];
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
                            int zmienna=nadrzedny[j];
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

void wczytaj(int n, int t[n][4])
{
    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d %d", &t[i][0], &t[i][1], &t[i][2], &t[i][3]);
    }
}

int det2(int wx, int wy, int vx, int vy)
{
    return wx*vy-wy*vx;
}
int det(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y)
{
    int wx=p1x-p0x;
    int wy=p1y-p0y;
    int vx=p2x-p0x;
    int vy=p2y-p0y;
    return det2(wx, wy, vx, vy);
}

int sgn(int x)
{
	if (x==0) return 0;
	if (x>0) return 1;
	return -1;
}


int strona(int pax, int pay, int pbx, int pby, int ppx, int ppy, int pqx, int pqy)
{
    if(sgn(det(pax, pay, pbx, pby, ppx, ppy))*sgn(det(pax, pay, pbx, pby, pqx, pqy))<0)
        return -1;
    if(sgn(det(pax, pay, pbx, pby, ppx, ppy))*sgn(det(pax, pay, pbx, pby, pqx, pqy))==0)
        return 0;
    return 1;
}

int min(int a, int b)
{
    if(a>b) return b;
    return a;
}

int max(int a, int b)
{
    if(a>b) return a;
    return b;
}
int nalezy(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y)
{
    if(det(p0x, p0y, p1x, p1y, p2x, p2y)==0 && p2x>=min(p0x, p1x) && p2x<=max(p0x, p1x) && p2y>=min(p0y, p1y) && p2y<=max(p0y, p1y))
        return 1;
    return 0;
}
