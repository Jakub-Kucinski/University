#include<stdio.h>

int main(void)
{
    int x=0;
    int y=0;
    scanf("%d", &x);
    scanf("%d", &y);
    y=(x+y)/2;
    x=y*2-x;
    y=y*2-x;
    printf("%d", x);
    printf("%d", y);
    return 0;
}
