-- Jakub Kuciński, pga
-- Zadanie 1
SELECT u.id, u.displayname, u.reputation, COUNT(DISTINCT p1.id) 
    FROM users u 
        JOIN posts p1 ON u.id = p1.owneruserid 
        JOIN postlinks pl ON p1.id = pl.postid  
    WHERE pl.linktypeid = 3 AND pl.postid != pl.relatedpostid 
    GROUP BY u.id, u.displayname, u.reputation 
    ORDER BY COUNT(DISTINCT p1.id) DESC, u.displayname ASC 
    LIMIT 20;

-- Zadanie 2
SELECT u.id, u.displayname, u.reputation, COUNT(c.id), AVG(c.score)  
    FROM users u 
        JOIN posts p ON u.id = p.owneruserid 
        JOIN badges b ON u.id = b.userid 
        LEFT JOIN comments c ON p.id = c.postid 
    WHERE b.name = 'Fanatic' 
    GROUP BY u.id, u.displayname, u.reputation 
    HAVING COUNT(c.id) <= 100 
    ORDER BY COUNT(c.id) DESC, u.displayname ASC 
    LIMIT 20;

-- Zadanie 3
ALTER TABLE users ADD CONSTRAINT pk_user PRIMARY KEY (id);
ALTER TABLE badges ADD CONSTRAINT fk_users_badges FOREIGN KEY (userid) REFERENCES users(id);
ALTER TABLE posts DROP COLUMN viewcount;
DELETE FROM posts WHERE body = '' OR body IS NULL;

-- Zadanie 4
CREATE SEQUENCE post_number;
SELECT setval('post_number', max(id)) FROM posts;
ALTER TABLE posts ALTER COLUMN id SET DEFAULT nextval('post_number');
ALTER SEQUENCE post_number OWNED BY posts.id;
INSERT INTO posts (posttypeid, parentid, owneruserid, body, score, creationdate) 
        SELECT 3, postid, userid, text, score, creationdate 
            FROM comments;