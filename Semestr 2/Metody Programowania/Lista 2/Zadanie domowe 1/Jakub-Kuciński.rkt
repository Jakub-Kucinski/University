#lang racket
;;Jakub Kuciński 309881

;;Kwadrat liczby
(define (square x) (* x x))

;;Wartość bezwzględna
(define (absolute x)
    (if (< x 0) (- 0 x) x))

;;Definicja procedury liczącej przybliżoną wartość ułamka łańcuchowego
;;o licznikach zadanych przez procedurę num i mianownikach zadanych przez procedurę den
(define (continued-fractions num den)

  ;;Sprawdzanie dwie liczby są wystarczająco blisko siebie
  (define (is-good-enough a b)
    (< (absolute (- a b)) 0.000001))

  ;;Procedura wylicza kolejne elementy ciągów An i Bn na podstawie wartości An-1, An-2, Bn-1, Bn-2, n
  ;;oraz wartości fk-2 i fk-1, według zależności podanych z w treści zadania.
  ;;Jeśli fk-2 i fk-1 są wystarczająco blisko siebie zostaje zwrócone fk-1,
  ;;wpp wywoływana jest funkcja con-iter z kolejnymi wyrazami ciągów An i Bn oraz n+1 w celu
  ;;znalezienia lepszego przybliżenia.
  (define (con-iter An-1 An-2 Bn-1 Bn-2 n)
    (let ([An (+ (* (den n) An-1) (* (num n) An-2))]
          [Bn (+ (* (den n) Bn-1) (* (num n) Bn-2))])
      (let ([fk-2 (/ An-2 Bn-2)]
          [fk-1 (/ An-1 Bn-1)])
        (if (is-good-enough fk-2 fk-1)
            fk-1
            (con-iter An An-1 Bn Bn-1 (+ n 1))))))

  ;;Wywołanie procedury con-iter z wyliczonymi pierwszymi dwoma elementami ciągów An i Bn
  ;;dla zadanych procedur den i num
  (let ([A1 (+ (* (den 1.0) 0) (* (num 1.0) 1))]
        [B1 (+ (* (den 1.0) 1) (* (num 1.0) 0))])
    (let ([A2 (+ (* (den 2.0) A1) (* (num 2.0) 0))]
          [B2 (+ (* (den 2.0) B1) (* (num 2.0) 1))])
      (con-iter A2 A1 B2 B1 3.0))))

;;Testy wykorzystują zależność między wartością arcusatangensa, a odpowiednim ułamkiem łańcuchowym,
;;przedstawioną w zadaniu 8.
(atan 1.0)
(continued-fractions (lambda (i) (if (= i 1) 1.0 (square (* (- i 1) 1.0))))
                     (lambda (i) (- (* 2 i) 1)))

(atan 0.5)
(continued-fractions (lambda (i) (if (= i 1) 0.5 (square (* (- i 1) 0.5))))
                     (lambda (i) (- (* 2 i) 1)))

(atan 2.0)
(continued-fractions (lambda (i) (if (= i 1) 2.0 (square (* (- i 1) 2.0))))
                     (lambda (i) (- (* 2 i) 1)))
