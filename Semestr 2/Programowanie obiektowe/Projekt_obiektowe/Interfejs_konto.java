package projekt;
import java.io.Console;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.sql.Date;
import java.sql.Timestamp;

/**
 * Klasa odpowiadająca za interfejs programu po zalogowaniu się użytkownika.
 */
public class Interfejs_konto
{
    /**
     * Wyświetla dostępne możliwe do wykonania przez program akcje. Wczytuje od użytkownika numer akcji, którą chce wywołać i zwraca jej numer.
     */
    public Integer funkcjonalnosci()
    {
        System.out.println("\nWybierz jedna z dostepnych akcji:");
        System.out.println("1. Wyswietlenie szczegolowych informacji o koncie");
        System.out.println("2. Wyswietlenie historii przelewow");
        System.out.println("3. Wykonanie przelewu");
        System.out.println("4. Wyswietlenie lokat");
        System.out.println("5. Zalozenie lokaty");
        System.out.println("6. Przerwanie lokaty");
        System.out.println("7. Wyjscie z aplikacji");
        Console c = System.console();
        if (c == null) 
        {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        Integer res = 0;
        String s;
        do
        {
            try
            {
                s = c.readLine();
                if(s.length()>1)
                {
                    System.out.print("\nNiepoprawny format\n");
                }
                else
                {
                    if(s.charAt(0) >= '1' && s.charAt(0) <= '7')
                    {
                        res = s.charAt(0) - '0';
                        b = false;
                    }
                    else
                    {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                System.out.print("\nNiepoprawny format\n");
            }
        } while (b);
        return res;
    }

    /**
     * Metoda wczytuje jedną linię. Służy do ignorowania następnej lini danych podanych przez użytkownika.
     */
    public void wczytaj_linie()
    {
        Console c = System.console();
        if (c == null) 
        {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        try
        {
            c.readLine();
        }catch(StringIndexOutOfBoundsException e)
        {
            ;
        }
    }

    /**
     * Wyświetla informacje o lokatach podanych w argumencie lokaty. Korzysta z metody toString dla obiektów klasy Lokata.
     */
    public void wyswietl_lokaty(ArrayList<Lokata> lokaty)
    {
        Lokata[] lokaty_konta = new Lokata[lokaty.size()];
        lokaty_konta = lokaty.toArray(lokaty_konta);
        System.out.print("\nLista lokat:\n");
        for (Lokata l : lokaty_konta) {
            System.out.print(l.toString());
        }
    }

    /**
     * Wczytuje od użytkownika niepusty ciąg znaków. Wczytane dane zwraca jako obiekt klasy String.
     */
    public String wczytanie_nazwy()
    {
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        System.out.println("\nPodaj nazwe");
        String s = "";
        do {
            try {
                s = c.readLine();
                if(s.length()!= 0)
                    break;
                else
                    System.out.println("Tytul nie moze byc pusty");
            } catch (StringIndexOutOfBoundsException e) {
                System.out.println("Tytul nie moze byc pusty");
            }
        } while (true);
        return s;
    }

    /**
     * Wczytuje od użytkownika dane, do momentu otrzymania ciągu znaków, które mogą zostać zinterpretowane jako obiekt klasy BigDecimal o co najwyżej 11 znakach przed kropką. Zwraca tak zinterpretowany ciąg jako obiekt BigDecimal.
     */
    public BigDecimal wczytanie_kwoty() {
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        Boolean b = true;
        String s = "";
        Boolean czy_kropka;
        System.out.print("\nPodaj kwote\n");
        do {
            b = false;
            czy_kropka = false;
            try {
                s = c.readLine();
                int len = s.length();
                for (int i = 0; i < len; i++) {
                    if (!Character.isDigit(s.charAt(i))) {
                        if (i > 0 && i == len - 3 && s.charAt(i) == '.' && Character.isDigit(s.charAt(i + 1))
                                && Character.isDigit(s.charAt(i + 2))) {
                            if (len > 14) {
                                System.out.print("\nPodana kwota przekracza zakres\n");
                                b = true;
                            }
                            czy_kropka = true;
                            break;
                        } else {
                            b = true;
                            break;
                        }
                    }
                }
                if (b == false && czy_kropka == false) {
                    if (len > 12) {
                        b = true;
                    }
                }
            } catch (StringIndexOutOfBoundsException e) {
                System.out.print("\nNiepoprawny format\n");
            }

        } while (b);
        return new BigDecimal(s);
    }

    /**
     * Zwraca bierzącą datę zapisaną w postaci obiekty klasy Date
     */
    public Date aktualna_data() {
        Timestamp ts = new Timestamp(System.currentTimeMillis());
        Date aktualna_data = new Date(ts.getTime());
        return aktualna_data;
    }

    /**
     * Zwraca datę, jaka nastąpi po upłynięciu liczby dni równej liczba_dni od bierzącej daty.
     */
    public Date data_po_liczbie_dni(int liczba_dni) {
        long liczba = liczba_dni;
        Timestamp ts = new Timestamp(System.currentTimeMillis() + liczba * 24 * 60 * 60 * 1000);
        Date przyszla_data = new Date(ts.getTime());
        return przyszla_data;
    }

    /**
     * Wyświetla listę możliwych do założenia lokat. Wczytuje od użytkownika dane, do momentu wczytania pustego Stringa lub znaku od '1' do '7'. Zwraca ten znak, bądź w przypadku pustego Stringa 0.
     */
    public int wyswietlanie_dostepnych_lokat() {
        System.out.println("\nWybierz jedna z dostepnych lokat:");
        System.out.println("\nlp. Czas trwania: Oprocentowanie:");
        System.out.println("1.  10 dni        0.45%");
        System.out.println("2.  30 dni        0.60%");
        System.out.println("3.  60 dni        0.60%");
        System.out.println("4.  90 dni        0.60%");
        System.out.println("5.  120 dni       0.80%");
        System.out.println("6.  180 dni       0.80%");
        System.out.println("7.  360 dni       1.20%");
        System.out.println("By wrocic do poprzedniego ekranu nacisnij enter");

        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        int res = 0;
        String s;
        do {
            try {
                s = c.readLine();
                if (s.length() == 0){
                    res = 0;
                    b = false;
                } else if (s.length() > 1) {
                    System.out.print("\nNiepoprawny format\n");
                } else {
                    if (s.charAt(0) >= '1' && s.charAt(0) <= '7') {
                        res = s.charAt(0) - '0';
                        b = false;
                    } else {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            } catch (StringIndexOutOfBoundsException e) {
                res = 0;
                b = false;
            }
        } while (b);
        return res;
    }
    
    /**
     * Zwraca w postaci obiektu klasy BigDecimal oprocentowanie odpowiadające podanej liczbie numer.
     */
    public BigDecimal podaj_oprocentowanie_od_lokaty(int numer)
    {
        BigDecimal oprocentowanie;
        switch (numer) {
        case 1:
            oprocentowanie = new BigDecimal("0.45");
            break;
        case 2:
            oprocentowanie = new BigDecimal("0.60");
            break;
        case 3:
            oprocentowanie = new BigDecimal("0.60");
            break;
        case 4:
            oprocentowanie = new BigDecimal("0.60");
            break;
        case 5:
            oprocentowanie = new BigDecimal("0.80");
            break;
        case 6:
            oprocentowanie = new BigDecimal("0.80");
            break;
        default:
            oprocentowanie = new BigDecimal("1.20");
        }
        return oprocentowanie;
    }

    /**
     * Zwraca w postaci obiektu klasy Date datę odpowiadającą dacie po upływie liczby dni równej numer, od bierzącej daty.
     */
    public Date utworz_date_zakonczenia_lokaty(int numer)
    {
        Date data_zakonczenia;
        switch (numer) {
        case 1:
            data_zakonczenia = this.data_po_liczbie_dni(10);
            break;
        case 2:
            data_zakonczenia = this.data_po_liczbie_dni(30);
            break;
        case 3:
            data_zakonczenia = this.data_po_liczbie_dni(60);
            break;
        case 4:
            data_zakonczenia = this.data_po_liczbie_dni(90);
            break;
        case 5:
            data_zakonczenia = this.data_po_liczbie_dni(120);
            break;
        case 6:
            data_zakonczenia = this.data_po_liczbie_dni(180);
            break;
        default:
            data_zakonczenia = this.data_po_liczbie_dni(360);
        }
        return data_zakonczenia;
    }

    /**
     * Wyświetla informacje o lokatach przekazanych w argumencie lokaty, a nstępnie wczytuje od użytkownika dane, do momentu otrzymania ciągu znaków, które mogą zostać zinterpretowane jako int. Zwraca tak zinterpretowany ciąg jako int. 
     */
    public int wybor_lokaty_do_usuniecia(ArrayList<Lokata> lokaty)
    {
        System.out.println("\nWybierz ktora z lokat chcesz usunac, wpisujac jej id");
        System.out.println("lub wcisnij enter, aby powrocic do poprzedniego ekranu");
        this.wyswietl_lokaty(lokaty);
        int liczba = 0;
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        String s = "";
        do {
            try {
                s = c.readLine();
                if (s.length() == 0) {
                    liczba = 0;
                    b = false;
                } else if (s.length() > 11) {
                    System.out.print("\nNiepoprawny format\n");
                } else {
                    try {
                        liczba = Integer.parseInt(s);
                        b = false;
                    } catch (NumberFormatException e) {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            } catch (StringIndexOutOfBoundsException e) {
                liczba = 0;
                b = false;
            }

        } while (b);
        return liczba;
    }
    
    /**
     * Wyswietla komuniakat ostrzegawczy o potwierdzeniu akcji, następnie wczytuje dane do momentu otrzymania Stringa "1", "2" lub pustej linii. Gdy wczyta "1" zwraca 1, gdy "2" zwraca 2, wpp 0.
     */
    public int potwierdzenie_akcji()
    {
        Console c = System.console();
        if (c == null) 
        {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        System.out.println("\nCzy na pewno chcesz wykonac ta akcje?");
        System.out.println("1. Tak");
        System.out.println("2. Nie");
        boolean b = true;
        int res = 0;
        String s;
        do
        {
            try
            {
                s = c.readLine();
                if (s.length() == 0) {
                    res = 0;
                    b = false;
                } else if(s.length() > 1)
                {
                    System.out.print("\nNiepoprawny format\n");
                }
                else
                {
                    if(s.charAt(0) == '2' || s.charAt(0) == '1')
                    {
                        res = s.charAt(0) - '0';
                        b = false;
                    }
                    else
                    {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                res = 0;
                b = false;
            }
        } while (b);
        return res;
    }

    /**
     * Wyświetla komunkat o wyborze typów przelewów, których historia ma zostać wyświetlona, następnie wczytuje dane do momentu otrzymania Stringa "1", "2" lub pustej linii. Gdy wczyta "1" zwraca 1, gdy "2" zwraca 2, wpp 0.
     */
    public int wyswietlenie_historii_ktorych_przelewow()
    {
        Console c = System.console();
        if (c == null) 
        {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        System.out.println("\nWybierz ktore przelewy nalezy wyswietlic:");
        System.out.println("1. Przelewy wychodzace");
        System.out.println("2. Przelewy przychodzace");
        System.out.println("lub wcisnij enter, aby powrocic do poprzedniego ekranu");
        boolean b = true;
        int res = 0;
        String s;
        do
        {
            try
            {
                s = c.readLine();
                if (s.length() == 0) {
                    res = 0;
                    b = false;
                } else if(s.length() > 1)
                {
                    System.out.print("\nNiepoprawny format\n");
                }
                else
                {
                    if(s.charAt(0) == '2' || s.charAt(0) == '1')
                    {
                        res = s.charAt(0) - '0';
                        b = false;
                    }
                    else
                    {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                res = 0;
                b = false;
            }
        } while (b);
        return res;
    }

    /**
     * Wyświetla informacje o przelewach podanych w przelewy_przychodzace przy użyciu metody toStringBezNadawcy() dla obiektów klasy Przelew.
     */
    public void wyswietl_przelewy_wychodzace(ArrayList<Przelew> przelewy_wychodzace)
    {
        Przelew[] przelewy = new Przelew[przelewy_wychodzace.size()];
        przelewy = przelewy_wychodzace.toArray(przelewy);
        System.out.print("\nLista przelewow wychodzacych:\n");
        for (Przelew p : przelewy) {
            System.out.print(p.toStringBezNadawcy());
        }
    }

    /**
     * Wyświetla informacje o przelewach podanych w przelewy_przychodzace przy użyciu metody toStringBezOdbiorcy() dla obiektów klasy Przelew.
     */
    public void wyswietl_przelewy_przychodzace(ArrayList<Przelew> przelewy_przychodzace)
    {
        Przelew[] przelewy = new Przelew[przelewy_przychodzace.size()];
        przelewy = przelewy_przychodzace.toArray(przelewy);
        System.out.print("\nLista przelewow przychodzacych:\n");
        for (Przelew p : przelewy) {
            System.out.print(p.toStringBezOdbiorcy());
        }
    }

    /**
     * Wczytuje od użytkownika dane, do momentu otrzymania ciągu znaków, które mogą zostać zinterpretowane jako numer_rachunku (ciąg cyfr o długości co najwyżej 50). Zwraca tak zinterpretowany ciąg jako obiekt String.
     */
    public String wczytanie_numeru_rachunku()
    {
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        String s = "";
        System.out.print("\nPodaj numer rachunku odbiorcy przelewu\n");
        do {
            b = false;
            try {
                s = c.readLine();
                int len = s.length();
                if (len > 50) {
                    System.out.print("\nNiepoprawny format\n");
                } else {
                    for (int i = 0; i < len; i++) {
                        if (!Character.isDigit(s.charAt(i))) {
                            System.out.print("\nNiepoprawny format\n");
                            b = true;
                            break;
                        }
                    }
                }

            } catch (StringIndexOutOfBoundsException e) {
                System.out.print("\nNiepoprawny format\n");
            }

        } while (b);
        return s;
    }
}