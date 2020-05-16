#lang racket

(define (lit pol var)
  (list 'lit pol var))

(define (pos x)
  (lit true x))

(define (neg x)
  (lit false x))

(define (lit-pol l)
  (second l))

(define (lit-var l)
  (third l))

(define (lit? x)
  (and (list? x)
       (= 3 (length x))
       (eq? 'lit (first x))
       (boolean? (second x))
       (var? (third x))))

(define (make-neg t)
  (list 'neg t))

(define (make-conj a b)
  (list 'conj a b))

(define (make-disj a b)
  (list 'disj a b))

(define (neg-subf f)
  (second f))

(define (disj-left f)
  (second f))

(define (disj-right f)
  (third f))

(define (conj-left f)
  (second f))

(define (conj-right f)
  (third f))

(define (var? t)
  (symbol? t))

(define (neg? t)
  (and (list? t)
       (= 2 (length t))
       (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (prop? f)
  (or (var? f)
      (and (neg? f)
           (prop? (neg-subf f)))
      (and (disj? f)
           (prop? (disj-left f))
           (prop? (disj-right f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-right f)))))

(define (free-vars f)
  (define (list-of-vars f xs)
    (cond [(var? f) (if (member f xs)
                        xs
                        (cons f xs))]
          [(neg? f) (list-of-vars (neg-subf f) xs)]
          [(disj? f) (list-of-vars (disj-left f) (list-of-vars (disj-right f) xs))]
          [(conj? f) (list-of-vars (conj-left f) (list-of-vars (conj-right f) xs))]))
  (list-of-vars f null))

(define (gen-vals xs)
  (if (null? xs)
      (list  null)
      (let* ((vss   (gen-vals (cdr xs)))
             (x     (car xs))
             (vst   (map (lambda(vs) (cons (list x true)   vs)) vss))
             (vsf   (map (lambda(vs) (cons (list x false) vs)) vss)))
        (append  vst  vsf))))

(define (eval-formula f values)
  (cond [(var? f) (if (eq? #f (member (list f #t) values))
                      #f
                      #t)]
        [(neg? f) (not (eval-formula (neg-subf f) values))]
        [(disj? f) (or (eval-formula (disj-left f) values)
                       (eval-formula (disj-right f) values))]
        [(conj? f) (and (eval-formula (conj-left f) values)
                        (eval-formula (conj-right f) values))]))

(define (falsifiable-eval? f)
  (define (falsi f xs)
    (if (null? xs)
        #f
        (if (eval-formula f (car xs))
            (falsi f (cdr xs))
            (car xs))))
  (falsi f (gen-vals (free-vars f))))

(define (transform-formula f)
  (cond [(var? f) (make-neg f)]
        [(conj? f) (make-disj (transform-formula (conj-left f)) (transform-formula (conj-right f)))]
        [(disj? f) (make-conj (transform-formula (disj-left f)) (transform-formula (disj-right f)))]
        [(neg? f) (convert-to-nnf (neg-subf f))]))

(define (convert-to-nnf f)
  (cond [(var? f) f]
        [(conj? f) (make-conj (convert-to-nnf (conj-left f)) (convert-to-nnf (conj-right f)))]
        [(disj? f) (make-disj (convert-to-nnf (disj-left f)) (convert-to-nnf (disj-right f)))]
        [(neg? f) (transform-formula (neg-subf f))]))