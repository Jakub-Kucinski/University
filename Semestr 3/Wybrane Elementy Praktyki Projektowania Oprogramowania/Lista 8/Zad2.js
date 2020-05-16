const Pool = require('pg').Pool
const pool = new Pool({
    user: 'postgres',
    host: 'localhost',
    database: 'zad2',
    password: 'postgres',
    port: 5432,
})

async function utworz_tabele() {
    try {
        await pool.query("CREATE TABLE IF NOT EXISTS OSOBA ( \
            id_osoba SERIAL PRIMARY KEY, \
            imie VARCHAR(1000), \
            nazwisko VARCHAR(1000), \
            plec VARCHAR(100), \
            wiek INTEGER); ");
        
    } catch(err) {
    console.log(err);
    throw err;
    }
}


async function dodaj_osobe(imie, nazwisko, plec, wiek) {
    try {
        var res = await pool.query("INSERT INTO OSOBA(imie, nazwisko, plec, wiek) \
        VALUES ($1, $2, $3, $4) RETURNING OSOBA.id_osoba ;", [imie, nazwisko, plec, wiek]);
        return res.rows[0].id_osoba;
    } catch(err) {
        console.log(err);
        throw err;
    }
}


async function uaktualnij_osobe_wiek(id, wiek) {
    try {
        var res = await pool.query("UPDATE OSOBA \
        SET wiek = $1 \
        WHERE OSOBA.id_osoba = $2 \
        RETURNING * ",
            [wiek, id]);
        return res.rows;
    } catch(err) {
        console.log(err);
        throw err;
    }
}

async function usun_osobe(id) {
    try {
        var res = await pool.query("DELETE FROM OSOBA \
        WHERE OSOBA.id_osoba = $1 \
        RETURNING * ",
            [id]);
        return res.rows;
    } catch(err) {
        console.log(err);
        throw err;
    }
}



async function main() {
    await utworz_tabele();
    w1 = await dodaj_osobe('Pawel', 'Kucharz', 'mezczyzna', 25);
    console.log(w1);
    w2 = await uaktualnij_osobe_wiek(w1, 30);
    console.log(w2);
    w3 = await usun_osobe(w1);
    console.log(w3);
}
  

main();
  