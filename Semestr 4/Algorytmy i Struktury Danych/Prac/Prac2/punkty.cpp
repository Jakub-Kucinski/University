#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

double minimum = MAXFLOAT;

struct Punkt
{
    int x;
    int y;
};

struct Result
{
    Punkt A, B, C;
    double r;
};

struct Trojka
{
    Punkt A, B, C;
};


bool compx(Punkt a, Punkt b)
{
    if(a.x != b.x) return a.x < b.x;
    return a.y <= b.y;
}

bool compy(Punkt a, Punkt b)
{
    if (a.y != b.y) return a.y < b.y;
    return a.x <= b.x;
}

long long square(int x)
{
    return ((long long)x) * ((long long)x);
}

double distance(int x1, int x2, int y1, int y2)
{
    
    return sqrt((double)(square(x1 - x2) + square(y1 - y2)));
}

double circum(int x1, int x2, int x3, int y1, int y2, int y3)
{
    return distance(x1, x2, y1, y2) + distance(x1, x3, y1, y3) + distance(x2, x3, y2, y3);
}


double mincirc(int first, int last, const Punkt X[], const Punkt Y[], Trojka *T)
{
    int n = last - first + 1;
    if(n<3)
    {
        return MAXFLOAT;
    }
    int center = (first + last) / 2;
    int boundary_x = X[center].x;
    int boundary_y = X[center].y;
    Punkt mid;
    mid.x = boundary_x;
    mid.y = boundary_y;
    // printf("center: %d, bound_x: %d, bound_y: %d\n", center, boundary_x, boundary_y);
    Punkt new_Y1[center - first + 1];
    Punkt new_Y2[last - center];
    int k1 = 0;
    int k2 = 0;
    for (int i = 0; i < n; i++)
    {
        if(compx(Y[i], mid))
        {
            new_Y1[k1] = Y[i];
            k1++;
        }
        else
        {
            new_Y2[k2] = Y[i];
            k2++;
        }
        
    }
    Trojka *T1 = (Trojka*) malloc(sizeof(Trojka));
    double res1 = mincirc(first, center, X, new_Y1, T1);
    Trojka *T2 = (Trojka*) malloc(sizeof(Trojka));
    double res2 = mincirc(center + 1, last, X, new_Y2, T2);
    if(res2 < res1)
    {   
        T->A.x = T2->A.x;
        T->A.y = T2->A.y;
        T->B.x = T2->B.x;
        T->B.y = T2->B.y;
        T->C.x = T2->C.x;
        T->C.y = T2->C.y;  
    }
    else
    {
        T->A.x = T1->A.x;
        T->A.y = T1->A.y;
        T->B.x = T1->B.x;
        T->B.y = T1->B.y;
        T->C.x = T1->C.x;
        T->C.y = T1->C.y;
    }
    free(T1);
    free(T2);

    double dist = minimum / 2;

    // std::vector<Punkt> close;
    Punkt close[n];
    // close.resize(n);

    int size = 0;
    for (int i = 0; i < n; i++)
    {
        if(std::abs(Y[i].x - boundary_x) < dist)
        {
            // Punkt p;
            // p.x = Y[i].x;
            // p.y = Y[i].y;
            // close.push_back(Y[i]);
            close[size] = Y[i];
            size++;
        }
    }

    int dl = size;
    int a = -1;
    int b = -1;
    int c = -1;
    for (int i = 0; i < dl; i++)
    {
        Punkt p = close[i];
        for (int k = i + 1; k < dl && (close[k].y - p.y) < dist; k++)
        {
            for (int j = k + 1; j < dl && (close[j].y - p.y) < dist; j++)
            {
                // if (p.x>boundary_x && close[j].x>boundary_x && close[k]>boundary_x)
                double d = circum(p.x, close[k].x, close[j].x, p.y, close[k].y, close[j].y);
                // printf("i,j,k: %d, %d, %d   %lf\n", i, j, k, d);
                if (d < minimum)
                {
                    // printf("i,j,k: %d, %d, %d   %lf\n", i, j, k, d);
                    a = i;
                    b = k;
                    c = j;
                    minimum = d;
                }
            }
        }
    }
    if(a != -1)
    {
        T->A.x = close[a].x;
        T->A.y = close[a].y;
        T->B.x = close[b].x;
        T->B.y = close[b].y;
        T->C.x = close[c].x;
        T->C.y = close[c].y;
    }
    return minimum;
}

int main()
{
    int n;
    scanf("%d\n", &n);
    Punkt X[n];
    Punkt Y[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &X[i].x, &X[i].y);
        Y[i].x = X[i].x;
        Y[i].y = X[i].y;
    }
    
    std::sort(X, X+n, compx);
    std::sort(Y, Y+n, compy);

    // printf("\n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d\n", X[i].x, X[i].y);
        
    // }
    // printf("\n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d\n", Y[i].x, Y[i].y);
    // }
    Trojka *T = (Trojka*) malloc(sizeof(Trojka));
    double r = mincirc(0, n - 1, X, Y, T);
    // printf("%lf\n", r);
    printf("%d %d\n%d %d\n%d %d", T->A.x, T->A.y, T->B.x, T->B.y, T->C.x, T->C.y);

    return 0;
}