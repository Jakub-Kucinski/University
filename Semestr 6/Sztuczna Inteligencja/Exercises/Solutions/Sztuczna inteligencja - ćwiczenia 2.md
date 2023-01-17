# Sztuczna inteligencja - ćwiczenia 2
###### tags: `si2020/2021` `ćwiczenia`
## Zadanie 1

### Wariant bez czarnej wieży
Obserwacje:
* czarny król musi być przy ścianie
* biały król musi być w odległości 2 od czarnego króla
* biały król musi być w odległości 2 od jakiejś ściany
* wieża jest mało istotna (dla heurystyki)
* ostatni ruch wykonuje biały (król lub wieża)

Propozycja:

```python3
# heurystyka 1
odleglosc_czarnego = odleglosc czarnego krola od najblizszej sciany
odleglosc_bialego = odleglosc bialego krola od nablizszego miejsca oddalonego o 2 od jakiejś ściany

if ruch czarnego:
    return 2*max(odleglosc_czarnego,odleglosc_bialego)
else:
    # ruch bialego
    if odleglosc_czarnego>odleglosc_bialego:
        return odleglosc_czarnego*2+1
    else:
        if odleglosc_bialego==odleglosc_czarnego==0:
            return not czy_mat
        if odleglosc_bialego==odleglosc_czarnego>0:
            return odlegosc_bialego*2+1
        return odleglosc_bialego*2-1
        
# heurystyka 2
return odleglosc czarnego krola od bialego pomniejszona o 2

# heurystyka 3
if mat:
    return 0
else:
    return 1
```


### Wariant z czarną wieżą
Obserwacje:
* Nie da się zamatować króla używając tylko dwóch wież różnych kolorów
* Król w odległości większej niż 2 nie ma żadnego wpływu na ruchy drugiego króla
* Szachowany król musi być nadal przy krawędzi (nie wprost, szachowany król ma 8 możliwych ruchów, drugi król zabiera 3, wieża szachuje i zabiera 2, druga wieża zabiera 1, razem 6 < 8)

Wniosek:
Ponownie obliczamy heurystykę zaproponowaną w pierwszej części zadania. Tym razem w dwóch przypadkach - gdy mat ma zostać osiągnięty przez białego lub czarnego gracza. Bierzemy minimum z otrzymanych wartości.

## Zadanie 2*

## Zadanie 3

Spójna heurystyka jest zawsze optymistyczna.

Dowód:
Indukcja względem odległości od punktu docelowego ($m$).
$N_m$ - wierzchołek znajdujący się w odległości $m$ od najbliższego punku docelowego
$h$ - spójna heurystyka
1. $m=0$
Wtedy znajdujemy się w punkcie końcowym i z rozsądności heurystyki $h(s_{end})=0\leq 0$
3. Załóżmy, że dla każdego $m'$ takiego, że $0\leq m' \leq m$ zachodzi $h(N_{m'}) \leq m'$. Pokażemy, że $h(N_{m+1})\leq m+1$.
Weźmy sąsiadujący wierzchołek $N_{m'}$ dla wierzchołka $N_{m+1}$ taki, że prowadzi przez niego optymalna ścieżka do nabliższego punktu docelowego. Wtedy ze spójności oraz z założenia indukcyjnego otrzymujemy $$h(N_{m+1}) \leq cost(N_{m+1},N_{m'}) + h(N_{m'}) \leq (m+1 - m') + m' = m+1$$


Optymistyczna heurystyka nie musi być spójna.

Kontrprzykład:

![](https://i.imgur.com/soQVsXF.png)
Optymistyczna, ale niespójna heurystyka:
$$8=h(s_3) \nleq cost(s_3,s_2)+h(s_2)=1+5 = 6$$


## Zadanie 4
Metryka:
* $d(x,y)=0 \Leftrightarrow x=y$
* $d(x,y) = d(y, x)$
* $d(x,z) \leq d(x,y) + d(y,z)$

Ustalmy dwa sąsiadujące ze sobą stany $s_1$, $s_2$.
Niech $s_2^{end}$ będzie najbliższym (w sensie metryki) stanem końcowym dla stanu $s_2$.
Wtedy z nierówności trójkąta:
$$ h(s_1) \leq d(s_1,s_2^{end}) \leq d(s_1,s_2) + d(s_2,s_2^{end}) = cost(s_1, s_2) + h(s_2)$$

## Zadanie 5


## Zadanie 6
### Wariant z paliwem
* celem jest minimalizacja długości drogi z punktu startowego do docelowego
* przy pomocy algorytmu UCS ustalamy koszt dotarcia z punktu docelowego do każdego punktu
* heurystyką dla danego wierzchołka będzie odległość do punktu docelowego (z pominięciem ilości paliwa i stacji bezynowych)

### Wariant z paczkami
* celem jest odwiedzenie wszystkich punktów docelowych przy jak najmniejszej pokonanej odległości
* przy pomocy algorytmu UCS dla każdego punktu docelowego ustalamy odległości do pozostałych punktów docelowych (dla punktu startowego również liczymy odległości do punktów docelowych)
* wtedy zadanie ulega uproszczeniu, ponieważ jedyne wierzchołki jakie rozważamy, to punkt startowy i punkty docelowe

## Zadanie 7
Najlepsze heurystyki dla 15-tki to ustalenie bazy rozłącznych wzorców i sumowanie kosztów wzorców dla stanu.
W przypadku Sokobana naszym wzorcem będzie umiejscowienie jednej skrzynki na pustej mapie i najmniejsza liczba popchnięc potrzebnych do wykonania, by znalazła się w punkcie docelowym.
Można uzyskać te wartości przy pomocy algorytmu BFS startującego z wszystkich punktów docelowych (w tym przypadku magazynier "ciągnie" skrzynkę) i zapisanie dla każdego pola najmniejszej liczby popchnięć.
Wtedy heurystyka to suma wartości przypisanych polom, na których znajdują się skrzynie.

## Zadanie 8
Relaksacja polega na założeniu, że ruch na wolne pole jest zawsze możliwy (nawet gdy wolne pole nie jest sąsiadujące).
Zauważmy, że źle ułożoną układankę można przedstawić w postaci permutacji (gdzie wolne pole można zapisać jako 16). Permutację możemy zapisać jako sumę rozłącznych cykli, np.:
$$\begin{pmatrix} 1 & 2 & 3 & 4 & 5 \\
4 & 1 & 5 & 2 & 3 \end{pmatrix} \equiv \begin{pmatrix}1 & 4 & 2 \end{pmatrix} \begin{pmatrix} 3 & 5 \end{pmatrix}$$

Zauważmy, że dążymy do uzyskania permutacji identycznościowej oraz jedyne ruchy, jakie możemy wykonywać to transpozycje z udziałem $16$.

W naszej sytuacji możemy rozważyć dwa przypadki:
1. $16$ znajduje się na swoim miejscu. Wtedy nasza permutacja jest postaci:
$$\begin{pmatrix} \ldots \end{pmatrix} \ldots \begin{pmatrix} \ldots \end{pmatrix}$$
Zamiana $16$ z elementem znajdującym się na swoim miejscu "pogarsza" permutację, bo powstaje kolejny cykl, a pozostałe cykle nie zmniejszają swojej długości.
Zamiana $16$ z elementem nieznajdującym się na swoim miejscu sprawia, że $16$ znajduje się także w tym cyklu, czyli wydłuża go o 1.
2. $16$ jest elementem jakiegoś cyklu. Wtedy nasza permutacja jest postaci:
$$\begin{pmatrix} 16 & \ldots \end{pmatrix} \ldots \begin{pmatrix} \ldots \end{pmatrix}$$
Zamiana $16$ z następnym elementem z cyklu skraca cykl o $1$ i wstawia ten element na odpowiednie miejsce.
Zamiana $16$ z innym elementem z tego samego cyklu jedynie permutuje kolejność elementów w cyklu.
Zamiana $16$ z elementem z innego cyklu łączy te dwa cykle i powstaje jeden o długości równej sumie długości dwóch łączonych cykli.

Wnioski:
* w przypadku 1. opłacającym się ruchem jest zamiana $16$ z źle umiejscowionym elementem.
* w przypadku 2. taką samą opłacalność ma zamiana $16$ z następnym elementem i zamiana z elementem z innego cyklu
* zatem minimalna liczba zamian potrzebna do osiągnięcia permutacji identycznościowej wynosi:
$$ (\text{liczba elementów nieznajdujących się na swoim miejscu}) + \\(\text{liczba cykli do których nie należy }16)$$

Uzasadnienie optymalności:
* na wstawienie każdego elementu nieznajdującego się na swoim miejscu potrzeba jednego ruchu, zamiana następuje tylko z $16$, więc niemożliwe jest wstawienie dwóch elementów na swoje miejsca w jednym ruchu
* jeśli $16$ nie ma w danym cyklu, to niemożliwe jest wstawienie jakiegokolwiek elementu z tego cyklu na swoje miejsce w następnym ruchu (każde z tych miejsc docelowych w tym cyklu jest zajęte, a zamiany można wykonywać tylko z $16$)

## Zadanie 9
Pomysł polega na "łączeniu" zmiennych i zamianie ich na krotki.

Opiszę go na przykładzie z zadania:
$$ 2A+ 4B > 7C + D^2 +EF +G^3$$

Zmienne z lewej i prawej strony nierówności zamieniamy na nowe zmienne będące krotkami. Czyli otrzymujemy:


\begin{align}
2X[0] + 4X[1] > 7 Y[0] + &Y[1]^2 + Y[2]Y[3] + Y[4]^3\\
X[0]&=A\\
X[1]&=B\\
Y[0]&=C\\
Y[1]&=D\\
Y[2]&=E\\
Y[3]&=F\\
Y[4]&=G
\end{align}
\begin{align}
D_X = D_A &\times D_B \\
D_Y = D_C \times D_D &\times D_E \times D_F \times D_G 
\end{align}
## Zadanie 10
