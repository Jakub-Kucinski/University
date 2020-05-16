const Pool = require('pg').Pool
const pool = new Pool({
    user: 'postgres',
    host: 'localhost',
    database: 'zad5',
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
    try {
        await pool.query("CREATE TABLE IF NOT EXISTS MIEJSCE_PRACY ( \
            id_miejsce_pracy SERIAL PRIMARY KEY, \
            adres VARCHAR(1000), \
            nazwa_firmy VARCHAR(1000)); ");
    } catch(err) {
    console.log(err);
    throw err;
    }
    try {
        await pool.query("CREATE TABLE IF NOT EXISTS Osoba_miejsce_pracy ( \
            id_osoba integer references OSOBA(id_osoba), \
            id_miejsce_pracy integer references MIEJSCE_PRACY(id_miejsce_pracy) ); ");
    } catch(err) {
    console.log(err);
    throw err;
    }
}

async function dodaj_nowa_osobe_z_nowym_miejscem_pracy(imie, nazwisko, plec, wiek, adres, nazwa_firmy) {
    var id;
    var id_2;
    try {
        var res = await pool.query("INSERT INTO MIEJSCE_PRACY(adres, nazwa_firmy) \
        VALUES ($1, $2) RETURNING MIEJSCE_PRACY.id_miejsce_pracy ;", [adres, nazwa_firmy]);
        id = res.rows[0].id_miejsce_pracy;
    } catch(err) {
    console.log(err);
    throw err;
    }
    try {
        var res = await pool.query("INSERT INTO OSOBA(imie, nazwisko, plec, wiek) \
        VALUES ($1, $2, $3, $4) RETURNING OSOBA.id_osoba ;", [imie, nazwisko, plec, wiek]);
        id_2 = res.rows[0].id_osoba;
    } catch(err) {
    console.log(err);
    throw err;
    }
    try {
        var res = await pool.query("INSERT INTO Osoba_miejsce_pracy(id_osoba, id_miejsce_pracy) \
        VALUES ($1, $2) RETURNING *;", [id_2, id]);
        return res.rows[0];
    } catch(err) {
    console.log(err);
    throw err;
    }
}

async function main() {
    await utworz_tabele();
    console.log(await dodaj_nowa_osobe_z_nowym_miejscem_pracy(
        "Jacek", "Kowalski", "mezczyzna", 21, "tutaj", "ciekawa firma"
    ));
}
  

main();