#include <cstdio>

using namespace std;

int k_th(int k, int T[], int n);


int kth_of_leq_5(const int k, int T[], const int start, const int n)
{
    for (int i = start; i < start + n; i++)
    {
        int t = T[i];
        int j = i - 1;
        while (j >= start && T[j] > t)
        {
            T[j + 1] = T[j];
            j = j - 1;
        }
        T[j + 1] = t;
    }
    return T[start + k - 1];
}

int find_median_of_5(int start, int T[])
{
    // a b c d e
    if(T[start + 1] < T[start]) // b < a
    {
        int x = T[start];
        T[start] = T[start + 1];
        T[start + 1] = x;
    }
    // a < b  c d e
    if(T[start + 3] < T[start + 2]) // d < c
    {
        int x = T[start + 3];
        T[start + 3] = T[start + 2];
        T[start + 2] = x;
    }
    // a < b  c < d  e
    if(T[start + 2] < T[start]) // c < a
    {
        int x = T[start];
        T[start] = T[start + 2];
        T[start + 2] = x;
    }
    // a (b  c < d  e)
    if(T[start + 4] < T[start + 1]) // e < b
    {
        int x = T[start + 4];
        T[start + 4] = T[start + 1];
        T[start + 1] = x;
    }
    // a (b < e  c < d) 
    if(T[start + 2] < T[start + 1]) // c < b
    {
        int x = T[start + 2];
        T[start + 2] = T[start + 1];
        T[start + 1] = x;
    }
    // a, b (e  c < d) = a, b (e  c) d
    if(T[start + 4] < T[start + 2]) // e < c
    {
        // a, b (e) c, d
        return T[start + 4];
    }
    // a, b (c) d, e
    return T[start + 2];
}

int get_pivot(int T[], int n)
{
    if(n < 5)
    {
        return kth_of_leq_5(n/2, T, 0, n);
    }
    int endloop = n / 5;
    int size = endloop;
    if(endloop * 5 != n)
    {
        size++;
    }
    int i = 0;
    int medians[size];

    for (; i < endloop; i++)
    {
        medians[i] = find_median_of_5(5 * i, T);
        // printf("%li ",medians[i]);
    }

    if(5 * i < n)
    {
        medians[i] = kth_of_leq_5((n - 5 * i) / 2, T, 5 * i, n - 5 * i);
        // printf("%li ",medians[i]);
    }
    // printf("\n%li %li \n", medians.size() / 2, medians.size());
    return k_th(size / 2, medians, size);
}

int k_th(int k, int T[], int n)
{
    for (;;)
    {
        if (n <= 5)
        {
            return kth_of_leq_5(k, T, 0, n);
        }

        int pivot = get_pivot(T, n);

        int left = 0;
        int mid = 0;
        int right = n;
        // Ustawiamy na środku między \in [left, mid) wartości równe pivot. Mniejesze przerzucamy na left, większe na right
        // Od [0 do left) mniejsze, od [left do mid) równe, od [mid, do right) nieprzetworzone, od [right do n) wieksze.
        while(mid < right)
        {
            if(T[mid] < pivot)
            {
                int x = T[mid];
                T[mid] = T[left];
                T[left] = x;
                left++;
                mid++;
            }
            else
            {
                if(T[mid] > pivot)
                {
                    right--;
                    int x = T[mid];
                    T[mid] = T[right];
                    T[right] = x;
                }
                else
                {
                    mid++;
                }
            }
        }

        if(k < left)
        {
            n = left;
        }
        else
        {
            if(k < mid)
            {
                return pivot;
            }
            else
            {
                k = k - mid;
                T = &T[mid];
                n = n - mid;
            }
        }
    }
}

int main()
{
    int n, k;
    scanf("%d %d\n", &n, &k);

    int T[n];
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d ", &a);
        T[i] = a;
    }

    printf("%d \n", k_th(k, T, n));

    return 0;
}