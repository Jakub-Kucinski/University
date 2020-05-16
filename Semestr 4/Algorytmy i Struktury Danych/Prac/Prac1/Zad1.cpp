#include <cstdio>
#include <vector>
#include <stack>

const int N = 10001;
struct Para
{
    int pierwszy;
    int drugi;
};

int DFS2(std::vector<std::vector<Para>> lista_krawedzi, int odwiedzony[N], int pochodzenie_m[N], int pochodzenie_l[N])
{
    std::stack < int > stos;
    int wierzcholek;
    int n;
    int r;
    stos.push(0);
    while (!stos.empty())
    {
        wierzcholek = stos.top();
        stos.pop();
        n = lista_krawedzi[wierzcholek].size();
        for (int i = 0; i < n; i++)
        {
            r = lista_krawedzi[wierzcholek][i].drugi;
            if(odwiedzony[r] == 0)
            {
                odwiedzony[r] = 1;
                pochodzenie_m[r] = lista_krawedzi[wierzcholek][i].pierwszy;
                pochodzenie_l[r] = wierzcholek;
                if (r == 0)
                {
                    return 0;
                }
                stos.push(r);
            }
        }
    }
    return -1;
}

int DFS(int wierzcholek, std::vector<std::vector<Para>> lista_krawedzi, int odwiedzony[N], int pochodzenie_m[N], int pochodzenie_l[N])
{
    int n = (int)lista_krawedzi[wierzcholek].size();
    // printf(" - %d  %d - \n", wierzcholek, n);
    for (int i = 0; i < n; i++)
    {
        int r = lista_krawedzi[wierzcholek][i].drugi;
        if(odwiedzony[r] == 0)
        {
            // printf(" -- %d -- \n", r);
            odwiedzony[r] = 1;

            pochodzenie_m[r] = lista_krawedzi[wierzcholek][i].pierwszy;
            pochodzenie_l[r] = wierzcholek;

            if (r == 0)
            {
                return 0;
            }
            if(DFS(r, lista_krawedzi, odwiedzony, pochodzenie_m, pochodzenie_l) == 0)
            {
                return 0;
            }
        }
    }
    return -1;
}

int program(std::vector<std::vector<Para>> lista_krawedzi, int pochodzenie_m[N], int pochodzenie_l[N])
{
    int odwiedzony[N];
    for (int i = 0; i < N; i++)
    {
        odwiedzony[i] = 0;
    }
    // return DFS(0, lista_krawedzi, odwiedzony, pochodzenie_m, pochodzenie_l);
    return DFS2(lista_krawedzi, odwiedzony, pochodzenie_m, pochodzenie_l);
}

void wypisz(int n, int r, int pochodzenie_m[N], int pochodzenie_l[N])
{
    if(pochodzenie_l[r] != 0)
    {
        wypisz(n+1, pochodzenie_l[r], pochodzenie_m, pochodzenie_l);
        printf("%d %d %d\n", pochodzenie_l[r], pochodzenie_m[r], r);
    }
    else
    {
        printf("%d\n%d %d %d\n", n+1, pochodzenie_l[r], pochodzenie_m[r], r);
    }
}


int main()
{
    int n;
    scanf("%d\n", &n);
    std::vector<std::vector<Para>> lista_krawedzi;
    lista_krawedzi.resize(N);
    int pochodzenie_m[N];
    int pochodzenie_l[N];
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Para p;
        p.pierwszy = b;
        p.drugi = c;
        lista_krawedzi[a].push_back(p);
    }

    if (program(lista_krawedzi, pochodzenie_m, pochodzenie_l) == 0)
    {
        int r = 0;
        int l = pochodzenie_l[r];
        int m = pochodzenie_m[r];
        // do
        // {
        //     printf("%d %d %d\n", l, m, r);
        //     r = l;
        //     l = pochodzenie_l[r];
        //     m = pochodzenie_m[r];
        // } while (r != 0);

        if(l == 0)
        {
            printf("%d\n%d %d %d\n", 1, 0, m, 0);
        }
        else
        {
            wypisz(1, l, pochodzenie_m, pochodzenie_l);
            printf("%d %d %d\n", l, m, r);
        }
    }
    else
    {
        printf("BRAK\n");
    }
    return 0;
}