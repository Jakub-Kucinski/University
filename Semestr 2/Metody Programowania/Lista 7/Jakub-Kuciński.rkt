#lang racket

;;Jakub Kuciński
(require rackunit)
(require rackunit/text-ui)

;;Definicje struktur
(struct const (val) #:transparent)
(struct sum (l r) #:transparent)
(struct variable () #:transparent)
(struct mult (l r) #:transparent)
(struct deriv (e) #:transparent)


;;Predykat sprawdzający czy podany argument jest wyrażeniem
(define (expr? e)
  (match e
    [(variable) true]
    [(const n)  (number? n)]
    [(sum l r) (and  (expr? l)
                     (expr? r))]
    [(mult l r) (and (expr? l)
                     (expr? r))]
    [(deriv e) (expr? e)]
    [_          false]))

;;Procedura obliczająca pochodną z wyrażenia 
(define (∂ f)
  (match f
    [(const n)   (const 0)]
    [(variable)  (const 1)]
    [(sum l r) (sum (∂ l) (∂ r))]
    [(mult l r) (sum (mult (∂ l) r)
                    (mult l (∂ r)))]
    [(deriv e) (∂ (∂ e))]))



;;Procedura zwraca wartość wyrażenia, jeśli za zmienne w wyrażeniu e podstawimy wartość val (nie const val)
(define (eval e val)
  (match e
    [(const n)    n]
    [(variable) val]
    [(sum l r)  (+ (eval l val) (eval r val))]
    [(mult l r)  (* (eval l val) (eval r val))]
    [(deriv e) (eval (∂ e) val)]))

(define eval-tests
  (test-suite
   "Evaluation tests"
   (test-case
    "Tests"
    ;2*x+∂(x*x+x) dla x=3
    (check-equal? (eval (sum (mult (const 2) (variable))
                             (deriv (sum (mult (variable) (variable))
                                         (variable)))) 3) 13 "Blad 1")
    ;;(x+2) dla x=5
    (check-equal? (eval (sum (variable) (const 2)) 5) 7 "Blad 2")
    ;;∂(x*∂(x*x)) dla x=6
    (check-equal? (eval (deriv (mult (variable) (deriv (mult (variable) (variable))))) 6) 24 "Blad 3")
    ;;2 dla x=999
    (check-equal? (eval (const 2) 999) 2 "Blad 4")
    ;;x dla x=999
    (check-equal? (eval (variable) 999) 999 "Blad 5")
    ;;∂(x*x) dla x=10
    (check-equal? (eval (deriv (mult (variable) (variable))) 10) 20 "Blad 6")
    ;;∂(x+x) dla x=999
    (check-equal? (eval (deriv (sum (variable) (variable))) 999) 2 "Blad 7")
    )))
(run-tests eval-tests)