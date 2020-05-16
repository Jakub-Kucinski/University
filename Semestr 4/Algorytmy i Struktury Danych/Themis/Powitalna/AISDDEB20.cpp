/*
Jakub Kuciński
309881
SDUD
*/

#include <cstdio>

int main()
{
    int t[12] = {1, 2, 4, 5, 10, 20, 101, 202, 404, 505, 1010, 2020};
    int a;
    int b;
    scanf("%d %d", &a, &b);
    for (int i = 0; i < 12; i++)
    {
        if(t[i] >= a)
        {
            if(t[i] <= b)
            {
                printf("%d ", t[i]);
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}