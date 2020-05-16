#lang racket

;; definicja wyrażeń arytmetycznych z jedną zmienną

(struct const (val) #:transparent)
(struct op (symb l r) #:transparent)
(struct variable () #:transparent)

(define (expr? e)
  (match e
    [(variable) true]
    [(const n)  (number? n)]
    [(op s l r) (and (member s '(+ *))
                     (expr? l)
                     (expr? r))]
    [_          false]))

;; przykładowe wyrażenie

(define f (op '* (op '* (variable) (variable))
              (variable)))

;; pochodna funkcji

(define (∂ f)
  (match f
    [(const n)   (const 0)]
    [(variable)  (const 1)]
    [(op '+ f g) (op '+ (∂ f) (∂ g))]
    [(op '* f g) (op '+ (op '* (∂ f) g)
                     (op '* f (∂ g)))]))

;; przykładowe użycie

(define df (∂ f))
(define ddf (∂ (∂ f)))
(define dddf (∂ (∂ (∂ f))))

(define (simplify f)
  (match f
    [(const n) (const n)]
    [(variable) (variable)]
    [(op '* f g) (let ((l (simplify f))
                       (r (simplify g)))
                   (cond
                     [(and (const? l) (= (const-val l) 0)) (const 0)]
                     [(and (const? l) (= (const-val l) 1)) r]
                     [(and (const? r) (= (const-val r) 0)) (const 0)]
                     [(and (const? r) (= (const-val r) 1)) l]
                     [(and (const? l) (const? r)) (const (* (const-val l) (const-val r)))]
                     [else (op '* l r)]))]
    [(op '+ f g) (let ((l (simplify f))
                       (r (simplify g)))
                   (cond
                     [(and (const? l) (= (const-val l) 0)) r]
                     [(and (const? r) (= (const-val r) 0)) l]
                     [(and (const? l) (const? r)) (const (+ (const-val l) (const-val r)))]
                     [(and (variable? l) (variable? r) (op '* (const 2) (variable)))]
                     [else (op '+ l r)]))]))
                            