#include<stdio.h>
#include<stdlib.h>

int main()
{
    int x; int y;
    scanf("%d", &x);
    scanf("%d", &y);
    int t[x][y];
    char pom;
    for(int i=0; i<y; i++)
    {
        for(int j=0; j<x; j++)
        {
            scanf("%c", &pom);
            if(pom=='.')
                t[j][i]=0;
            if(pom=='#')
                t[j][i]=1;
        }
    }

    for(int i=0; i<y; i++)
    {
        t[3][i]='2';
    }
    for(int i=4; i<x; i++)
    {
        t[i][0]='2';
    }
    t[0][3]='0';
    t[5][3]='0';
    t[2][5]='2';
    t[3][5]='2';
    t[4][5]='2';
    for(int i=0; i<y; i++)
    {
        for(int j=0; j<x; j++)
        {
            if(t[j][i]==0)
                printf(".");
            if(t[j][i]==1)
                printf("#");
            if(t[j][i]==2)
                printf("X");
        }
        printf("\n");
    }
    return 0;
}
