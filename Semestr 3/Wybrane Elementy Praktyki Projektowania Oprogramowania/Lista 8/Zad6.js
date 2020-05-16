const Pool = require('pg').Pool
const pool = new Pool({
    user: 'postgres',
    host: 'localhost',
    database: 'zad6',
    password: 'postgres',
    port: 5432,
})

async function utworz_tabele() {
    try {
        await pool.query("CREATE TABLE IF NOT EXISTS OSOBA ( \
            id_osoba SERIAL PRIMARY KEY, \
            imie VARCHAR(100), \
            nazwisko VARCHAR(100), \
            plec VARCHAR(10), \
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

async function dodaj_milion_osob() {
    for (var i = 0; i < 500000; i++){
        await dodaj_osobe(Math.random().toString(36).substring(2, 20),
            Math.random().toString(36).substring(2, 20), "mezczyzna", 21);
    }
    dodaj_osobe("Jacek", "Kowalski", "mezczyzna", 21);
    for (var i = 0; i < 500000; i++){
        await dodaj_osobe(Math.random().toString(36).substring(2, 20),
            Math.random().toString(36).substring(2, 20), "mezczyzna", 21);
    }
}

async function znajdz_kowalskich() {
    try {
        var res = await pool.query("SELECT * FROM OSOBA WHERE Nazwisko='Kowalski'");
        return res.rows;
    } catch(err) {
        console.log(err);
        throw err;
    }
}

async function dodaj_indeks() {
    try {
        var res = await pool.query("CREATE INDEX indeks_nazwisk ON OSOBA (Nazwisko);");
    } catch(err) {
        console.log(err);
        throw err;
    }
}

async function usun_indeks() {
    try {
        var res = await pool.query("DROP INDEX indeks_nazwisk;");
    } catch(err) {
        console.log(err);
        throw err;
    }
}

async function main() {
    await utworz_tabele();
    await dodaj_milion_osob();

    console.time("Time this");
    w = await znajdz_kowalskich();
    console.timeEnd("Time this");
    console.log(w);

    await dodaj_indeks();
    console.time("Time that");
    w = await znajdz_kowalskich();
    console.timeEnd("Time that");
    console.log(w);
}

// Time this: 54.629ms
// Time that: 0.722ms

main();