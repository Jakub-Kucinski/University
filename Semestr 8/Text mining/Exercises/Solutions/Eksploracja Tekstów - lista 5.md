# Eksploracja Tekstów - lista 5

###### tags: `et2021/2022` `ćwiczenia`


### Zadanie 1
![](https://i.imgur.com/eauY8vU.png)
PageRank - rozkład zdania
Węzły - słowa,
linki, jeśli są po sobie, lub ważone po zanurzeniach kontekstowych

Uruchamiamy Page Rank - dostajemy rangę
Zaczynamy rozbiór od najwyżej ważonych 

### Zadanie 2
![](https://i.imgur.com/dkGbAnR.png)

### K-means++

1. Wylosuj pierwsze centrum (prototyp) z rozkładem jednostajnym spośród punktów danych.
2. Dla każdego punktu danych $x$, oblicz $D(x)$ - odległość pomiędzy x a najbliższym centrum spośród dotychczas wyznaczonych.
3. Wylosuj kolejne centrum używając rozkładu prawdopodobieństwa, w którym prawdopodobieństwo wylosowania punktu $x$ jest proporcjonalne do $D(x)^2$.
4. Jeżeli liczba wyznaczonych centrów jest mniejsza od K, wróć do kroku 2.

#### Kaufman

1. Jako pierwsze centrum wybierz punkt znajdujący się najbliżej środka danych.
2. Dla każdego z niewybranych punktów $x_i$:
    2.1. Dla każdego z niewybranych punktów $x_j$ oblicz $C_{ji}$ = $max(D_j - d_{ji}, 0)$, gdzie $d_{ji}$ - odległość pomiędzy $x_i$ i $x_j$, a $D_j$ - odległość pomiędzy $x_j$ a najbliższym centrum.
    2.2. Oblicz $\sum_jC_{ji}$
3. Jako kolejne centrum wybierz $x_i$ maksymalizujące $\sum_jC_{ji}$
4. Jeżeli liczba wyznaczonych centrów jest mniejsza od K, wróć do kroku 2.


Metody inicjalizacji algorytmu k-means. 
- wybranie losowo pierwszego punku i wybieranie następnych jako nadalsze od najbliższego ze wszystkich poprzednich


### Zadanie 3
![](https://i.imgur.com/XcARIho.png)

Język: Python + Scipy (moduł `scipy.sparse`)

Sposoby (do wyboru):

- Dictionary of keys (DOK)
    Słownik, gdzie kluczem jest krotka z indeksami, a wartością -- wartość.
    Zalety: szybki dostęp, szybka konstrukcja
    Wady: wolna iteracja (w porządku leksykograficznym), wolna arytmetyka
- List of list (LIL)
    Dwie tablice list -- jedna (`rows`) zawiera indeksy, druga (`data`) wartości.
    Zalety: szybkie dodawanie wartości, szybka konwersja na csr/csc, szybkie sliceowanie wierszy
    Wady: pamięć, wolna arytmetyka, wolne sliceowanie kolumn
    TODO: czy rzędy są w kolejności?
- Coordinate list (COO)
    Trzy tablice (dla macierzy) -- jedna na wartość, dwie na indeksy.
    Zalety: szybkie dodawanie wartości, szybkie operacje na elementach, pozwala na , bardzo szybka konwersja na csr/csc
    Wady: wolny dostęp, wolna arytmetyka
- Compressed Sparse Row/Column (CSR/CSC)
    Trzy tablice (objaśnienia dla CSR):
    
    - `data` -- wartości w porządku rzędowym (row-major)
    - `indptr` -- wskaźniki, gdzie zaczyna się który rząd
    - `indices` -- indeksy kolumn
    
    Zalety: szybka arytmetyka
    Wady: wolne edytowanie
![](https://i.imgur.com/Q11UwaA.png)

Przeglądowe źródło: https://rushter.com/blog/scipy-sparse-matrices

### Zadanie 4
![](https://i.imgur.com/nTHZj9b.png)

**a) Znaczenia słowa skóra**
Skóra ma 7 znaczeń:
* surowiec, materiał do szycia różnych rzeczy, otrzymywany z okryw zewnętrznych zwierząt, 
* zewnętrzna otoczka, powłoka czegoś, 
* powłoka ciał zwierząt i ludzi,
* życie, zdrowie, bezpieczeństwo, własny interes, coś, co człowiek ma najcenniejszego (ocalić własną skórę)
* przenośnie: rola, charakter (wejść w czyjąś skórę)
* wierzchnie okrycie (najczęściej kurtka lub płaszcz) ze skóry
* cecha kogoś lub czegoś, która jest wyraźna, widoczna, a, często, przysłania coś innego

**b) Hiperonimy** 
 hiperonim -- słowo ogólniejsze (ptak jest hiperonimem dla wróbel). W zależności od znaczenia dla skóry są to:
* surowiec1
* okrywa1, powłoka2
* organ3, powłoka2 
* rzecz oceniana pozytywnie1
* funkcja2
* okrycie4
* właściwość1

Łącznie 8, czyli o 1 więcej niż znaczeń.

**c) Fuzzynimia** 
**Fuzzynimia** to relacja znaczeniowa silna, lecz wynikająca nie bezpośrednio ze znaczeń wyrazów, ale z jakiejś sytuacji, np. sekwencji przyczynowo-skutkowej, której dotyczą, i z tego powodu trudna do sklasyfikowania (niesystemowa).

Relacja łącząca dwa dowolne znaczenia, mówiąca o tym, że istnieje pomiędzy nimi jakiś (nieokreślony) związek znaczeniowy.

* miauczeć - kot
* informatyka - program
* informatyka - baza danych


**d) Derywaty i deminutywy** 
 derywytyw -- wyraz pochodny np. ekoskóra od skóra, farmakologiczny od farmakologia
 deminutywa -- zdrobnienie -- kotek od kot, skórka od skóra


### Zadanie 5
![](https://i.imgur.com/iHBHP3R.png)

Słowosieć (z relacją is_a) nie jest drzewem (jest DAGiem), ponieważ jeden leksem może mieć więcej niż jeden hiperonim (czyli więcej niż jednego rodzica), np. ***zamek/1*** (*warowna budowla mieszkalna, rezydencja pana, króla, księcia lub magnata*) ma **2 hiperonimy**: 
* rezydencja/1
* budowla obronna/1

Oczywiście, jeden hiperonim może mieć wiele hiponimów, np. hiperonim *zamknięcie/12* ma następujące hiponimy: 
* zasuwa/1
* kapsel/1
* okiennica/1
* nakrętka/2
* kłódka/1
* zatyczka/1
* zawór/1
* zapięcie/2
* zamek/2

Ścieżki do najwyższego hiperonimu dla leksemu ***zamek/2*** (*mechanizm lub urządzenie do zamykania np. drzwi, szuflad, walizek*):
1. zamek/2 -> zamknięcie/12 -> przedmiot/1 -> rzecz/4 -> obiekt/2 -> coś/1
2. zamek/2 -> zamknięcie/12 -> mechanizm/2 -> zespół urządzeń/1 -> zespół/1 -> zbiór/1 -> ogół/1


### Zadanie 6
![](https://i.imgur.com/Z1CA8p8.png)

Mianem meronimu określa się część składową lub fragment większej całości. Tak więc, *X jest meronimem Y jeśli X(-y) są częściami lub członami Y(-ów)*

Stąd przeciwieństwem meronimu jest **holonim (holonimia)**, oznaczający całość złożoną z pewnych części, np. *samochód w stosunku do wyrazu koło*

* **Jakie są rodzaje meronimii (relacji is_a_part_of)?**

1. części (klawisz → klawiatura)
2. element kolekcji (członek → organizacja, uczeń → klasa)
3. miejsca (leśniczówka → las, stolica → kraj)
4. porcji (kropla → płyn)
5. materiału (kord → opona) 
rodzaj tkaniny sztucznej (z włókien szklanych, innych chemicznych, nawet drutów) używanej do wzmacniania opon
6. taksonomiczna (zwierzę → zwierzęta)


### Zadanie 7
![](https://i.imgur.com/tDAnlVV.png)

1. Wykorzystanie hiperonimów:
* lematyzacja hiperonimami
* jeśli w tekście padło słowo "jamnik" możemy również policzyć, że padło słowo "pies"
2. Wykorzystanie synonimów 
* losowa zamiana słów z dokumentów na ich synonimy
* utożsamianie synonimów w dokumentach (np. zamiana na jeden wybrany - słabe bo jedno słowo może mieć wiele znaczeń i różne synonimy)
* jeśli dane słowo występuje w dokumencie, to dodajemy też wystąpienie do jego synonimów (można próbować wyznaczyć znaczenie danego słowa na podstawie kontekstu i dodać tylko do określonej grupy synonimów)
* szukanie artykułów, ze słowami które są synonimami słów z wejściowego dokumentu
