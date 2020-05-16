#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool t[2000001];

int main()
{
    int p;
    scanf("%d", &p);
    int napisze[2*p];
    int czyprawo[2*p];
    int czyzatrzyma[2*p];
    int nowystan[2*p];
    for(int i=0; i<2*p; i++)
    {
        scanf("%d %d %d %d", &napisze[i], &czyprawo[i], &czyzatrzyma[i], &nowystan[i]);
    }
    int najmniej=1000000;
    int najwiecej=1000000;
    int liczbakrokow;
    scanf("%d", &liczbakrokow);
    int miejsce=1000000;
    int aktualnystan=0;
    int zachowanie=aktualnystan*2+t[miejsce];
    int k=0;
    // aktualnystan*2 + t[miejsce]
    for(int i=0; i<liczbakrokow; i++)
    {
        zachowanie=aktualnystan*2+t[miejsce];

        if(czyzatrzyma[zachowanie])
        {
            k=1;
            break;
        }

        t[miejsce]=napisze[zachowanie];

        if(czyprawo[zachowanie])
            miejsce++;
        else miejsce--;

        if(miejsce>najwiecej)
            najwiecej=miejsce;
        else
        {
            if(miejsce<najmniej)
                najmniej=miejsce;
        }

        aktualnystan=nowystan[zachowanie];
    }
    if(k==1)
    {
        printf("halted %d\n", miejsce-1000000);
    }
    else
    {
        printf("running %d\n", miejsce-1000000);
    }

    printf("%d ", najmniej-1000000);
    for(int i=najmniej; i<=najwiecej; i++)
    {
        printf("%d", t[i]);
    }
    printf(" %d", najwiecej-1000000);

    return 0;
}
