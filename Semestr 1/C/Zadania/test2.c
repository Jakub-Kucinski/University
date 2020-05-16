#include<stdio.h>

int main(void)
{
    char a[10];
    for(int i=0; i<10; i++)
    {
        a[i]='\0';
    }
    for(int i=0; i<10; i++)
    {
        printf("%ci", a[i]);
    }

    return 0;
}

