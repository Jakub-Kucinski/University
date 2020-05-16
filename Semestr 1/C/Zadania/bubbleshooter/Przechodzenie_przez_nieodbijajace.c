#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <float.h>

typedef struct Vec2T { float x; float y; } Vec2;

typedef struct BubbleT
{
  Vec2 center;
  float radius;
  int visibility;
  int durability;
  int reflectivity;
} Bubble;

typedef
  struct BubbleCloudT
{
  Bubble* bubbles;
  long xN;
  long yN;
} BubbleCloud;

unsigned int rnd_d(unsigned int* rnd)
  { *rnd = 69069*(*rnd) + 1234567; return *rnd; }
float rnd_f(unsigned int* rnd)
  { *rnd = 69069*(*rnd) + 1234567; return ( ((float) *rnd) / ((float) 0xFFFFFFFF) ); }

BubbleCloud generateBubbleCloud(long xN, long yN, long seed, int* visSeq, int* durSeq, int* refSeq)
{
  /* local decls */
  BubbleCloud bubbleCloud;
  int x, y;
  unsigned int rndval;

  /* early init */
  bubbleCloud.bubbles = NULL;
  rndval = seed;
  x = y = 0;

  /* create bubble cloud */
  bubbleCloud.xN = xN;
  bubbleCloud.yN = yN;
  bubbleCloud.bubbles = (Bubble*) malloc( xN * yN * sizeof(Bubble) );

  for (y = 0; y < yN; y++)
    for (x = 0; x < xN; x++)
    {
      bubbleCloud.bubbles[x + y * xN].center.x = (float) x;
      bubbleCloud.bubbles[x + y * xN].center.y = (float) y;
      bubbleCloud.bubbles[x + y * xN].radius   = rnd_f(&rndval) * 0.4f;

      if ( visSeq == NULL || durSeq == NULL || refSeq == NULL )
      {
        /* generate randomized data by using higher half of bits, lower half is too regular */
        bubbleCloud.bubbles[x + y * xN].visibility   = (rnd_d(&rndval) >> 5) & 0x1;
        bubbleCloud.bubbles[x + y * xN].durability   = (rnd_d(&rndval) >> 6) & 0xF;
        bubbleCloud.bubbles[x + y * xN].reflectivity = (rnd_d(&rndval) >> 7) & 0x1;
      }
      else
      {
        bubbleCloud.bubbles[x + y * xN].visibility   = visSeq[x + y * xN];
        bubbleCloud.bubbles[x + y * xN].durability   = durSeq[x + y * xN];
        bubbleCloud.bubbles[x + y * xN].reflectivity = refSeq[x + y * xN];
      }
    }

  return bubbleCloud;
}

void normalizacja(float * x, float * y)
{
    float pom=(*x);
    (*x)=(*x)/(sqrt((*x) * (*x) + (*y) * (*y)));
    (*y)=(*y)/(sqrt((pom) * (pom) + (*y) * (*y)));
}

float odleglosckwadrat(float x1, float y1, float x2, float y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void rozwiazania_m(float x_lasera, float y_lasera, float x_wektora, float y_wektora, float x_srodka_babelka, float y_srodka_babelka, float promien_babelka,
float *delta, float *m1, float *m2)
{
    float a_delta=x_wektora * x_wektora + y_wektora * y_wektora;
    float b_delta=2*((x_lasera - x_srodka_babelka)*x_wektora + y_wektora*(y_lasera - y_srodka_babelka));
    float c_delta=(x_srodka_babelka - x_lasera)*(x_srodka_babelka - x_lasera) + (y_srodka_babelka - y_lasera)*(y_srodka_babelka - y_lasera) - promien_babelka*promien_babelka;
    (*delta)=b_delta * b_delta - 4 * a_delta * c_delta;
    if((*delta)>=0.0f)
    {
        (*m1)=((-1)*b_delta + sqrt((*delta)))/(2 * a_delta);
        (*m2)=((-1)*b_delta - sqrt((*delta)))/(2 * a_delta);
    }
    else
    {
        (*m1)=0.0f;
        (*m2)=0.0f;
    }
}

float odbicie(float x_przeciecia, float y_przeciecia, float x_wektora_lasera, float y_wektora_lasera, float x_srodka_okregu, float y_srodka_okregu)
{
    float x_wektora_promienia=x_przeciecia - x_srodka_okregu;
    float y_wektora_promienia=y_przeciecia - y_srodka_okregu;
    normalizacja(&x_wektora_promienia, &y_wektora_promienia);
    //float x_punktu_p=x_przeciecia - x_wektora_lasera;
    //float y_punktu_p=y_przeciecia - y_wektora_lasera;
    float t=((-1)*(x_wektora_promienia * x_wektora_lasera + y_wektora_promienia * y_wektora_lasera))/(x_wektora_promienia*x_wektora_promienia + y_wektora_promienia*y_wektora_promienia);
    return t;
}

float minimum(float m1, float m2)
{
    if(m1<=0.0001f && m2<=0.0001f)
        return 0.0f;
    else
    {
        if(m1<=0.0001f)
        {
            return m2;
        }
        else
        {
            if(m2<=0.0001f)
            {
                return m1;
            }
            else
            {
                if(m1>m2)
                {
                    return m2;
                }
                else
                {
                    return m1;
                }
            }
        }
    }
}

long long int program(BubbleCloud chmura, long xN, long yN, float x_lasera, float y_lasera, float x_wektora, float y_wektora, long long int liczba_strzalow);

int main()
{
    char c[10];
    scanf("%s", c);
    long xN, yN;
    scanf("%li", &xN);
    scanf("%li", &yN);
    scanf("%s", c);
    long seed;
    scanf("%li", &seed);

    int k=1;
    scanf("%s", c);
    scanf("%s", c);
    int visSeq[xN*yN];
    if(strcmp(c, "rng")==0)
    {
        k=0;
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                visSeq[x + y * xN]=0;
            }
    }
    else
    {
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                scanf("%d", &visSeq[x + y * xN]);
            }
    }

    scanf("%s", c);
    scanf("%s", c);
    int durSeq[xN*yN];
    if(strcmp(c, "rng")==0)
    {
        k=0;
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                durSeq[x + y * xN]=0;
            }
    }
    else
    {
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                scanf("%d", &durSeq[x + y * xN]);
            }
    }

    scanf("%s", c);
    scanf("%s", c);
    int refSeq[xN*yN];
    if(strcmp(c, "rng")==0)
    {
        k=0;
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                refSeq[x + y * xN]=0;
            }
    }
    else
    {
        for (int y = 0; y < yN; y++)
            for (int x = 0; x < xN; x++)
            {
                scanf("%d", &refSeq[x + y * xN]);
            }
    }

    scanf("%s", c);
    float rayorgx;
    float rayorgy;
    scanf("%f", &rayorgx);
    scanf("%f", &rayorgy);

    scanf("%s", c);
    float raydirx;
    float raydiry;
    scanf("%f", &raydirx);
    scanf("%f", &raydiry);

    scanf("%s", c);
    long long int numrays;
    scanf("%lli", &numrays);

    //printf("%li %li %li %f %f %f %f %lli \n", xN, yN, seed, rayorgx, rayorgy, raydirx, raydiry, numrays);
    BubbleCloud chmura;
    if(k==0)
    {
        chmura=generateBubbleCloud(xN, yN, seed, NULL, NULL, NULL);
    }
    else
    {
        chmura=generateBubbleCloud(xN, yN, seed, visSeq, durSeq, refSeq);
    }
    /*for(int i=0; i<xN*yN; i++)
    {
        printf("%d %f %f %f %d %d %d \n", i, chmura.bubbles[i].center.x, chmura.bubbles[i].center.y, chmura.bubbles[i].radius, chmura.bubbles[i].durability, chmura.bubbles[i].visibility,
        chmura.bubbles[i].reflectivity);
    }*/
    printf("%lli", program(chmura, xN, yN, rayorgx, rayorgy, raydirx, raydiry, numrays));
    return 0;
}

long long int program(BubbleCloud chmura, long xN, long yN, float x_lasera, float y_lasera, float x_wektora, float y_wektora, long long int liczba_strzalow)
{
    normalizacja(&x_wektora, &y_wektora);
    //printf("%li %li %f %f %f %f %lli \n", xN, yN, x_lasera, y_lasera, x_wektora, y_wektora, liczba_strzalow);
    long long int ostatni_nieodbity;
    long long int ostatni_odbity;
    for(long long int i=0; i<liczba_strzalow; i++)
    {
        float x_chwilowe_lasera=x_lasera;
        float y_chwilowe_lasera=y_lasera;
        float x_chwilowe_wektora=x_wektora;
        float y_chwilowe_wektora=y_wektora;
        ostatni_nieodbity=-1;
        ostatni_odbity=-1;
        while(1)
        {
            float delta, m1, m2, m;
            float m_min=FLT_MAX;
            int index=-1;
            for(long long int j=0; j<xN*yN; j++)
            {
                if(chmura.bubbles[j].visibility!=0 &&chmura.bubbles[j].durability!=0 && j!=ostatni_odbity)
                {
                    rozwiazania_m(x_chwilowe_lasera, y_chwilowe_lasera, x_chwilowe_wektora, y_chwilowe_wektora, chmura.bubbles[j].center.x, chmura.bubbles[j].center.y,
                    chmura.bubbles[j].radius, &delta, &m1, &m2);
                    m=minimum(m1, m2);
                    if(m==0.0f)
                    {

                    }
                    else
                    {
                        if(m<m_min)
                        {
                            //printf("Delta: %f\n", delta);
                            m_min=m;
                            index=j;
                        }
                    }
                }
            }
            //printf("*%d*", index);
            if(index==-1) break;
            if(chmura.bubbles[index].reflectivity==0)
            {
                ostatni_nieodbity=index;
                (chmura.bubbles[index].durability)--;
                if(chmura.bubbles[index].durability==0)
                    chmura.bubbles[index].visibility=0;
                x_chwilowe_lasera=x_chwilowe_lasera + x_chwilowe_wektora * m_min;
                y_chwilowe_lasera=y_chwilowe_lasera + y_chwilowe_wektora * m_min;
                ostatni_odbity=index;
            }
            else
            {
                (chmura.bubbles[index].durability)--;
                if(chmura.bubbles[index].durability==0)
                    chmura.bubbles[index].visibility=0;
                ostatni_odbity=index;
                float x_przeciecia=x_chwilowe_lasera + x_chwilowe_wektora * m_min;
                float y_przeciecia=y_chwilowe_lasera + y_chwilowe_wektora * m_min;
                float x_wektora_promienia=x_przeciecia - chmura.bubbles[index].center.x;
                float y_wektora_promienia=y_przeciecia - chmura.bubbles[index].center.y;
                normalizacja(&x_wektora_promienia, &y_wektora_promienia);
                float t=odbicie(x_przeciecia, y_przeciecia, x_chwilowe_wektora, y_chwilowe_wektora, chmura.bubbles[index].center.x, chmura.bubbles[index].center.y);
                float x_nowy=2*(t*(x_wektora_promienia)) + x_chwilowe_wektora;
                float y_nowy=2*(t*(y_wektora_promienia)) + y_chwilowe_wektora;
                x_chwilowe_lasera=x_przeciecia;
                y_chwilowe_lasera=y_przeciecia;
                x_chwilowe_wektora=x_nowy;
                y_chwilowe_wektora=y_nowy;
                normalizacja(&x_chwilowe_wektora, &y_chwilowe_wektora);
            }
        }
    }
    return ostatni_nieodbity;
}

