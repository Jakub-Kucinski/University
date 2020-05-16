#lang racket

;; definicja wyrażeń z let-wyrażeniami

(struct const    (val)      #:transparent)
(struct op       (symb l r) #:transparent)
(struct let-expr (x e1 e2)  #:transparent)
(struct variable (x)        #:transparent)
(struct power    (a b)      #:transparent)
(struct sum      (f n m i)  #:transparent)
(struct integral (f a b x)  #:transparent)
(struct min      (f i)      #:transparent)
(struct if-expr  (w e1 e2)  #:transparent)
(struct cond-expr (xs)      #:transparent)
(struct lambda-expr (xs e)  #:transparent) 


(define (expr? e)
  (match e
    [(variable s)       (symbol? s)]
    [(const n)          (number? n)]
    [(op s l r)         (and (member s '(+ *))
                             (expr? l)
                             (expr? r))]
    [(power a b)        (and (expr? a)
                             (expr? b))]
    [(sum f n m i)      (and (variable? i)
                             (expr? f)
                             (match n
                               [(const v) (natural? v)]
                               [_         false])
                             (match m
                               [(const v) (natural? v)]
                               [_         false]))]
    [(integral f a b x) (and (expr? f)
                             (expr? a)
                             (expr? b)
                             (variable? x))]
    [(min f i)          (and (expr? f)
                             (variable? i))]
    [(let-expr x e1 e2) (and (symbol? x)
                             (expr? e1)
                             (expr? e2))]
    [_                  false]))

;; podstawienie wartości (= wyniku ewaluacji wyrażenia) jako stałej w wyrażeniu

(define (subst x v e)
  (match e
    [(op s l r)   (op s (subst x v l)
                        (subst x v r))]
    [(const n)    (const n)]
    [(variable y) (if (eq? x y)
                      (const v)
                      (variable y))]
    [(let-expr y e1 e2)
     (if (eq? x y)
         (let-expr y
                   (subst x v e1)
                   e2)
         (let-expr y
                   (subst x v e1)
                   (subst x v e2)))]))

;; (gorliwa) ewaluacja wyrażenia w modelu podstawieniowym

(define (eval e)
  (match e
    [(const n)    n]
    [(op '+ l r)  (+ (eval l) (eval r))]
    [(op '* l r)  (* (eval l) (eval r))]
    [(let-expr x e1 e2)
     (eval (subst x (eval e1) e2))]
    [(variable n) (error n "cannot reference an identifier before its definition ;)")]))

;; przykładowe programy

(define p1
  (let-expr 'x (op '+ (const 2) (const 2))
     (op '+ (const 1000) (let-expr 'y (op '+ (const 5) (const 5))
                            (op '* (variable 'x) (variable 'y))))))

(define p2
  (let-expr 'x (op '+ (const 2) (const 2))
     (op '+ (const 1000) (let-expr 'x (op '+ (const 5) (const 5))
                            (op '* (variable 'x) (variable 'x))))))

(define p3
  (let-expr 'x (op '+ (const 2) (const 2))
     (op '+ (const 1000) (let-expr 'y (op '+ (const 5) (const 5))
                            (op '* (variable 'x) (variable 'z))))))