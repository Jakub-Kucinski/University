-- Jakub Kuciński, pga
-- Zadanie 1
ALTER TABLE comments 
	ADD COLUMN lasteditdate timestamp NOT NULL DEFAULT now();

UPDATE comments SET lasteditdate = creationdate;

CREATE TABLE commenthistory (
	id SERIAL PRIMARY KEY,
	commentid integer,
	creationdate timestamp,
	text text
);


-- Zadanie 2
CREATE OR REPLACE FUNCTION on_comment_update()

	RETURNS TRIGGER AS $X$

	DECLARE

	BEGIN

		IF (NEW.id != OLD.id OR NEW.postid != OLD.postid OR NEW.lasteditdate != OLD.lasteditdate) THEN
			RAISE EXCEPTION 'Niedozwolona zmiana atrybutów'
			USING HINT = 'Proszę sprawdzić modyfikowane atrybuty';
		END IF;

		NEW.creationdate := OLD.creationdate;

		IF (NEW.text != OLD.text) THEN
			NEW.lasteditdate = now();

			INSERT INTO commenthistory(commentid, creationdate, text)
				VALUES(NEW.id, OLD.lasteditdate, OLD.text);		
		END IF;

		RETURN NEW;

	END

$X$ LANGUAGE plpgsql;

CREATE TRIGGER on_update_comment BEFORE UPDATE ON comments
FOR EACH ROW EXECUTE PROCEDURE on_comment_update();


-- Zadanie 3
CREATE OR REPLACE FUNCTION before_comment_insert()

	RETURNS TRIGGER AS $X$

	DECLARE

	BEGIN

		IF (NEW.creationdate != NEW.lasteditdate) THEN
			NEW.lasteditdate := New.creationdate;
		END IF;

		RETURN NEW;
	
	END

$X$ LANGUAGE plpgsql;

CREATE TRIGGER on_insert_comment BEFORE INSERT ON comments
FOR EACH ROW EXECUTE PROCEDURE before_comment_insert();
