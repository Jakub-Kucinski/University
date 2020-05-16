#lang racket

;; definicja wyrażeń arytmetycznych

(struct const (val) #:transparent)
(struct op (symb l r) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(op s l r) (and (member s '(+ *))
                     (expr? l)
                     (expr? r))]
    [_ false]))

;; przykładowe wyrażenie

(define e1 (op '* (op '+ (const 2) (const 2))
               (const 2)))

;; ewaluator wyrażeń arytmetycznych

(define (eval e)
  (match e
    [(const n) n]
    [(op '+ l r) (+ (eval l) (eval r))]
    [(op '* l r) (* (eval l) (eval r))]))

;; kompilator wyrażeń arytmetycznych do odwrotnej notacji polskiej

(define (to-rpn e)
  (match e
    [(const n) (list n)]
    [(op s l r) (append (to-rpn l)
                        (to-rpn r)
                        (list s))]))

(define (from-quote f)
  (cond [(number? f) (const f)]
        [(null? f) (void)]
        [(list? f) (let ((sym (first f)))
                     (if (= (length (cdr f)) 2)
                         (op sym (from-quote (second f)) (from-quote (third f)))
                         (op sym (from-quote (second f)) (from-quote (cons sym (cddr f))))))]
        [else (error "Unexpected form")]))

(struct stos (xs) #:transparent)

(define (empty? s)
  (if (null? (stos-xs s))
      true
      false))
(define (stos-add s x)
  (stos (cons x (stos-xs s))))
(define (stos-top s)
  (if (empty? s)
      (error "Pusty")
      (car (stos-xs s))))
(define (stos-pop s)
  (if (empty? s)
      (error "Pusty")
      (stos (cdr (stos-xs s)))))

(define (eval-rpn ys)
  (define (helper s ys)
    (cond
      [(null? ys) (if (empty? s)
                      (error "Brak argumentu")
                      (stos-top s))]
      [(number? (car ys)) (helper (stos-add s (car ys)) (cdr ys))]
      [(eq? '* (car ys)) (let* ((a (stos-top s))
                                (new-stos (stos-pop s))
                                (b (stos-top s))
                                (new-stos2 (stos-pop new-stos)))
                           (helper (stos-add (new-stos2) (* a b)) (cdr ys)))]
      [(eq? '+ (car ys)) (let* ((a (stos-top s))
                                (new-stos (stos-pop s))
                                (b (stos-top s))
                                (new-stos2 (stos-pop new-stos)))
                           (helper (stos-add (new-stos2) (+ a b)) (cdr ys)))]))
  (helper (stos null) ys))
