-- Jakub Kuciński, grupa Paweł Garncarek
-- Zadanie 1
SELECT creationdate FROM posts WHERE body LIKE '%Turing%' ORDER BY creationdate DESC;

-- Zadanie 2
SELECT id, title FROM posts WHERE (creationdate)::date > '2018-10-10' AND EXTRACT(MONTH FROM creationdate) BETWEEN 9 AND 12 AND title IS NOT NULL AND score >=9 ORDER BY title;

-- Zadanie 3
SELECT DISTINCT users.displayname, users.reputation FROM users JOIN posts ON users.id = posts.owneruserid JOIN comments ON posts.id = comments.postid WHERE posts.body LIKE '%deterministic%' AND comments.text LIKE '%deterministic%' ORDER BY users.reputation DESC;

-- Zadanie 4
SELECT DISTINCT s.displayname FROM ((SELECT DISTINCT users.id, users.displayname FROM users JOIN posts ON users.id = posts.owneruserid) EXCEPT (SELECT DISTINCT users.id, users.displayname FROM users JOIN comments ON users.id = comments.userid)) s ORDER BY s.displayname LIMIT 10;

