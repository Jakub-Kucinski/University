# Eksploracja Tekstów - Lista 1
###### tags: `et2021/2022` `ćwiczenia`

## Zadanie 1
![](https://i.imgur.com/0MUcuPD.png)

### Przypomnienie z wykładu

Jak możemy szukać dokumentów zawierających dane słowa?
* Indeks odwrotny: słowa $\rightarrow$ indeksy dokmentów
Problem: Bardzo wiele kluczy i wiele sum zbiorów indeksów. 
* Lematyzacja słów przed użyciem indeksu odwrotnego.
Zaleta: mniej kluczy i mniej sum
### Rozwiązanie
* Wspólne stemowanie form bazowych (lematów) do wspólnej części, np. $\{wino, wina\}\rightarrow win$.
Problem 1: Niektóre lematy są zupełnie różne, np. gazociąg daje lematy gaz i ciągnąć, które nie mają nawet jednego wspólnego znaku. Pusta forma superbazowa - łamie założenie iii)
Problem 2: Weźmy słowa *winem* i *wina*. Dla pierwszego dostaniemy jeden lemat **wino**, a dla drugiego dostaniemy lematy **wino** i **wina**. Dla pierwszego najdłuższa wspólna część to ***wino***, a dla drugiego to ***win*** - łamie założenie ii)
* Domknięcie relacji lematów - Powiedzmy, że słowo **s1** ma lematy **l1** i **l2**. Wtedy mówimy, że **l1** i **l2** są w relacji. Robimy (przechodnie?) domknięcie tej relacji. W ten sposób zbiór wszystkich lematów zostaje podzielony na rozdzielne podzbiory. Każdy podzbiór możemy reprezentować przez zbiór lematów do niego należących (lub dowolny, ustalony element z tego zbioru). Zbiór lematów z jednego podzbioru (lub dowolny, ustalony element z tego podzbioru) to nasza forma superbazowa.

Czemu  może być użyteczna? Mamy mniejszy odwrotny indeks - mniej kluczy i mniej sum.


## Zadanie 2
![](https://i.imgur.com/HtH1ut6.png)

Dzięki Union-Findowi.

Tworzymy jednoelementowe zbiory ze wszystkich lematów. Dla każdego słowa przechodzimy przez jego lematy i na każdych kolejnych dwóch wykonujemy Union.

Na końcu dostajemy rozłączne zbiory będącymi naszymi formami superbazowymi
![](https://i.imgur.com/Yqa0ck7.png)



## Zadanie 3
![](https://i.imgur.com/4uCd5SH.png)

### a)
1. Zbieramy wszystkie słowa o tej samej formie bazowej.
2. Dla każdego słowa szukamy najdłuższej frazy wspólnej pośród pozostałych słów.
3. Z obu słów wycinamy najdłuższą frazę wspólną.
4. Pozostałe fragmenty traktujemy jako regułę: sufiks A $\rightarrow$ sufiks B.

### b)
1. Dla każdej pary wycinamy najdłuższą frazę wspólną.
2. Pozostałe fragmenty traktujemy jako regułę: dłuższy sufiks $\rightarrow$ krótszy sufiks.

Sprawdzanie użyteczności: 
Możemy testować ile razy znaleziona reguła wystąpiła w procesie. Reguły występujące więcej niż raz są potencjalnie użyteczne. Jest to szczególnie przydatne w podpunkcie a), gdzie będziemy mieli wiele form gramatycznych tego samego słowa.
Dla każdego słowa zaaplikować pasującą do niego regułę i zobaczyć czy powstanie poprawne słowo (należące do słownika).


## Zadanie 4
![](https://i.imgur.com/riubfgb.png)

Tokenizator minimalny - rozdzielamy słowa i interpunkcję. Oczywiście spełnia warunek z zadania.
Realizacja: Przed użyciem metody split() dodajemy przed każdym znakiem specjalnym dodatkową spację.
Kiedy warto łączyć mikrotokeny?
1. Zachowanie łączności nazwanych encji, np. czerwono-czarni, F-16,
2. Nazwy zawierające znaki specjalne, np. yahoo! - generowałoby !, który nie kończy zdania,
3. Zachowanie odmiany przez przypadki obcojęzycznych nazw, np. Charles’a de Gaulle’a, pendrive’a
4. Zachowanie wielokropka - trzy kropki po sobie.

## Zadanie 5
![](https://i.imgur.com/hrJq5eV.png)
Przykłady:
1. Artykuły Wikipedii często zawierają odwołania do innych tematów z dziedziny, które nie są bezpośrednio poruszone w danym artykule.
2. Może być trywialna miara odpowiedniości do zapytania.
3. Większa pewność, którego lematu tyczy się wystąpienie termu.

## Zadanie 6
![](https://i.imgur.com/sO8hizE.png)

I rozwiązanie:
Liczba wystąpień danego termu może pomóc określić jak „wartościowe” jest w danym dokumencie. Możemy obliczyć jaki ułamek ogólnej liczby termów stanowi wybrany term. Wartość możemy pamiętać jako cyfry po przecinku w systemie dwójkowym. Jeśli chcielibyśmy pamiętać tę wartość w pierwszym bajcie, to możemy przyjąć, że do zapisu wykorzystujemy 7 bitów a pierwszy bit będzie wykorzystany tak jak w zwykłym kodowaniu VB. Żeby uzyskać liczbę wystąpień wystarczy policzyć liczbę termów w dokumencie i pomnożyć przez zapamiętany ułamek.

II rozwiązanie:
Liczba wystąpień mogła by być kwantyfikowana do konkretnych wartości. Każdy kod w bajcie odpowiadałby konkretnemu przedziale wartości, z którego pochodzi liczba wystąpień danego termu w dokumencie. Zakładając, że mamy dostęp do dokumentów, można by spróbować wyznaczyć te przedziały w jakiś inteligentny sposób (np. żeby każdy przedział zawierał średnio tyle samo dokumentów). Nie jesteśmy w stanie odtworzyć dokładnej liczby, ale wiemy jakiego była rzędu.


## Zadanie 7
![](https://i.imgur.com/fpo30fc.png)
![](https://i.imgur.com/MKBxgs6.png)

http://informatyka.wroc.pl/node/1129
![](https://i.imgur.com/114PZPJ.png)

Trie jest to ukorzenione drzewo przeszukiwań przechowujące skończoną liczbę kluczy (słów). Klucz jest postaci $w=w_1w_2..w_m$, gdzie każde $w_i \in w$ jest literą należącą do ustalonego alfabetu $\Sigma$. Każdy węzeł zawiera listę krawędzi wychodzących etykietowanych literami alfabetu $\Sigma$. Każdy węzeł reprezentuje pewien fragment (prefiks) klucza/y. Istnieje krawędź $e$ z węzła $v$ do $u$ o etykiecie $c$, jeśli prefiks klucza reprezentowanego przez $v$ rozszerzony o literę $c$ również jest prefiksem dla pewnego klucza (niekoniecznie tego samego).



### a) 
1. Korzeń jest pustym napisem
2. Węzły, które odpowiadają poprawnym wyrazom, zawierają listy postingowe
3. Poddrzewo wybieramy w czasie stałym, bo mamy skończony alfabet, więc wystaczy odwołać sie do odpowiedniego elementu w tablicy
4. Możemy budować drzewo dynamicznie przechodząc po kolejnych słowach kolejnych dokumentów

### b)
1. Korzeń jest pustym napisem
2. Węzły, które odpowiadają frazom, zawierają listy postingowe
3. W węzłach trzymamy słowniki (może też drzewa trie albo tablice haszujące), żeby mieć szybki dostęp do kolejnych krawędzi wybierając dane słowo
4. Drzewo możemy budować albo na podstawie zbioru fraz, albo maksymalnie ustalonej długości


## Zadanie 8
![](https://i.imgur.com/zgNOXMR.png)
### a)
Przez zwykły indeks znajdujemy dokumenty zawierające pojedyncze słowa. Przeglądamy znalezione dokumenty odrzucając te, w których słowa z jednej frazy nie znajdują się obok siebie.

### b)
Indeks bigramowy - kluczami są pary słów. Dla każdej pary kolejnych słów z frazy znajdujemy dokumenty w których występuje i bierzemy przekrój tych dokumentów (może dawać false positive).

### c)
Indeks pozycyjny - traktujemy cały zbiór dokumentów jak jeden dokument. Dla każdego słowa mamy listę pozycji, na których występuje. Między dokumentami robimy mały skok numeracji wyrazów (wystarczy +1). Zapamiętujemy pozycje pierwszego słowa kolejnych dokumentów, wyszukujemy w nich binarnie, aby móc wyszukiwać numer dokumentu na podstawie pozycji słowa.

### d)
Indeks frazowy - mamy zbiór fraz z zewnętrznych źródeł. Dla każdej frazy zapamiętujemy dokumenty, które ją zawierają, używając drzewa trie.


Kombinacje:
1. Możemy połączyć indeks frazowy z dowolną inną metodą. Zapewne nie wszystkie frazy wpisane przez użytkowników będą w indeksie. Jeśli dana fraza jest w indeksie frazowym to zwracamy wynik z indeksu frazowego. W przeciwnym razie używamy alternatywnej metody.
2. Bigramowe, pozycyjny: dla fraz dłuższych od 2, robimy pozycyjny indeks bigramowy


## Zadanie 9
![](https://i.imgur.com/1uySR6o.png)
### Bez zmian w indeksowaniu
Przykład "Ala ma kota".
Musimy sumować przypadki:
- "Ala" jako pierwsze, pozostałe dwa na dowolnych z 9 pozostałych
- "ma" jako pierwsze, pozostałe dwa na dowolnych z 9 pozostałych
- "kota" jako pierwsze, pozostałe dwa na dowolnych z 9 pozostałych

### Zmiana procedury indeksowania
Dla każdego wystąpienia słowa dodajemy do listy pozycji K kolejnych pozycji np. jeśli konto wystąpiło na 10 miejscu to dodajemy liczby 10-19. Wtedy obsługa zapytania wygląda tak:
$index(Ala)\cap index(ma) \cap index(kota)$


## Zadanie 10
![](https://i.imgur.com/wRzxp81.png)



## Zadanie 11
![](https://i.imgur.com/ZcGWhLW.png)
Dokładnie to co w treści: Na początku mamy ciąg zer zakończonych jedynką. Długość tego ciągu określa liczbę bitów, w ilu będzie zapisana liczba. Następnie mamy zapisaną liczbę. Rozkodowywanie polega na wczytaniu ciągu zer zakończonego jedynką i odpowiadającej liczby zapisanej w systemie dwójkowym.


## Zadanie 12
![](https://i.imgur.com/IPOtcNR.png)
W kodowaniu z powyższego zadania potrzebujemy około $2 \log n$ bitów na zakodowanie liczby $n$.
Możemy pamiętać unarnie długość "długości". Wtedy nasze kodowanie składa się z dwóch części: unarne kodowanie długości "długości", binarne kodowanie długości, binarne kodowanie liczby.
Łączna liczba wymaganych bitów to około $2 \log \log n + \log n$.



