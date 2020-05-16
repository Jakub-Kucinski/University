#lang racket
;;Jakub Kuciński

(require rackunit)
(require rackunit/text-ui)
;; definicja wyrażeń

(struct variable     (x)        #:transparent)
(struct const        (val)      #:transparent)
(struct op           (symb l r) #:transparent)
(struct let-expr     (x e1 e2)  #:transparent)
(struct if-expr      (b t e)    #:transparent)
(struct cons-expr    (l r)      #:transparent)
(struct car-expr     (p)        #:transparent)
(struct cdr-expr     (p)        #:transparent)
(struct pair?-expr   (p)        #:transparent)
(struct null-expr    ()         #:transparent)
(struct null?-expr   (e)        #:transparent)
(struct symbol-expr  (v)        #:transparent)
(struct symbol?-expr (e)        #:transparent)
(struct lambda-expr  (xs b)     #:transparent)
(struct app-expr     (f es)     #:transparent)
(struct apply-expr   (f e)      #:transparent)

(define (expr? e)
  (match e
    [(variable s)       (symbol? s)]
    [(const n)          (or (number? n)
                            (boolean? n))]
    [(op s l r)         (and (member s '(+ *))
                             (expr? l)
                             (expr? r))]
    [(let-expr x e1 e2) (and (symbol? x)
                             (expr? e1)
                             (expr? e2))]
    [(if-expr b t e)    (andmap expr? (list b t e))]
    [(cons-expr l r)    (andmap expr? (list l r))]
    [(car-expr p)       (expr? p)]
    [(cdr-expr p)       (expr? p)]
    [(pair?-expr p)     (expr? p)]
    [(null-expr)        true]
    [(null?-expr p)     (expr? p)]
    [(symbol-expr v)    (symbol? v)]
    [(symbol?-expr p)   (expr? p)]
    [(lambda-expr xs b) (and (andmap symbol? xs)
                             (expr? b)
                             (not (check-duplicates xs)))]
    [(app-expr f es)    (and (expr? f)
                             (andmap expr? es))]
    [(apply-expr f e)   (and (expr? f)
                             (expr? e))]
    [_                  false]))

;; wartości zwracane przez interpreter

(struct val-symbol (s)   #:transparent)


;;;;Domknięcie, xs to lista zmiennych
(struct closure (xs b env))

;;;;;;;;;;Dodałem closure do wartości, closure-xs to lista zmiennych w danym domknięciu
(define (my-value? v)
  (or (number? v)
      (boolean? v)
      (and (pair? v)
           (my-value? (car v))
           (my-value? (cdr v)))
      ; null-a reprezentujemy symbolem (a nie racketowym
      ; nullem) bez wyraźnej przyczyny
      (and (symbol? v) (eq? v 'null))
      (and ((val-symbol? v) (symbol? (val-symbol-s v))))
      (and (closure? v) (list? (closure-xs v))
                        (andmap symbol? (closure-xs v))
                        (expr? (closure-b v))
                        (env? (closure-env v)))))

;; wyszukiwanie wartości dla klucza na liście asocjacyjnej
;; dwuelementowych list

(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x) (cadar xs)]
    [else (lookup x (cdr xs))]))

;; kilka operatorów do wykorzystania w interpreterze

(define (op-to-proc x)
  (lookup x `(
              (+ ,+)
              (* ,*)
              (- ,-)
              (/ ,/)
              (> ,>)
              (>= ,>=)
              (< ,<)
              (<= ,<=)
              (= ,=)
              (eq? ,(lambda (x y) (eq? (val-symbol-s x)
                                       (val-symbol-s y))))
              )))

;; interfejs do obsługi środowisk

(define (env-empty) null)
(define env-lookup lookup)
(define (env-add x v env) (cons (list x v) env))

(define (env? e)
  (and (list? e)
       (andmap (lambda (xs) (and (list? xs)
                                 (= (length xs) 2)
                                 (symbol? (first xs)))) e)))

;; interpretacja wyrażeń


(define (eval e env)
  (match e
    [(const n) n]
    [(op s l r)
     ((op-to-proc s) (eval l env)
                     (eval r env))]
    [(let-expr x e1 e2)
     (let ((v1 (eval e1 env)))
       (eval e2 (env-add x v1 env)))]
    [(variable x) (env-lookup x env)]
    [(if-expr b t e) (if (eval b env)
                         (eval t env)
                         (eval e env))]
    [(cons-expr l r)
     (let ((vl (eval l env))
           (vr (eval r env)))
       (cons vl vr))]
    [(car-expr p)      (car (eval p env))]
    [(cdr-expr p)      (cdr (eval p env))]
    [(pair?-expr p)    (pair? (eval p env))]
    [(null-expr)       'null]
    [(null?-expr e)    (eq? (eval e env) 'null)]
    [(symbol-expr v)   (val-symbol v)]
    [(lambda-expr xs b) (closure xs b env)]
    [(app-expr f es)   (define (my-add xs ves env)
                         (cond
                           [(and (null? xs) (null? ves)) env]
                           [(or (null? xs) (null? ves)) (error "arity mismatch")]
                           [else (my-add (cdr xs) (cdr ves) (env-add (car xs) (car ves) env))]))
                        (let ((vf (eval f env))
                             (ves (map (lambda (n) (eval n env)) es)))
                         (match vf
                           [(closure xs b c-env)
                             (eval b (my-add xs ves c-env))]
                           [_ (error "application: not a function :(")]))]
    [(apply-expr f e)  (define (my-add xs es env)
                         (cond
                           [(and (null? xs) (eq? es 'null)) env]
                           [(or (null? xs) (eq? es 'null)) (error "arity mismatch")]
                           [else (my-add (cdr xs) (cdr es) (env-add (car xs) (car es) env))]))
                        (let ((vf (eval f env))
                             (ves (eval e env)))
                         (match vf
                           [(closure xs b c-env)
                             (eval b (my-add xs ves c-env))]
                           [_ (error "application: not a function :(")]))
                       ]))

(define (run e)
  (eval e (env-empty)))

(define wyrazenie1
  (app-expr (lambda-expr (list 'x 'y 'z 'u) (op '* (variable 'x) (op '* (variable 'y) (op '* (variable 'z) (variable 'u)))))
            (list (const 1) (const 2) (const 3) (const 4))))

(define wyrazenie11
  (app-expr (lambda-expr (list 'a 'b 'c) (op '* (variable 'a) (op '+ (variable 'b) (variable 'c))))
            (list (const 4) (const 5) (const 6))))

(define wyrazenie111
  (app-expr (lambda-expr (list) (op '+ (const 1) (const 1)))
            (list)))

(define wyrazenie1111
  (app-expr (lambda-expr (list) (op '+ (const 1) (const 1)))
            (list (const 1))))

(define wyrazenie11111
  (app-expr (lambda-expr (list 'x) (op '+ (const 1) (const 1)))
            (list)))

(define wyrazenie2
  (apply-expr (lambda-expr (list 'x 'y 'z 'u) (op '* (variable 'x) (op '* (variable 'y) (op '* (variable 'z) (variable 'u)))))
            (cons-expr (const 1) (cons-expr (const 2) (cons-expr (const 3) (cons-expr (const 4) (null-expr)))))))

(define wyrazenie22
  (apply-expr (lambda-expr (list 'a 'b 'c) (op '* (variable 'a) (op '+ (variable 'b) (variable 'c))))
            (cons-expr (const 4) (cons-expr (const 5) (cons-expr (const 6) (null-expr))))))

(define wyrazenie222
  (apply-expr (lambda-expr (list) (op '+ (const 1) (const 1)))
            (null-expr)))

(define wyrazenie2222
  (apply-expr (lambda-expr (list) (op '+ (const 1) (const 1)))
            (cons-expr (const 1) (null-expr))))

(define wyrazenie22222
  (apply-expr (lambda-expr (list 'x) (op '+ (const 1) (const 1)))
            (null-expr)))

(define eval-tests
  (test-suite
   "Evaluation tests"
   (test-case
    "Tests of app-expr"
    (check-equal? (run wyrazenie1) 24 "Blad 1")
    (check-equal? (run wyrazenie11) 44 "Blad 2")
    (check-equal? (run wyrazenie111) 2 "Blad 3"))
   (test-case
    "Tests of apply-expr"
    (check-equal? (run wyrazenie2) 24 "Blad 4")
    (check-equal? (run wyrazenie22) 44 "Blad 5")
    (check-equal? (run wyrazenie222) 2 "Blad 6")
    )))
(run-tests eval-tests)

;;Ewaluacja wrazenie1111, wrazenie11111, wrazenie2222, wrazenie22222 poprawnie zwraca błędy o niezgadzającej się arności
;;funkcji i liczby aplikowanych argumentów. Zwracają one errory i niestety nie wiem w jaki sposób można by umieścić je
;;w testach. Dlatego też zamieszczam zakomentowane testy poniżej z prośbą o ręczne ich sprawdzenie.
;;Dziękuję za wyrozumiałość.

;(run wyrazenie1111)
;(run wyrazenie11111)
;(run wyrazenie2222)
;(run wyrazenie22222)