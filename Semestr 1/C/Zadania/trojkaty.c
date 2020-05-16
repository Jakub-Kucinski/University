#include<stdio.h>
long long int det2(long long int wx, long long int wy, long long int vx, long long int vy);
long long int det(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y);
long long int sgn(long long int x);
long long int strona(long long int pax, long long int pay, long long int pbx, long long int pby, long long int ppx, long long int ppy, long long int pqx, long long int pqy);
long long int nalezy(long long int p0x, long long int p0y, long long int p1x, long long int p1y, long long int p2x, long long int p2y);
long long int min(long long int a, long long int b);
long long int max(long long int a, long long int b);
void wczytaj(int n, long long int w[n][6], long long int p[n][2]);
void czy_teraz(int n, long long int w[n][6], int teraz[n]);
int czy_boki_przecinaja(long long int wx1, long long int wy1, long long int wx2, long long int wy2,
                        long long int px1, long long int py1, long long int px2, long long int py2);
int czy_wewnatrz(int i, int j, int n, long long int w[n][6]);
void czy_pozniej(int n, long long int w[n][6], long long int p[n][2], int pozniej[n], int teraz[n]);
int czy_przecina_pozniej(int i, int j, int n, long long int w[n][6], long long int p[n][2]);

int main()
{
    int n;
    scanf("%d", &n);
    long long int w[n][6];
    long long int p[n][2];
    int teraz[n];
    int pozniej[n];
    for(int i=0; i<n; i++)
    {
        teraz[i]=0; pozniej[i]=0;
    }
    wczytaj(n, w, p);
    czy_teraz(n, w, teraz);
    czy_pozniej(n, w, p, pozniej, teraz);
    for(int i=0; i<n; i++)
    {
        if(teraz[i]==0)
        {
            if(pozniej[i]==1)
                printf("3 ");
            else
                printf("1 ");
        }
        else
        {
            printf("0 ");
        }
    }

    return 0;
}


void czy_pozniej(int n, long long int w[n][6], long long int p[n][2], int pozniej[n], int teraz[n])
{
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(teraz[i]==1 && teraz[j]==1){;}
            else
            {
                if(czy_przecina_pozniej(i, j, n, w, p))
                {
                    pozniej[i]=1;
                    pozniej[j]=1;
                }
                else
                {
                    if(czy_przecina_pozniej(j, i, n, w, p))
                    {
                        pozniej[i]=1;
                        pozniej[j]=1;
                    }
                }
            }
        }
    }
}

int czy_przecina_pozniej(int i, int j, int n, long long int w[n][6], long long int p[n][2])
{
    int vx=p[i][0]-p[j][0];
    int vy=p[i][1]-p[j][1];
    for(int k=0; k<3; k++)
    {
        int zmienionyx=w[i][2*(k%3)]+vx;
        int zmienionyy=w[i][(2*(k%3))+1]+vy;
        if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], zmienionyx, zmienionyy, w[j][0], w[j][1], w[j][2], w[j][3]))
            return 1;
        if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], zmienionyx, zmienionyy, w[j][2], w[j][3], w[j][4], w[j][5]))
            return 1;
        if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], zmienionyx, zmienionyy, w[j][4], w[j][5], w[j][0], w[j][1]))
            return 1;
    }
    return 0;
}

void czy_teraz(int n, long long int w[n][6], int teraz[n])
{
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(teraz[i]==1 && teraz[j]==1)
            {;}
            else
            {
                for(int k=0; k<3; k++)
                {
                    if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1],
                    w[j][0], w[j][1], w[j][2], w[j][3]))
                    {
                        teraz[i]=1;
                        teraz[j]=1;
                        break;
                    }
                    if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1],
                    w[j][2], w[j][3], w[j][4], w[j][5]))
                    {
                        teraz[i]=1;
                        teraz[j]=1;
                        break;
                    }
                    if(czy_boki_przecinaja(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1],
                    w[j][4], w[j][5], w[j][0], w[j][1]))
                    {
                        teraz[i]=1;
                        teraz[j]=1;
                        break;
                    }
                }
                if(teraz[i]==1 && teraz[j]==1)
                {;}
                else
                {
                    if(czy_wewnatrz(i, j, n, w))
                    {
                        teraz[i]=1;
                        teraz[j]=1;
                    }
                    else
                    {
                        if(czy_wewnatrz(j, i, n, w))
                        {
                            teraz[i]=1;
                            teraz[j]=1;
                        }
                    }
                }
            }
        }
    }
}

int czy_wewnatrz(int i, int j, int n, long long int w[n][6])
{
    for(int k=0; k<3; k++)
    {
        if(strona(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1], w[i][2*((k+2)%3)], w[i][(2*((k+2)%3))+1], w[j][0], w[j][1])<=0)
        {
            return 0;
        }
        if(strona(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1], w[i][2*((k+2)%3)], w[i][(2*((k+2)%3))+1], w[j][2], w[j][3])<=0)
        {
            return 0;
        }
        if(strona(w[i][2*(k%3)], w[i][(2*(k%3))+1], w[i][2*((k+1)%3)], w[i][(2*((k+1)%3))+1], w[i][2*((k+2)%3)], w[i][(2*((k+2)%3))+1], w[j][4], w[j][5])<=0)
        {
            return 0;
        }
    }
    return 1;
}


int czy_boki_przecinaja(long long int wx1, long long int wy1, long long int wx2, long long int wy2,
long long int px1, long long int py1, long long int px2, long long int py2)
{
    if(nalezy(wx1, wy1, wx2, wy2, px1, py1)==1 || nalezy(wx1, wy1, wx2, wy2, px2, py2)==1 || nalezy(px1, py1, px2, py2, wx1, wy1)==1 || nalezy(px1, py1, px2, py2, wx2, wy2)==1)
        return 1;
    if(strona(wx1, wy1, wx2, wy2, px1, py1, px2, py2)<0 && strona(px1, py1, px2, py2, wx1, wy1, wx2, wy2)<0)
        return 1;
    return 0;
}

void wczytaj(int n, long long int w[n][6], long long int p[n][2])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<6; j++)
        {
            scanf("%lld", &w[i][j]);
        }
        scanf("%lld %lld", &p[i][0], &p[i][1]);
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

