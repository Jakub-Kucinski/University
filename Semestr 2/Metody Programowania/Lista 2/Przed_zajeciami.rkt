#lang racket

(define (compose f1 f2)
  (lambda (x) (f1 (f2 x))))

(define (square x) (* x x))

(define (inc x) (+ x 1))

(define (identity x) x)

(define (repeated p n)
  (if (> n 0)
      (compose p (repeated p (- n 1)))
      identity))

(define (repeated2 p n)
  (if (> n 0)
      (compose (repeated2 p (- n 1)) p)
      identity))

(define (product value next start end)
  (if (> start end)
      1.0
      (* (value start)
         (product value next (next start) end))))

(define (pi-val x) (/ (* x (+ 2 x)) (square (inc x))))

(define (pi-next x) (+ x 2))

(define (accumulate combiner null-value term next start end)
  (if (> start end)
      null-value
      (combiner (term start)
         (accumulate combiner null-value term next (next start) end))))

(define (cont-rek num den i k)
  (if (> i k)
      0
      (/ (num i) (+ (den i) (cont-rek num den (inc i) k)))))

(define (cont-frac num den k)
  (cont-rek num den 1 k))

(define (cont-iter num den k c)
  (if(< k 2)
     (/ (num k) (+ (den k) c))
     (cont-iter num den (- k 1) (/ (num k) (+ (den k) c)))))
  

(define (cont-frac2 num den k)
  (cont-iter num den k 0))

(define (pi-num k) (square (- (* 2 k) 1)))

(define (atan-cf x k)
  (cont-frac (lambda (i) (if (= i 1) x (square (* (- i 1) x)))) (lambda (i) (- (* 2 i) 1)) k))

(define (build n d b) (/ n (+ d b)))

(define (repeated-build k n d b)
  (repeated 