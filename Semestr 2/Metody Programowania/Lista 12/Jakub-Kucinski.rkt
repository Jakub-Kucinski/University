#lang racket
;;Jakub Kuciński
;; sygnatura: grafy
(define-signature graph^
  ((contracted
    [edge?        (-> any/c boolean?)]
    [edge         (-> any/c any/c edge?)]
    [edge-start   (-> edge? any/c)]
    [edge-end     (-> edge? any/c)]
    [graph?       (-> any/c boolean?)]
    [graph        (-> list? (listof edge?) graph?)]
    [graph-nodes  (-> graph? list?)]
    [graph-edges  (-> graph? (listof edge?))]
    [has-node?    (-> graph? any/c boolean?)]
    [outnodes     (-> graph? any/c list?)]
    [remove-node  (-> graph? any/c graph?)]
    )))

;; prosta implementacja grafów
(define-unit simple-graph@
  (import)
  (export graph^)

  (define (graph? g)
    (and (list? g)
         (eq? (length g) 3)
         (eq? (car g) 'graph)))

  (define (edge? e)
    (and (list? e)
         (eq? (length e) 3)
         (eq? (car e) 'edge)))

  (define (graph-nodes g) (cadr g))

  (define (graph-edges g) (caddr g))

  (define (graph n e) (list 'graph n e))

  (define (edge n1 n2) (list 'edge n1 n2))

  (define (edge-start e) (cadr e))

  (define (edge-end e) (caddr e))

  (define (has-node? g n) (not (not (member n (graph-nodes g)))))
  
  (define (outnodes g n)
    (filter-map
     (lambda (e)
       (and (eq? (edge-start e) n)
            (edge-end e)))
     (graph-edges g)))

  (define (remove-node g n)
    (graph
     (remove n (graph-nodes g))
     (filter
      (lambda (e)
        (not (eq? (edge-start e) n)))
      (graph-edges g)))))

;; sygnatura dla struktury danych
(define-signature bag^
  ((contracted
    [bag?       (-> any/c boolean?)]
    [bag-empty? (-> bag? boolean?)]
    [empty-bag  (and/c bag? bag-empty?)]
    [bag-insert (-> bag? any/c (and/c bag? (not/c bag-empty?)))]
    [bag-peek   (-> (and/c bag? (not/c bag-empty?)) any/c)]
    [bag-remove (-> (and/c bag? (not/c bag-empty?)) bag?)])))

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag? b)
    (and (list? b)
         (eq? (car b) 'stack)))

  (define (bag-empty? b)
    (null? (cdr b)))
  
  (define empty-bag
    (list 'stack))

  (define (bag-insert b v)
    (cons 'stack (cons v (cdr b))))

  (define (bag-peek b)
    (cadr b))

  (define (bag-remove b)
    (cons 'stack (cddr b)))
)

;; struktura danych - kolejka FIFO
;; do zaimplementowania przez studentów
(define-unit bag-fifo@
  (import)
  (export bag^)

  (define (bag? b)
    (and (list b)
         (eq? 'queue (car b))
         (list? (second b))
         (list? (third b))))

  (define (bag-empty? b)
    (and (null? (second b))
         (null? (third b))))
  
  (define empty-bag
    (list 'queue (list) (list)))

  (define (bag-insert b v)
    (if (null? (third b))
        (list 'queue (list) (reverse (cons v (second b))))
        (list 'queue (cons v (second b)) (third b))))

  (define (bag-peek b)
    (car (third b)))

  (define (bag-remove b)
    (if (null? (cdr (third b)))
        (list 'queue (list) (reverse (second b)))
        (list 'queue (second b) (cdr (third b)))))
)

;; sygnatura dla przeszukiwania grafu
(define-signature graph-search^
  (search))

;; implementacja przeszukiwania grafu
;; uzależniona od implementacji grafu i struktury danych
(define-unit/contract graph-search@
  (import bag^ graph^)
  (export (graph-search^
           [search (-> graph? any/c (listof any/c))]))
  (define (search g n)
    (define (it g b l)
      (cond
        [(bag-empty? b) (reverse l)]
        [(has-node? g (bag-peek b))
         (it (remove-node g (bag-peek b))
             (foldl
              (lambda (n1 b1) (bag-insert b1 n1))
              (bag-remove b)
              (outnodes g (bag-peek b)))
             (cons (bag-peek b) l))]
        [else (it g (bag-remove b) l)]))
    (it g (bag-insert empty-bag n) '()))
  )

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
;; TODO: napisz inne testowe grafy!
(define test-graph2
  (graph
   (list 1 2 3 4 5 6 7 8)
   (list (edge 1 2)
         (edge 1 3)
         (edge 2 4)
         (edge 2 5)
         (edge 3 6)
         (edge 3 7))))

(define test-graph3
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 1 4)
         (edge 2 1)
         (edge 2 3)
         (edge 4 1)
         (edge 4 3)
         (edge 3 2)
         (edge 3 4))))

(define test-graph4
  (graph
   (list 1 2 3 4)
   (list (edge 2 3)
         (edge 2 1)
         (edge 2 4))))

(define test-graph5
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 4)
         (edge 4 5)
         (edge 5 1))))

(define test-graph6
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2) (edge 1 3) (edge 1 4) (edge 1 5)
         (edge 2 1) (edge 2 3) (edge 2 4) (edge 2 5)
         (edge 3 1) (edge 3 2) (edge 3 4) (edge 3 5)
         (edge 4 1) (edge 4 2) (edge 4 3) (edge 4 5)
         (edge 5 1) (edge 5 2) (edge 5 3) (edge 5 4))))
         

;; otwarcie komponentu stosu
(define-values/invoke-unit/infer bag-stack@)
;; opcja 2: otwarcie komponentu kolejki
;(define-values/invoke-unit/infer bag-fifo@)

;; testy w Quickchecku
(require quickcheck)

;; test przykładowy: jeśli do pustej struktury dodamy element
;; i od razu go usuniemy, wynikowa struktura jest pusta
(quickcheck
 (property ([s arbitrary-symbol])
           (bag-empty? (bag-remove (bag-insert empty-bag s)))))
;; TODO: napisz inne własności do sprawdzenia!
;; jeśli jakaś własność dotyczy tylko stosu lub tylko kolejki,
;; wykomentuj ją i opisz to w komentarzu powyżej własności

;;Kolejka/Stos
;;Jeśli do pustej struktury dodamy dowolny element s
;;i odrazu pobierzemy element ze struktury, to dostaniemy s.
(quickcheck
 (property ([s arbitrary-symbol])
           (eq? (bag-peek (bag-insert empty-bag s)) s)))


;;Stos
;;Jeśli do stosu dodamy dwa elementy i pobierzemy jeden,
;;to ten pobrany będzie drugim dodanym
#;(quickcheck
 (property ([s1 arbitrary-symbol]
            [s2 arbitrary-symbol])
           (eq? (bag-peek (bag-insert (bag-insert empty-bag s1) s2)) s2)))


;;Kolejka
;;Jeśli do kolejki dodamy dwa elementy i pobierzemy jeden,
;;to ten pobrany będzie pierwszym dodanym
#;(quickcheck
 (property ([s1 arbitrary-symbol]
            [s2 arbitrary-symbol])
           (eq? (bag-peek (bag-insert (bag-insert empty-bag s1) s2)) s1)))



;;Stos
;;Jeśli do stosu dodamy dwa elementy, usuniemy jeden i pobierzemy jeden,
;;to ten pobrany będzie pierwszym dodanym
#;(quickcheck
 (property ([s1 arbitrary-symbol]
            [s2 arbitrary-symbol])
           (eq? (bag-peek (bag-remove (bag-insert (bag-insert empty-bag s1) s2))) s1)))


;;Kolejka
;;Jeśli do kolejki dodamy dwa elementy, usuniemy jeden i pobierzemy jeden,
;;to ten pobrany będzie drugim dodanym
#;(quickcheck
 (property ([s1 arbitrary-symbol]
            [s2 arbitrary-symbol])
           (eq? (bag-peek (bag-remove (bag-insert (bag-insert empty-bag s1) s2))) s2)))


;; otwarcie komponentu przeszukiwania
(define-values/invoke-unit/infer graph-search@)

;; uruchomienie przeszukiwania na przykładowym grafie
(search test-graph 1)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach!
(search test-graph2 1)

(search test-graph3 1)

(search test-graph4 1)

(search test-graph5 1)

(search test-graph6 1)