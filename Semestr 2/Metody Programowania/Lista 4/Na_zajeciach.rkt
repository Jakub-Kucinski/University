#lang racket

(define (better-append . l)
  (if (null? l)
      null
      (append (car l) (apply better-append (cdr l)))))

(define (tagged-list? len sym x)
  (and (list? x)
       (= (length x) len)
       (eq? (first x) sym)))

(define leaf 'leaf)

(define (leaf? x)
  (eq? x 'leaf))

(define (node e l r)
  (list 'node e l r))

(define (node-elem x)
  (second x))

(define (node-left x)
  (third x))

(define (node-right x)
  (fourth x))

(define (node? x)
  (tagged-list? 4 'node x))

(define (btree? t)
  (or (eq? t 'leaf)
      (and (tagged-list? 4 'node t)
           (btree? (third t))      ; lub (caddr t)
           (btree? (fourth t))))) ; lub (cadddr t)

(define (insert x t)
  (cond
    [(leaf? t)            (node x leaf leaf)]
    [(= (node-elem t) x)  t]
    [(> (node-elem t) x)  (node (node-elem t)
                                (insert x (node-left t))
                                (node-right t))]
    [(< (node-elem t) x)  (node (node-elem t)
                                (node-left t)
                                (insert x (node-right t)))]))

(define (mirror t)
  (if (eq? t 'leaf)
      'leaf
      (list 'leaf (second t) (mirror (fourth t)) (mirror (third t)))))

(define (flatten t)
  (if (eq? t 'leaf)
      #;(list 'leaf)
      null
      (append (flatten (third t)) (cons (second t) (flatten (fourth t))))
      #;(better-append (list (flatten (third t))) (list (second t)) (list (flatten (fourth t)))) 
      #;(cons (flatten (third t)) (cons (second t) (flatten (fourth t))))
      ))

(define (flatten2 t)
  (define (help t xs)
    (if (leaf? t)
        xs
        (help (third t) (cons (second t) (help (fourth t) xs)))))
  (help t null))

(define (treesort xs)
  (define (maketree xs t)
    (if (null? xs)
        t
        (maketree (cdr xs) (insert (car xs) t))))
  (flatten2 (maketree xs 'leaf)))


(define (concatMap f xs)
  (if (null? xs)
      null
      (append (f (car xs)) (concatMap f (cdr xs)))))

(define (from-to s e)
  (if (= s e)
      (list s)
      (cons s (from-to (+ s 1) e))))

(define (queens board-size)
  ;; Return the representation of a board with 0 queens inserted
  (define (empty-board)
    (define (iter i)
      (if (= i board-size)
          (cons 0 null)
          (cons 0 (iter (+ i 1)))))
    (iter 1))
  ;; Return the representation of a board with a new queen at
  ;; (row, col) added to the partial representation `rest'
  (define (adjoin-position row col rest)
    (define (iter i tail)
      (if (= i col)
          (cons row tail)
          (cons (car tail) (iter (+ i 1) (cdr tail)))))
    (iter 1 rest))
  ;; Return true if the queen in k-th column does not attack any of
  ;; the others
  (define (safe? k positions)
    (define (get-row-of-k k)
      (define (iter i tail)
      (if (= i col)
          (car tail)
          (iter (+ i 1) (cdr tail))))
    (iter 1 positions))
    )
  ;; Return a list of all possible solutions for k first columns
  (define (queen-cols k)
    (if (= k 0)
        (list (empty-board))
        (filter
         (lambda (positions) (safe? k positions))
         (concatMap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (from-to 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

 