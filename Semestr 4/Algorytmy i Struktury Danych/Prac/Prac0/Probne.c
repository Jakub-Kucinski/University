#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;
    scanf("%d %d", &a, &b);
    if(a > b)
    {
        int t = b;
        b = a;
        a = t;
    }
    for (int i = a; i <= b; i++)
    {
        printf("%d\n", i);
    }
    return 0;
}