# Sztuczna inteligencja - ćwiczenia 1
###### tags: `si2020/2021` `ćwiczenia`
## Zadanie 1
Plansza $n \times n$.
### a)
W pierwszej i ostatniej kolumnie musimy zakolorować 1 pole. Analogicznie w pierwszym i ostatnim wierszu. Pozostałe wiersze i kolumny puste. Wtedy istnieją dokładnie dwa rozwiązania, będące planszami, na których pokolorowane są tylko dwa przeciwległe rogi.

Uzasadnienie:
Możemy zauważyć, że wszystkie pola poza rogami planszy muszą być puste.

Rozważmy dwa przypadki:
1. Kolorujemy lewy górny róg.
Wtedy jedyne możliwe do zakolorowania pole to pole w prawym dolnym rogu.
2. Kolorujemy lewy dolny róg.
Wtedy jedyne możliwe do zakolorowania pole to pole w prawym górnym rogu.

Zobrazowanie:

![](https://i.imgur.com/0Jjmfyo.png)

### b)
W każdej kolumnie i w każdym wierszu musimy zakolorować jedno pole. Wtedy problem możemy utożsamić z problemem rozstawienia $n$ wież na szachownicy $n \times n$ tak, aby się nie biły.
Jeśli będziemy ustawiać wieże po kolei kolumnami, to pierwszą wieżę możemy ustawić na $n$ sposobów, drugą na $n-1$ itd.
Zatem mamy $n!$ możliwych kolorowań.

Na przykład:

![](https://i.imgur.com/Du2Tlj0.png)


## Zadanie 2
<!-- http://www.tectonicpuzzel.eu/nonogram-solving-techniques-griddler-tips.html -->
### Liczba pól do zaczernienia równa rozmiarowi kolumny/wiersza.

![](https://i.imgur.com/5RPNhhM.png)


### Liczba większa od połowy rozmiaru wiersza/kolumny
(lub od połowy rozmiaru wolnego miejsca)

![](https://i.imgur.com/ylIodwP.png)



### Liczby oddzielone jedną komórką równe rozmiarowi wiersza/kolumny

![](https://i.imgur.com/s0nMU5M.png)

### Nieosiągalne miejsca

![](https://i.imgur.com/jtzShjY.png)


### Czy jest nadal wystarczająco miejsca na wybrane segmenty?

![](https://i.imgur.com/Wh3uaKS.png)

### Uzupełniaj wiedzą z innych kolumn

![](https://i.imgur.com/q388IWC.png)

### Łącz i dziel

![](https://i.imgur.com/zLHzjRP.png)

![](https://i.imgur.com/TzlkPrI.png)


### Otaczaj gotowe grupy białymi polami

![](https://i.imgur.com/O0ydKSo.png)


### Ustalanie koloru przez unikanie sprzeczność


![](https://i.imgur.com/x041sg0.png)

## Zadanie 3*


## Zadanie 4
<!-- Liczba różnych rąk blotkarza: ${{36}\choose{5}} = 376992$
Liczba różnych rąk figuranta: ${{16}\choose{5}} = 4368$
Iloczyn = 1 646 701 056 (trochę dużo) -->
Można zaklasyfikować każde rozdanie blotkarza i figuranta w odpowiedni układ pokerowy.


$W$ - zdarzenie, że blotkarz wygrał
$U_B$ - zbiór zdarzeń dzielących przestrzeń na różne układy u blotkarza
$U_F$ - zbiór zdarzeń dzielących przestrzeń na różne układy u figuranta

Ze wzoru na prawdopodobieństwo całkowite:

$$ \mathbb{P}[W] = \sum_{U_b \in U_B} \mathbb{P}[W|U_b] \cdot \mathbb{P}[U_b] $$

$$ \mathbb{P}[W|U_b] = \sum_{U_f \in U_F}\mathbb{P} [W \cap U_f |U_b] $$

Wtedy dla ustalonych $U_b$ i $U_f$ mamy
$$\mathbb{P}[W \cap U_f | U_b] = \begin{cases}
\mathbb{P}[U_f],& \text{gdy blotkarz wygyrywa z figurantem dla } f \text{ i }b \\
0, & \text{wpp.}
\end{cases}$$

Inaczej, 
$$\mathbb{P}[W] = \sum_{U_f \in U_F} \sum_{U_b \in U_b} \chi_{\{b \text{ wygrywa z }f\}} \mathbb{P}[U_f] \mathbb{P}[U_b]$$

$B$ - zbiory poszczególnych układów blotkarza
$F$ - zbiory poszczególnych układów figuranta
```
p_blotkarz_win = 0
for b in B:
    p(b) = |b| / |B|
    p(f < b) = |{f < b : f in F}| / |F|
    p_blotkarz_win += p(b) * p(f < b)
```

Złożoność czasowa: O(|B| + |F|)


## Zadanie 5*


## Zadanie 6
W tym przykładzie znajduje, ale nie znajduje najkrótszej.
![](https://i.imgur.com/Bco2ZQX.png)

![](https://i.imgur.com/8ZPaEa5.png)

## Zadanie 7

## Zadanie 8
Stan: Umiejscowienie skrzynek i z której strony można je popchnąć.

Ruch: Przesunięcie skrzynki.

Aktualizacja stanu: Używamy algorytmu BFS do znalezienia skrzynek i możliwych stron, z których możemy je popchnąć. Startujemy z miejsca, na którym stała skrzynka, którą popchnęliśmy.

Jeśli dotrzemy do skrzynki, to sprawdzamy, czy coś za nią stoi, jeśli nie, to dodajemy stronę, z której możemy ją popchnąć


## Zadanie 9

### a)
Stan:
* miasto, w którym znajduje się samochód
* ilość paliwa
* sumaryczny koszt trasy?

Model:
Przejście do sąsiadującego miasta, do którego koszt przejścia jest mniejszy lub równy ilości paliwa w baku. Jeśli w mieście znajduje się stacja benzynowa, to uzupełniamy bak, w przeciwnym razie zmniejszamy ilość paliwa o koszt przejścia. Uaktulaniamy koszt trasy i miasto.

### b)
Stan:
* miasto, w którym znajduje się kurier
* odwiedzone lokalizacje spośród docelowych lokalizacji
* sumaryczny koszt trasy?

Model:
Przejście do sąsiadującego miasta, zaktualizowanie miasta i sumarycznego kosztu trasy, jeśli nowym miastem jest jeszcze nieodwiedzone miasto docelowe, to zaznaczamy je jako odwiedzone.


## Zadanie 10


W problemie z pocztą konną nasz "samochód" ma bak o pojemności 3. Wszystkie ścieżki mają koszt 1. Stanice z możliwością wymiany konia to stacje beznynowe.

Koń przejeżdża bez odpoczynku 3 krawędzie.
Jest 100 stancji, 10 ma stajnię.
Punkt startowy i końcowy ma stajnię.

Stan:
* która stancja: 100
* zasięg: 3

W stancjach ze stajnią koń ma zawsze zasięg 3.
W stancjach bez stajni koń nie może mieć zasięgu 3.
Nie musimy pamiętać zasięgu 0, ponieważ gdy mamy zasięg 1, możemy jedynie pozwalać na ruch do stanicy ze stajnią.

Minimalna liczba stanów pozwalająca opisać każdą przesterzeń:
$$90 \cdot 2+10$$

## Zadanie 11
### b)

Wielkość przestrzeni stanów: $N^K$.
Wszystkie możliwe położenia przyjaciół na grafie.

Ustalmy przyjaciela $p_0$. Algorytmem BFS znajdujemy najbliższego przyjaciela i udajemy się na jego węzeł (możemy, bo graf jest spójny). Teraz przyjaciół na jednym polu utożsamiamy jako jednego, czyli będą poruszać się razem. Znów szukamy dla nich najbliższego przyjaciela. Iterujemy się, aż 'zbierzemy' wszystkich przyjaciół.

Koszt:
$$\mathcal{O}(K\cdot b^d)$$
gdzie: 
* $d$ to maksymalna odległość jaką może mieć jeden przyjaciel do drugiego
* $b$ to maskymalny stopień wychodzący wierzchołka w grafie




<!-- Przestrzeń stanów: $N^K$
Przeszukujemy równocześnie BFS'em z każdego wierzchołka, w którym znajduje się przyjaciel. Jedna iteracja algorytmu to pogłębienie każdego BFS'a o jeden. Jeśli w pewnej iteracji jeden z BFS'ów natrafi na wierzchołek odwiedzony już przez innego BFS'a, to zapamiętujemy połączenie i łączymy kolejki obu BFS'ów, z tym że duplikowane albo inne odwiedzone już przez któryś z tych BFS'ów wierzchołki pomijamy.

W zewnętrznej liście dla danego wierzchołka pamiętamy z jakiego wierzchołka do niego doszliśmy. -->