# Szutuczna inteligencja - ćwiczenia 3
###### tags: `si2020/2021` `ćwiczenia`
## Zadanie 1
1. local beam search dla k = 1 to hill climbing
hill climbing
dla pojedynczego stanu generujemy następniki, wybieramy jednego lidera
2. local beam search z jednym początkowym stanem i bez limitu na liczbę zachownych stanów po generacji następnika
bfs
3. symulowane wyrzażanie z $T = 0$ przez cały czas działania algorytmu
first choice hill climbing
ponieważ przechodzimy do następnika, tylko gdy jest lepszy od stanu, w którym jesteśmy
4. symulowane wyżarzanie z $T = \infty$ przez cały czas działanie algorytmu
spacer losowy po przestrzeni stanów
ponieważ przemiszczamy się do tego stanu, który wylosujemy
5. algorytm genetyczny z populacją wielkości 1
algorytm genetyczny wykonuje same mutacje, bo jeden osobnik nie ma się z kim krzyżować

## Zadanie 2
1. **algorytmy ewolucyjne i hill climbing**
mamy popoluację osobników, dla każdego osobnika uruchamiamy hill climbing (do końca lub na kilka iteracji albo w formie mutacji), później otrzymane osobniki krzyżujemy/mutujemy, proces powtarzamy
2. **$A^\ast$ oraz local beam search**
w algorytmie local beam search w momencie wybierania $k$ liderów spośród wygenerownych następników liderzy są wybierani ze względu na jak najmniejszą wartość heurystyki, można to sobie wyobrazić jako zachłanne dążenie do stanu końcowego
3. **symulowane wyżarzanie i algorytmy ewolucyjne**
Prawdopodobieństwo mutacji można zmniejszać wraz z upływem czasu. Początkowo chcemy bardziej rozlegle przglądać przestrzeń stanów, z czasem jak jesteśmy bliżej jakiegoś ekstremum, to chcemy wykonywać mniej zmian i dokładniej przejrzeć ten fragment przestrzeni.
4. **taboo search i algorytmy ewolucyjne**
Chcemy pamiętać jakąś liczbę ostatnich osobników tak, aby gdy będzie 'wypłaszczenie' nie zatrzymać się na nim. Jeśli otrzymany osobnik jest niedawno odwiedzony, to mutujemy go tak, aby nie był.

## Zadanie 3
Idea algorytmu: Mamy kolonię mrówek. Każda mrówka przechodzi po przestrzeni stanów, aż trafi do celu. Mrówka wraca do mrowiska zostawiając po sobie feromony, które przyciągają kolejne mrówki (im lepsza była droga, bądź stan docelowy, tym więcej feromonów). Po powrocie do mrowiska mrówki ponownie wybierają się w trasę. Tym razem na decyzję, w jakim kierunku iść wpływa nie tylko jakaś lokalna heurystyka (np. zasięg widzenia, wybór może być też w jakimś stopniu losowy), ale również intensywność feromonów na ścieżkach. Mrówki są bardziej skłonne wybrać ścieżkę, na której jest sporo feromonów. Dzięki temu kolonia jest w stanie dokładniej przejrzeć podprzestrzeń odpowiadającą dobrym ścieżkom, ale jednocześnie przeszukiwać też resztę przestrzeni. Feremony zanikają wraz z upływem czasu, więc jeśli popularna ścieżka przestanie być tak optymalna lub zostanie znaleziona lepsza, to stara przestanie być tak uczęszczana.


TSP, czyli problem komiwojażera polega na odwiedzeniu wszystkich miast pokonując jak najkrótszą drogę. Mamy dane miasta i odległości pomiędzy nimi. Nasz algorytm mrówkowy będzie opierał się o następujące zasady:
1. Każde miasto ma zostać odwiedzone dokładnie raz.
2. Odległe miasto ma mniejsze prawdopodobieństwo zostania wybranym jako następne.
3. Im silniejszy ślad feromonów na krawędzi łączącej dwa miasta tym większe prawdopodobieństwo wybrania tej krawędzi.
4. W momencie gdy mrówka odwiedziła wszystkie miasta, to w zależności od tego, jak długą drogę pokonała, zostawia odpowiednią ilość feromonów na przebytej drodze.
5. Po każdym powrocie mrówek do mrowiska/punktu startowego feromony częściowo zanikają.

## Zadanie 4
Obrazki logiczne jako problem spełnialności więzów w `SWI-Prolog`

Podzielimy więzy na dwie części:
***
Wiersz/kolumna:
Dla $n$ bloków do wpisania tworzymy zmienne $P_1$, $\ldots$, $P_n$. Niech $d_i$ oznacza długość $i$-tego bloku. Wtedy dokładamy więzy:
$P_{i+1}-P_i > d_i$
Dziedzina $P_i$ to `0..dlugosc_wiersza-d_i`
Tutaj zapewniamy sobie, aby bloki były dobrze ustawione w wierszu/kolumnie, tzn. mieściły się oraz były w odstępach co najmniej 1.

***
$V_{xy}$ - komórka w $x$-tym wierszu i $y$-owej kolumnie.
Dziedzina $V_{xy}$ to `0..1`
Jesteśmy w $j$-tej kolumnie. Niech $P_1,\ldots ,P_n$ będą początkami bloków w tej kolumnie. 

Dla dowolnego (sensownego) $k$:
$P_{i} \leq k < P_i + d_i \Rightarrow V_{kj} = 1$
Kolorujemy te komórki, gdzie jest blok.

$( P_{i-1}+d_{i-1} \leq k \leq P_i-1 \vee P_i+d_i \leq k < P_{i+1}) \Rightarrow V_{kj}=0$
$k < P_1 \Rightarrow V_{kj}=0$
$P_n + d_n \leq k \Rightarrow V_{kj}=0$
Te komórki, które są poza blokami, mają być puste.

Tutaj łączymy położenia bloków z wierszy i kolumn poprzez wartości konretnych komórek wynikające z połozenia początków bloków.
***

## Zadanie 5
Lekcja - (klasa,nauczyciel)
Każdej takiej parze należy przyporządkować liczbę.
Mamy $K$ klas i $N$ nauczycieli.
Weźmy dowolną klasę $k$.
Klasa ma $X_k$ zajęć.  i każdy nauczyciel ma $Y_n$ zajęć.
Dla każdej lekcji tworzymy zmienną
$L_i \in \{1,\ldots,50\}$ oraz mówimy, że dla $i \neq j$ mamy $L_i \neq L_j$
Weźmy dowolnego nauczyciela

$L_{ki} \in \{1,\ldots,50\}$ oraz dla ustalonego $k$ dla każdego $i \neq j$ mamy $L_{ki} \neq L_{kj}$. Dla ustalonego $i$ dla każdego $k_1, k_2$ mamy $L_{k_1i} \neq L_{k_2i}$

$S_{k1}, S_{k2}, S_{k3}, S_{k4}, S_{k5}$
$E_{k1}, E_{k2}, E_{k3}, E_{k4}, E_{k5}$
$S_{ki} \in \{(i-1)\cdot 10+1, \ldots, i\cdot 10\}$
$E_{ki} \in \{(i-1)\cdot 10+1, \ldots, i\cdot 10\}$

$S_{ki} =$
$X_k$ - liczba wszystkich lekcji danej klasy
$X_k = B_{k1} + B_{k2} + B_{k3} + B_{k4} + B_{k5}$
B - ile lekcji w danym dniu
P - o której godzinie klasa zaczyna lekcje w danym dniu
$P_{ki} \in \{1,X_k\}$
$B_{ki} \in \{1,X_k-4\}$


godzina 30-sta:
Zmienna_30 = $\bigvee_{i} L_{ki} = 30$
## Zadanie 6

## Zadanie 7

Breakthrough
![](https://i.imgur.com/wbJIess.png)
* Pionki mogą poruszać się do przodu lub na ukos o jedno pole. 
* Pionki mogą się bić na ukos. 
* Wygrywa ten, kto pierwszy dotrze jakimś pionkiem do linii końcowej przeciwnika.


Heurystyka:
1. przewaga materialna - liczba figur gracza i przeciwnika
2. dla pionków na naszej połowie tablicy liczymy, ile i jak duże formacje obronne tworzą
3. dla pionków na połowie przeciwnika zliczamy ile i jak duże są formacje ofensywne
4. najdalej wysunięty pion grzacza oraz najdalej wysunięty pion przeciwnika
5. dla każdego pionka w obronie liczymy, ile pionków przeciwnika ma w zasaięgu (im więcej tym lepiej)
6. dla każdego pionka w ataku liczymy, ile pionków przeciwnika ma w zasięgu (im mniej tym lepiej)

*** 
1. Wystarczy policzyć piony i je od siebie odjąć, wynik przemnażamy przez jakiś współczynnik
2. algorytmem BFS znajdujemy nasze pionki na naszej połowie, gdy znajdziemy nasz pionek, to ustalamy, jak dużą formację obronną tworzy (np. bfsem poruszającym się tylko w pionie/poziomie)
ponadto ustalamy, czy nie tworzy formacji atakującej (siatki z dziurami, też bfs tylko ruchy na ukos)
3. algorytmem bfs ustalamy, jak duże są formacje atakujące (siatki nie muszą być z dziurami)
4. Odległość najbliższego naszego pinka od granicy przeciwnika, odległość pionka przeciwnika od naszej granicy. Obie liczby przemnożone przez jakieś współczynniki
5. oczywiste
6. oczywiste

Przez formację obronną rozumiemy pionki ułożone w linii poziomej lub pionowej, również tworzące blok.
![](https://i.imgur.com/htY72kN.png)

Przez formację ofensywną rozumiemy pionki ułożone na ukos względem siebie.
![](https://i.imgur.com/IwWaZS9.png)

## Zadanie 8

## Zadanie 9

Kółko i krzyżyk z buczeniem

Obserwacje:
* gracz który zaczyna pierwszy ma więcej (5) pól do zaznaczenia
* gracz który zaczyna pierwszy może szybciej wygrać

## Zadanie 10
