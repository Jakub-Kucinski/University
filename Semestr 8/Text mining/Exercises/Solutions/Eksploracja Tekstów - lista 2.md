# Eksploracja Tekstów - lista 2

###### tags: `et2021/2022` `ćwiczenia`

### Zadanie 1
![](https://i.imgur.com/DSi6H8c.png)
#### Metoda pierwsza
1. Czytamy wiersz po wierszu dane z bazy danych.
2. Piszemy na dysk pary (nr_pozycji,  indeksowany_term).
3. Sortujemy wg pozycji (np. poleceniem `sort`).
4. Termy z posortowanego pliku przepisujemy do kolekcji dokumentów (korzystając z faktu, że tam, gdzie jest przeskok o 2 między kolejnymi numerami pozycji, znajduje się początek kolejnego dokumentu).

#### Metoda druga
 - Sortujemy rosnąco każdy z indeksów
 - Tworzymy iterator dla każdego z indeksów
 - Bierzemy n takie, że w pamięci jesteśmy w stanie przechować n słów
 - upper_bound = n
 - Powtarzaj, dopóki każdy iterator ma jeszcze coś do przejścia:
 	- Dla każdego indeksu:
 		- Przeglądaj wskazywne przez jego iterator słowa, dopóki ich indeksy są mniejsze niż upper_bound
 		- Dla każdego z tych słów - zapisz je w przygotowanym miejscu, na odpowiednim indeksie
	- Zapisz gotowe n słów na dysk i przygotuj miejsce na nowe n słów
	- upper_bound += n
<!--  		- Jeśli któregoś z n kolejnych indeksów nie będzie (tzn mamy przeskok i nowy dokument) to upper_bound += 1 -->

### Zadanie 2
![](https://i.imgur.com/uEZJB3u.png)
![](https://i.imgur.com/KXCQbTL.png)
![](https://i.imgur.com/xwC1QlD.png)

Precyzja (precision) – jak wiele ze zwróconych dokumentów odpowiada potrzebie użytkownika
Zupełność, pokrycie, recall – jak wiele interesujących dokumentów z kolekcji udało się znaleźć.

a) **Stemming nigdy nie powoduje zmniejszenia precyzji.**
Nie prawda. Tokeny o różnych znaczeniach mogą mieć ten sam wynik stemmingu. To może powodować zmniejszenie precyzji.
b) **Stemming nigdy nie powoduje zmniejszenia kompletności.**
Prawda. Każdy wynik przy wyszukiwaniu dla dokładnych słów będzie również wynikiem dla wyszukiwania przy stemmingu. 
c) **Stemming zwiększa rozmiar słownika.**
Ogólnie nie musi, ale może się tak zdarzyć. Stemminng na pewno nie zwiększa (a może zmniejszyć) liczbę elementów słownika. Jednak wynik stemmingu może zajmować więcej pamięci (np. być dłuższym słowem) oraz liczba elementów słownika może pozostać niezmienna. Teoretycznie rozmiar słownika może się więc zwiększyć. 
d) **Stemming należy wykonywać w procesie indeksowania dokumentów, ale nie dla treści zapytania**
Stemming musi być wykonywany zarówno przy indeksowaniu jak i dla treści zapytania, aby móc wyszukać odopowiednie listy postingowe. 

### Zadanie 3
![](https://i.imgur.com/359FP5D.png)

**Rozważamy nieskompresowane listy postingowe. Wyjaśnij, jaką korzyść można uzyskać, umieszczając w pewnych miejscach takiej listy informacje o tym, że za K pozycji znajdzie się dokument o numerze N.**

Mamy dwie listy postingowe i chcielibyśmy zrobić ich przekrój. Jeśli korzystamy z metody analogicznej do łączenia fragmentów ciągów jak w merge sort to w przypadku połączenia słowa bardzo popularnego (mającego dużo rekordów w liście postingowej) i mało popularnego musielibyśmy przejść przez prawie całą długą listę np.

słowo_popularne: [1, 2, 3, 4, 15, ..., 572, 579]
słowo_mniej_popularne: [572, 984, 1024]

alternatywnie mielibyśmy:

słowo_popularne: [1, 2, 3 (za 500 rekordów występuje 572), 4, 15, ..., 572, 579]
słowo_mniej_popularne: [572, 984, 1024]

co pozwala znacząco skrócić czas szukania przecięcia
(z każdym takim przeskokiem zaoszczędzamy K porównań).

// W przypadku trzymania jedynie różnic między kolejnymi numerami dokumentów nie możemy skorzystać z algorytmu binsearch, dzięki takiej dodatkowej informacji jesteśmy jednak w stanie "skakać" między numerami dokumentów i nie musismy wyszukiwać informacji liniowo.

### Zadanie 4
![](https://i.imgur.com/BevoL9f.png)

#### Co jest nam potrzebne do stworzenia takiego słownika?
- potrzebujemy mieć informacje na jakich pozycjach zaczynają się następne dokumenty


#### Jak będziemy pamiętać dwupoziomowy indeks pozycyjny?
- lista krotek


    {
        słowo_1: [(nr_dokumentu_1, [pozycja_1, pozycja_2]),
                 (nr_dokumentu_2, [pozycja_1, pozycja_2, pozycja_3]),
                 ...,
                 (nr_dokumentu_n, [pozycja_1])],
        słowo_2: [(nr_dokumentu_1, [pozycja_1]),
                 (nr_dokumentu_2, [pozycja_1, pozycja_2]),
                 ...,
                 (nr_dokumentu_n, [pozycja_1, pozycja_2, pozycja_3])],
        ...
    }

#### Efektywność
- dla większej kompresji możemy pamiętać różnice między kolejnymi pozycjami w dokumencie zamiast pozycji

### Zadanie 5
![](https://i.imgur.com/92UII7x.png)

![](https://i.imgur.com/zXJM1vz.png)

Jeśli założymy, że nie modyfikujemy nigdy jednego fragmentu słowa dwukrotnie, to jest to zwykły ważony editdistance z dodanymi operacjami zamiany sąsiednich lub niesąsiednich liter. W przypadku zamiany niesąsiednich liter zakładamy ponadto, że tekst, który był między nimi, pozostaje bez zmian.

```python=
import numpy as np
import editdistance
from collections import defaultdict

def weighted_editdistance(w1, w2, weight=None):
    if weight is None:
        weight = dict()
    weight = defaultdict(lambda: 1, weight)
    len_w1, len_w2 = len(w1), len(w2)
    distance = np.zeros((len_w1 + 1, len_w2 + 1))
    w1 = " " + w1
    w2 = " " + w2

    distance[:, 0] = weight["del"] * np.arange(len_w1 + 1)
    distance[0, :] = weight["ins"] * np.arange(len_w2 + 1)
    
    for i in range(1, len_w1+1):
        for j in range(1, len_w2+1):
            distance[i, j] = min(distance[i-1, j] + weight["ins"], 
                                 distance[i, j-1] + weight["del"])
            
            distance[i, j] = min(distance[i, j], 
                                     distance[i-1, j-1] + weight["replace"] * (w1[i] != w2[j]))
                
            if i >= 2 and j >= 2 and w1[i] == w2[j-1] and w1[i-1] == w2[j]:
                distance[i, j] = min(distance[i, j],
                                     distance[i-2, j-2] + weight["ab->ba"])
            
            if i >= 3 and j >= 3 and w1[i] == w2[j-2] and w1[i-2] == w2[j]:
                distance[i, j] = min(distance[i, j],
                                     distance[i-3, j-3] + weight["abc->cba"])
    return distance[len_w1, len_w2]
```

Jeśli pozwolimy na modyfikację wielokrotną (np. najpierw wykonanie swap, a potem wstawiania), to sprawa się komplikuje, bo tracimy niezmiennik nieedytowania fragmentu wielokrotnie. Znalazłem jednak algorytm dla tego przypadku, ale tylko jeśli dopuścimy zamianę `xy -> yx`. Nazywa się "Damerau–Levenshtein distance", i poniżej jest implementacja:

<!-- 
```python=
def DLdistance(w1, w2, alphabet):
    n1, n2 = len(w1), len(w2)
    match_1 = { c: -1 for c in alphabet }
    maxdist = n1 + n2
    distance = zeros((n1 + 2, n2 + 2))

    distance[:, 0] += maxdist
    distance[:, 1] = arange(n1 + 2) # arange(n) = [0, 1, 2, ... n-1]
    distance[0, :] += maxdist
    distance[1, :] = arange(n2 + 2)
    
    for i in range(n1):
        match_2 = 0
        for j in range(n2):
            k = match_1[w2[j]]
            l = match_2
            if w1[i] == w2[j]:
                match_2 = j

            distance[i+2, j+2] = min(
                distance[i+1, j+2] + cost("addition"),
                distance[i+2, j+1] + cost("deletion"),
                distance[i+1, j+1] + cost("substitution") if w1[i] != w2[j] else distance[i+1, j+1],
                distance[k+1, l+1] + (i-k+1) + cost("transposition") + (j-l+1)
            )

        match_1[w1[i]] = i

    return distance[n1+1, n2+1]
```
 -->

```python=
 algorithm DL-distance is
    input: strings a[1..length(a)], b[1..length(b)]
    output: distance, integer
    
    da := new array of |Σ| integers
    for i := 1 to |Σ| inclusive do
        da[i] := 0
    
    let d[−1..length(a), −1..length(b)] be a 2-d array of integers, dimensions length(a)+2, length(b)+2
    // note that d has indices starting at −1, while a, b and da are one-indexed.
    
    maxdist := length(a) + length(b)
    d[−1, −1] := maxdist
    for i := 0 to length(a) inclusive do
        d[i, −1] := maxdist
        d[i, 0] := i
    for j := 0 to length(b) inclusive do
        d[−1, j] := maxdist
        d[0, j] := j
    
    for i := 1 to length(a) inclusive do
        db := 0
        for j := 1 to length(b) inclusive do
            k := da[b[j]]
            ℓ := db
            if a[i] = b[j] then
                cost := 0
                db := j
            else
                cost := 1
            d[i, j] := minimum(d[i−1, j−1] + cost,  //substitution
                               d[i,   j−1] + 1,     //insertion
                               d[i−1, j  ] + 1,     //deletion
                               d[k−1, ℓ−1] + (i−k−1) + 1 + (j-ℓ−1)) //transposition
        da[a[i]] := i
    return d[length(a), length(b)]
 ```
Złożoność: $O(n\cdot m)$. Zasada działania polega na fakcie, że istnieje pewna optymalna kolejność taka, że raz transponowane litery nie są potem modyfikowane (ten fakt zachodzi, jeśli koszt transpozycji jest równy co najmniej średniej kosztów wstawiania i usuwania) .


### Zadanie 6
![](https://i.imgur.com/rP32iHg.png)

![](https://i.imgur.com/xZQhIAV.png)
![](https://i.imgur.com/pTmU95Q.png)

#### Pierwsze rozwiązanie - mega wolne i wymagające pamięciowo ale działa
Dla danego słowa wygenerować wszystkie możliwe słowa za pomocą podanych przekształceń (do pewnej długości słów). Jeśli z dwóch słów można wygenerować taki sam wyraz, to je utożsamimy. Robimy przechodnie domknięcie. Ze zbioru utożsamionych słów wybieramy jednego reprezentanta. Pamiętamy jakie słowa utożsamiliśmy, może też wszystkie wygenerowane słowa. Przy korekcie typu non-word możemy rozpatrzyć wszystkie słowa należące do tego samego zbioru. Podobnie w błędach typu word, jeśli początkowe słowo nie pasuje do kontekstu.


#### Drugie rozwiązanie - chyba potencjalnie może się wyłożyć?
Aby otrzymać taką postać normalną dla danego słowa, wykonujemy trzy kroki:

1. zamieniamy polskie znaki na łacińskie (ą → a itp.);
2. unifikujemy niejednoznaczną ortografię;
3. unifikujemy sekwencje, które brzmią tak samo.

(Możliwe, że 3 musi być przed 1 i 2.)

Np. chrzołszcz → chrząszcz → chrzaszcz → hzaszcz

Jak taka postać może być użyteczna przy wykonywaniu korekty słowa?
Możemy korygować błędy non-word -- jeśli dany ciąg znaków nie jest słowem, to zamieniamy go na taką postać normalną i patrzymy, czy jakieś prawdziwe słowo też taką ma. Możemy też korygować błędy typu word, jeżeli słowa nie pasują do konekstu i jest prawdopodobne, że miało być inne słowo o tej samej formie.

### Zadanie 7
![](https://i.imgur.com/WWqskc9.png)

#### NYSIIS.
1.  Jeśli pierwsze litery nazwiska to:
* MAC -> zmień na MCC
* KN -> zmień na NN
* K -> zmień na C
* PH albo PF -> zmień na FF
* SCH -> zmień na SSS
2. Jeśli ostatnie litery to:
* EE bądź IE -> zmień na Y␢
* DT, RT, RD, NT, ND -> zmień na D␢
3. Pierwsza litara kodu to pierwszy znak nazwiska
4. Zaczynamy od drugiej litery. Powtarzamy dla wszystkich liter. Tylko jeden statement może zostać wykonany.
    a) Jeśli znak to spacja, to idź do j)
    b) Jeśli aktualna litera to E oraz kolejna to V -> zmień aktualną na A i koejną na F
    c) Jeśli aktualna litera to samogłoska -> zmień na 'A'
    d) Jeśli aktualna litera to Q -> zmień na G
    e) Jeśli aktualna litera to Z -> zmień na S
    f) Jeśli aktualna litera to M -> zmień na N
    g) Jeśli aktualna litera to K to:
        \> Jeśli kolejna litera to N to zamień K na N
        \> W.p.p na zamień na C
    h) Jeśli aktualna litera to początek SCH -> zmień je na SSS
    i) Jeśli aktualna litera to początek PH -> zmień je na FF 
    h) Jeśli aktualna litera to H i nie ma sąsiada który byłby samogłoską, to zamień H na poprzednią literę
    i) Jeśli aktualna literaz to W, i poprzednik to samogłoska, zastąp W poprzednikiem
    j) Jeśli nic z ww. nie można zastosować, to nie rób nic.
    
5. Jeśli litera na którą wskazuje ww. wskaźnik jest inna niż poprzednia litera w NYSIIS, dorzuć tę literę do kodu.
 Zwiększ wskaźnik i wróć do kroku 4 
<!--  (oczywiście nie nadpisując go 2-ką) -->
6. Jeśli ostatnia litera kodu to S -> usuń ją
7. Jeśli ostatnie dwie litery kodu to AY -> zmień na Y
8. Jeśli ostatnia litera to A -> usuń ją

Przykładowe konwersje
| przed | po |
|-------|----|
|Bishop    |      BASAP    |
|Carlson   |      CARLSAN  |
|Carr      |      CAR      |
|Chapman   |      CAPNAN   |
|Franklin  |      FRANCLAN |
|Greene    |      GRAN     |
|Harper    |      HARPAR   |
|Jacobs    |      JACAB    |
|Larson    |      LARSAN   |
(implementacje można znaleźć tutaj https://rosettacode.org/wiki/NYSIIS)

#### Metaphone
http://aspell.net/metaphone/
https://en.wikipedia.org/wiki/Metaphone

Udoskonala Soundex, wykorzystując informacje o odmianach i niespójnościach w pisowni i wymowie języka angielskiego w celu uzyskania dokładniejszego kodowania, które lepiej radzi sobie z dopasowywaniem słów i nazwisk brzmiących podobnie.
W oryginalnych kodach Metaphone użyto 16 symboli spółgłosek 0BFHJKLMNPRSTWXY. 0" reprezentuje "th" (jako ASCII przybliżenie Θ), "X" reprezentuje "sh" lub "ch", a pozostałe reprezentują ich zwykłą angielską wymowę. Używane są również samogłoski AEIOU, ale tylko na początku kodu. Tabela ta podsumowuje większość reguł w oryginalnej implementacji: 
1. Usuń duplikaty sąsiednich liter poza C.
2. Jeśli słowo zaczyna się od 'KN', 'GN', 'PN', 'AE', 'WR', usuwamy pierwszą literę.
3. Jeśli słowo kończy się na 'MB', usuń 'B'.
4. 'C' -> 'X' jeśli poprzedza 'IA' or 'H' (o ile nie jest częścią '-SCH-', wtedy -> 'K'). 
5. 'C' -> 'S' jeśli poprzedza 'I', 'E', or 'Y' wpp 'C' ->'K'.
6. 'D' -> 'J' jeśli poprzedza 'GE', 'GY', or 'GI' wpp. 'D' -> 'T'.
7. Usuń 'G' jeśli poprzedza 'H' i 'H' nie jest na końcu ani przed albo przed samogłoską. 
8. Usuń 'G' jeśli poprzedza 'N' albo 'NED' i jest na końcu słowa.
9. 'G' -> 'J' jeśli poprzedza 'I', 'E', or 'Y' i nie jest w 'GG' wpp. 'G' -> 'K'.
10. Usuń 'H' jeśli po i nie przed samogłoską.
11. 'CK' -> 'K'.
12. 'PH' -> 'F'.
13. 'Q' -> 'K'.
14. 'S' -> 'X' jeśli poprzedza 'H', 'IO', or 'IA'.
15. 'T' -> 'X' jeśli poprzedza 'IA' or 'IO'. 
16. 'TH' -> '0'. 
17. Usuń 'T' jeśli poprzedza 'CH'.
18. 'V' -> 'F'.
19. 'WH' -> 'W' jeśli na początku. Usuń 'W' jeśli nie przed samogłoską.
20. 'X' -> 'S' jeśli na początku, wpp. 'X' -> 'KS'.
21. Drop 'Y' jeśli nie przed samogłoską.
22. 'Z' -> 'S'.
23. Usuń wszystkie samogłoski poza samogłoską zaczynającą słowo.

.
1. Został zaprojektowany z myślą o regularnych, "słownikowych" słowach, a nie tylko nazwiskach.
2. Algorytmy Metaphone nie tworzą fonetycznych reprezentacji słów; wyniki są przybliżoną reprezentacją fonetyczną:
<!-- - słowa, które zaczynają się od samogłoski, będą miały literę "A", reprezentującą dowolną samogłoskę, jako pierwszy znak kodowania (w Double Metaphone i Metaphone 3 - oryginalny Metaphone zachowuje tylko rzeczywistą samogłoskę), -->
- samogłoski występujące po początkowym dźwięku samogłoski będą pomijane i nie będą kodowane, oraz
- pary spółgłosek dźwięcznych i bezdźwięcznych będą mapowane do tego samego kodowania. (Przykładami par dźwięcznych/niedźwięcznych spółgłosek są D/T, B/P, Z/S, G/K itd.).

Takie przybliżone kodowanie jest konieczne, aby uwzględnić sposób, w jaki użytkownicy języka angielskiego zmieniają swoją wymowę i błędnie wymawiają lub w inny sposób zmieniają słowa i nazwiska, które próbują przeliterować. Samogłoski, oczywiście, są notorycznie bardzo zmienne. Użytkownicy języka brytyjskiego często skarżą się, że Amerykanie wymawiają "T" tak samo jak "D". Należy również wziąć pod uwagę, że wszyscy użytkownicy języka angielskiego często wymawiają 'Z' tam, gdzie pisze się 'S', prawie zawsze, gdy rzeczownik kończący się na dźwięczną spółgłoskę, na przykład "seasons", "beams", "examples" itd. Niekodowanie samogłosek po początkowym dźwięku samogłoski pomoże pogrupować wyrazy, w których samogłoska i spółgłoska mogą być zamienione w błędnej pisowni lub alternatywnej wymowie. 


#### Testy różnych 
Performance Evaluation of Phonetic Matching Algorithms on English
Words and Street Names
Comparison and Correlation
Keerthi Koneru, Venkata Sai Venkatesh Pulla and Cihan Varol

### Zadanie 8
![](https://i.imgur.com/EEzZmoS.png)

Możemy przyjąć, że słownik = zbiór słów występujących w tytułach wikipediowych i liczyć odległość edycyjną pomiędzy wpisanym słowem, a wszystkimi słowami z tytułów wikipediowych. Słowo wpisane poprawiamy na słowo o najmniejszej odległości edycyjnej.
W przypadku, gdy kilka różnych słów z tytułów ma tą samą odległość edycyjną, możemy:
* sprawdzać zgodność pozostałych słów z zapytania z tytułami zawierającymi dane słowo,
* wybierać słowa, które występują w największej liczbie tytułów.

Alternatywnie:
Dla każdego słowa z zapytania liczymy odległości edycyjne ze słowami z tytułów. Dla K = 0, 1, 2, 3 zapamiętujemy listy numerów tytułów zawierających słowo oddalone o K. Wybieramy tytuł, z którym jest największa zgodność (najwięcej słów z zapytania jest oddalonych o K od pewnego słowa z danego tytułu) i poprawiamy słowa z zapytania na słowa występujące w znalezionym tytule.

### Zadanie 9
![](https://i.imgur.com/VQCNxHL.png)

Podczas wybierania optymalnej operacji dla danego podproblemu należy zapamiętać jaką operację się wybrało lub z którego stanu się przyszło. Zaczynając od ostatniej komórki jesteśmy w stanie odtworzyć ścieżkę. Potencjalnie może istnieć kilka równie dobrych wyborów. Możemy zapamiętywać jeden albo wszystkie. Przez to może istnieć wiele potencjalnych ścieżek.

```python=
import numpy as np
import editdistance
from collections import defaultdict

def weighted_editdistance(w1, w2, weight=None):
    if weight is None:
        weight = dict()
    weight = defaultdict(lambda: 1, weight)
    len_w1, len_w2 = len(w1), len(w2)
    distance = np.zeros((len_w1 + 1, len_w2 + 1))
    w1 = " " + w1
    w2 = " " + w2

    distance[:, 0] = weight["del"] * np.arange(len_w1 + 1)
    distance[0, :] = weight["ins"] * np.arange(len_w2 + 1)
    
    operations = [[None for i in range(len_w2 + 1)] for j in range(len_w1 + 1)]
    history = [[None for i in range(len_w2 + 1)] for j in range(len_w1 + 1)]
    
    for i in range(1, len_w1+1):
        for j in range(1, len_w2+1):
            distance[i, j] = distance[i-1, j] + weight["ins"]
            operations[i][j] = "insert" + " " + w1[i]
            history[i][j] = (i-1, j)
            
            value = distance[i, j-1] + weight["del"]
            if value < distance[i, j]:
                distance[i, j] = value
                operations[i][j] = "delete" + " " + w2[j]
                history[i][j] = (i, j-1)
            
            if w1[i] == w2[j]:
                value = distance[i-1, j-1]
                if value < distance[i, j]:
                    distance[i, j] = value
                    operations[i][j] = w1[i] + " equal " + w2[j]
                    history[i][j] = (i-1, j-1)
            else: 
                value = distance[i-1, j-1] + weight["replace"]
                if value < distance[i, j]:
                    distance[i, j] = value
                    operations[i][j] = "replace" + " " + w1[i] + " with " + w2[j]
                    history[i][j] = (i-1, j-1)

    path = []
    node = (len_w1, len_w2)
    while node is not None:
        path.append(operations[node[0]][node[1]])
        node = history[node[0]][node[1]]
    path.reverse()
    return distance[len_w1, len_w2], path[1:]


weighted_editdistance("kitten", "sitting")
(3.0,
 ['replace k with s',
  'i equal i',
  't equal t',
  't equal t',
  'replace e with i',
  'n equal n',
  'delete g'])
```

Algorytm ten mógłby być użyty do zbierania statystyk, które operacje częściej prowadzą optymalnie do celu, dzięki czemu moglibyśmy dostosować wagi operacji albo usunąć rzadko używane operacje.

### Zadanie 10
![](https://i.imgur.com/86PO1I2.png)
1. Patrzymy czy dla wystąpienia polskiego znaku diaktrycznego w poprawnym słowie występuje też on we wpisanym słowie (być może z dokładnością do jakiejś odległości np. 1, bo mogą być też inne błędy). Zliczamy ile razy znak nie wystąpił choć powinien i dzielimy przez liczbę wystąpień polskich znaków diaktrycznych. Potencjalnie moglibyśmy też uważać na sytuacje gdy mamy np. ał.łb oraz a.ł.b tzn każdy znak może być tylko raz związany z innym. Wystarczy chyba zawsze związywać z będącym najbardziej na lewo i pamiętać które są już zajęte.
2. Dla podwojonej literki we wpisanym słowie sprawdzamy czy w ustalonej odległości występuje ta sama podwojona literka w słowie poprawnym (jeśli mamy potrojenie itd to tylko jednego podwojenia nie zliczamy)
3. Podobnie jak wcześniej sprawdzamy czy ten wzorzec występuje w naszej parze (potencjalnie z pewnym przesunięciem). Możemy pozwalać lub zabraniać nakadania się wzorców.

Za koszty poszczególnych operacji można przyjąć odwrotności obliczonych częstości występowania (im coś częściej występuje tym mniejszy powinien być koszt operacji bo jest większa szansa że użytkownik w dany sposób się pomylił).

### Zadanie 11

#### Query "Jan Paweł II"
Snippet 1. Jan Paweł II – Wikipedia, wolna encyklopedia `Był trzecim najdłużej urzędującym papieżem w historii, po św. Piotrze (30–67) i Piusie IX (1846–1878), pierwszym papieżem z Polski oraz pierwszym spoza Włoch od ...` 
`Jan Paweł II był pierwszym papieżem z Polski, jak również pierwszym po 455 latach (od czasu pontyfikatu Hadriana VI) biskupem Rzymu niebędącym Włochem oraz ...`
~wikipedia
tytuł, kawałek z początkowego fragmentu artykułu, zdjęcie

Snippet 2. Jan Paweł II - Postacie | dzieje.pl - Historia Polski `Papież Jan Paweł II ... 16 października 1978 r. konklawe wybrało arcybiskupa i metropolitę Krakowa, 58-letniego kard. Karola Wojtyłę na papieża – 264. z kolei ...` ~dzieje.pl 
Tytuł + podpis zdjęcia + początek artykułu


Snippet 3. ŚWIĘTY JAN PAWEŁ II - Archidiecezja Krakowska `Po śmierci papieża Pawła VI i jego następcy Jana Pawła I w wyniku konklawe – 16 października 1978 roku abp Karol Wojtyła został wybrany papieżem przyjmując imię ...` ~diecezja.pl  
prefiks dalszego paragrafu artykułu

#### Query "układ fpga"

Snippet 1. Co to jest FPGA? - Extronic `FPGA (Field Programmable Gate Array) - złożone i bardzo zaawansowane. Przy pomocy FPGA można tworzyć własne procesory i bardzo zaawansowane układy. Na ogół nie ...` ~extronic.pl  
prefiks artykułu, zdjęcie

Snippet 2. Układy FPGA - Czy warto? Programowanie i zastosowanie `Czym właściwie są układy FPGA? Jak podaje Wikipedia – są to programowalne macierze bramek logicznych. Można je określić prościej: jako zbiór ...` ~botland.com.pl
Początek jedngo z pierwszych paragrafów, zdjęcie

Snippet 3. Bezpośrednio programowalna macierz bramek - Wikipedia `field-programmable gate array, FPGA) – rodzaj programowalnego układu logicznego. Dla projektanta ma funkcjonalność taką samą jak specjalizowany układ scalony, ...` ~wikipedia 
fragment pierwszego paragrafu artykułu, zdjęcie

#### Query "klasyfikacja i grupowanie tekstów"
Snippet 1. Klasyfikacja i predykcja - AGH `Grupowanie (klastrowanie) - obejmuje metody analizy danych i znajdowania skończonych zbiorów klas obiektów posiadających podobne cechy. W przeciwieństwie do metod klasyfikacji i predykcji, klasyfikacja obiektów (podział na klasy) nie jest znana a-priori, lecz jest celem metod grupowania.`~home.agh.edu.pl
fragment tekstu z początku prezentacji

Snippet 2. `Krokiem w klasyfikacji danych jest grupowanie lub analiza skupień (clustering). ○ Problem terminologiczny: w języku angielskim termin classify data.` ~jarekj.home.amu.edu.pl 
fragment tekstu z początku prezentacji

Snippet 3. Analiza skupień – Wikipedia, wolna encyklopedia `Analiza skupień jest metodą tzw. klasyfikacji bez nadzoru (ang. unsupervised learning). Jest to metoda dokonująca grupowania elementów we względnie ...`~wikipedia 
prefiks drugiego paragrafu



Algorytm tworzący ranking fragmentów mógłby wyglądać tak:
1. Jeśli dużo różnych termów z zapytania znajduje się w krótkim fragmencie tekstu, ten fragment jest dobrym kandydatem do wyświetlenia. Preferujemy sytuacje gdy wszystkie termy (myć może w innej formie) znajdują się w tym fragmencie. Premiujemy jeśli cała fraza występuje w zwartej formie (np. Jan Paweł II).
2. Jeśli w najlepszym znalezionym fragmencie brakuje niektórych termów z zapytania, szukamy najlepszego fragmentu zawierającego jak najwięcej brakujących termów.
3. Powtarzamy krok 2, do momentu aż przekroczymy limit długości snippetu lub w znalezionych fragmentach będziemy mieli już wszystkie termy wspólne dla zapytania i dokumentu lub dokument nie zawiera pozostałych termów.
4. Fragmenty tekstu wyświetlamy w kolejności, w jakiej znajdują się w dokumencie i łączymy je używając "...".

Uwaga: Algorytm wyznaczania snippetu pomija stopwords. (chociaż wyszukiwarka zdaje się nie pomijać ich całkowicie).
