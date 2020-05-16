-- Jakub Kuciński, pga
-- Zadanie 1
CREATE VIEW ranking( 
    displayname, liczba_odpowiedzi) AS 
SELECT u1.displayname, COUNT(B.id) 
    FROM users u1 
        RIGHT JOIN posts A ON u1.id = A.owneruserid 
        JOIN posts B ON B.acceptedanswerid = A.id 
    GROUP BY u1.id, u1.displayname 
    ORDER BY COUNT(B.id) DESC, u1.displayname ASC;

SELECT * FROM ranking;

-- Zadanie 2
WITH u_z_odznaka AS (
        SELECT b1.userid AS id 
        FROM badges b1 
        WHERE b1.name = 'Enlightened'),
    u_upvotes_z_odznaka AS (
        SELECT DISTINCT users.id, users.upvotes 
        FROM badges 
            JOIN users ON badges.userid = users.id 
        WHERE badges.name = 'Enlightened'),
    u_z_wiecej_niz_1_kom AS (
        SELECT u.id 
        FROM users u 
            JOIN comments c ON u.id = c.userid 
        WHERE EXTRACT(YEAR FROM c.creationdate) = 2020 
        GROUP BY u.id 
        HAVING COUNT(DISTINCT c.id) > 1)
(SELECT u1.id, u1.displayname, u1.reputation 
FROM users u1 
    JOIN u_z_wiecej_niz_1_kom u2 ON u1.id = u2.id 
WHERE u1.id NOT IN (
        SELECT u3.id FROM u_z_odznaka u3) 
    AND u1.upvotes > (
        SELECT AVG(u4.upvotes) 
        FROM u_upvotes_z_odznaka u4) 
ORDER BY u1.creationdate ASC);

-- Zadanie 3
WITH RECURSIVE uzytkownicy(id, displayname) AS (
    (SELECT u.id, u.displayname 
    FROM users u 
        JOIN posts p ON u.id = p.owneruserid 
    WHERE p.body LIKE '%recurrence%') 
    UNION 
    (SELECT u1.id, u1.displayname 
    FROM users u1 
        JOIN comments c1 ON u1.id = c1.userid 
        JOIN posts p1 ON c1.postid = p1.id 
        JOIN uzytkownicy u2 ON p1.owneruserid = u2.id)
    ) 
(SELECT * FROM uzytkownicy);