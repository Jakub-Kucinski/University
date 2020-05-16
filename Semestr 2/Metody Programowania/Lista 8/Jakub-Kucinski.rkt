#lang racket
;Jakub Kuciński
(module my-module-1 racket
(provide (all-defined-out))

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

(define (lookup x xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x) (cadar xs)]
    [else (lookup x (cdr xs))]))

;; aktualizacja środowiska dla danej zmiennej (koniecznie już
;; istniejącej w środowisku!)

(define (update x v xs)
  (cond
    [(null? xs)
     (error x "unknown identifier :(")]
    [(eq? (caar xs) x)
     (cons (list (caar xs) v) (cdr xs))]
    [else
     (cons (car xs) (update x v (cdr xs)))]))

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
(define env-lookup lookup)
(define (env-add x v env) (cons (list x v) env))
(define env-update update)
(define env-discard cdr)
(define (env-from-assoc-list xs) xs)

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
(define (add-to-n m)
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

;; testujemy, żeby dowiedzieć się, jak dużo wydajności tracimy przez
;; uruchamianie programu w naszym interpreterze

(define (test)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance)))

(define (test-performance)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply find-prime-using-WHILE (list 11111111)))
       ((r2 cpu2 real2 gc2) (time-apply find-prime-native      (list 11111111))))
    (begin
      (display "WHILE  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "native time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))

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
)

;;Koniec modułu1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

















(module my-module-2 racket
(provide (all-defined-out))

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
;(define (env-add x v env) (begin (set! env (mcons (mcons x (mcons v null)) env)) env))
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
(define (add-to-n m)
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

;; testujemy, żeby dowiedzieć się, jak dużo wydajności tracimy przez
;; uruchamianie programu w naszym interpreterze

(define (test)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance)))

(define (test-performance)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply find-prime-using-WHILE (list 11111111)))
       ((r2 cpu2 real2 gc2) (time-apply find-prime-native      (list 11111111))))
    (begin
      (display "WHILE  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "native time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))




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
  
)

;;Koniec modułu2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(require (prefix-in mod1: 'my-module-1))
(require (prefix-in mod2: 'my-module-2))


;;Factorial
(define (test-performance2)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply mod1:factorial (list 111111)))
       ((r2 cpu2 real2 gc2) (time-apply mod2:factorial (list 111111))))
    (begin
      (display "Normal  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "Mutal time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))

(define (test2)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance2)))

;;Dodawanie 1 aż do n
(define (test-performance3)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply mod1:add-to-n (list 11111111)))
       ((r2 cpu2 real2 gc2) (time-apply mod2:add-to-n (list 11111111))))
    (begin
      (display "Normal  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "Mutal time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))

(define (test3)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance3)))

;;Fibonacci
(define (test-performance4)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply mod1:fibonacci (list 1111111)))
       ((r2 cpu2 real2 gc2) (time-apply mod2:fibonacci (list 1111111))))
    (begin
      (display "Normal  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "Mutal time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))

(define (test4)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance4)))


;;1000 zmiennych, 100000 obrotów pętli z dostępami do zmiennej na końcu listy
(define (test-performance6)
  (let-values
      (((r1 cpu1 real1 gc1) (time-apply mod1:k-steps-with-m-variables (list 100000 1000)))
       ((r2 cpu2 real2 gc2) (time-apply mod2:k-steps-with-m-variables (list 100000 1000))))
    (begin
      (display "Normal  time (cpu, real, gc): ")
      (display cpu1)  (display ", ")
      (display real1) (display ", ")
      (display gc1)   (display "\n")
      (display "Mutal time (cpu, real, gc): ")
      (display cpu2)  (display ", ")
      (display real2) (display ", ")
      (display gc2)   (display "\n"))))

(define (test6)
  (begin
    (display "wait...\n")
    (flush-output (current-output-port))
    (test-performance6)))


;factorial dla n=111111
;(test2)
;(test2)
;(test2)
;wait...
;Normal  time (cpu, real, gc): 17642, 17622, 5085
;Mutal time (cpu, real, gc): 16034, 16020, 3290
;wait...
;Normal  time (cpu, real, gc): 15126, 15112, 3052
;Mutal time (cpu, real, gc): 15256, 15241, 3096
;wait...
;Normal  time (cpu, real, gc): 16112, 16096, 3831
;Mutal time (cpu, real, gc): 15738, 15712, 3187

;add-to-n <- dodaje 1 do licznika aż osiągnie n, gdzie n=11111111
;(test3)
;(test3)
;(test3)
;wait...
;Normal  time (cpu, real, gc): 18249, 18235, 930
;Mutal time (cpu, real, gc): 19144, 19119, 1588
;wait...
;Normal  time (cpu, real, gc): 18769, 18739, 1591
;Mutal time (cpu, real, gc): 19128, 19101, 1526
;wait...
;Normal  time (cpu, real, gc): 18710, 18683, 1572
;Mutal time (cpu, real, gc): 19111, 19082, 1534

;;Fibonacci dla n=1111111
;(test4)
;(test4)
;(test4)
;wait
;Normal  time (cpu, real, gc): 24982, 23043, 4037
;Mutal time (cpu, real, gc): 22241, 22201, 3332
;wait...
;wait...
;Normal  time (cpu, real, gc): 23580, 23541, 3781
;Mutal time (cpu, real, gc): 22798, 22763, 3016
;wait...
;Normal  time (cpu, real, gc): 21723, 21692, 3166
;Mutal time (cpu, real, gc): 21759, 21728, 3243

;;1000 zmiennych, 100000 obrotów pętli z podstawieniami do zmiennej na końcu listy
;(test6)
;(test6)
;(test6)
;(test6)
;(test6)
;(test6)
;wait...
;Normal  time (cpu, real, gc): 16726, 16700, 2207
;Mutal time (cpu, real, gc): 13530, 13518, 113
;wait...
;Normal  time (cpu, real, gc): 15527, 15507, 1321
;Mutal time (cpu, real, gc): 12808, 12795, 18
;wait...
;Normal  time (cpu, real, gc): 14297, 14280, 185
;Mutal time (cpu, real, gc): 13275, 13265, 13
;wait...
;Normal  time (cpu, real, gc): 14304, 14291, 174
;Mutal time (cpu, real, gc): 13140, 13130, 15
;wait...
;Normal  time (cpu, real, gc): 14113, 14100, 177
;Mutal time (cpu, real, gc): 13264, 13253, 15
;wait...
;Normal  time (cpu, real, gc): 14322, 14309, 189
;Mutal time (cpu, real, gc): 13171, 13162, 15


;Z powyższych testów nasuwa się wniosek, że w przypadku gdy liczba zmiennych jest mała (<=3), to czas działania programów
;jest bardzo podobny, chociaż już nawet dla kilku zmiennych czas gc jest mniejszy dla mutowalnych list niż dla stałych.
;Jednak gdy liczba zmiennych jest duża (jak w teście6 -> 1000 zmiennych) i wykonujemy podstawienia do zmiennej
;zapisanej na końcu listy to czas działania programu operującego na liście stałej jest większy niż dla programu
;działającego na liście mutowalnej, gdyż w tym drugim przypadku nie musimy odbudowywać całej listy przy każdym podstawieniu.