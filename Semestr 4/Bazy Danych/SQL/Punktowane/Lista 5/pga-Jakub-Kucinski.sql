-- Jakub Kuciński, pga
-- Zadanie 1
-- Z treści zadania uważam, że powinniśmy liczyć tylko osoby mające przynajmniej 2 różne odznaki.
-- "oblicz liczbę postów napisanych przez posiadaczy różnych odznak"
WITH posiadacze_roznych_odznak AS (
    SELECT DISTINCT b1.userid 
    FROM badges b1 JOIN badges b2 ON b1.userid = b2.userid
    WHERE b1.name != b2.name
)
(SELECT b.name AS odznaka, COUNT(p.id) AS liczba
FROM posiadacze_roznych_odznak pro 
    JOIN badges b ON pro.userid = b.userid
    JOIN posts p ON b.userid = p.owneruserid
GROUP BY b.name
ORDER BY COUNT(p.id) DESC
);

-- Jednak pan Wieczorek napisał wieczorem, że chodziło o
-- 'można to rozumieć jako "Na podstawie tabeli badges oblicz liczbę postów napisanych przez posiadaczy poszczególnych odznak."'
-- Wtedy rozwiązaniem powinno być:
SELECT b.name AS odznaka, COUNT(p.id) AS liczba
FROM badges b JOIN posts p ON b.userid = p.owneruserid
GROUP BY b.name
ORDER BY COUNT(p.id) DESC;

-- Zadanie 2
CREATE OR REPLACE FUNCTION powtarzajace_sie(input text) RETURNS SETOF text AS $X$ 
BEGIN 
RETURN QUERY 
    SELECT match[1] FROM
            (SELECT DISTINCT regexp_matches(input,'(\w+\w+\w+)\s\1','g') as match) A;
RETURN;
END $X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION wyrazy() RETURNS SETOF text AS $X$
BEGIN
    RETURN QUERY 
        SELECT powtarzajace_sie(comments.text) FROM comments;
RETURN;
END $X$ LANGUAGE plpgsql;

SELECT DISTINCT wyrazy();


-- Zadanie 3
ALTER TABLE users ADD CONSTRAINT pk_users
    PRIMARY KEY(id);
ALTER TABLE posts ADD CONSTRAINT fk_posts_users
    FOREIGN KEY (owneruserid) REFERENCES users(id);

-- Wartość NULL w polu owneruserid może oznaczać, że konto użytkownika, 
-- który utworzył dany post z jakiegoś powodu już nie istnieje.
-- Jeśli chcemy zamienić wartość NULL z tej kolumny tak, 
-- aby nie utracić żadnych informacji możemy utworzyć nową tabelę,
-- która będzie przechowywała wszystkie posty, które nie mają przypisanego właściciela.
-- Drugą opcją może być przypisanie specjalnej, unikalnej wartości owneruserid każdemu
-- postowi, który zawiera wartość NULL w owneruserid. Można by dodać odpowiadającego
-- tej wartości specjalnego użytkownika do tabeli users. 

-- Utworzenie nowej tablicy na posty bez owneruserid będzie wymagać usuwania
-- wpisu z tabeli posts i dodaniu go do nowej tabeli za każdym razem,
-- gdy owneruserid zostanie zamieniony na NULL (potencjalne przypisanie właściciela
-- osieroconemu postowi wymagałoby odwrotnych operacji). Jednak taka struktura bazy
-- usprawnia zapytania odnoszące się tylko do postów posiadających właścicieli albo
-- tych nieposiadających właścicieli. Z drugiej strony utrudnia nieco zapytania
-- bazujące na obu tabelach.

-- Dodanie specjalnego użytkownika odpowiadającego wartości NULL nie powoduje znaczących
-- różnic w funkcjonowaniu bazy, ale dodaje niepotrzebne, nieintuicyjnie skomplikowanie.
-- Jeśli natomiast chcielibyśmy rozróżniać rodzaje postów o wartościach NULL w owneruserid
-- np. w celu rozróżnienia usunięcia konta użytkownika lub innej opercji, to moglibyśmy
-- w tym celu utworzyć kilku specjalnych użytkowników odpowiadających tym wartościom,
-- dzięki czemu mielibyśmy w bazie więcej informacji o danym poście.

-- Moim zdaniem spośród rozważonych opcji najlepiej pasuje tutaj pozostawienie wartości 
-- NULL w polach owneruserid, bo niekomplikuje to struktury bazy, a w przypadku chęci
-- ograniczenia zapytania do postów posiadających lub nieposiadających właścicieli
-- wystarczy użyć operatorów IS NULL lub IS NOT NULL.