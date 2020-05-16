#lang racket

;;Procedura "square" zwraca wartość kwadratu liczby
(define (square x)
  (* x x))

;;Procedura "cube" zwraca wartość sześcianu liczby
(define (cube x)
  (* x x x))

;;Procedura "absolute" zwraca wartość modułu z liczby
(define (absolute x)
  (if (< x 0) (- x) x))

;;Procedura "distance" zwraca odległość między dwoma liczbami (wartość bezwzględna różnicy)
(define (distance x y)
  (absolute (- x y)))



;;Początek definicji głównej procedury "cube-root"
(define (cube-root x)

  ;;Procedura "better-approximation" zwraca wartość lepszego przybliżenia wartości
  ;;sqrt3(x) od danego przybliżenia y i wartości x
  (define (better-approximation y)
    [/
      {+
        [/
          x
          (square y)]
        (* 2 y)}
      3])
  
  ;;Definicja procedury "is-good-enough" zwracającej #t, gdy błąd przybliżenia y jest
  ;;mniejszy niż zadana stała 0.0001, #f wpp.
  (define (is-good-enough y)
    (< [distance x (cube y)] 0.0001))
  
  ;;Procedura obliczająca przybliżoną wartość sqrt3(x). Zwraca y (przybliżenie),
  ;;gdy procedura (is-good-enough y) zwróci #t (czyli gdy przybliżenie będzie wystarczająco dobre),
  ;;wpp wywołuje samą siebie z wartością lepszego przybliżenia wartości sqrt(3) (better-approximation y).
  (define (loop y)
    (if (is-good-enough y)
        y
        [loop (better-approximation y)]))
  
  ;;Pierwsze wywołanie procedury petla, obliczającej przybliżoną wartość sqrt3(x), z początkowym
  ;;przybliżeniem tej wartości wynoszącym 1 gdy x jest dodatnie, -1 wpp, w celu uniknięcia
  ;;sytuacji, w której w pewnym wywołaniu "loop" przybliżenie y będzie równe 0
  ;;(sytuacja jest możliwa tylko gdy początkowe x i y są przeciwnych znaków lub y=0) i kolejne wywołanie
  ;;procedury "better-approximation" spowoduje błąd (dzielenie przez 0)
  (if (< 0 x) (loop 1) (loop -1))
)

;;Testy
8 
(cube-root 8.0)

27 
(cube-root 27.0)

-8 
(cube-root -8.0)

-27 
(cube-root -27.0)

1
(cube-root 1.0)

-1
(cube-root -1.0)

1000
(cube-root 1000.0)

0.001
(cube-root 0.001)