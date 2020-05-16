#lang racket

(require racklog)

(define %rodzic ; (%rodzic x y) oznacza, że iks jest rodzicem igreka
  (%rel ()
        [('elżbieta2 'karol)]
        [('elżbieta2 'anna)]
        [('elżbieta2 'andrzej)]
        [('elżbieta2 'edward)]
        [('karol     'william)]
        [('karol     'harry)]
        [('anna      'piotr)]
        [('anna      'zara)]
        [('andrzej   'beatrycze)]
        [('andrzej   'eugenia)]
        [('edward    'james)]
        [('edward    'louise)]
        [('william   'george)]
        [('william   'charlotte)]
        [('william   'louis)]
        [('harry     'archie)]
        [('piotr     'savannah)]
        [('piotr     'isla)]
        [('zara      'mia)]
        [('zara      'lena)]))

(define %rok-urodzenia
  (%rel ()
        [('elżbieta2 1926)]
        [('karol     1948)]
        [('anna      1950)]
        [('andrzej   1960)]
        [('edward    1964)]
        [('william   1982)]
        [('harry     1984)]
        [('piotr     1977)]
        [('zara      1981)]
        [('beatrycze 1988)]
        [('euagenia  1990)]
        [('james     2007)]
        [('louise    2003)]
        [('george    2013)]
        [('charlotte 2015)]
        [('louis     2018)]
        [('archie    2019)]
        [('savannah  2010)]
        [('isla      2012)]
        [('mia       2014)]
        [('lena      2018)]))

(define %plec
  (%rel ()
        [('elżbieta2 'k)]
        [('karol     'm)]
        [('anna      'k)]
        [('andrzej   'm)]
        [('edward    'm)]
        [('william   'm)]
        [('harry     'm)]
        [('piotr     'm)]
        [('zara      'k)]
        [('beatrycze 'k)]
        [('euagenia  'k)]
        [('james     'm)]
        [('louise    'k)]
        [('george    'm)]
        [('charlotte 'k)]
        [('louis     'm)]
        [('archie    'm)]
        [('savannah  'k)]
        [('isla      'k)]
        [('mia       'k)]
        [('lena      'k)]))

(define %spadl-z-konia
  (%rel ()
        [('anna)]))

(define %jest-kobieta
  (%rel (x)
        [(x)
         (%plec x 'k)]))

(define %jest-mezczyzna
  (%rel (x)
        [(x) (%plec x 'm)]))

(define %babcia
  (%rel (x y z)
        [(x) (%jest-kobieta) (%rodzic x y) (%rodzic y z)]))

(define %prababcia
  (%rel (x y z w)
        [(x) (%jest-kobieta) (%rodzic x y) (%rodzic y z) (%rodzic z w)]))

(define %jest-prawnukiem
  (%rel (x y z w)
        [(w) (%rodzic x y) (%rodzic y z) (%rodzic z w)]))

(define %rok-urodzenia-prawnukow
  (%rel (x y z)
        [(x y z)
         (%jest-prawnukiem y x)
         (%rok-urodzenia y z)]))

(define %kuzyni-archiego
  (%rel (x z y a)
        [(a)
         (%rodzic y 'archie)
         (%rodzic x y)
         (%rodzic x z)
         (%rodzic z a)
         (%/= z y)
         ]))


(define %starsze-rodzenstwo
  (%rel (x y z rx yx)
        [(x y) (%jest-mezczyzna x)
               (%jest-kobieta y)
               (%rodzic z x)
               (%rodzic z y)]
        [(x y) (%jest-mezczyzna x)
               (%jest-mezczyzna y)
               (%rodzic z x)
               (%rodzic z y)
               (%rok-urodzenia x rx)
               (%rok-urodzenia y yx)
               (%> rx yx)]
        [(x y) (%jest-kobieta x)
               (%jest-kobieta y)
               (%rok-urodzenia x rx)
               (%rok-urodzenia y yx)
               (%> rx yx)]
        ))
(define %starsze-rodzenstwo2
  (%rel (x y wx wy rx ry)
        [(x y)
         (%jest-rodzenstwem x y)
         (%ta-sama-plec x y)
         (%wiek x wx)
         (%wiek y wy)
         (%> wx wy)]
        [(x y)
         (%jest-rodzenstwem x y)
         (%plec x 'm)
         (%plec y 'k)
         (%rok-urodzenia x rx)
         (%rok-urodzenia y ry)
         (%< ry 2011)]
        [(x y)
         (%jest-rodzenstwem x y)
         (%plec x 'm)
         (%plec y 'k)
         (%rok-urodzenia x rx)
         (%rok-urodzenia y ry)
         (%> ry 2011)
         (%< rx ry)]))

(define %jest-rodzenstwem
  (%rel (x y z)
        [(x y)
         (%rodzic z x)
         (%rodzic z y)]))
(define %wiek
  (%rel (rok x lata)
       [(x lata)
        (%rok-urodzenia x rok)
        (%is lata (- 2019 rok))]))
(define %ta-sama-plec
  (%rel (x y z)
        [(x y)
         (%plec x z)
         (%plec y z)]))


(define %pom
    (%rel (xs ys zs x)
          [(null xs xs)]
          [((cons x xs) ys zs)
           (%pom xs ys (cons x zs))]))

(define %rev
  (%rel (xs ys)
        [(null null)]
        [(xs ys) (%pom xs ys null)]))

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
         (%merge (cons x xs ) ys zs)]
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
         (%len bs n2)
         ;(%is n (+ n1 n2))
         (%mergesort as as2)
         (%mergesort bs bs2)
         (%merge as2 bs2 ys)]))

        #;[(null (cons y ys) (cons y zs))
         (%merge null ys zs)]
        #;[((cons x xs) null (cons x zs))
         (%merge xs null zs)]