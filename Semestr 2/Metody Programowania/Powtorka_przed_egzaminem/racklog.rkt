#lang racket

(require racklog)


(define %repeated
  (%rel (p n1 n2 res res2)
        [(p 0 identity)]
        [(p n1 res)
         (%repeated p n2 res2)
         (%is n1 (+ n2 1))
         (%is res (compose p res2))
                   ]))

(define %len
  (%rel (n x xs m)
        [(null 0)]
        [((cons x xs) n)
         (%len xs m)
         (%is n (+ 1 m))]))

(define %merge
  (%rel (xs ys zs x y)
        [(null ys ys)]
        [(xs null xs)]
        [((cons x xs) (cons y ys) (cons x zs))
         (%< x y)
         (%merge xs (cons y ys) zs)]
        [((cons x xs) (cons y ys) (cons y zs))
         (%<= y x)
         (%merge (cons x xs) ys zs)]
        )) 

(define %mergesort
  (%rel (xs ys as bs as2 bs2 x n n1 n2)
        [(null null)]
        [((cons x null) (cons x null))]
        [(xs ys)
         (%len xs n)
         (%append as bs xs)
         (%len as n1)
         (%is n1 (quotient n 2))
         (%mergesort as as2)
         (%mergesort bs bs2)
         (%merge as2 bs2 ys)]))

(define %pom
  (%rel (xs ys acc x)
          [(null ys ys)]
          [((cons x xs) ys acc)
           (%pom xs ys (cons x acc))]))

(define %rev
  (%rel (xs ys)
        [(null null)]
        [(xs ys) (%pom xs ys null)]))


(define %sorted
  (%rel (x y xs)
        [(null)]
        [((cons x null))]
        [((cons x (cons y xs))) (%<= x y)
                              (%sorted (cons y xs))]))

(define %contain
  (%rel (x y xs)
        [(x (cons x xs))]
        [(x (cons y xs)) (%contain x xs)]))

(define %remove
  (%rel (x xs y ys)
        [(x (cons x xs) xs)]
        [(x (cons y xs) (cons y ys))
         (%remove x xs ys)]))

(define %is-permutation
  (%rel (xs ys zs x)
        [(null null)]
        [((cons x xs) ys)
         (%contain x ys)
         (%remove x ys zs)
         (%is-permutation xs zs)
         ]))

(define %permutation-sort
  (%rel (xs ys)
        [(xs ys) (%is-permutation ys xs)
                 (%sorted ys)
                 ]))

(define %knapsack
  (%rel (n xs rs x m)
        [(0 xs null)]
        [(n (cons x xs) (cons x rs)) (%< 0 n)
                            (%is m (- n x))
                            (%knapsack m xs rs)]
        [(n (cons x xs) rs) (%< 0 n)
                            (%knapsack n xs rs)]))

(define %combine
  (%rel (xs ys zs x)
        [(null null null)]
        [((cons x xs) ys (cons x zs)) (%combine xs ys zs)]
        [(xs (cons x ys) (cons x zs)) (%combine xs ys zs)]))


(define (run-concurrent . thunks)
  (define threads (map thread thunks))
  (for-each thread-wait threads))

(define (make-serializer)
  (define sem (make-semaphore 1))
  (lambda (proc)
    (lambda args
      (semaphore-wait sem)
      (define ret (apply proc args))
      (semaphore-post sem)
      ret)))

(define x 5)
(define s (make-serializer))
(run-concurrent
 (lambda ()
   (s (set! x (+ x x)))
   (s (set! x (+ x 3))))
 (lambda ()
   (s (set! x (+ x 2))))
 )

(define (mreverse xs)
  (define (help ys)
    (if (null? (mcdr ys))
        ys
        (begin (help (mcdr ys))
               (set-mcdr! (mcdr ys) ys))))
  (if (null? xs)
      xs
      (begin (help xs)
             (set-mcdr! xs null))))