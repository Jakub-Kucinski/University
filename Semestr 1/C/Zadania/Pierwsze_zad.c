#include <stdio.h>

/*Jakub Kuciñski, numer indeksu: 309881, "Lista zadañ na pierwsze zajêcia" Pierwsze zadanie dla sprawdzarki., data: 09.10.2018, grupa: œroda 10-12"*/

int main(void)
{
    long int a=0;
    scanf("%li", &a);
    long int lim=a*10;
    long int iloczyn=0;
    long int n=0;
    long int wynik=-1;

    while(a<=lim)
    {
        int k=1;
        n=a;
        iloczyn=a*a;
        while(n>0 && k==1)
        {
            if(n%10!=iloczyn%10)
                k=0;
            n=n/10;
            iloczyn=iloczyn/10;
        }
        if(k==1)
        {
            wynik=a;
            a=lim;
        }
        a++;
    }

    if(wynik==-1)
        printf("BRAK");
    else
        printf("%li", wynik);



    return 0;
}
