package projekt;
import java.io.*;
import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.ArrayList;
import java.sql.Date;
/**
 * Główna klasa programu. Zapewnia komunikację między interfejsem, a bazą danych.
 */
public class Aplikacja
{
    static DatabaseHandler baza;
    static Logowanie logowanie;
    static Interfejs_konto interfejs_konto;

    /** 
     * Metoda bierze jako argument obiekt klasy Konto.
     * Wczytuje od użytkownika dane dotyczące przelewu, a następnie po potwierdzeniu przez użytkownika, stara się go wykonać.
     */
    public static void wykonanie_przelewu(Konto konto)
    {
        String numer_rachunku = Aplikacja.interfejs_konto.wczytanie_numeru_rachunku();
        String tytul_przelewu = Aplikacja.interfejs_konto.wczytanie_nazwy();
        BigDecimal kwota = Aplikacja.interfejs_konto.wczytanie_kwoty();
        if (Aplikacja.interfejs_konto.potwierdzenie_akcji() == 1) {
            try {
                if (baza.czyIstniejeKonto(numer_rachunku)) {
                    baza.wykonaniePrzelewu(konto.getId_konta(), numer_rachunku, tytul_przelewu, kwota);
                    System.out.println("\nPrzelew zostal pomyslnie zrealizowany\n");
                } else {
                    System.out.println("\nKonto o podanym numerze rachunku nie istnieje\n");
                }
            } catch (SQLException e) {
                System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
            } catch (ArithmeticException e) {
                System.out.println("\nNiewystarczajace srodki na koncie\n");
            }
        } else {
            System.out.println("\nAnulowano wykonanie przelewu\n");
        }
    }
    /**
     * Metoda bierze jako argument obiekt klasy Konto_osobiste.
     * Wczytuje od użytkownika, czy ma wyświetlić przelewy wychodzące czy przychodzące, a następnie stara się je wyświetlić.
     */
    public static void historia_przelewow_konto_osobiste(Konto_osobiste konto_osobiste)
    {
        int n = Aplikacja.interfejs_konto.wyswietlenie_historii_ktorych_przelewow();
        if (n == 1) {
            try{
                ArrayList<Przelew> przelewy_wychodzace = baza
                    .pobraniePrzelewowWychodzacychKontoOsobiste(konto_osobiste.getId_konta());
                Aplikacja.interfejs_konto.wyswietl_przelewy_wychodzace(przelewy_wychodzace);
            } catch (SQLException e) {
                System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
            }
            
        } else if (n == 2) {
            try{
                ArrayList<Przelew> przelewy_przychodzace = baza
                        .pobraniePrzelewowPrzychodzacychKontoOsobiste(konto_osobiste.getId_konta());
                Aplikacja.interfejs_konto.wyswietl_przelewy_przychodzace(przelewy_przychodzace);
            } catch (SQLException e) {
                System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
            }
        }
    }
    /**
     * Metoda bierze jako argument obiekt klasy Konto_firmowe.
     * Wczytuje od użytkownika, czy ma wyświetlić przelewy wychodzące czy przychodzące, a następnie stara się je wyświetlić.
     */
    public static void historia_przelewow_konto_firmowe(Konto_firmowe konto_firmowe)
    {
        int n = Aplikacja.interfejs_konto.wyswietlenie_historii_ktorych_przelewow();
        if (n == 1) {
            try {
                ArrayList<Przelew> przelewy_wychodzace = baza
                        .pobraniePrzelewowWychodzacychKontoFirmowe(konto_firmowe.getId_konta());
                Aplikacja.interfejs_konto.wyswietl_przelewy_wychodzace(przelewy_wychodzace);
            } catch (SQLException e) {
                System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
            }

        } else if (n == 2) {
            try {
                ArrayList<Przelew> przelewy_przychodzace = baza
                        .pobraniePrzelewowPrzychodzacychKontoFirmowe(konto_firmowe.getId_konta());
                Aplikacja.interfejs_konto.wyswietl_przelewy_przychodzace(przelewy_przychodzace);
            } catch (SQLException e) {
                System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
            }
        }

    }

    /**
     * Metoda bierze jako argument obiekt klasy Konto.
     * Wyswietla użytkownikowi założone na zalogowanym koncie lokaty i stara się usunąć wybraną przez użytkownika, po potwierdzeniu.
     */
    
    public static void usuwanie_lokaty(Konto konto) {
        try {
            ArrayList<Lokata> lokaty = baza.pobranieLokat(konto.getId_konta());
            int id_lokaty = Aplikacja.interfejs_konto.wybor_lokaty_do_usuniecia(lokaty);
            if (id_lokaty == 0) {
                
            } else if (Aplikacja.interfejs_konto.potwierdzenie_akcji() == 1) {
                if (baza.czyIstniejeIdLokaty(konto.getId_konta(), id_lokaty)){
                    baza.usuwanieLokaty(konto.getId_konta(), id_lokaty);
                    System.out.println("\nLokata zostala pomyslnie przerwana\n");
                } else {
                    System.out.println("\nLokata o podanym id nie istnieje\n");
                }
            } else {
                System.out.println("\nAnulowano usuwanie lokaty\n");
            }
        } catch (SQLException e) {
            System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
        }
    }
    /**
     * Metoda bierze jako argument obiekt klasy Konto.
     * Wyswietla użytkownikowi założone na zalogowanym koncie lokaty.
     */
    public static void wyswietlanie_lokat(Konto konto)
    {
        try{
            ArrayList<Lokata> lokaty = baza.pobranieLokat(konto.getId_konta());
            Aplikacja.interfejs_konto.wyswietl_lokaty(lokaty);
        } catch(SQLException e){
            System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
        }
    }

    /**
     * Metoda bierze jako argument obiekt klasy Konto.
     * Wczytuje od użytkownika dane dotyczące lokaty, a następnie po potwierdzeniu przez użytkownika, stara się stworzyć daną lokatę.
     */
    public static void dodawanie_lokaty(Konto konto)
    {
        int numer = Aplikacja.interfejs_konto.wyswietlanie_dostepnych_lokat();
        if (numer != 0)
        {
            String nazwa_lokaty = Aplikacja.interfejs_konto.wczytanie_nazwy();
            BigDecimal kwota = Aplikacja.interfejs_konto.wczytanie_kwoty();
            BigDecimal oprocentowanie = Aplikacja.interfejs_konto.podaj_oprocentowanie_od_lokaty(numer);
            Date data_zalozenia = Aplikacja.interfejs_konto.aktualna_data();
            Date data_zakonczenia = Aplikacja.interfejs_konto.utworz_date_zakonczenia_lokaty(numer);
            if (Aplikacja.interfejs_konto.potwierdzenie_akcji() == 1)
            {
                try{
                    baza.dodanieLokatyDoBazy(konto.getId_konta(), nazwa_lokaty, kwota, oprocentowanie, data_zalozenia, data_zakonczenia);
                    System.out.println("\nLokata zostala pomyslnie utworzona\n");
                }catch(SQLException e){
                    System.out.println("\nBlad w przetwarzaniu zapytania do bazy danych\n");
                }catch(ArithmeticException e){
                    System.out.println("\nNiewystarczajace srodki na koncie\n");
                }
            } else {
                System.out.println("\nAnulowano tworzenie lokaty\n");
            }
            
        }
    }

    /**
     * Metoda bierze jako argumenty obiekt klasy Konto_osobiste, obiekt klasy Integer i obiekt klasy String, które są odpowiednio zalogowanym kontem, numerem zalogowanego klienta i pasującym hasłem.
     * Metoda pozwala wywołać odpowiednie funkcjonalności przeznaczone dla kont osobistych.
     */
    public static void main_konto_osobiste(Konto_osobiste konto_osobiste, Integer numer_klienta, String haslo)
    {
        do
        {
            try{
                konto_osobiste = baza.logowanieKontoOsobiste(numer_klienta, haslo);
            } catch (SQLException | NullPointerException e) {
                e.printStackTrace();
                System.err.println("Brak polaczenia z baza");
                System.exit(1);
            } 
            int n = Aplikacja.interfejs_konto.funkcjonalnosci();
            if (n == 1){
                System.out.println(konto_osobiste.toString());
            } else if (n == 2) {
                Aplikacja.historia_przelewow_konto_osobiste(konto_osobiste);
            } else if (n == 3) {
                Aplikacja.wykonanie_przelewu(konto_osobiste);
            } else if (n == 4) {
                Aplikacja.wyswietlanie_lokat(konto_osobiste);
            } else if (n == 5) {
                Aplikacja.dodawanie_lokaty(konto_osobiste);
            } else if (n == 6) {
                Aplikacja.usuwanie_lokaty(konto_osobiste);
            } else {
                System.exit(0);
            }
            
        } while (true);
    }

    /**
     * Metoda bierze jako argumenty obiekt klasy Konto_firmowe, obiekt klasy Integer i obiekt klasy String, które są odpowiednio zalogowanym kontem, numerem zalogowanego klienta i pasującym hasłem.
     * Metoda pozwala wywołać odpowiednie funkcjonalności przeznaczone dla kont firmowych.
     */
    public static void main_konto_firmowe(Konto_firmowe konto_firmowe, Integer numer_klienta, String haslo, Integer id_konta_firmowego)
    {
        do
        {
            try {
                ArrayList<Klient> wlasciciele = new ArrayList<Klient>();
                baza.pobranieInformacjiWlascicieleKontaFirmowego(id_konta_firmowego, wlasciciele);
                Klient[] wlasciciele_konta_firmowego = new Klient[wlasciciele.size()];
                wlasciciele_konta_firmowego = wlasciciele.toArray(wlasciciele_konta_firmowego);
                konto_firmowe = baza.pobranieInformacjiKontoFirmowe(id_konta_firmowego, wlasciciele_konta_firmowego);
            } catch (SQLException | NullPointerException e) {
                e.printStackTrace();
                System.err.println("Brak polaczenia z baza");
                System.exit(1);
            }
            int n = Aplikacja.interfejs_konto.funkcjonalnosci();
            if (n == 1){
                System.out.println(konto_firmowe.toString());
            } else if (n == 2) {
                Aplikacja.historia_przelewow_konto_firmowe(konto_firmowe);
            } else if (n == 3) {
                Aplikacja.wykonanie_przelewu(konto_firmowe);
            } else if (n == 4) {
                Aplikacja.wyswietlanie_lokat(konto_firmowe);
            } else if (n == 5) {
                Aplikacja.dodawanie_lokaty(konto_firmowe);                
            } else if (n == 6) {
                Aplikacja.usuwanie_lokaty(konto_firmowe);
            } else {
                System.exit(0);
            }
            
        } while (true);
    }


    /**
     * Metoda rozpoczynająca działanie programu.
     * Tworzy obiekty pól statycznych klasy Aplikacja i odpowiada za zalogowanie użytkownika do konta firmowego lub osobistego, poprzez wywoływanie odpowiednich metod na obiektach klas DatabaseHandler i Logowanie
     */
    public static void main(String[] args) {
        baza = new DatabaseHandler();
        try{
            baza.connect();
        }catch(SQLException e){
            e.printStackTrace();
            System.err.println("Brak polaczenia z baza");
            System.exit(1);
        }
        logowanie = new Logowanie();
        interfejs_konto = new Interfejs_konto();

        int n;
        int numer_klienta;
        String haslo;
        
        do
        {
            n = logowanie.wybor_trybu_logowania();
            numer_klienta = logowanie.wczytywanie_numeru_klienta();
            haslo = logowanie.wczytywanie_hasla();
            if (n == 1)
            {
                Konto_osobiste konto_osobiste = new Konto_osobiste();
                boolean good = false;
                try {
                    konto_osobiste = baza.logowanieKontoOsobiste(numer_klienta, haslo);
                    System.out.println("Poprawne dane logowania");
                    good = true;
                } catch (SQLException e) {
                    e.printStackTrace();
                    System.err.println("Brak polaczenia z baza");
                    System.exit(1);
                } catch (NullPointerException e) {
                    System.out.println("Niepoprawny login lub haslo");
                }
                if (good){
                    Aplikacja.main_konto_osobiste(konto_osobiste, numer_klienta, haslo);
                    break;
                }
            }
            else
            {
                ArrayList<String> nazwy_firm = new ArrayList<String>();
                ArrayList<String> numery_rachunkow = new ArrayList<String>();
                ArrayList<Integer> konta;
                int id_konta_firmowego = 0;
                Konto_firmowe konto_firmowe = new Konto_firmowe();
                boolean good = false;
                try
                {
                    konta = baza.logowanieKontaFirmowe(numer_klienta, haslo, nazwy_firm, numery_rachunkow);
                    System.out.println("Poprawne dane logowania\n");
                    id_konta_firmowego = logowanie.wczytywanie_indeksu_sposrod_dostepnych_kont(konta, nazwy_firm,
                            numery_rachunkow);
                    ArrayList<Klient> wlasciciele = new ArrayList<Klient>();
                    baza.pobranieInformacjiWlascicieleKontaFirmowego(id_konta_firmowego, wlasciciele);
                    Klient[] wlasciciele_konta_firmowego = new Klient[wlasciciele.size()];
                    wlasciciele_konta_firmowego = wlasciciele.toArray(wlasciciele_konta_firmowego);
                    konto_firmowe = baza.pobranieInformacjiKontoFirmowe(id_konta_firmowego,
                            wlasciciele_konta_firmowego);
                    good = true;
                } catch (SQLException e) {
                    e.printStackTrace();
                    System.err.println("Brak polaczenia z baza");
                    System.exit(1);
                } catch (NullPointerException e) {
                    System.out.println("Niepoprawny login lub haslo");
                }
                if (good) {
                    Aplikacja.main_konto_firmowe(konto_firmowe, numer_klienta, haslo, id_konta_firmowego);
                    break;
                }
            }
        } while (true);

    }
}