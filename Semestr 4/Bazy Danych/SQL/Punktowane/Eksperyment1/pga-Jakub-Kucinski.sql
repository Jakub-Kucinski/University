-- 35, SP-GIST, inet_ops, <>    -- Jakub Kuciński, 309881

-- SP oznacza space partitioning czyli podział przestrzeni. SP-GIST jest użyteczne dla struktur,
-- w których przestrzeń może być podzielona rekurencyjnie na nieprzecinające się obszary.

-- Klasa operatorów inet_ops to operatory dostępne dla typów cidr oraz inet, służących do
-- przetrzymywania adresów IPv4 i IPv6. inet_ops umożliwiają porównywanie adresów sieciowych
-- oraz wzajemne położenie sieci.

-- Operator <> sprawdza czy dwa adresy ip są od siebie różne. Zwraca prawdę jeśli są różne. 
-- Fałsz w przeciwnym przypadku.

CREATE OR REPLACE FUNCTION random_number(a INTEGER, b INTEGER)                                                                                                
RETURNS INTEGER AS $$                                                                                                                                         
SELECT width_bucket(random(), 0, 1, (b-a)+1) + (a-1); 
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION get_random_ipv4() 
RETURNS inet AS $$
WITH cte AS (
    SELECT random_number(0,255) AS n
    FROM generate_series(1,4)
)
SELECT array_to_string(array_agg(n), '.')::inet FROM cte;
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION get_random_ipv4_version2() 
RETURNS inet AS $$
WITH cte AS (
    SELECT random_number(0,1) AS n
    FROM generate_series(1,4)
)
SELECT array_to_string(array_agg(n), '.')::inet FROM cte;
$$ LANGUAGE SQL;


CREATE TABLE ips2(id SERIAL PRIMARY KEY, ip inet, t text, n numeric, ts timestamp);

INSERT INTO ips2(ip, t, n, ts) 
    SELECT get_random_ipv4_version2(), MD5(random()::text) || 'Some random text', 
           random()*1234567::numeric, now() 
    FROM generate_series(1,1000000) AS n;

INSERT INTO ips2(ip, t, n, ts) 
    SELECT get_random_ipv4(), MD5(random()::text) || 'Some random text', 
           random()*1234567::numeric, now() 
    FROM generate_series(1,30) AS n;

EXPLAIN ANALYZE SELECT ip FROM ips2 WHERE ip <> inet'192.168.1.0'
 and ip <> inet'0.0.0.0'
 and ip <> inet'0.0.0.1'
 and ip <> inet'0.0.1.0'
 and ip <> inet'0.0.1.1'
 and ip <> inet'0.1.0.0'
 and ip <> inet'0.1.0.1'
 and ip <> inet'0.1.1.0'
 and ip <> inet'0.1.1.1'
 and ip <> inet'1.0.0.0'
 and ip <> inet'1.0.0.1'
 and ip <> inet'1.0.1.0'
 and ip <> inet'1.0.1.1'
 and ip <> inet'1.1.0.0'
 and ip <> inet'1.1.0.1'
 and ip <> inet'1.1.1.0'
 and ip <> inet'1.1.1.1';

CREATE index my_index ON ips2 USING spgist(ip inet_ops);
SET enable_seqscan=off;

EXPLAIN ANALYZE SELECT ip FROM ips2 WHERE ip <> inet'192.168.1.0'
 and ip <> inet'0.0.0.0'
 and ip <> inet'0.0.0.1'
 and ip <> inet'0.0.1.0'
 and ip <> inet'0.0.1.1'
 and ip <> inet'0.1.0.0'
 and ip <> inet'0.1.0.1'
 and ip <> inet'0.1.1.0'
 and ip <> inet'0.1.1.1'
 and ip <> inet'1.0.0.0'
 and ip <> inet'1.0.0.1'
 and ip <> inet'1.0.1.0'
 and ip <> inet'1.0.1.1'
 and ip <> inet'1.1.0.0'
 and ip <> inet'1.1.0.1'
 and ip <> inet'1.1.1.0'
 and ip <> inet'1.1.1.1';

 SET enable_seqscan=on;

-- Widzimy, że w przypadku gdy mamy mało wyników i pewną bardzo liczebną ale mało zróżnicowaną liczbę ip różnych od wynikowych,
-- to index daje nam już pewne przyśpieszenie, ale niewielkie. Spróbujmy zatem jeszcze bardziej zróżnicować nasz zbiór.

CREATE TABLE ips(id SERIAL PRIMARY KEY, ip inet, t text, n numeric, ts timestamp);

INSERT INTO ips(ip, t, n, ts) 
    SELECT get_random_ipv4(), MD5(random()::text) || 'Some random text', 
           random()*1234567::numeric, now() 
    FROM generate_series(1,1000000) AS n;

INSERT INTO ips(ip, t, n, ts) 
    SELECT inet'1.1.1.1', MD5(random()::text) || 'Some random text', 
           random()*1234567::numeric, now() 
    FROM generate_series(1,1) AS n;

EXPLAIN ANALYZE SELECT ip FROM ips WHERE NOT(ip <> inet'1.1.1.1');

CREATE index my_index2 ON ips USING spgist(ip inet_ops);

EXPLAIN ANALYZE SELECT ip FROM ips WHERE NOT(ip <> inet'1.1.1.1');

-- W przypadku gdy ip w tabeli są o wiele bardziej zróżnicowane, index zdecydowanie przyspiesza nam działanie zapytania.
