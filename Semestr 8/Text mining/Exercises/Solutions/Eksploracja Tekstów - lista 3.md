# Eksploracja Tekstów - lista 3

###### tags: `et2021/2022` `ćwiczenia`

## Zadanie 1
![](https://i.imgur.com/Hk6PBTH.png)

1. Patrzymy czy dla wystąpienia polskiego znaku diaktrycznego w poprawnym słowie występuje też on we wpisanym słowie (być może z dokładnością do jakiejś odległości np. 1, bo mogą być też inne błędy). Zliczamy ile razy znak nie wystąpił choć powinien i dzielimy przez liczbę wystąpień polskich znaków diaktrycznych. Potencjalnie moglibyśmy też uważać na sytuacje gdy mamy np. ał.łb oraz a.ł.b tzn każdy znak może być tylko raz związany z innym. Wystarczy chyba zawsze związywać z będącym najbardziej na lewo i pamiętać które są już zajęte.
2. Dla podwojonej literki we wpisanym słowie sprawdzamy czy w ustalonej odległości występuje ta sama podwojona literka w słowie poprawnym (jeśli mamy potrojenie itd to tylko jednego podwojenia nie zliczamy)
3. Podobnie jak wcześniej sprawdzamy czy ten wzorzec występuje w naszej parze (potencjalnie z pewnym przesunięciem). Możemy pozwalać lub zabraniać nakadania się wzorców.

Za koszty poszczególnych operacji można przyjąć odwrotności obliczonych częstości występowania (im coś częściej występuje tym mniejszy powinien być koszt operacji bo jest większa szansa że użytkownik w dany sposób się pomylił).
## Zadanie 2
![](https://i.imgur.com/P1Sneds.png)

zimny ***dzień*** (z przymiotnikiem)
liceum ***ekonomiczne*** (z przymiotnikiem za rzeczownikiem)
ten ***chłopiec*** (z zaimkiem)
za ***stołem*** (z przyimkiem)
robić ***obiad*** (z czasownikiem)
posiadanie ***kota*** (z rzeczownikiem odczasownikowym)
lub ***sól*** (ze spójnikiem)
trzy ***łyżki*** (z liczebnikiem)
tylko ***talerz*** (z partykułą)
***kobieta*** pracująca - rzeczownik + imiesłów przymiotnikowy
***lekarz*** stomatolog - rzeczownik + rzeczownik
***uczucie*** izolacji - rzeczownik + rzeczownik w dopełniaczu
moja ***siostra*** - zaimek dzierżawczy + rzeczownik
Och ***ty***
***Henryk*** VIII
***Fiat*** 125p
5 ***samochodów***

## Zadanie 3
![](https://i.imgur.com/ZByQSHI.png)
https://wiki.python.org/moin/TimeComplexity

Średni czas działania operacji na set():
 * s.union(t) 				=> O(len(s) + len(t))
 * s.intersection(t) 		=> O(min(len(s), len(t)))
 * s.difference(t) 		=> O(len(s))
 * s.difference_update(t) 	=> O(len(t))

Mamy wejście +s1, +s2, +s3, ..., +sn, -t1, -t2, -t3, ..., -tm
Mamy kilka możliwych podejść:
 
 0. s = s1 & s2 & ... & sn. dla kolejnych i: s \ ti.
 Przy czym przed każdym odejmowaniem patrzymy na len(s) i len(ti) w O(1) i wybieramy odpowiednie difference lub difference_update. Taki wybierany set difference jest O(min(len(s), len(ti))). Czyli na koniec mamy ciąg operacji o koszcie O(min(len(coś_prawdopodobnie_małego), len(si lub ti))).
 Worst case: si=sj, ti&sj=0 oraz len(si)=len(tj). len(si)*(n+m)


 1. Bierzemy t = t1 | t2 | ... | tm, s = s1 & s2 & ... & sn. 
     Następnie zwracamy s\t.
        Złożoność: max(si)*n + sum(ti) + sum(ti)

 2. Bierzemy sumę t = t1 | t2 | ... | tm. 
      Odejmujemy je od każdego si: si' = si \ t. 
      Zwracamy przecięcie wszystkich si': s1' & s2' & ... & sn'
      Złożoność - zależna od tego czy użyjemy różnicy w miejscu, czy z tworzeniem nowego set-u():
				* dla zwykłej róźnicy: sum(ti) + sum(ti)*n + max(si')*n
				* dla różnicy w miejscu: sum(ti) + sum(si) + max(si')*n

 3. Bierzemy przecięcie s = s1 & s2 & ... & sm. 
      Odejmujemy od niego kolejne ti': r0 = s, ri = r{i-1} / ti
      Złożoność - zależna od tego czy użyjemy różnicy w miejscu, czy z tworzeniem nowego set-u():
				* dla zwykłej róźnicy: max(si)*n + max(si)*m
				* dla różnicy w miejscu: max(si)*n + sum(ti)

Użytkownik najczęściej będzie szukał więcej róźnych si niż ti. Dodatkowo ti będą zwykle bardziej specjalistycznymi terminami.
Zatem możemy założyć n>m oraz dla każdego i,j si > tj.
Przy takich załoźeniach, najlepszym tozwiązaniem wydaje się być podejście 3) z róźnicą w miejscu.


## Zadanie 4
![](https://i.imgur.com/kUetLIW.png)

Załóżmy, że mamy zaimplementowaną wyszukiwarkę bazującą na zwykłym _proximity search_ (czyli znajdującą dokumenty, w których termy z zapytania mieszczą się w oknie o wielkości $k$). Jak wykorzystując ten mechanizm zaimplementować wyszukiwarkę, która:

a) Znajduje dokumenty, w których wszystkie termy z zapytania są w jednym zdaniu.

Dysponujemy $W(k)$ -- wyszukiwarką bazującą na _proximity search_ z oknem wielkości $k$.

Indeksując naszą kolekcję dokumentów, ustalamy długość najdłuższego zdania w tej kolekcji, po czym ustawiamy $k$ na tą wartość. Następnie stawiamy między wszystkimi zdaniami $k$ pustych znaków odstępu -- w ten sposób $W$ znajdzie tylko dokumenty, w którym szukane termy są w jednym zdaniu, bo pozostałe zdania będą poza oknem.

b) Znajduje dokumenty, w których premiowana jest obecność wszystkich termów w jednym wątku dokumentu (czyli spójnym kawałku na 1 temat).

Zakładamy że wynikiem zapytania proximity search są dokumenty i początki okien w których występują wszystkie termy (jeśli implementacja za pomocą indeksu pozycyjnego jak na pierwszej liście). 

Jak zmieniamy wątek to wstawiamy znacznik zmiany wątku. Aby wykonać otrzymać wynik z zakresu jednego wątku wykonujemy zapytanie bez znacznika i od wyniku odejmujemy wynik zapytania ze znacznikiem. (ciche założenie że wątki nie są zbyt krótkie, jeśli są krótkie to może wydłużyć kropkami).

<!-- Podczas indeksowania kolekcji wstawiamy znaczniki ^ i $ na początku i końcu każdego wątku, po czym wykonujemy zapytanie, dorzucając do niego termy ^ i $. Wtedy premiowane będą wyniki zawierające początek wątku, termy z zapytania i koniec wątku w ramach jednego wątku.
 -->
## Zadanie 5
![](https://i.imgur.com/tztm5vm.png)

Dla głównego przypadku z jedną \*. Na wejściu dostajemy zapytanie *w1\*w2*. Wtedy w drzewie trie idziemy po ścieżce *w2\$w1* i otrzymujemy całe poddrzewo, które jest poprawnym wypełneieniem * (zgadza się prefiks i sufiks).

Przykład:
Wkładamy do drzewa słowa *krowa* i *krówka* w postaci *\$krowa, a\$krow, wa\$kro, owa\$kr, rowa\$k* oraz *\$krówka, a\$krówk, ka\$krów, wka\$kró, ówka\$kr, rówka$k*.
Sprawdzamy zapytanie **kr\*a**, co tłumaczymy jako **a\$kr**, co wpasowuje się w *a\$krow* oraz *a\$krówk*.

W przypadku zapytania *w1\*w2\*w3*. Zaczynamy od wyszukania *w3\$w1*, co odpowiada zapytaniu *w1\*w3*, następnie zgadujemy tylką jedną gwiazdkę, bo jesteśmy już w dobrym przedziale. Problem sprowadza się do tego jak w wersji klasycznej.

## Zadanie 6
![](https://i.imgur.com/92iahfq.png)

Chcemy wyznaczyć poprawne słowa o określonej (lub mniejszej równej) odległości edycyjnego od ustalonego $w$. 

***Rozwiązanie brutalne*** - przeszukać całą przestrzeń słów (np. rekurencyjnie jak przy rozwiązaniu dynamicznym bez spamiętywania) i wybrać poprawne słowa

***Problem*** - bardzo trudno ograniczyć tą przestrzeń

***Rozwiązanie z drzewem trie***
Wykonujemy podobny backtracking jak brutalnie, z tym że pamiętamy również pozycję naszego zmodyfikowanego słowa (prefiksu $w$ z jakimiś zmianami) w drzewie trie. Przy przedłużaniu słowa (dodaniu operacji edycyjnych lub odpowiadającej literki z $w$) przesuwamy się odpowiednią krawędzią w drzewie trie. 

***Co nam to daje?***
Jeżeli dojdziemy do prefiksu w którego poddrzewie nie ma żadnego poprawnego słowa możemy od razu przestać patrzeć na ten prefiks. 

## Zadanie 7
![](https://i.imgur.com/wFxPn6g.png)

Żeby znaleźć średnie podpobieństwo cosinusowe do klasy musimy policzyć podobieństwo cosinusowe ze wszystkimi elementami danej klasy, więc jeśli $m$ jest liczbą wektorów we wszystkich klasach a $n$ wymiarem wektora, złożoność to $O(m\cdot n)$.


<!-- Niech $x = (x_1, x_2, ..., x_n)$ będzie wektorem dokumentu $X$, natomiast $y^i = (y_1^i, y_2^i, ..., y_n^i)$ dla $i=1...k$ będą wektorami pewnej klasy. Ponadto niech $\bar{y}^i_j$ będzie $j$-tą współrzędną $i$-tego **unormowanego** wektora danej klasy ($\bar{y}^i_j=\frac{y^i_j}{|y^i|}$). Wówczas średnie podobieństwo cosinusowe to: -->

<!-- $$
\frac{1}{k}\sum_{i=1}^k\frac{y^i\cdot x}{|y^i|\cdot|x|} = \frac{1}{k\cdot|x|} \sum_{i=1}^k \sum_{j=1}^n \bar{y}^i_jx_j = \frac{1}{k\cdot|x|}\sum_{j=1}^n \sum_{i=1}^k \bar{y}^i_jx_j = \frac{1}{|x|} \sum_{j=1}^n \left( \frac{1}{k} \sum_{i=1}^k \bar{y}^i_j \right)x_j
$$
 -->
$$
\frac{1}{|Y|}\sum_{y\in Y} \frac{y \circ x}{|x||y|} = \frac{1}{|Y|}\sum_{y\in Y} \sum_i \frac{y_i \cdot x_i}{|x||y|} = \frac{1}{|Y||x|} \sum_i \sum_{y\in Y} \frac{y_i \cdot x_i}{|y|} = \frac{1}{|x|} \sum_i x_i \frac{1}{|Y|} \sum_{y\in Y} \frac{y_i}{|y|}
$$
$$
\frac{1}{|x|} \sum_i x_i \cdot \textrm{Avg_claster_vector}_i = \frac{x \circ \textrm{Avg_claster_vector}}{|x|}
$$

$|x|$ jest nie istotne bo dla każdego klastra jest to samo

Więc jeśli wyliczymy wcześniej centrum klasy (czyli wektor będący unormalizowaną średnią wektorów klasy), to wystarczy policzyć podobieństwo cosinusowe do centrum, by otrzymać średnie podobieństwo cosinusowe do wektorów klasy. Nie musimy wtedy liczyć podobieństwa cosinusowego ze wszystkimi $m$ wektorami, a jedynie z $K$ wyliczonymi wcześniej (gdzie $K$ jest liczbą klas), stąd złożoność: $O(K\cdot n)$



## Zadanie 9
![](https://i.imgur.com/qYb5xRF.png)


Source: https://fribbels.github.io/vptree/writeup

Struktura Vantage Point Trees służy do rozwiązywania problemów związanych z podziałem przestrzeni i efektywnym odpowiadaniu na zadane o nią pytania. Drzewa VP to w szczególności drzewa metryczne, które są drzewami zdolnymi do skutecznego dzielenia danych w n-wymiarowej przestrzeni.

Ich zaletą jest wykonywanie zapytań o zakres w zbiorze danych, na przykład wyszukiwanie najbliższego sąsiada.

Opis struktury:

W każdym węźle drzewa VP przechowujemy następujące informacje:
- data: lista punktów należących do podprzestrzeni
- vp: punkt obserwacyjny (vantage point)
- mu: promień "widoczności" (dobierany tak, żeby podzielić zbiór na ok połowę)
- inside: punkty leżące w promieniu (lewe poddrzewo)
- outside: punkty leżące poza promieniem (prawe poddrzewo)

Złożoność zbudowania: $O(n \log{(n)})$

Ilustracja działania:

![](https://i.imgur.com/6Ai7LhY.png)

---

![](https://i.imgur.com/0mwtueT.png)

---

![](https://i.imgur.com/9zzTPqk.png)

---

![](https://i.imgur.com/DCLLLZp.png)


Wyszukiwanie najbliższych sąsiadów odbywa się rekurencyjnie.

Załóżmy, że pytamy o najbliższego sąsiada punktu x. Jeśli odległość d punktu x od vantage point v jest mniejsza niż promień "mu" to szukamy w poddrzewie z punktami wewnątrz okręgu. Jeśli wynik rekurencyjnych wywołań zwróci nam punkt, do którego odległość jest mniejsza niż mu-d to nie musimy sprawdzać punktów na zewnątrz i kończymy. Wpp wywołujemy się dla zewnętrznego poddrzewa i porównujemy wyniki.

Jeśli wyszukujemy kilku najbliższych to analogicznie, z tym że w zewnętrznym poddrzewie szukamy tylko tyle punktów ile wykraczało poza mu-d.
