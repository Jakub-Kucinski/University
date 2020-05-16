#include<stdio.h>
/*Jakub Kuciñski, numer indeksu: 309881, Lista zadań 1,  Zadanie 2., data: 14.10.2018, grupa: œroda 10-12"*/


//Funkcja jako argumenty przyjmuje liczbę "n" w systemie dziesiętnym oraz podstawę "b"
//i zwraca zapis liczby "n" w systemie o podstawie "b"
unsigned long long int zamiana(unsigned long long int n, unsigned long long int b)
{
    unsigned long long k=0;
    unsigned long long pot=1;
    while(n>0)
    {
        k=k+(n%b)*pot;
        pot=pot*10;
        n=n/b;
    }
    return k;
}

//Funkcja sprawdza z ilu cyfr składa się liczba "n" i zwraca tą wartość
int dlugosc(unsigned long long int n)
{
    int length=0;
    while(n>0)
    {
        n=n/10;
        length++;
    }
    return length;
}

//Funkcja sprawdza czy dana liczba jest narcystyczna, czyli czy jej zapis dziesiętny ("m10") jest równy
//sumie poszczególnych cyfr tej liczby w zapisie o podstawie b ("mb")
//podniesionych do potęgi równej liczbie cyfr w zapisie o podstawie b tej liczby ("k" - obliczana z funkcji dlugosc)
int narc(unsigned long long int m10, unsigned long long int mb, int k)
{
    unsigned long long int sum=0;
    while(mb>0)
    {
        unsigned long long int skladnik=1;
        unsigned long long int p=mb%10;//Pobieranie ostatniej cyfry z liczby mb
        //Pętla oblicza potęgę danej cyfry liczby mb (cyfra^k)
        for(int i=0; i<k; i++)
        {
            skladnik=skladnik*p;
        }
        sum=sum+skladnik;//Dodawanie potęg kolejnych cyfr liczby mb
        mb=mb/10;
    }
    if(sum==m10)
        return 1;
    return 0;
}

int main(void)
{
    unsigned long long int n;
    scanf("%I64u", &n);
    unsigned long long int b=3;

    //Pętla zewnętrzna zmieniająca podstawę systemu, w którym mamy szukać liczby narcystycznej większej równej podanej na wejściu ("n")
    while(b<11)
    {
        //Zapis dziesiętny potencjalnej liczby narcystycznej
        unsigned long long int m10=n;
        unsigned long long int mb;
        int krot;
        int k=0;
        //Pętla w każdym obrocie sprawdza, czy dana liczba o zapisie dziesiętnym "m10"
        //I zapisie mb w systemie o podstawie "b" i długości "krot" (w systemie b), jest narcystyczna
        //Pętla kontynuuje sprawdzanie kolejnych liczb, aż do znalezienia liczby narcystycznej
        //Wtedy wypisuje jej podstawę, zapis dziesiętny i zapis w systemie o podstawie b
        while(k==0)
        {
            mb=zamiana(m10, b);//Obliczenie reprezentacji liczby m10 w systemie o podstawie b - mb
            krot=dlugosc(mb);//Obliczenie długości mb
            if(narc(m10, mb, krot)==1)//Sprawdzenie czy liczba jest narcystyczna
            {
                printf("%I64u   %I64u    %I64u \n", b, m10, mb);//Jeśli jest narcystyczna to wypisuje odpowiednie wartości
                k=1;//Zatrzymanie pętli
            }
            m10++;//Zwiększenie liczby, która sprawdzimy czy jest narcystyczna
        }
        b++;//Zwiększenie podstawy
    }

    return 0;
}
