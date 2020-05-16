#lang racket
;;Jakub Kuciński 309881

;;Procedura zwraca wartość floor(log[a] (n)) + 1
(define (power-close-to a n)
  (define (potega e c)
    (if (> c n)
        e
        (potega (+ e 1) (* c a))))
  (potega 1 a))

;;Identyczność
(define (identity x) x)

;;Złożenie funkcji
(define (compose f1 f2)
  (lambda (x) (f1 (f2 x))))

;;n-krotne złożenie funkcji
(define (repeated p n)
  (if (> n 0)
      (compose p (repeated p (- n 1)))
      identity))

;;Wartość bezwzględna z liczby
(define (absolute x)
    (if (< x 0) (- 0 x) x))

;;Średnia arytmetyczna dwóch liczb
(define (average a b)
  (/ (+ a b) 2))

;;Definicja głównej procedury nth-root zwracającej przybliżoną wartość pierwiastka stopnia n z liczby x
(define (nth-root x n)
  ;;Procedura zwraca funkcję, której punktem stałym jest pierwiastek n-tego stopnia z x
  (define (fixed-point-function y)
    (/ x (expt y (- n 1))))

  ;;Procedura sprawdzająca czy kolejne dwie wartości są odpowiednio blisko od siebie (zwraca #t gdy tak, #f wpp)
  (define (good-enough? a b)
    (< (absolute (- a b)) 0.000001))

  ;;Procedura obliczająca kolejne przybliżenie wartości sqrtn(x) zaczynając od wartości początkowej s
  ;;(poprzez znalezienie punktu stałego funkcji f)
  ;;Argument f jest funkcją wielokrotnie (odpowiednią liczbę razy w zależności od n) uśrednioną przez tłumienie
  (define (fixed-point f s)
    (define (iter k)
      (let ((new-k (f k)))
        (if (good-enough? k new-k)
            k
            (iter new-k))))
    (iter s))

  ;;Procedura zwraca funkcję uśrednioną przez tłumienie
  (define (average-damp f)
    (lambda (x) (average x (f x))))

  ;;Procedura przyjmuje argument start, który oznacza początkową wartość od której mamy szukać punktu stałego funkcji.
  ;;Wywołuje procedurę fixed-point od start i złożenia: złożenia floor(log2 (n))-krotnego funkcji zwracanej przez procedurę average-damp
  ;;z funkcją zwracaną przez procedurę fixed-point-function.
  (define (sqrt-n-fix start)
    (fixed-point ((repeated average-damp (- (power-close-to 2 n) 1)) fixed-point-function) start))

  ;;Jeśli x < 0 to jeśli pierwiastek (n) jest stopnia nieparzystego, to wywołuje procedurę sqrt-n-fix od -1.0,
  ;;jeśli n jest parzyste, to nie można wyliczyć pierwiastka i zostaje zwrócona ustalona wartość 0.
  ;;Jeśli x >=0 to wywołuje procedurę sqrt-n-fix od 1.0
  (if (< x 0)
      (if (= (modulo n 2) 1)
          (sqrt-n-fix -1.0)
          0)
      (sqrt-n-fix 1.0)))



;;Podczas testowania ilukrotne tłumienie jest niezbędne do obliczenia pierwiastka stopnia n
;;w miejsce (- (power-close-to 2 n) 1)) w procedurze fixed-point wstawiałem różne wartości naturalne
;;W ten sposób otrzymałem, że minimalna liczba tłumień dla odpowiednich wartości n wynosi:
;;(przedział wartości n, minimalna liczba tłumień): (2-3, 1), (4-7, 2), (8-15, 3), (16-31, 4), (32-63, 5).
;;Stąd wywnioskowałem, że liczba tłumień niezbędna do policzenia wartości pierwiastka stopnia n z x
;;wynosi podłoga(log2 (n)).

8 3
(nth-root 8.0 3)
10e12 128
(nth-root 1000000000000.0 128)
64 6
(nth-root 64.0 6)
64 3
(nth-root 64.0 3)
64 2
(nth-root 64.0 2)
10e12 12
(nth-root 1000000000000.0 12)