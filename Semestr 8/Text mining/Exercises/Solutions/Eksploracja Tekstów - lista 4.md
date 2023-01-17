# Eksploracja Tekstów - lista 4

###### tags: `et2021/2022` `ćwiczenia`



### Zadanie 1
![](https://i.imgur.com/Y8KA0ea.png)

a) Tworzymy słownik po odpowiednio sklejonym napisie odzielonym znakiem specjalnym (' ', '_'), lub po krotkach napisów.
	Następnie przeglądamy kolejne ngramy i zwiększamy odpowiadający im licznik

b) 
I Metoda:
Tworzymy słownik (dla n = 3):
```python
frequencies = {
    słowo_1: {słowo_2: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...},
              słowo_2a: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...}, 
              ...},
    słowo_1a: {słowo_2: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...},
              słowo_2a: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...}, 
              ...},
    ...
}
```
`frequencies['ala']['ma']['kota']` = liczba wystąpień n-gramu *"ala ma kota"*


II Metoda:
Indeksujemy dwustopniowo:
* 	tworzymy indeks wszyskich słów (napis -> id)
* 	indeks ngramu (krotka id-ików -> liczba wystąpień)

Być może możemy też odrzucic bardzo rzadkie słowa - jeżeli krotka zawiera bardzo rzadkie słów, to nie liczymy jej wystąpień

c) 
I Metoda:
Przepisujemy po kolei wszystkie n-gramy do pliku pomocniczego (każdy n-gram w osobnym wierszu) i sortujemy leksykograficznie (poleceniem *sort*). Zliczamy ile razy powtarza się każdy n-gram:
```bash
sort <file> | uniq -c
```

II Metoda:
Iterujemy po zbiorze słów:
* dla danego słowa wpisujemy do pamięci wszystkie n-gramy  zaczynające się od tego słowa, tzn. tworzymy w pamięci kawałek słownika z podpunktu **b)** (i zapisujemy go na dysk):
```python
{
    słowo_1: {słowo_2: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...},
              słowo_2a: {
                    słowo_3: liczba_wystąpień,
                    słowo_3a: liczba_wystąpień,
                    ...}, 
              ...}
}
```
Ta metoda wymaga wielokrotnego czytania pliku (dla każdego słowa czytamy cały plik w poszukiwaniu n-gramów zaczynających się od tego słowa).


III Metoda:
Wykonujemy dwa przejścia tekstu:
* W pierwszym tworzymy indeks pozycyjny każdego ze słów.
* W drugim przejściu przeglądamy ngramy zaczynające się na kolejnych pozycjach. Dla każdego z nich znajdujemy wszyskie wystąpienia tego ngramu (przecięcie przesuniętych zbiorów pozycji). Jeżeli nie jestes to pierwsze wystąpienie tego ngramu (istnieje mniejszy indeks) to pomijamy ten ngram. Gdy zaczyna nam brakować pamięci, to zapisujemy dotychczasowe wyniki na dysk, i kontynuujemy przeglądanie ngramów.


### Zadanie 2
![](https://i.imgur.com/7Wj8fb6.png)

Graf podkategorii nie musi być drzewem, ale powinien być skierowanym grafem acykliczny (nie jest drzewem, bo zdarzają się kategorie, które mają więcej niż jedną nadkategorię, np. kategoria "Teoria grafów" ma 2 nadkategorie: "Matematyka dyskretna" i "Kombinatoryka", przy czym "Kombinatoryka" ma nadkategorię "Matematyka dyskretna"). 

Sposoby wykorzystania do szukania podobnych dokumentów: 
- Dla danego dokumentu, możemy szukać dokumentów podobnych (np. metodą cosinusów) wśród "rodzeństwa", tzn. wśród dokumentów o wspólnych kategoriach.
- Możemy go wykorzystać do rozstrzygania remisów w innych metodach wyznaczania podobieństwa, np. premiując dokumenty wg "wysokości" najniższego wspólnego przodka (przez wysokość rozumiemy maksymalną odległość wierzchołka reprezentującego kategorię od wierzchołków reprezentujących dokumenty - "liści") - im mniejsza wysokość wspólnego przodka, tym lepiej - większa premia.


### Zadanie 3
![](https://i.imgur.com/RBYxN5j.png)

- Możemy szukać podobnych nazw kategorii: Jak jest wiele podobnych kategorii to zakładamy, że jest mniej fajnie np pochowani 45, więc będzie raczej 46,47,... itd. 
- Jeżeli w tytule jest coś co podejrzewamy że jest nazwą własną to (potencjalnie) może to być to mniej fajna kategoria (np. zabytki we Wrocławiu)
- Policzyć podobieństwo cossinusowe artykułów z kategorii i fajne są te kategorie które mają podobne artykuły - jeśli sporo artykułów jest podobnych do siebie, to zapewne pozostałe artykuły z tej kategorii też są w pewien sposób z nimi powiązane.


### Zadanie 4
![](https://i.imgur.com/zWgwV64.png)

Oprócz normalnego tworzenia par słów dla word2vec'a tworzymy też pary (tytuł, słowo), gdzie słowo jest słowem z artykułu o tytule z tej pary. Pewnie nie chcemy brać słów występujących w wielu artykułach jak stopwords itp więc moglibśmy słowa z artykułu wybierać np. za pomocą tf-idf.

2 opcja, w tekście co jakiś czas wrzucić tytuł.


### Zadanie 5
![](https://i.imgur.com/TbD2qpt.png)



### Zadanie 6
![](https://i.imgur.com/C0bq9Cw.png)

Scenariusz:
1. Dzielimy słowa na kawałki i wstawiamy je do tekstu zamiast (lub obok) słowa pierwotnego.
2. Uruchamiamy word2vec na tak zmodyfikowanym tekście.
3. Zanurzenie słowa = średnia zanurzeń kawałków.

W jaki sposób możemy podzielić słowo na kawałki?
* Bierzemy zbiór polskich prefiksów i sufiksów z jakiegoś źródła (lub szukamy sensownych prefiksów i sufiksów na podstawie statystyk ze słownika) i rozdzielamy słowo na prefiks + część środkowa + sufiks (jeśli słowo zawiera jakiś sensowny prefiks lub sufiks). Część środkową możemy próbować dzielić rekurencyjnie (dopóki będzie zawierała jakiś sensowny prefiks lub sufiks).
* Bierzemy wszystkie n-gramy do jakiejś długości włącznie (tak było w algorytmie fastText, bo miał być niezależny od języka, uniwersalny).

### Zadanie 7
![](https://i.imgur.com/aH1Q4vw.png)

* Odpowiadanie na pytania konkretnego typu np. "Jaka jest stolica Niemiec?" (wektor "ustoliczniania")
* Stopniowanie przymiotników
* Automatyzacja odmiany (np. "ukobiecanie zawodów")
* Generowanie potencjalnie ciekawych kategorii
* Antonimy(?)



### Zadanie 8
![](https://i.imgur.com/UUwDqcB.png)

Algorytm:
1. Oblicz odległości między sąsiednimi słowami
2. Połącz najbliższe słowa w nawias i ich wektor zastąp średnią obu z nich

Być może zamiast odległości od średniej to minimalna odległość od słów w nawiasie.


### Zadanie 9
![](https://i.imgur.com/lcdDtlm.png)

Tworzymy dwa dodatkowe korpusy:
1. W korpusie angielskim w losowych miejscach podmieniamy słowo angielskie na jego (losowe) tłumaczenie na język polski.
2. W korpusie polskim w losowych miejscach podmieniamy słowo polskie na jego (losowe) tłumaczenie na język angielski.
3. 
Na wymieszanych korpusach trenujemy Word2vec.