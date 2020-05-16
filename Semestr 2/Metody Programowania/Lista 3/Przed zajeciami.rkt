#lang racket

(define (square x) (* x x))

(define (make-vect p1 p2)
  (cons p1 p2))

(define (vect? v)
  (and (cons? v)
       (point? (car v))
       (point? (cdr v))))

(define (vect-begin v)
  (car v))

(define (vect-end v)
  (cdr v))

(define (make-point x y)
  (cons x y))

(define (point? p)
  (and (cons? p)
       (rational? (car p))
       (rational? (cdr p))))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))

(define (vect-lenght v)
  (sqrt (+ (square (- (point-x (vect-end v)) (point-x (vect-begin v))))
           (square (- (point-y (vect-end v)) (point-y (vect-begin v))))
           )))

(define (vect-scale v k)
  (make-vect (vect-begin v) (make-point (+
                                         (* (- (point-x (vect-end v))
                                              (point-x (vect-begin v)))
                                           k)
                                         (point-x (vect-begin v)))
                                        (+
                                         (* (- (point-y (vect-end v))
                                              (point-y (vect-begin v)))
                                           k)
                                         (point-y (vect-begin v)))
                                        )))

(define (display-point p)
  (display "(")
  (display (point-x p))
  (display ", ")
  (display (point-y p))
  (display ")"))

(define (display-vect v)
  (display "[")
  (display-point (vect-begin v))
  (display ", ")
  (display-point (vect-end v))
  (display "]"))

(define (vect-translate v p)
  (make-vect p (make-point (+ (point-x p) (- (point-x (vect-end v))
                                 (point-x (vect-begin v))))
               (+ (point-y p) (- (point-y (vect-end v))
                                 (point-y (vect-begin v))))
               )))

(define (reverse-rek xs)
    (if (null? xs)
        xs
        (cons (car xs) (reverse (cdr xs)))))

(define (reverse-iter xs)
  (define (helper xs ys)
    (if (null? xs)
        ys
        (helper (cdr xs) (cons (car xs) ys))))
  (helper xs (list)))


(define (add-begin x xs)
    (if (null? xs)
        null
        (cons (cons x (car xs)) (add-begin x (cdr xs)))))

(define (perm xs)
  (define (for-all xs)
    (define (helper ys)
      (if (null? ys)
          null
          (append (add-begin (car ys) (for-all (remove (car ys) xs))) (helper (cdr ys)))))
    (if (null? xs)
        (list null)
        (helper xs))
      )
  (for-all xs))


(reverse-iter (list 1 2 3 4))


#;(define (perm xs)
  (define (for-all xs)
    (define (helper ys)
      (if (null? ys)
          (list null)
          (append (add-begin (car ys) (for-all (remove (car ys) xs))) (helper (cdr ys)))))
        (helper xs))
  (for-all xs))