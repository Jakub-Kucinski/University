# Sztuczna inteligencja - ćwiczenia 4
###### tags: `si2020/2021` `ćwiczenia`
## Zadanie 1
### a)
Ocaniając dany stan w funkcji heurystycznej możemy do jej wyniku dodać liczbę naszych pól bezpiecznych pomnożonych przez wybraną wagę oraz odjąć liczbę pól bezpiecznych przeciwnika pomnożonych przez wybraną wagę.

### b)
Pole z pionkiem jest bezpiczene wtw. gdy dla każdego możliwego dokończenia gry dane pole nie zmieniłoby koloru w żadnej z tych rozgrywek.

Zatem "wystarczy" przejść przez wszystkich potomków danego ustawienia w drzewie gry.

### c)
Konstruktywna propozycja:
Można zauważyć, że każde pole leży na czterech przekątnych. Każdą przekątną dzielimy na dwie części oddzielone od siebie przez pole. Pole jest bezpieczne, jeśli co najmniej jedna część z każdej przekątnej składa się z pól, na których nigdy nie będą mogły się znaleźć pionki przeciwnego koloru.
W praktyce możemy wymagać, aby te zapewniające bezpieczeństwo części ze sobą sąsiadowały.
![](https://i.imgur.com/7Y5uJ8S.png)

Możemy to sprawdzać poprzez sprawdzanie, jak duże konstrukcje z czarnych pól możemy umieścić zaczynając od każdego z rogów najpierw w orientacji poziomej a później pionowej. Czyli mielibyśmy osiem takich sytuacji:
![](https://i.imgur.com/D1yXkG8.png)

W ten sposób możemy przyśpieszać sprawdzanie:
![](https://i.imgur.com/lx1rXej.png)



## Zadanie 2

### a)

Możliwy stan gry oznacza losowanie takich stanów, że np.:
- karty wykorzystane do losowania nie zostały jeszcze zagrane
- dane ustawienie jest możliwe przy aktualnym stanie rozgrywki
- na podstawie naszych kart (naszej wiedzy), możemy wykorzystać wiedzę, jakie karty ma przeciwnik
- możemy wykorzystać wiedzę z przeszłych zagrań, np. przeciwnik nie miał karty do koloru

### b)
Np. na podstawie licytacji i naszych kart możemy wiedzieć (np. brydż) lub przewidywać (np. tysiąc), które ustawienia są bardziej prawdopodobne. Podobnie z rozgrywki gry możemy podejrzewać, że w pewnych sytuacjach jakby przeciwnik miał daną kartę, to by ją zagrał.

Problem jest taki, że poprzez nierównomierny rozkład możemy faworyzować pewien ruch, który może okazać się ekstremalnie nieoptymalny w nieco rzadszym układzie.

Przy jednostajnym rozkładzie częściej podejmowalibyśmy nieoptymalne decyzje, które byśmy podejmowali o wiele rzadziej w przypadku niejednakowych prawdopodobieństw.


### c)
Pomijane jest "ludzkie" zachowanie pozostałych graczy:
- możliwość popełniania błędów
- udawanie, że ma się lepsze karty
- zachowanie wynikające z emocji, intuicji i niedawnych doświadczeń

## Zadanie 3

- agent losowy z ulepszeniami
Agent chce sprawdzać, gdy po swoich kartach widzi, że deklaracja gracza poprzedniego nie była prawdziwa (np. powiedział: dwie szóstki, a my mamy trzy szóstki).
Agent mniej boi się kłamać, gdy ma zadeklarowane karty, tzn. rzucił dwójkę i trójkę, powiedział dwie siódemki, ma na ręce dwie siódemki, więc małe są sznase, że ktoś mu zarzuci nieprawdę
- agent, który kłamie dużo na początku, ale na końcu woli mówić prawdę
Prawdopodobieństwo skłamania może maleć z liczbą kart znajdujących sie na stole.
Oczywiście agent kłamie, gdy mu się to opłaca, tzn. nie rzuca lepszych kart, mówiąc, że są gorsze.


## Zadanie 4
### a)
![](https://i.imgur.com/wm5EGeE.png)
$x_1x_2$ podane w featurach.
![](https://i.imgur.com/xtvS72p.png)
Zwykła prosta oddziela klasy.
![](https://i.imgur.com/uM9p1aJ.png)
$x_1^2 + x_2^2 - r^2 = 0$

### b) 
Nie zbiegnie do żadnego rozwiązania / będzie oscylować / nie da żadnego sensownego rozwiązania.

### c)
W sumie da się w każdym bez.
![](https://i.imgur.com/9Zw6klZ.png)

### d)
![](https://i.imgur.com/mzISGwh.png)
![](https://i.imgur.com/CopHp8W.png)
![](https://i.imgur.com/JowxbIp.png)



## Zadanie 5
### a)
![](https://i.imgur.com/ofWk4Br.png)

### b,c)
![](https://i.imgur.com/IjUzsK7.png)


## Zadanie 6

Za pomocą sieci neuronowych można wyrazić dowolną funkcję boolowską, ponieważ w poprzednim zadaniu pokazaliśmy, jak wygląda koniunkcja i negacja, a koniunkcja i negacja tworzą zupełny zbiór spójników logicznych. Przedstawienie bardziej skomplikowanych formuł polega na budowaniu większych sieci, których neurony dalej będą wykonywać koniunkcję/alternatywę.

Minimalna liczba warstw, która wystarcza, to dwie, ponieważ każdą formułę boolowską można przedstawić w CNF (koniunkcyjna postać normalna). Pierwsza warstwa będzie wykonywać alternatywy a druga warstwa będzie wykonywać koniunkcję wszystkich klauzul. Negacje mogą być "wciągnięte" do alternatywy.

## Zadanie 7


## Zadanie 8

Nadracjonalność polega na tym, że gracz gra najbardziej optymalną strategią biorącą pod uwagę fakt, że każdy inny gracz jest nadracjonalny, czyli wszyscy gracze grają taką samą strategią.
Przy ustalaniu strategii gracz nadracjonalny zakłada, że wszyscy inni gracze są nadracjonalni i będą mieli taką samą strategię.

## Zadanie 9

Dla N graczy grających w grę ze strategiami $A_1$, $\ldots$, $A_N$ punkt równowagi Nasha polega na tym, że strategia $i$-tego gracza jest optymalna przy założeniu, że pozostali gracze grają swoimi strategiami (każda zmiana strategii $i$-tego gracza prowadziłaby do zmniejszenia jego nagrody). Tzn. $i$-temu graczowi nie opłaca się zmieniać strategii.

Dylemat więźnia
Gra w dylemat więźnia polega na tym, że dwóch członków gangu jest złapanych i oddzielnie przesłuchiwanych. Każdy więzień ma dwie opcje do wyboru - może milczeć lub zdradzić swojego kompana.

Jeśli obaj milczeli, to dostają rok więzienia.
Jeśli zdradzili się nawzajem, to dostają dwa lata więzienia.
Jeśli jedna osoba milczała a druga ją zdradziła, to milczący idzie na trzy lata do więzienia a zdrajca jest wolny.

Punkt równowagi Nasha dla dylematu więźnia jest taki, że obaj przestępcy się zdradzają. Jeśli któryś przestępca będzie chciał milczeć, to mu się to nie opłaca.

Propozycja agenta dla zaproponowanej wersji dylematu więźnia:
* w pierwszej rozgrywce z danym graczem zawsze milczymy
* w każdej następnej rozgrywce wykonujemy ruch, który wykonał przeciwnik w poprzedniej rozgrywce z nami
* jeśli ruchem ma być zdradzenie, to z pewnym mały prawdopodobieństwem możemy milczeć (próba odbudowania zaufania)

## Zadanie 10
![](https://i.imgur.com/nN1yu54.png)

**Alfa-Beta Search**
a) Zapamiętujemy poddrzewo przeszukiwań obliczone w poprzednium ruchu odpowiadające ruchowi, który ostatecznie wybraliśmy. Sortujemy jego liście po wartościach heurystyki, jakie dla nich otrzymaliśmy (w zależności od tego jakiego gracza one dotyczą - dla min rosnąco, dla max malejąco). Niezależnie od pruningu dokonanego przy obliczaniu poprzedniego ruchu musimy rozpatrzeć je wszystkie (bo nasza heurystyka może się przecież mylić), ale takie ich ustawienie maksymalizuje naszą szansę, że uda nam się jak najwięcej poddrzew prunować w tej iteracji.

![](https://i.imgur.com/J9aQZn2.png)

b) Równolegle liczymy poddrzewa wywodzące się z dzieci korzenia drzewa (po to, żeby każdy węzeł był rozpatrzony dokładnie raz). Alfy i bety synchornizujemy pomiędzy poddrzewami tylko po policzeniu całego poddrzewa, co zmniejsza efektywnośc pruningu, ale dzięki wielowątkowości i tak wyjdziemy na tym lepiej.
Jak to optymalizować? Dawać priorytet wątkom zajmującym się poddrzewami z obiecującą wartością w korzeniu j.w.

**MCTS**

![](https://i.imgur.com/FSsDmV3.png)

a) Dość oczywiste - zapamiętujemy poddrzewo ruchu, który wybraliśmy i wykorzystujemy je w kolejnej iteracji.
b) Możemy wielowątkowo:
- przeprowadzać rozwinięcie dla więcej niż jednego dziecka
- przeprowadzić więcej niż jedną symulacje dla wybranego dziecka