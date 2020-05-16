#include<stdio.h>

char szachownica[8][8];
char wynik[8][8];

int bialen=0;
int czarnen=0;
int bialex[64];
int bialey[64];
int czarnex[64];
int czarney[64];

int zadanie();
void wczytywanie();
void uzupelnijfigury();
int figurabiala(int i);
int czypuste(int x, int y);
int czywwymiarach(int x, int y);
int bialypion(int x, int y);
int czylegalny();//tutaj
int bialykrol(int x, int y);
int czybialykrol(int x, int y, int x2, int y2, char figura);
int bialyskoczek(int x, int y);
int czybialawieza(int x2, int y2);
int czybialawiezalegalna(int x, int y, int x2, int y2, char figura);
int bialawieza(int x, int y);
int bialygoniec(int x, int y);
int bialyhetman(int x, int y);

int figuraczarna(int x, int y);
int czarnykrol(int x, int y);
int czarnypion(int x, int y);
int czarnawieza(int x, int y);
int czarnyskoczek(int x, int y);
int czarnygoniec(int x, int y);
int czarnyhetman(int x, int y);

int czyczarnykrol(int x2, int y2);
int czybiciebialegokrola(int x, int y);

int main()
{
    int wynik=zadanie();
    printf("%d", wynik);
    return 0;
}

void wczytywanie()
{
    char linia;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            scanf("%c", &szachownica[j][i]);
        }
        scanf("%c", &linia);
    }
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            wynik[i][j]=szachownica[i][j];
        }
    }
    /*for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            printf("%c", szachownica[j][i]);
        }
        printf("\n");
    }*/

}

void uzupelnijfigury()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(szachownica[i][j]=='.'){;}
            else
            {
                if(szachownica[i][j]=='K' || szachownica[i][j]=='H' || szachownica[i][j]=='G' || szachownica[i][j]=='W' || szachownica[i][j]=='S' || szachownica[i][j]=='P')
                {
                    bialex[bialen]=i;
                    bialey[bialen]=j;
                    bialen++;
                }
                else
                {
                    czarnex[czarnen]=i;
                    czarney[czarnen]=j;
                    czarnen++;
                }
            }
        }
    }
}

int zadanie()
{
    wczytywanie();
    uzupelnijfigury();
    int ile=0;
    for(int i=0; i<bialen; i++)
    {
        ile=ile+figurabiala(i);
    }
    return ile;
}

int figurabiala(int i)
{
    int legalne=0;
    char znak=szachownica[bialex[i]][bialey[i]];
    switch (znak)
    {
        case 'K':
            legalne=bialykrol(bialex[i], bialey[i]);
            //printf("K%d   ", legalne);
            break;
        case 'H':
            legalne=bialyhetman(bialex[i], bialey[i]);
            //printf("H%d   ", legalne);
            break;
        case 'G':
            legalne=bialygoniec(bialex[i], bialey[i]);
            //printf("G%d   ", legalne);
            break;
        case 'W':
            legalne=bialawieza(bialex[i], bialey[i]);
            //printf("W%d   ", legalne);
            break;
        case 'S':
            legalne=bialyskoczek(bialex[i], bialey[i]);
            //printf("S%d   ", legalne);
            break;
        case 'P':
            legalne=bialypion(bialex[i], bialey[i]);
            //printf("P%d   ", legalne);
            break;
    }
    return legalne;
}

int czypuste(int x, int y)
{
    //szachownica[i][j]=='k' ???
    if(szachownica[x][y]=='.')
        return 1;
    if(szachownica[x][y]=='K' || szachownica[x][y]=='H' || szachownica[x][y]=='G' || szachownica[x][y]=='W' || szachownica[x][y]=='S' || szachownica[x][y]=='P')
    {return 0;}

    return -1;
}

int czywwymiarach(int x, int y)
{
    if(0<=x && x<8 && 0<=y && y<8)
        return 1;
    return 0;
}

int bialypion(int x, int y)
{
    int ile=0;

    if(czywwymiarach(x-1, y-1))
    {
        if(czypuste(x-1, y-1)==-1)
        {
            wynik[x][y]='.';
            wynik[x-1][y-1]='P';
            if(czylegalny())
            {
                if((y-1)==0)
                    ile=ile+4;
                else
                    ile=ile+1;
            }
            wynik[x][y]='P';
            wynik[x-1][y-1]=szachownica[x-1][y-1];
        }
    }
    if(czywwymiarach(x+1, y-1))
    {
        if(czypuste(x+1, y-1)==-1)
        {
            wynik[x][y]='.';
            wynik[x+1][y-1]='P';
            if(czylegalny())
            {
                if((y-1)==0)
                    ile=ile+4;
                else
                    ile=ile+1;
            }
            wynik[x][y]='P';
            wynik[x+1][y-1]=szachownica[x+1][y-1];
        }
    }
    if(czywwymiarach(x, y-1))
    {
        //printf("(HEJ:%d)", czypuste(x, y-1));
        //printf("[%d]", szachownica[x-1][y]);

        if(czypuste(x, y-1)==1)
        {

            wynik[x][y]='.';
            wynik[x][y-1]='P';
            if(czylegalny())
            {
                if((y-1)==0)
                    ile=ile+4;
                else
                    ile=ile+1;
            }
            wynik[x][y]='P';
            wynik[x][y-1]='.';
        }
    }
    if(y==6)
    {
        if(czypuste(x, y-2)==1 && czypuste(x, y-1)==1)
        {
            wynik[x][y]='.';
            wynik[x][y-2]='P';
            if(czylegalny())
            {
                    ile=ile+1;
            }
            wynik[x][y]='P';
            wynik[x][y-2]='.';
        }
    }

    return ile;
}

int czybialykrol(int x, int y, int x2, int y2, char figura)
{
    int czy=0;
    if(czywwymiarach(x2, y2))
    {
        if(czypuste(x2, y2)==-1 || czypuste(x2, y2)==1)
        {
            wynik[x][y]='.';
            wynik[x2][y2]=figura;
            if(czylegalny())
            {
                czy=1;
            }
            wynik[x][y]=figura;
            wynik[x2][y2]=szachownica[x2][y2];
        }
    }
    return czy;
}

int bialykrol(int x, int y)
{
    int ile=0;
    ile=ile+czybialykrol(x, y, x+1, y-1, 'K');
    ile=ile+czybialykrol(x, y, x+1, y, 'K');
    ile=ile+czybialykrol(x, y, x+1, y+1, 'K');
    ile=ile+czybialykrol(x, y, x, y-1, 'K');
    ile=ile+czybialykrol(x, y, x, y+1, 'K');
    ile=ile+czybialykrol(x, y, x-1, y-1, 'K');
    ile=ile+czybialykrol(x, y, x-1, y, 'K');
    ile=ile+czybialykrol(x, y, x-1, y+1, 'K');

    return ile;
}

int bialyskoczek(int x, int y)
{
    int ile=0;
    ile=ile+czybialykrol(x, y, x-1, y+2, 'S');
    ile=ile+czybialykrol(x, y, x+1, y+2, 'S');
    ile=ile+czybialykrol(x, y, x+2, y+1, 'S');
    ile=ile+czybialykrol(x, y, x+2, y-1, 'S');
    ile=ile+czybialykrol(x, y, x+1, y-2, 'S');
    ile=ile+czybialykrol(x, y, x-1, y-2, 'S');
    ile=ile+czybialykrol(x, y, x-2, y-1, 'S');
    ile=ile+czybialykrol(x, y, x-2, y+1, 'S');
    return ile;
}

int czybialawieza(int x2, int y2)
{
    int czy=0;
    if(czywwymiarach(x2, y2))//w tablicy
    {
        if(czypuste(x2, y2)==1)//puste pole
        {
            czy=1;
        }
        if(czypuste(x2, y2)==-1)//figura czarna
        {
            czy=-1;
        }
    }
    return czy;
}

int czybialawiezalegalna(int x, int y, int x2, int y2, char figura)
{
    int czy=0;
    wynik[x][y]='.';
    wynik[x2][y2]=figura;
    if(czylegalny())
    {
        czy=1;
    }
    wynik[x][y]=figura;
    wynik[x2][y2]=szachownica[x2][y2];
    return czy;
}

int bialawieza(int x, int y)
{
    int ile=0;
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x+i, y);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x-i, y);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x, y+i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x, y+i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x, y+i, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x, y-i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x, y-i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x, y-i, 'W');
                break;
            }
        }
    }

    return ile;
}

int bialygoniec(int x, int y)
{
    int ile=0;
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x+i, y+i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y+i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y+i, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x-i, y+i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y+i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y+i, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x-i, y-i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y-i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x-i, y-i, 'W');
                break;
            }
        }
    }
    for(int i=1; i<8; i++)
    {
        int pom=czybialawieza(x+i, y-i);
        if(pom==0)
        {
            break;
        }
        else
        {
            if(pom==1)
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y-i, 'W');
            }
            else
            {
                ile=ile+czybialawiezalegalna(x, y, x+i, y-i, 'W');
                break;
            }
        }
    }
    return ile;
}

int bialyhetman(int x, int y)
{
    int ile=0;
    ile=ile+bialawieza(x, y);
    ile=ile+bialygoniec(x, y);
    return ile;
}

int czylegalny()
{
    /*printf("\n");
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            printf("%c", wynik[j][i]);
        }
        printf("\n");
    }*/

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(wynik[i][j]=='.' || wynik[i][j]=='K' || wynik[i][j]=='H' || wynik[i][j]=='G' || wynik[i][j]=='W' || wynik[i][j]=='S' || wynik[i][j]=='P')
            {;}
            else
            {
                if(figuraczarna(i, j)==1)//jesli bije
                return 0;
            }
        }
    }

    /*for(int i=0; i<czarnen; i++)
    {
        if(figuraczarna(i)==1)//jesli bije
            return 0;
    }*/
    return 1;
}

int czybiciebialegokrola(int x, int y)
{
    if(wynik[x][y]=='K')
        return 1;
    return 0;
}

int figuraczarna(int x, int y)
{
    int legalne=0;
    char znak=szachownica[x][y];
    switch (znak)
    {
        case 'k':
            legalne=czarnykrol(x, y);
            //printf("k%d ", legalne);
            break;
        case 'h':
            legalne=czarnyhetman(x, y);
            //printf("h%d ", legalne);
            break;
        case 'g':
            legalne=czarnygoniec(x, y);
            //printf("g%d ", legalne);
            break;
        case 'w':
            legalne=czarnawieza(x, y);
            //printf("w%d ", legalne);
            break;
        case 's':
            legalne=czarnyskoczek(x, y);
           // printf("s%d ", legalne);
            break;
        case 'p':
            legalne=czarnypion(x, y);
            //printf("p%d ", legalne);
            break;
    }
    /*
    int legalne=0;
    char znak=szachownica[czarnex[i]][czarney[i]];
    switch (znak)
    {
        case 'k':
            legalne=czarnykrol(czarnex[i], czarney[i]);
            printf("k%d ", legalne);
            break;
        case 'h':
            legalne=czarnyhetman(czarnex[i], czarney[i]);
            printf("h%d ", legalne);
            break;
        case 'g':
            legalne=czarnygoniec(czarnex[i], czarney[i]);
            printf("g%d ", legalne);
            break;
        case 'w':
            legalne=czarnawieza(czarnex[i], czarney[i]);
            printf("w%d ", legalne);
            break;
        case 's':
            legalne=czarnyskoczek(czarnex[i], czarney[i]);
            printf("s%d ", legalne);
            break;
        case 'p':
            legalne=czarnypion(czarnex[i], czarney[i]);
            printf("p%d ", legalne);
            break;
    }*/
    return legalne;
}

int czyczarnykrol(int x2, int y2)
{
    int czy=0;
    if(czywwymiarach(x2, y2))
    {
        czy=czybiciebialegokrola(x2, y2);
    }
    return czy;
}

int czarnykrol(int x, int y)
{
    int ile=0;
    ile=ile+czyczarnykrol(x+1, y-1);
    ile=ile+czyczarnykrol(x+1, y);
    ile=ile+czyczarnykrol(x+1, y+1);
    ile=ile+czyczarnykrol(x, y-1);
    ile=ile+czyczarnykrol(x, y+1);
    ile=ile+czyczarnykrol(x-1, y-1);
    ile=ile+czyczarnykrol(x-1, y);
    ile=ile+czyczarnykrol(x-1, y+1);
    return ile;
}

int czarnyskoczek(int x, int y)
{
    int ile=0;
    ile=ile+czyczarnykrol(x-1, y+2);
    ile=ile+czyczarnykrol(x+1, y+2);
    ile=ile+czyczarnykrol(x+2, y+1);
    ile=ile+czyczarnykrol(x+2, y-1);
    ile=ile+czyczarnykrol(x+1, y-2);
    ile=ile+czyczarnykrol(x-1, y-2);
    ile=ile+czyczarnykrol(x-2, y-1);
    ile=ile+czyczarnykrol(x-2, y+1);
    return ile;
}

int czypuste2(int x, int y)
{
    if(wynik[x][y]=='.')
        return 1;
    if(wynik[x][y]=='K' || wynik[x][y]=='H' || wynik[x][y]=='G' || wynik[x][y]=='W' || wynik[x][y]=='S' || wynik[x][y]=='P')
    {return 0;}

    return -1;
}

int czarnawieza(int x, int y)
{
    int ile=0;
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x, y+i))
        {
            int pom=czypuste2(x, y+i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x, y+i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x-i, y))
        {

            int pom=czypuste2(x-i, y);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x-i, y);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}

    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x+i, y))
        {
            int pom=czypuste2(x+i, y);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x+i, y);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x, y-i))
        {
            int pom=czypuste2(x, y-i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x, y-i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }

    return ile;
}

int czarnygoniec(int x, int y)
{
    int ile=0;
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x+i, y+i))
        {
            int pom=czypuste2(x+i, y+i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x+i, y+i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x-i, y+i))
        {

            int pom=czypuste2(x-i, y+i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x-i, y+i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}

    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x+i, y-i))
        {
            int pom=czypuste2(x+i, y-i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x+i, y-i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }
    for(int i=1; i<8; i++)
    {
        if(czywwymiarach(x-i, y-i))
        {
            int pom=czypuste2(x-i, y-i);
            if(pom==0)
            {
                ile=ile+czybiciebialegokrola(x-i, y-i);
                break;
            }
            else
            {
                if(pom==-1){break;}
            }
        }
        else{break;}
    }

    return ile;
}

int czarnyhetman(int x, int y)
{
    int ile=0;
    ile=ile+czarnawieza(x, y);
    ile=ile+czarnygoniec(x, y);
    return ile;
}

int czarnypion(int x, int y)
{
    int ile=0;
    if(czywwymiarach(x-1, y+1))
    {
       ile=ile+czybiciebialegokrola(x-1, y+1);
    }
    if(czywwymiarach(x+1, y+1))
    {
        ile=ile+czybiciebialegokrola(x+1, y+1);
    }

    return ile;
}


