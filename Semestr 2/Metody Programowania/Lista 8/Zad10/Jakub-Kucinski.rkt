#lang racket
;;Jakub Kuciński
(require rackunit)
(require rackunit/text-ui)
;; definicja wyrażeń z let-wyrażeniami i if-wyrażeniami

(struct variable (x)         #:transparent)
(struct const    (val)       #:transparent)
(struct op       (symb l r)  #:transparent)
(struct let-expr (x e1 e2)   #:transparent)
(struct if-expr  (b t e)     #:transparent)

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
    [_                  false]))

;; definicja instrukcji w języku WHILE

(struct skip      ()       #:transparent) ; skip
(struct comp      (s1 s2)  #:transparent) ; s1; s2
(struct assign    (x e)    #:transparent) ; x := e
(struct while     (b s)    #:transparent) ; while (b) s
(struct if-stm    (b t e)  #:transparent) ; if (b) t else e
(struct var-block (x e s)  #:transparent) ; var x := e in s

(define (stm? e)
  (match e
    [(skip) true]
    [(comp s1 s2)   (and (stm? s1) (stm? s2))]
    [(assign x e)   (and (symbol? x) (expr? e))]
    [(while b s)    (and (expr? b) (stm? s))]
    [(if-stm b t e) (and (expr? b) (stm? t) (stm? e))]
    [_ false]))
  
;; wyszukiwanie wartości dla klucza na liście asocjacyjnej
;; dwuelementowych list

;; Dla zwykłej listy dwuelementowych list (potrzebna do op-to-proc więc zostawiłem)
(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x) (cadar xs)]
    [else (lookup x (cdr xs))]))

;; Dla mlisty mpar
  (define (lookup2 x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (mcar (mcar xs)) x) (mcdr (mcar xs))]
    [else (lookup2 x (mcdr xs))]))


;; aktualizacja środowiska dla danej zmiennej (koniecznie już
;; istniejącej w środowisku!)

  
(define (update x v ys)
  (define (update2 x v xs)
    (cond
      [(null? xs)
       (error x "unknown identifier :(")]
      [(eq? (mcar (mcar xs)) x)
       (begin (set-mcdr! (mcar xs) v) ys)]
      [else
       (update2 x v (mcdr xs))]))
  (update2 x v ys))

;; Zamiana listy dwuelementowych list na mlistę mpar 
(define (list-to-mlist xs)
  (if (null? xs)
      null
      (mcons (mcons (caar xs) (cadar xs)) (list-to-mlist (cdr xs)))))

;; kilka operatorów do wykorzystania w interpreterze

(define (op-to-proc x)
  (lookup x `((+ ,+)
              (* ,*)
              (- ,-)
              (/ ,/)
              (%, modulo)
              (> ,>)
              (>= ,>=)
              (< ,<)
              (<= ,<=)
              (= ,=)
              (!= ,(lambda (x y) (not (= x y)))) 
              (&& ,(lambda (x y) (and x y)))
              (|| ,(lambda (x y) (or x y)))
              )))

;; interfejs do obsługi środowisk

(define (env-empty) null)
(define env-lookup lookup2)
(define (env-add x v env) (mcons (mcons x v) env))
(define env-update update)
(define env-discard (lambda (env) (begin (set! env (mcdr env)) env)))
(define (env-from-assoc-list xs) (list-to-mlist xs))

;; ewaluacja wyrażeń ze środowiskiem

(define (eval e env)
  (match e
    [(const n) n]
    [(op s l r) ((op-to-proc s) (eval l env)
                                (eval r env))]
    [(let-expr x e1 e2)
     (let ((v1 (eval e1 env)))
       (eval e2 (env-add x v1 env)))]
    [(variable x) (env-lookup x env)]
    [(if-expr b t e) (if (eval b env)
                         (eval t env)
                         (eval e env))]))

;; interpretacja programów w języku WHILE, gdzie środowisko m to stan
;; pamięci. Interpreter to procedura, która dostaje program i początkowy
;; stan pamięci, a której wynikiem jest końcowy stan pamięci. Pamięć to
;; aktualne środowisko zawierające wartości zmiennych

(define (interp p m)
  (match p
    [(skip) m]
    [(comp s1 s2) (interp s2 (interp s1 m))]
    [(assign x e)
     (env-update x (eval e m) m)]
    [(while b s)
     (if (eval b m)
         (interp p (interp s m))
         m)]
    [(var-block x e s)
     (env-discard
       (interp s (env-add x (eval e m) m)))]
    [(if-stm b t e) (if (eval b m)
                        (interp t m)
                        (interp e m))]))

;; silnia zmiennej i

(define fact-in-WHILE
  (var-block 'x (const 0)                                           ; var x := 0 in
     (comp (assign 'x (const 1))                                    ;   x := 1
     (comp (while (op '> (variable 'i) (const 0))                   ;   while (i > 0)
              (comp (assign 'x (op '* (variable 'x) (variable 'i))) ;     x := x * i
                    (assign 'i (op '- (variable 'i) (const 1)))))   ;     i := i - 1
           (assign 'i (variable 'x))))))                            ;   i := x

(define (factorial n)
  (env-lookup 'i (interp fact-in-WHILE
                         (env-from-assoc-list `((i ,n))))))

;; najmniejsza liczba pierwsza nie mniejsza niż i

(define find-prime-in-WHILE
 (var-block 'c (variable 'i)                                         ; var c := i in
 (var-block 'continue (const true)                                   ; var continue := true in
 (comp
  (while (variable 'continue)                                        ; while (continue)
   (var-block 'is-prime (const true)                                 ;   var is-prime := true in
   (var-block 'x (const 2)                                           ;   var x := 2 in
    (comp
     (while (op '&& (variable 'is-prime)                             ;   while (is-prime &&
                    (op '< (variable 'x) (variable 'c)))             ;            x < c)
        (comp (if-stm (op '= (op '% (variable 'c) (variable 'x))     ;     if (c % x =
                             (const 0))                              ;                 0)
                      (assign 'is-prime (const false))               ;       is-prime := false
                      (skip))                                        ;     else skip
              (assign 'x (op '+ (variable 'x) (const 1)))))          ;     x := x + 1 
     (if-stm (variable 'is-prime)                                    ;   if (is-prime)
             (assign 'continue (const false))                        ;     continue := false
             (comp (assign 'continue (const true))                   ;   else continue := true
                   (assign 'c (op '+ (variable 'c) (const 1))))))))) ;        c := c + 1
  (assign 'i (variable 'c))))))                                      ; i := c

(define (find-prime-using-WHILE n)
  (env-lookup 'i (interp find-prime-in-WHILE
                         (env-from-assoc-list `((i ,n) (is-prime ,true))))))         

(define fib
  (var-block 'x1 (const 0)
      (var-block 'x2 (const 0)
           (var-block 'x3 (const 1)
                 (if-stm (op '= (variable 'n) (const 0)) (assign 'wynik (const 0))
                      (if-stm (op '= (variable 'n) (const 1)) (assign 'wynik (const 1))
                         (comp (while (op '> (variable 'n) (const 0))
                                  (comp (assign 'x1 (variable 'x2))
                                        (comp (assign 'x2 (variable 'x3))
                                              (comp (assign 'x3 (op '+ (variable 'x1) (variable 'x2)))
                                                    (assign 'n (op '- (variable 'n) (const 1)))))))
                               (assign 'wynik (variable 'x3)))))))))
(define (fibonacci x)
  (env-lookup 'wynik (interp fib (env-from-assoc-list `((n ,x) (wynik 0))))))

(define add1
  (var-block 'x (const 0)
       (comp (while (op '> (variable 'n) (variable 'x))
                    (assign 'x (op '+ (variable 'x) (const 1))))
             (assign 'n (variable 'x)))))
(define (add-one-to-n m)
  (env-lookup 'n (interp add1 (env-from-assoc-list `((n ,m))))))



;; ten sam algorytm do wyszukiwania liczby pierwszej nie mniejszej niż n
;; zapisany funkcyjnie jest dosc brzydki, ale odpowiada temu zapisanemu w WHILE

(define (find-prime-native n)
  (define (is-prime c isp x)
    (if (and isp (< x c))
      (if (= (modulo c x) 0)
          (is-prime c false (+ x 1))
          (is-prime c isp   (+ x 1)))
      isp))
  (if (is-prime n true 2)
      n
      (find-prime-native (+ n 1))))

;;Procedura tworzy symbol ze stringu s i liczby i
(define (gen-symbol s i)
  (string->symbol (string-append s (number->string i))))

;;Procedura generuje program w WHILE, który jest zawiera n varblocków i wykonuje pętlę 'n razy
(define (in-while-k-with-n-variables n)
  (define (make-variables i)
    (if (= i 0)
        (comp (while (op '> (variable 'n) (const 0))
                     (comp (assign 'n (op '- (variable 'n) (const 1)))
                           (assign (gen-symbol "x" n) (op '+ (variable (gen-symbol "x" n)) (const 1)))))
              (assign 'n (variable (gen-symbol "x" n))))
        (var-block (gen-symbol "x" i) (const 0) (make-variables (- i 1)))))
  (make-variables n))


(define (k-steps-with-m-variables k m)
  (env-lookup 'n (interp (in-while-k-with-n-variables m) (env-from-assoc-list `((n ,k))))))



(define eval-tests
  (test-suite
   "Tests of mutal environment representation"
   (test-case
    "Tests"
    (check-equal? (fibonacci 5) 8 "Blad 0")
    (check-equal? (fibonacci 6) 13 "Blad 1")
    (check-equal? (find-prime-using-WHILE 100) (find-prime-native 100) "Blad 2")
    (check-equal? (factorial 5) 120 "Blad 3")
    (check-equal? (add-one-to-n 999) 999 "Blad 4")
    (check-equal? (k-steps-with-m-variables 100 1000) 100 "Blad 5")
    (check-equal? (k-steps-with-m-variables 1000 100) 1000 "Blad 6")
    (check-equal? (find-prime-using-WHILE 1000) (find-prime-native 1000) "Blad 7")
    )))
(run-tests eval-tests)