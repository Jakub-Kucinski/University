#lang racket


(define (power-close-to a n)
  (define (potega e c)
    (if (> c n)
        e
        (potega (+ e 1) (* c a))))
  (potega 1 a))

(define (identity x) x)

(define (compose f1 f2)
  (lambda (x) (f1 (f2 x))))

(define (repeated p n)
  (if (> n 0)
      (compose p (repeated p (- n 1)))
      identity))

(define (absolute x)
    (if (< x 0) (- 0 x) x))

(define (average a b)
  (/ (+ a b) 2))


(define (nth-root x n)
  (define (fixed-function y)
    (/ x (expt y (- n 1))))
  
  (define (is-good-enough a b)
    (< (absolute (- a b)) 0.000001))
  
  (define (fixed-point f s)
    (define (iter k)
      (let ((new-k (f k)))
        (if (is-good-enough k new-k)
            k
            (iter new-k))))
    (iter s))
  ;;(define (repeated-new f k)
    ;;(lambda (x)
      ;;(let (
    ;;(define (repeated-build k)
      ;;(repeated (lambda (b) (average z b)) k))

  (define (average-damp f)
    (lambda (x) (average x (f x))))
  
  (define (sqrt-n-fix)
    (fixed-point (repeated (average-damp fixed-function) (- n 1)) 1.0))

  (define (sqrt-n-fix2)
    (fixed-point (lambda (z) (lambda () ((repeated (lambda (b) (average z b)) (- n 2)) (average-damp (fixed-function z))))) 1.0))

  (define (sqrt-n-fix3)
    (fixed-point (lambda (z) ((compose (repeated (lambda (b) (average z b)) (- (power-close-to 2 n) 1)) (average-damp fixed-function)) z)) 1.0))

  (define (sqrt-n-fix4)
    (fixed-point (lambda (z) ((compose (repeated (lambda (b) (average z b)) (- (power-close-to 2 n) 1)) (average-damp fixed-function)) z)) 1.0))
  
  (define (sqrt-n-fix5)
    (fixed-point (lambda (z) (((repeated average-damp (power-close-to 2 n) ) fixed-function) z)) 1.0))

  (define (sqrt-n-fix6)
    (fixed-point ((repeated average-damp (power-close-to 2 n) ) fixed-function) 1.0))
  
  (sqrt-n-fix6))

(nth-root 8.0 3)