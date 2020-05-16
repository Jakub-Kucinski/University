#lang racket
;;Jakub Kuciński

(require rackunit)
(require rackunit/text-ui)

;; procedury pomocnicze
(define (tagged-tuple? tag len x)
  (and (list? x)
       (=   len (length x))
       (eq? tag (car x))))

(define (tagged-list? tag x)
  (and (pair? x)
       (eq? tag (car x))
       (list? (cdr x))))

;; reprezentacja formuł w CNFie
;; zmienne
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

(define (var<? x y)
  (symbol<? x y))

;; literały
(define (lit pol var)
  (list 'lit pol var))

(define (pos x)
  (lit true (var x)))

(define (neg x)
  (lit false (var x)))

(define (lit? x)
  (and (tagged-tuple? 'lit 3 x)
       (boolean? (second x))
       (var? (third x))))

(define (lit-pol l)
  (second l))

(define (lit-var l)
  (third l))

;; klauzule
(define (clause? c)
  (and (tagged-list? 'clause c)
       (andmap lit? (cdr c))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? f)
  (and (tagged-list? 'cnf f)
       (andmap clause? (cdr f))))

(define (cnf . clauses)
  (cons 'cnf clauses))

(define (cnf-clauses f)
  (cdr f))

;; definicja rezolucyjnych drzew wyprowadzenia
(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (axiom c)
  (list 'axiom c))

(define (axiom-clause a)
  (second a))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (res x pf-pos pf-neg)
  (list 'resolve x pf-pos pf-neg))

(define (res-var p)
  (second p))
(define (res-proof-pos p)
  (third p))
(define (res-proof-neg p)
  (fourth p))

(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;;Procedura sprawdza czy podany dowód "pf" jest poprawny, zwraca jego wynik jeśli tak, wpp #f
(define (proof-result pf prop-cnf)
  ;; XXX: zaimplementuj
  ;;Procedura zwraca rezolwentę klauzul l i r względem zmiennej p
  (define (resolvent l r p)
    ;;Procedura pomocnicza zwraca klauzulę składającą się z literałów występujących w l i r (bez powtórzeń)
    (define (resolvent-helper l r)
      (if (null? l)                       ;;Jeśli l jest puste to znaczy że sprawdziliśmy całą listę l w poszukiwaniu duplikatów literałów (zwracamy r)
          r
          (if (eq? #f (member (car l) r)) ;;Jeśli pierwszy literał z l nie występuje w r to dodajemy go do klauzuli wynikowej, wpp sprawdzamy kolejny element l
              (cons (car l) (resolvent-helper (cdr l) r))
              (resolvent-helper (cdr l) r))))
    ;;Zwróć klauzulę składającą się z literałów występujących w l i r (bez powtórzeń) z usuniętą zmienną p
    (cons 'clause (resolvent-helper (remove (pos p) (clause-lits l))
                                    (remove (neg p) (clause-lits r)))))
  ;;Procedura sprawdza czy zmienna p występuje pozytywnie w klauzli positive-clause
  (define (is-positive positive-clause p)
    (if (eq? #f (member (pos p) (clause-lits positive-clause)))
        #f
        #t))
  ;;Procedura sprawdza czy zmienna p występuje negatywnie w klauzli negative-clause
  (define (is-negative negative-clause p)
    (if (eq? #f (member (neg p) (clause-lits negative-clause)))
        #f
        #t))
  ;;Procedura sprawdza czy klauzla (z axiomu) występuje w formule w cnfie, zwraca ją jeśli tak, wpp #f
  (define (find-clause clause-from-axiom)
    (if (eq? #f (member clause-from-axiom (cnf-clauses prop-cnf)))
        #f
        clause-from-axiom))
  ;;Główna procedura sprawdzająca czy poprawność dowodu rezolucyjnego, wylicza jego wynik jeśli istnieje, wpp #f.
  (define (check-proof pf)
    (cond [(axiom? pf) (find-clause (axiom-clause pf))]         ;;Jeśli pf jest axiomem to sprawdź czy jego clauzula występuje w cnfie
          [(res? pf) (let ([l (check-proof (res-proof-pos pf))] ;;Jeśli pf jest rezolwentą to oblicz jej lewą klauzlę i prawą klauzulę
                           [r (check-proof (res-proof-neg pf))] ;;oraz zmienną względem której będziemy prowadzić rezolucję.
                           [p (res-var pf)])
                       (if (or (eq? #f l) (eq? #f r))           ;;Jeśli obliczanie którejś z klauzul zwróci fałsz, to oznacza że dowód jest niepoprawny.
                           #f
                           (if (and (is-positive l p) (is-negative r p)) ;;Jeśli lewa i prawa podklauzle są dowiedzione poprawnie sprawdź
                               (resolvent l r p)                         ;;czy p wysępuje pozytywnie w lewej l i nagatywnie w prawej r
                               #f)))]                                    ;;Jeśli tak zwróć ich rezolwentę, wpp zwróć fałsz.
          [else #f]))                                           ;;Jeśli pf nie jest axiomem ani rezolwentą zwróć fałsz
  ;;Wywołanie głównej procedury
  (check-proof pf))

(define (check-proof? pf prop)
  (let ((c (proof-result pf prop)))
    (and (clause? c)
         (null? (clause-lits c)))))

;; XXX: Zestaw testów do zadania pierwszego

(define proof-result-tests
  (test-suite
   "Proof-result"
   (test-case
     "No null tests"
     (check-equal?  (proof-result '(axiom (clause (lit #t p) (lit #t q))) (cnf (clause (lit #t 'p) (lit #t 'q)))) '(clause (lit #t p) (lit #t q)) "Blad 1")
     ;;Przykład z treści zadania
     (check-equal?  (proof-result '(resolve q
                                            (resolve p (axiom (clause (lit #t p) (lit #t q)))
                                                     (axiom (clause (lit #f p) (lit #t q))))
                                            (resolve r (axiom (clause (lit #f q) (lit #t r)))
                                                     (axiom (clause (lit #f q) (lit #f r)))))
                                  '(cnf (clause (lit #f p) (lit #t q))
                                        (clause (lit #t p) (lit #t q))
                                        (clause (lit #f q) (lit #t r))
                                        (clause (lit #f q) (lit #f r)))) '(clause) "Blad 2")
     ;; r negatywne w pierwszej klauzuli
     (check-equal? (proof-result  '(resolve r (axiom (clause (lit #f q) (lit #f r)))
                                            (axiom (clause (lit #f q) (lit #f r))))
                                  '(cnf (clause (lit #f q) (lit #f r)))) #f "Blad 3")
     ;; r pozytywne w drugiej klauzli 
     (check-equal? (proof-result '(resolve r (axiom (clause (lit #f q) (lit #t r)))
                                            (axiom (clause (lit #f q) (lit #t r))))
                                 '(cnf (clause (lit #f q) (lit #t r)))) #f "Blad 4")
     ;; p nie występuje w pierwszej klauzuli
     (check-equal? (proof-result '(resolve p (axiom (clause (lit #f q) (lit #t r)))
                                            (axiom (clause (lit #f p) (lit #t q))))
                                 '(cnf (clause (lit #f p) (lit #t q))
                                        (clause (lit #t p) (lit #t q))
                                        (clause (lit #f q) (lit #t r))
                                        (clause (lit #f q) (lit #f r)))) #f "Blad 5")
     ;;p nie występuje w drugiej klauzuli
     (check-equal? (proof-result '(resolve p (axiom (clause (lit #t p) (lit #t q)))
                                            (axiom (clause (lit #f q) (lit #t r))))
                                 '(cnf (clause (lit #f p) (lit #t q))
                                        (clause (lit #t p) (lit #t q))
                                        (clause (lit #f q) (lit #t r))
                                        (clause (lit #f q) (lit #f r)))) #f "Blad 6"))
   (test-case
    "Tests with null"
    (check-equal? (proof-result '(axiom (clause (lit #t p) (lit #t q))) (cnf)) #f "Blad 7"))
   ))
(run-tests proof-result-tests)

;; Wewnętrzna reprezentacja klauzul

(define (sorted? ord? xs)
  (or (null? xs)
      (null? (cdr xs))
      (and (ord? (car xs)
                (cadr xs))
           (sorted? ord? (cdr xs)))))

(define (sorted-varlist? xs)
  (and (andmap var? xs)
       (sorted? var<? xs)))

(define (res-clause pos neg pf)
  (list 'res-clause pos neg pf))

(define (res-clause-pos rc)
  (second rc))
(define (res-clause-neg rc)
  (third rc))
(define (res-clause-proof rc)
  (fourth rc))

(define (res-clause? p)
  (and (tagged-tuple? 'res-clause 4 p)
       (sorted-varlist? (second p))
       (sorted-varlist? (third  p))
       (proof? (fourth p))))

;; implementacja zbiorów / kolejek klauzul do przetworzenia

;;Procedura sprawdza czy pierwsza z klauzul jest trudniejsza od drugiej (równoważnie czy c2 zawiera wszystkie literały z c1)
(define (subsumes? c1 c2)
  (define (include-lits l1 l2)
    (cond [(null? l1) #t] ;;Jeśli l1 jest pusta to skończyliśmy sprawdzanie
          [(null? l2) #f] ;;Jeśli l2 jest pusta to znaczy że l2 nie zawiera (car l1)
          [(eq? (car l1) (car l2)) (include-lits (cdr l1) (cdr l2))];;Jeśli głowy l1 i l2 są równe to sprawdź czy reszta l2 zawiera pozostałe literały z l1
          [(var<? (car l2) (car l1)) (include-lits l1 (cdr l2))];;Jeśli głowa l2 jest mniejsza niż głowa l1 to głowa l1 może być nadal w cdr l2
          [else #f])) ;;Gdy głowa l1 jest większa niż głowa l2, to głowy l1 nie ma w l2, zwróć #f
  (and (include-lits (res-clause-pos c1) (res-clause-pos c2))  ;;Sprawdzamy czy c2 zawiera wszystkie pozytywne literały c1
       (include-lits (res-clause-neg c1) (res-clause-neg c2))));;Sprawdzamy czy c2 zawiera wszystkie negatywne literały c1

;;Procedura przyjmuje jako argumenty klauzule (singleton) z jednym literałem-lit i zbiór klauzul (set) i zwraca zbiór z usuniętymi klauzulami,
;;w których występuje lit z tym samym znakiem co w singleton oraz wykonuje rezolucje wględem klauzul, w których występuje lit z przeciwnym znakiem.
(define (clause-set-map singleton set)
  ;;Procedura sprawdza czy x jest niełatwiejsze niż singleton
  (define (not-subsumes-right x) 
    (not (subsumes? singleton x)))
  ;;Procedura filtruje n-ty element (który jest listą klauzul) zbioru set przy użyciu not-subsumes-right
  (define (clause-number-map nth) 
    (clause-map singleton (filter not-subsumes-right (nth set))));;Następnie wywołuje clause-map na nowej liście
  ;;Procedura zmienia klauzulę c1 w założeniu że zmienna literal występowała pozytywnie w singleton
  (define (change-clause-pos-lit literal c1) 
    (let ([new-proof (if (member literal (res-clause-neg c1)) ;;Tworzenie dowodu nowej klauzuli w zależności od tego czy literal występuje negatywnie w c1
                         (res literal (res-clause-proof singleton) (res-clause-proof c1));;Jeśli tak to tworzymy odpowiedni dowód względem literału literal
                         (res-clause-proof c1))]);;Wpp zostawiamy dowód c1
      (list 'res-clause (res-clause-pos c1);;Literały pozytywne pozostają bez zmian
                  (remove literal (res-clause-neg c1));;Usuwamy literal z negatywnych literałów c1 (bo względem niego wykonaliśmy rezolucję)
                  new-proof)));;Wstawiamy nowy dowód
  ;;Procedura działa analogicznie do change-clause-pos-lit, z założeniem, że literal był negatywny w singleton
  (define (change-clause-neg-lit literal c1)
    (let ([new-proof (if (member literal (res-clause-pos c1))
                         (res literal (res-clause-proof c1) (res-clause-proof singleton))
                         (res-clause-proof c1))])
    (list 'res-clause (remove literal (res-clause-pos c1))
                  (res-clause-neg c1)
                  new-proof)))
  ;;Procedura w zależoności od tego czy literał w singleton jest pozywyny czy negatywny mapuje listę klauzul za pomocą change-clause-pos-lit lub change-clause-neg-lit
  (define (clause-map singleton list-clauses)
    (if (null? (res-clause-neg singleton))
        (map (lambda (x) (change-clause-pos-lit (car (res-clause-pos singleton)) x)) list-clauses)
        (map (lambda (x) (change-clause-neg-lit (car (res-clause-neg singleton)) x)) list-clauses)))
  ;;W zależności czy car od set jest stop czy run to filtrujemy i mapujemy odpowiednie listy klauzul za pomocą clause-number-map
  (if (eq? 'stop (car set))
      (list 'stop (clause-number-map second)
                  (clause-number-map third))
      (list 'run (clause-number-map second)
                   (clause-number-map third)
                   ;;Czwarty element zbioru z car równym run nie jest listą tylko pojedyńczą klauzulą, musimy rozpatrzyć ją osobno
                   (if (null? (res-clause-neg singleton)) 
                       (change-clause-pos-lit (car (res-clause-pos singleton)) (fourth set))
                       (change-clause-neg-lit (car (res-clause-neg singleton)) (fourth set)))
                   (clause-number-map fifth))))

                        
(define clause-set-empty
  '(stop () ()))

(define (clause-set-add rc rc-set)
  (define (eq-cl? sc)
    (and (equal? (res-clause-pos rc)
                 (res-clause-pos sc))
         (equal? (res-clause-neg rc)
                 (res-clause-neg sc))))
  ;;Procedura pomocnicza sprawdzająca czy klauzula x jest trudniejsza od rc
  (define (subsumes-left x)
    (subsumes? x rc))
  ;;Procedura pomocnicza sprawdzająca czy klauzula x jest niełatwiejsza od rc
  (define (not-subsumes-right x)
    (not (subsumes? rc x)))
  (define (add-to-stopped sset)
    (let ((procd  (cadr  sset))
          (toproc (caddr sset)))
      (cond
       [(null? procd) (list 'stop (list rc) '())]
       [(or (memf subsumes-left procd)  ;;Sprawdzamy czy w procd istnieje klauzula trudniejsza od rc
            (memf subsumes-left toproc))  ;;Sprawdzamy czy w toproc istnieje klauzula trudniejsza od rc
        sset];;Jeśli tak to nie dodajemy rc i zwracamy sset
       ;;Sprawdzenie czy klauzula rc zawiera tylko jeden literał
       [(or (and (null? (res-clause-pos rc))
                 (not (null? (res-clause-neg rc)))
                 (null? (cdr (res-clause-neg rc))))
            (and (null? (res-clause-neg rc))
                 (not (null? (res-clause-pos rc)))
                 (null? (cdr (res-clause-pos rc)))))
        (let ([new-set (clause-set-map rc sset)]) ;;Przetworzenie zbioru sset przy użyciu singletonu rc
          (list 'stop (cons rc (second new-set)) (third new-set)))] ;;Dołącznie rc do listy procd nowego zbioru 
       [else
        (let ([new-procd (filter not-subsumes-right procd)] ;;Usuwamy klauzule łatwiejsze niż rc z procd i toproc
              [new-toproc (filter not-subsumes-right toproc)])
          ;;Musimy sprawdzić przypadek gdy new-procd jest nullem, ponieważ clause-set-next-pair nie ma zaimplementowanej takiej sytuacji
          (if (null? new-procd) 
              (list 'stop (cons rc null) new-toproc) ;;Jeśli jest nullem to dodajemy rc do new-procd (null)
              (list 'stop new-procd (cons rc new-toproc))))])));;Wpp dodajemy rc do new-toproc
  (define (add-to-running rset)
    (let ((pd  (second rset))
          (tp  (third  rset))
          (cc  (fourth rset))
          (rst (fifth  rset)))
      ;;Sprawdzamy czy w odpowiednich listach istnieje klauzula trudniejsza od rc, jeśli tak to nie dodajemy rc - zwracamy rset
      (if (or (memf subsumes-left pd)
              (memf subsumes-left tp)
              (subsumes-left cc)
              (memf subsumes-left rst))
          rset
          ;;Sprawdzenie czy klauzula rc zawiera tylko jeden literał
          (if (or (and (null? (res-clause-pos rc))
                 (not (null? (res-clause-neg rc)))
                 (null? (cdr (res-clause-neg rc))))
            (and (null? (res-clause-neg rc))
                 (not (null? (res-clause-pos rc)))
                 (null? (cdr (res-clause-pos rc)))))
              (let ([new-set (clause-set-map rc rset)]) ;;Przetworzenie zbioru rset przy użyciu singletonu rc
                    (list 'run (cons rc (second new-set)) (third new-set) (fourth new-set) (fifth new-set)));;Dodajemy rc do nowego pd
              ;;Wpp usuwamy klauzule łatwiejsze niż rc z odpowiednich zbiorów
          (let ([new-pd (filter not-subsumes-right pd)]
                [new-tp (filter not-subsumes-right tp)]
                [new-rst (filter not-subsumes-right rst)])
            ;;Musimy sprawdzić przypadek gdy new-procd jest nullem, ponieważ clause-set-next-pair nie ma zaimplementowanej takiej sytuacji
            (if (null? new-tp) ;;Jeśli tak to skończyła nam się lista klauzul do przetworzenia (new-tp) więc tworzymy zbiór 'stop
                (list 'stop (cons cc new-pd) (cons rc new-rst));;i dodajemy do przetworzonych (new-pd) cc oraz do listy do przetworzenia (new-rst) rc
                (list 'run new-pd new-tp cc (cons rc new-rst))))))));;Tworzymy zbiór 'run z nowymi listami klauzul i do new-rst dodajemy rc
  (if (eq? 'stop (car rc-set))
      (add-to-stopped rc-set)
      (add-to-running rc-set)))

(define (clause-set-done? rc-set)
  (and (eq? 'stop (car rc-set))
       (null? (caddr rc-set))))

(define (clause-set-next-pair rc-set)
  (define (aux rset)
    ;(if (null? (third rset))
     ;   (clause-set-next-pair (list 'stop (cons (fourth rset) (second rset)) (fifth rset)))
    (let* ((pd  (second rset))
           (tp  (third  rset))
           (nc  (car tp))
           (rtp (cdr tp))
           (cc  (fourth rset))
           (rst (fifth  rset))
           (ns  (if (null? rtp)
                    (list 'stop (cons cc (cons nc pd)) rst)
                    (list 'run  (cons nc pd) rtp cc rst))))
      (cons cc (cons nc ns))));)
  (if (eq? 'stop (car rc-set))
      (let ((pd (second rc-set))
            (tp (third  rc-set)))
        (aux (list 'run '() pd (car tp) (cdr tp))))
      (aux rc-set)))

(define (clause-set-done->clause-list rc-set)
  (and (clause-set-done? rc-set)
       (cadr rc-set)))

;; konwersja z reprezentacji wejściowej na wewnętrzną

(define (clause->res-clause cl)
  (let ((pos (filter-map (lambda (l) (and (lit-pol l) (lit-var l)))
                         (clause-lits cl)))
        (neg (filter-map (lambda (l) (and (not (lit-pol l)) (lit-var l)))
                         (clause-lits cl)))
        (pf  (axiom cl)))
    (res-clause (sort pos var<?) (sort neg var<?) pf)))

;; tu zdefiniuj procedury pomocnicze, jeśli potrzebujesz

;;Procedura pomocnicza sprawdzająca czy istnieje zmienna taka, że występuje w obu listach l1 i l2
;;Korzystam z faktu, że listy literałów są uporządkowane alfabetycznie przez predykat var<?
;;Jeśli taka zmienna istnieje, zwraca ją, wpp #f.
(define (find-same-var-in-lists l1 l2)
    (if (or (null? l1) (null? l2))                       ;;Jeśli któraś z list jest pusta, zwracamy #f
        #f
        (if (eq? (car l1) (car l2))                      ;;Jeśli pierwsze elementy list są równe, zwróć pierwszy z nich
            (car l1)
            (if (var<? (car l1) (car l2))                ;;Jeśli car l1 jest mniejszy od car l2 to znaczy, żę car l1 jest
                (find-same-var-in-lists (cdr l1) l2)     ;;najmniejszy ze wszystkich elementów w l1 i l2, kontynuuj sprawdzanie dla cdr l1 i l2,
                (find-same-var-in-lists l1 (cdr l2)))))) ;;wpp car l2 jest najmniejszy i kontunuujemy sprawdzanie dla l1 i cdr l2

;;Procedura sprawdza czy klauzula jest trywialna (spełnialna dla każdego wartościowania)
(define (rc-trivial? rc)
  ;; XXX: uzupełnij
  (if (eq? #f (find-same-var-in-lists (res-clause-pos rc) (res-clause-neg rc))) ;;Jeśli istnieje zmienna p, taka że występuje w zmiennych pozytywnych
      #f                                                                        ;;i zmiennych negatywnych klauzli to klazula jest trywialna.
      #t))

;;Procedura zwraca rezolwentę dwóch klauzul lub #f gdy ta nie istnieje
(define (rc-resolve rc1 rc2)
  ;; XXX: uzupełnij
  ;;Procedura łączy dwie listy w jedną bez powtórzeń.
  ;;Działanie procedury jest analogiczne do procedury find-same-var-in-lists. Wykorzystuje fakt, że zmienne są uporządkowane alfabetycznie.
  (define (unite l1 l2)
    (cond [(null? l1) l2]
          [(null? l2) l1]
          [(eq? (car l1) (car l2)) (cons (car l1) (unite (cdr l1) (cdr l2)))]
          [(var<? (car l1) (car l2)) (cons (car l1) (unite (cdr l1) l2))]
          [else (cons (car l2) (unite l1 (cdr l2)))]))

  ;;Sprawdzenie czy istnieje zmienna należąca jednocześnie do zmiennych pozytywnych rc1 i negatywnych rc2
  (let ([p (find-same-var-in-lists (res-clause-pos rc1) (res-clause-neg rc2))])
    (if (eq? #f p) ;;Jeśli nie istnieje taka zmienna, to sprawdzamy czy istnieje zmienna należąca jednocześnie do pozytywnych rc1 i negatywnych rc2
        (let ([p (find-same-var-in-lists (res-clause-pos rc2) (res-clause-neg rc1))])
          (if (eq? #f p) ;;Jeśli nie istnieje to znaczy że nie można utworzyć rezolwenty tych klauzul, zwracamy #f
              #f
              (let ([new-positives (unite (res-clause-pos rc1) (remove p (res-clause-pos rc2)))] ;;Tworzymy nowe listy zmiennych pozytywnych i negatywnych
                    [new-negatives (unite (remove p (res-clause-neg rc1)) (res-clause-neg rc2))] ;;w oparciu o zmienne w rc1 i rc2. Usuwamy z odpowiednich list
                    [new-proof (res p (res-clause-proof rc2) (res-clause-proof rc1))])           ;;zmienną względej której prowadzimy rezolucję. Tworzymy
                (res-clause new-positives new-negatives new-proof))))                            ;;ścieżkę skąd pochodzi nowa klauzula (nowy dowód).
         (let ([new-positives (unite (remove p (res-clause-pos rc1)) (res-clause-pos rc2))]      ;;Zwracamy nową klauzulę.
               [new-negatives (unite (res-clause-neg rc1) (remove p (res-clause-neg rc2)))]      ;;Analogicznie postępujemy w przypadku gdy istniała wspólna
               [new-proof (res p (res-clause-proof rc1) (res-clause-proof rc2))])                ;;zmienna pozytywnych rc1 i negatywnych rc2.
           (res-clause new-positives new-negatives new-proof)))))

(define (fixed-point op start)
  (let ((new (op start)))
    (if (eq? new false)
        start
        (fixed-point op new))))

(define (cnf->clause-set f)
  (define (aux cl rc-set)
    (clause-set-add (clause->res-clause cl) rc-set))
  (foldl aux clause-set-empty (cnf-clauses f)))

(define (get-empty-proof rc-set)
  ;(write (second rc-set))
  (define (rc-empty? c)
    (and (null? (res-clause-pos c))
         (null? (res-clause-neg c))))
  (let* ((rcs (clause-set-done->clause-list rc-set))
         (empty-or-false (findf rc-empty? rcs)))
    (and empty-or-false
         (res-clause-proof empty-or-false))))

(define (improve rc-set)
  (if (clause-set-done? rc-set)
      false
      (let* ((triple (clause-set-next-pair rc-set))
             (c1     (car  triple))
             (c2     (cadr triple))
             (rc-set (cddr triple))
             (c-or-f (rc-resolve c1 c2)))
        (if (and c-or-f (not (rc-trivial? c-or-f)))
            (clause-set-add c-or-f rc-set)
            rc-set))))

(define (prove cnf-form)
  (let* ((clauses (cnf->clause-set cnf-form))
         (sat-clauses (fixed-point improve clauses))
         (pf-or-false (get-empty-proof sat-clauses)))
    (if (eq? pf-or-false false)
        'sat
        (list 'unsat pf-or-false))))

;; XXX: Zestaw testów do zadania drugiego
(define rc-trivial-tests
  (test-suite
   "Trivial tests"
   (test-case
     "No null tests"
     (check-equal? (rc-trivial? (res-clause '(a c e g) '(b d f h) true)) #f "Blad 1")
     (check-equal? (rc-trivial? (res-clause '(c d f g) '(e f g h i) true)) #t "Blad 2"))
   (test-case
    "Tests with null"
    (check-equal? (rc-trivial? (res-clause '(a c e g) '() true)) #f "Blad 3")
    (check-equal? (rc-trivial? (res-clause '() '(b d f h) true)) #f "Blad 4")
    (check-equal? (rc-trivial? (res-clause '() '() true)) #f "Blad 5"))
   ))
(run-tests rc-trivial-tests)


(define resolve-by-prove-tests
  (test-suite
   "Resolve-prove"
   (test-case
     "No null tests"
     (check-equal? (check-proof? (cadr (prove '(cnf (clause (lit #f p) (lit #t q))
                                (clause (lit #t p) (lit #t q))
                                (clause (lit #f q) (lit #t r))
                                (clause (lit #f q) (lit #f r)))))
                                 '(cnf (clause (lit #f p) (lit #t q))
                                (clause (lit #t p) (lit #t q))
                                (clause (lit #f q) (lit #t r))
                                (clause (lit #f q) (lit #f r)))) #t "Blad 1")
     (check-equal? (check-proof? (cadr (prove '(cnf (clause (lit #f p))
                                                    (clause (lit #t p)))))
                                 '(cnf (clause (lit #f p))
                                                    (clause (lit #t p)))) #t "Blad 2")
     (check-equal? (prove '(cnf (clause (lit #f p))
                               (clause (lit #t q) (lit #f r))
                               (clause (lit #f q) (lit #t r)))) 'sat "Blad 3")
     (check-equal? (check-proof? (cadr (prove '(cnf
                                                (clause (lit #f t) (lit #f y))
                                                (clause (lit #t s) (lit #f x))
                                                (clause (lit #f x) (lit #f y) (lit #t z))
                                                (clause (lit #t t) (lit #t x))
                                                (clause (lit #t u) (lit #t y))
                                                (clause (lit #f u) (lit #t y))
                                                (clause (lit #f s))
                                                (clasue (lit #t v)))))
                                              '(cnf
                                                (clause (lit #f t) (lit #f y))
                                                (clause (lit #t s) (lit #f x))
                                                (clause (lit #f x) (lit #f y) (lit #t z))
                                                (clause (lit #t t) (lit #t x))
                                                (clause (lit #t u) (lit #t y))
                                                (clause (lit #f u) (lit #t y))
                                                (clause (lit #f s))
                                                (clasue (lit #t v))))
                                  #t "Blad5"))
   (test-case
    "Tests with null"
    (check-equal? (prove '(cnf)) 'sat "Blad 4"))
   ))
(run-tests resolve-by-prove-tests)


(define subsumes-tests
  (test-suite
   "subsumes? tests"
   (test-case
    "Tests"
    (check-equal? (subsumes? (list 'res-clause '(a b c) '(h i j) #t)
                             (list 'res-clause '(a b c d) '(g h i j) #t)) #t "Blad 1")
    (check-equal? (subsumes? (list 'res-clause '(b c d) '(h i j) #t)
                             (list 'res-clause '(a b c d) '(g h i j) #t)) #t "Blad 2")
    (check-equal? (subsumes? (list 'res-clause '() '() #t)
                             (list 'res-clause '() '() #t)) #t "Blad 3")
    (check-equal? (subsumes? (list 'res-clause '(a) '() #t)
                             (list 'res-clause '() '(a) #t)) #f "Blad 4")
    (check-equal? (subsumes? (list 'res-clause '() '(a) #t)
                             (list 'res-clause '(a) '() #t)) #f "Blad 5")
    )))
(run-tests subsumes-tests)

(define clause-set-map-tests
  (test-suite
   "clause-set-map-tests"
   (test-case
    "Tests"
    (check-equal? (clause-set-map (list 'res-clause '(a) '() #t)
                                  (list 'stop (list (list 'res-clause '(a b c) '(f) #t)
                                                    (list 'res-clause '(b c) '(a f g) #t)) null))
                  '(stop ((res-clause (b c) (f g) (resolve a #t #t))) ()) "Blad 1")
    (check-equal? (clause-set-map (list 'clause '(a) '() #t)
                                  (list 'stop
                                        (list (list 'clause '(a b c) '(f) #t)
                                                    (list 'clause '(b c) '(a f g) #t))
                                        (list (list 'clause '(b c) '(d f) #t))))
                  '(stop
                    ((res-clause (b c) (f g) (resolve a #t #t)))
                    ((res-clause (b c) (d f) #t))) "Blad 2")
    (check-equal? (clause-set-map (list 'clause '() '(f) #t)
                                  (list 'stop
                                        (list (list 'clause '(a b c) '(f) #t)
                                                    (list 'clause '(b c) '(a f g) #t))
                                        (list (list 'clause '(b c) '(d f) #t))))
                  '(stop () ()) "Blad 3")
    )))
(run-tests clause-set-map-tests)
