#lang racket
;;Jakub Kuciński

(require rackunit)
(require rackunit/text-ui)

(define (inc n)
  (+ n 1))

;;; tagged lists
(define (tagged-list? len-xs tag xs)
  (and (list? xs)
       (= len-xs (length xs))
       (eq? (first xs) tag)))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (tagged-list? 5 'hnode h)
       (natural? (caddr h))))

;;Konstruktor węzła kopca.
(define (make-hnode elem heap-a heap-b)
  ;;Przypisanie do zmiennych a-rank i b-rank rang kopców heap-a i heap-b.
  (let ([a-rank (rank heap-a)]
        [b-rank (rank heap-b)])
    ;;Jeśli ranga kopca b jest większa niż ranga kopca a to rangą węzłą będzie ranga a
    ;;powiększona o 1, prawym poddrzewem będzie a, a lewym b. W przeciwnym wypadku
    ;;rangą węzła będzie ranga b powiększona o 1, prawym poddrzewem będzie b, a lewym a.
    (if (> b-rank a-rank)
        (list 'hnode elem (inc a-rank) heap-b heap-a)
        (list 'hnode elem (inc b-rank) heap-a heap-b))))

(define (hnode-elem h)
  (second h))

(define (hnode-left h)
  (fourth h))

(define (hnode-right h)
  (fifth h))

(define (hnode-rank h)
  (third h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (hnode-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (hnode-left h))
           (heap? (hnode-right h))
           (<= (rank (hnode-right h))
               (rank (hnode-left h)))
           (= (rank h) (inc (rank (hnode-right h))))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-left h))
           (hord? (elem-priority (hnode-elem h))
                  (hnode-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (hnode-rank h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-hnode elt leaf leaf)))

(define (heap-min heap)
  (hnode-elem heap))

(define (heap-pop heap)
  (heap-merge (hnode-left heap) (hnode-right heap)))


;;Procedura łącząca dwa kopce w jeden (rekurencyjnie).
(define (heap-merge h1 h2)
  (cond
    ;;Jeśli któryś z kopców jest liściem, to zwróć drugi z nich.
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   ;;Jeśli najmniejszego elementu z kopca h1 jest mniejszy niż najmniejszy
   ;;element z kopca h2 to zwracamy węzeł stworzony z najmniejszego elementu h1, lewego poddrzewa
   ;;kopca h1 i rekurencyjnie połączonych kopca h2 i prawego poddrzewa kopca h1.
   ;;W przeciwnym wypadku zwracany jest analogiczny węzeł z odpowienio zamienionymi miejscami h1 i h2
   [(< (elem-priority (heap-min h1)) (elem-priority (heap-min h2)))
    (make-hnode (heap-min h1) (heap-merge (hnode-right h1) h2) (hnode-left h1))] 
   [else (make-hnode (heap-min h2) (heap-merge (hnode-right h2) h1) (hnode-left h2))]))


;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))


(define merge-tests
  (test-suite
   "Tests of sorting with filled gaps in make-hnode and heap-merge procedures"
   (test-case
     "No null tests"
     (check-equal? (sorted? (heapsort (randlist 1 100))) #t)
     (check-equal? (sorted? (heapsort (randlist 10 100))) #t)
     (check-equal? (sorted? (heapsort (randlist 1000 100))) #t)
     (check-equal? (sorted? (heapsort (randlist 100 100000))) #t)
     (check-equal? (sorted? (heapsort (randlist 100 1))) #t))
   (test-case
    "Tests with null"
    (check-equal? (heapsort (list)) null))
   ))
(define random-list (randlist 10 100))

random-list

(heapsort random-list)

(run-tests merge-tests)