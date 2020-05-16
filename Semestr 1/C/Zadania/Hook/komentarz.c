#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Nieprawidłowe argumenty");
        return 1;
    }
    FILE *zrodlo;
    zrodlo=fopen(argv[1], "r");
    if(zrodlo==NULL)
    {
        printf("Nie ma takiego pliku");
        fclose(zrodlo);
        return 1;
    }
    char c;
    int i=0;
    while((c=getc(zrodlo))!='\n' && c!=EOF && i<=50)
    {
        i++;
    }
    fclose(zrodlo);
    if(i>50){ printf("Liczba znaków w pierwszym wierszu większa niż 50");
    return 1;}
    return 0;
}
