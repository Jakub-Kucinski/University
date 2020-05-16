package projekt;

import java.math.BigDecimal;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import javax.swing.table.DefaultTableModel;
import java.util.ArrayList;

/**
 * Klasa odpowiadająca za komunikację z bazą danych, aby działała poprawnie, należy mieć stworzoną bazę danych o konkretnej strukturze oraz należy uzupełnić pola url, user i password odpowiednimi wartościami.
 */
public class DatabaseHandler {

    private static String url = "jdbc:mysql://localhost:3306/bank?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
 
    private static String user = "root";
 
    private static String password = "011235";
    
    private Connection con = null;
 
    /**
     * Metoda tworzy połączenie z bazą danych.
     * W przypadku błędu wykonania rzucany jest SQLException
     */
    public void connect() throws SQLException
    {
        con = DriverManager.getConnection(url, user, password);
        System.out.println("Success");
    }
     
    /**
     * Metoda odpowiadająca za logowanie się na konto osobiste. Jako argumenty przyjmuje numer klienta oraz hasło i zwraca obiekt klasy Konto_osobiste zawierający informacje o koncie, na które zalogował się użytkownik, jeśli numer klienta i odpowiadajce mu hasło są poprawne.
     * Jeśli nie są poprawne, rzucany jest wyjątek NullPointerException. W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public Konto_osobiste logowanieKontoOsobiste(int numer_klienta, String haslo) throws NullPointerException, SQLException
    {
       
        String query = "select * from Konto_osobiste inner join Klient on Klient.id_klienta = Konto_osobiste.id_klienta inner join Adres on Klient.id_adresu = Adres.id_adresu where Klient.numer_klienta ='"+numer_klienta+"' and Konto_osobiste.haslo ='"+haslo+"'";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        if (rs.next())
        {
            Integer id_konta = rs.getInt("id_konta");
            String numer_rachunku = rs.getString("numer_rachunku");
            Date data_zalozenia = rs.getDate("data_zalozenia");
            //String data_zalozenia = rs.getString("data_zalozenia");
            BigDecimal saldo = rs.getBigDecimal("saldo");

            Integer id_klienta = rs.getInt("id_klienta");
            String imie = rs.getString("imie");
            String nazwisko = rs.getString("nazwisko");
            String plec = rs.getString("plec");
            String pesel = rs.getString("PESEL");

            Integer id_adresu = rs.getInt("id_adresu");
            String panstwo = rs.getString("panstwo");
            String miasto = rs.getString("miasto");
            String ulica = rs.getString("ulica");
            String numer_budynku = rs.getString("numer_budynku");
            String numer_lokalu = rs.getString("numer_lokalu");
            Adres adres = new Adres(id_adresu, panstwo, miasto, ulica, numer_budynku, numer_lokalu);
            Klient klient = new Klient(id_klienta, numer_klienta, imie, nazwisko, plec, pesel, adres);
            Konto_osobiste konto_osobiste = new Konto_osobiste(id_konta, numer_rachunku, data_zalozenia, saldo,
            haslo, klient);
            return konto_osobiste;

        }
        else
        {
            throw new NullPointerException();
        }
    }
    
    /**
     * Metoda odpowiadająca za logowanie na konto firmowe. Jako argumenty przyjmuje numer klienta, hasło, listy nazwy_firm i numery_rachunkow. Zwraca listę Integerów będącą listą id_konta.
     * Metoda znajduje konta firmowe, do których ma dostęp klient o podanym numerze klienta i haśle. Zwraca listę ich zawierającą ich id. Razem z dodawaniem id do listy wynikowej, do list nazwy_firm i numery_rachunkow zostają dodane odpowiednie nazwy firm i ich numery rachunków.
     * Jeśli nie zostanie znalezione żadne odpowiadające konto firmowe to rzucany jest wyjątek NullPointerException. W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. 
     */
    public ArrayList<Integer> logowanieKontaFirmowe(int numer_klienta, String haslo, ArrayList<String> nazwy_firm, ArrayList<String> numery_rachunkow) throws NullPointerException, SQLException
    {

        String query = "select Konto_firmowe.id_konta, Firma.nazwa_firmy, Konto_firmowe.numer_rachunku from Firma inner join Konto_firmowe on Firma.id_firmy = Konto_firmowe.id_firmy inner join Konto_firmowe_klient on Konto_firmowe.id_konta = Konto_firmowe_klient.id_konta inner join Klient on Konto_firmowe_klient.id_klienta = Klient.id_klienta where Klient.numer_klienta ='"+numer_klienta+"' and Konto_firmowe_klient.haslo ='"+haslo+"'";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        ArrayList<Integer> konta_firmowe = new ArrayList<Integer>();
        if(!rs.next()) 
        {
            throw new NullPointerException();
        }
        do
        {     
            Integer id_konta = rs.getInt("id_konta");
            String nazwa_firmy = rs.getString("nazwa_firmy");
            String numer_rachunku = rs.getString("numer_rachunku");
            konta_firmowe.add(id_konta);
            nazwy_firm.add(nazwa_firmy);
            numery_rachunkow.add(numer_rachunku);
        } while (rs.next());
        return konta_firmowe;
    }


    /**
     * Metoda przyjmuje jako argumenty id konta oraz tablicę właścicieli klasy Klient i zwraca obiekt klasy Konto_firmowe, które zawiera informacje o koncie firmowym o podanym id_konta, gdzie za pole właścicieli zostaną podstawieni wlasciciele z argumentu.
     * Jeśli nie zostanie znalezione żadne odpowiadające konto firmowe to rzucany jest wyjątek NullPointerException. W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. 
     */
    public Konto_firmowe pobranieInformacjiKontoFirmowe(int id_konta, Klient[] wlasciciele) throws NullPointerException, SQLException
    {
        String query = "select * from Firma inner join Konto_firmowe on Firma.id_firmy = Konto_firmowe.id_firmy where Konto_firmowe.id_konta ='"+id_konta+"'";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        if (rs.next())
        {
            Integer id_firmy = rs.getInt("id_firmy");
            String nazwa_firmy = rs.getString("nazwa_firmy");
            String NIP = rs.getString("NIP");
            String numer_rachunku = rs.getString("numer_rachunku");
            Date data_zalozenia = rs.getDate("data_zalozenia");
            //String data_zalozenia = rs.getString("data_zalozenia");
            BigDecimal saldo = rs.getBigDecimal("saldo");
            Firma firma = new Firma(id_firmy, nazwa_firmy, NIP);
            Konto_firmowe konto_firmowe = new Konto_firmowe(id_konta, numer_rachunku, data_zalozenia, saldo, wlasciciele, firma);
            return konto_firmowe;
        }
        else
        {
            throw new NullPointerException();
        }
    }

    /**
     * Metoda pobiera informacje o wlascicielach konta firmowego o id konta równemu id_konta. Odpowiednie informacje przekazuje jako obiekty klasy Klient to listy wlasciciele podanej jako argument.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public void pobranieInformacjiWlascicieleKontaFirmowego(int id_konta, ArrayList<Klient> wlasciciele) throws SQLException
    {
        String query = "select Klient.imie, Klient.nazwisko from Konto_firmowe_klient inner join Klient on Konto_firmowe_klient.id_klienta = Klient.id_klienta where Konto_firmowe_klient.id_konta ='"+id_konta+"' ";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        while (rs.next())
        {     
            String imie = rs.getString("imie");
            String nazwisko = rs.getString("nazwisko");
            wlasciciele.add(new Klient(imie, nazwisko));
        } 
    }
    
    /**
     * Metoda dodaje do bazy danych nową lokatę o parametrach podanych w argumentach. W zależności czy id_konta odpowiada kontu osobistemu czy firmowemu ustawia odpowiednią wartość w kolumnie na id_konta a drugą na null.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. Jeśli saldo konta jest mniejsze niż kwota na jaką ma zostać założona lokata, rzucany jest wyjątek ArithmeticException.
     */
    public void dodanieLokatyDoBazy(int id_konta, String nazwa_lokaty, BigDecimal kwota, BigDecimal oprocentowanie, Date data_zalozenia, Date data_zakonczenia) throws SQLException, ArithmeticException
    {
        String query = "select * from Konto_osobiste where Konto_osobiste.id_konta ='" + id_konta + "' ";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        int affectedRows = 0;

        if (rs.next()) {
            BigDecimal saldo = rs.getBigDecimal("saldo");
            if (saldo.compareTo(kwota) >= 0) {
                BigDecimal noweSaldo = saldo.subtract(kwota);
                PreparedStatement ps = con.prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
                ps.setBigDecimal(1, noweSaldo);
                ps.setInt(2, id_konta);
                ps.executeUpdate();
                PreparedStatement preparedStatement = con.prepareStatement(
                        "insert into Lokata(id_konto_firmowe, id_konto_osobiste, nazwa_lokaty, kwota, oprocentowanie, data_zalozenia, data_zakonczenia) values (?, ?, ?, ?, ?, ?, ?)");
                preparedStatement.setString(1, null);
                preparedStatement.setInt(2, id_konta);
                preparedStatement.setString(3, nazwa_lokaty);
                preparedStatement.setBigDecimal(4, kwota);
                preparedStatement.setBigDecimal(5, oprocentowanie);
                preparedStatement.setDate(6, data_zalozenia);
                preparedStatement.setDate(7, data_zakonczenia);
                //preparedStatement.setString(6, data_zalozenia);
                //preparedStatement.setString(7, data_zakonczenia);
                affectedRows = preparedStatement.executeUpdate();
            } else {
                throw new ArithmeticException();
            }

        } else {
            String query2 = "select * from Konto_firmowe where Konto_firmowe.id_konta ='" + id_konta + "' ";
            Statement statement = con.createStatement();
            ResultSet resultset = statement.executeQuery(query2);
            BigDecimal saldo = null;
            while (resultset.next()) {
                saldo = resultset.getBigDecimal("saldo");

            }
            if (saldo.compareTo(kwota) >= 0) {
                BigDecimal noweSaldo = saldo.subtract(kwota);
                PreparedStatement ps = con.prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
                ps.setBigDecimal(1, noweSaldo);
                ps.setInt(2, id_konta);
                ps.executeUpdate();
                PreparedStatement preparedStatement = con.prepareStatement(
                        "insert into Lokata(id_konto_firmowe, id_konto_osobiste, nazwa_lokaty, kwota, oprocentowanie, data_zalozenia, data_zakonczenia) values (?, ?, ?, ?, ?, ?, ?)");
                preparedStatement.setInt(1, id_konta);
                preparedStatement.setString(2, null);
                preparedStatement.setString(3, nazwa_lokaty);
                preparedStatement.setBigDecimal(4, kwota);
                preparedStatement.setBigDecimal(5, oprocentowanie);
                preparedStatement.setDate(6, data_zalozenia);
                preparedStatement.setDate(7, data_zakonczenia);
                //preparedStatement.setString(6, data_zalozenia);
                //preparedStatement.setString(7, data_zakonczenia);
                affectedRows = preparedStatement.executeUpdate();
            } else {
                throw new ArithmeticException();
            }
        }
        if (affectedRows == 0) {
            throw new SQLException("Nie utworzono lokaty");
        }

    }
    
    /**
     * Metoda pobiera z bazy saldo konta. Zwraca je jako obiekt klasy BigDecimal.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public BigDecimal pobranie_salda(int id_konta) throws SQLException
    {
        BigDecimal saldo;
        if(!this.czyKontoOsobiste(id_konta)){
            String query = "select * from Konto_firmowe where Konto_firmowe.id_konta='" + id_konta + "'";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            if (rs.next()) {
                saldo = rs.getBigDecimal("saldo");
            } else {
                throw new SQLException();
            }
        } else {
            String query = "select * from Konto_osobiste where Konto_osobiste.id_konta='" + id_konta + "'";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            if (rs.next()) {
                saldo = rs.getBigDecimal("saldo");
            } else {
                throw new SQLException();
            }
        }
        return saldo;
    }

    /**
     * Metoda pobiera informacje o lokatach przypisanych do konta o id konta równemu id_konta. Dane zwraca w liście obiektów klasy Lokata.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public ArrayList<Lokata> pobranieLokat(int id_konta) throws SQLException
    {
        String query = "select * from Lokata where Lokata.id_konto_firmowe='"+id_konta+"' or Lokata.id_konto_osobiste='"+id_konta+"'";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        ArrayList<Lokata> lokaty = new ArrayList<Lokata>();
        while (rs.next())
        {
            Integer id_lokaty = rs.getInt("id_lokaty");  
            String nazwa_lokaty = rs.getString("nazwa_lokaty");     
            BigDecimal kwota = rs.getBigDecimal("kwota");
            BigDecimal oprocentowanie = rs.getBigDecimal("oprocentowanie");
            Date data_zalozenia = rs.getDate("data_zalozenia");
            Date data_zakonczenia = rs.getDate("data_zakonczenia");
            lokaty.add(
                    new Lokata(id_lokaty, nazwa_lokaty, kwota, oprocentowanie, data_zalozenia, data_zakonczenia));
        }
        return lokaty; 
    }

    /**
     * Metoda sprawdza czy istnieje w bazie danych lokata o podanych id_lokaty i id_konta. Zwraca true jeśli tak, false wpp.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public boolean czyIstniejeIdLokaty(int id_konta, int id_lokaty) throws SQLException
    {
        String query = "select * from Lokata where Lokata.id_lokaty='"+id_lokaty+"' and (Lokata.id_konto_firmowe='"+id_konta+"' or Lokata.id_konto_osobiste='"+id_konta+"')";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        return rs.next();
    }

    /**
     * Metoda usuwa z bazy danych aktywną lokatę o podaych id_lokaty i id_konta. Uaktualnia również stan konta, na którym została założona ta lokata.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public void usuwanieLokaty(int id_konta, int id_lokaty) throws SQLException
    {
        BigDecimal saldo = pobranie_salda(id_konta);
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (czyKontoOsobiste){
            String query = "select * from Lokata where id_konto_osobiste='"+id_konta+"'";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            BigDecimal kwota = null;
            while (rs.next()){
                kwota = rs.getBigDecimal("kwota");
            }

            BigDecimal noweSaldo = saldo.add(kwota);

            PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
            preparedStatement.setBigDecimal(1, noweSaldo);
            preparedStatement.setInt(2, id_konta);
            preparedStatement.executeUpdate();
                    
            String query2 = "delete from Lokata where id_konto_osobiste = ? and id_lokaty = ? ";
            PreparedStatement st2 = con.prepareStatement(query2);
            st2.setInt(1,id_konta);
            st2.setInt(2,id_lokaty);
            st2.execute();
        }
        if (!czyKontoOsobiste){
            String query = "select * from Lokata where id_konto_firmowe='"+id_konta+"'";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            BigDecimal kwota = null;
            while (rs.next()){
                kwota = rs.getBigDecimal("kwota");
            }

            BigDecimal noweSaldo = saldo.add(kwota);

            PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
            preparedStatement.setBigDecimal(1, noweSaldo);
            preparedStatement.setInt(2, id_konta);
            preparedStatement.executeUpdate();
            String query2 = "delete from Lokata where id_konto_firmowe = ? and id_lokaty = ? ";
            PreparedStatement st2 = con.prepareStatement(query2);
            st2.setInt(1,id_konta);
            st2.setInt(2,id_lokaty);
            st2.execute();
        }
    }
    
    /**
     * Pobiera informacje o przelewach wykonanych z konta osobistego o numerze id_konta. Zwraca te informacje w liście obiektów typu Przelew.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public ArrayList<Przelew> pobraniePrzelewowWychodzacychKontoOsobiste(int id_konta) throws SQLException
    {
        ArrayList<Przelew> przelewy = new ArrayList<Przelew>();
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (czyKontoOsobiste){
            String query = "(select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_odbiorcy_firmowe, Konto_firmowe.numer_rachunku from Przelew inner join Konto_firmowe on Przelew.id_konta_odbiorcy_firmowe = Konto_firmowe.id_konta where Przelew.id_konta_nadawcy_osobiste ='"+id_konta+"' ) union (select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_odbiorcy_osobiste, Konto_osobiste.numer_rachunku from Przelew inner join Konto_osobiste on Przelew.id_konta_odbiorcy_osobiste = Konto_osobiste.id_konta where Przelew.id_konta_nadawcy_osobiste ='"+id_konta+"')";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            
            while (rs.next()){
                int id_przelewu = rs.getInt("id_przelewu");
                String tytul_przelewu = rs.getString("tytul_przelewu");
                Date data_przelewu = rs.getDate("data_przelewu");
                BigDecimal kwota = rs.getBigDecimal("kwota");
                String numer_rachunku_odbiorcy = rs.getString("numer_rachunku");
                przelewy.add(new Przelew(id_przelewu, "", numer_rachunku_odbiorcy, tytul_przelewu, data_przelewu,
                        kwota));
            }
        }
        return przelewy;
    }
    
    /**
     * Pobiera informacje o przelewach otrzymanych na konto osobiste o numerze id_konta. Zwraca te informacje w liście obiektów typu Przelew.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. 
     */
    public ArrayList<Przelew> pobraniePrzelewowPrzychodzacychKontoOsobiste(int id_konta) throws SQLException
    {
        ArrayList<Przelew> przelewy = new ArrayList<Przelew>();
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (czyKontoOsobiste){
            String query = "(select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_nadawcy_firmowe, Konto_firmowe.numer_rachunku from Przelew inner join Konto_firmowe on Przelew.id_konta_nadawcy_firmowe = Konto_firmowe.id_konta where Przelew.id_konta_odbiorcy_osobiste ='"+id_konta+"' ) union (select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_nadawcy_osobiste, Konto_osobiste.numer_rachunku from Przelew inner join Konto_osobiste on Przelew.id_konta_nadawcy_osobiste = Konto_osobiste.id_konta where Przelew.id_konta_odbiorcy_osobiste ='"+id_konta+"')";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            while (rs.next()){
                int id_przelewu = rs.getInt("id_przelewu");
                String tytul_przelewu = rs.getString("tytul_przelewu");
                Date data_przelewu = rs.getDate("data_przelewu");
                BigDecimal kwota = rs.getBigDecimal("kwota");
                String numer_rachunku_nadawcy = rs.getString("numer_rachunku");
                przelewy.add(new Przelew(id_przelewu, numer_rachunku_nadawcy, "", tytul_przelewu, data_przelewu,
                        kwota));
            }
        }
        return przelewy;
    }
    
    /**
     * Pobiera informacje o przelewach wykonanych z konta firmowego o numerze id_konta. Zwraca te informacje w liście obiektów typu Przelew.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException.
     */
    public ArrayList<Przelew> pobraniePrzelewowWychodzacychKontoFirmowe(int id_konta) throws SQLException
    {
        ArrayList<Przelew> przelewy = new ArrayList<Przelew>();
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (!czyKontoOsobiste){
            String query = "(select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_odbiorcy_firmowe, Konto_firmowe.numer_rachunku from Przelew inner join Konto_firmowe on Przelew.id_konta_odbiorcy_firmowe = Konto_firmowe.id_konta where Przelew.id_konta_nadawcy_firmowe ='"+id_konta+"' ) union (select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_odbiorcy_osobiste, Konto_osobiste.numer_rachunku from Przelew inner join Konto_osobiste on Przelew.id_konta_odbiorcy_osobiste = Konto_osobiste.id_konta where Przelew.id_konta_nadawcy_firmowe ='"+id_konta+"')";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            while (rs.next()){
                int id_przelewu = rs.getInt("id_przelewu");
                String tytul_przelewu = rs.getString("tytul_przelewu");
                Date data_przelewu = rs.getDate("data_przelewu");
                //DateFormat dateFormat = new SimpleDateFormat("yyyy-mm-dd");  
                //String strdata_przelewu = dateFormat.format(data_przelewu);  
                BigDecimal kwota = rs.getBigDecimal("kwota");
                //int id_konta_odbiorcy_firmowe = rs.getInt("id_konta_odbiorcy_firmowe");
                String numer_rachunku_odbiorcy = rs.getString("numer_rachunku");
                przelewy.add(new Przelew(id_przelewu, "", numer_rachunku_odbiorcy, tytul_przelewu, data_przelewu,
                        kwota));
            }
        }
        return przelewy;
    }
    
    /**
     * Pobiera informacje o przelewach otrzymanych na konto firmowe o numerze id_konta. Zwraca te informacje w liście obiektów typu Przelew.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. 
     */
    public ArrayList<Przelew> pobraniePrzelewowPrzychodzacychKontoFirmowe(int id_konta) throws SQLException
    {
        ArrayList<Przelew> przelewy = new ArrayList<Przelew>();
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (!czyKontoOsobiste){
            String query = "(select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_nadawcy_firmowe, Konto_firmowe.numer_rachunku from Przelew inner join Konto_firmowe on Przelew.id_konta_nadawcy_firmowe = Konto_firmowe.id_konta where Przelew.id_konta_odbiorcy_firmowe ='"+id_konta+"' ) union (select Przelew.id_przelewu, Przelew.tytul_przelewu, Przelew.data_przelewu, Przelew.kwota, Przelew.id_konta_nadawcy_osobiste, Konto_osobiste.numer_rachunku from Przelew inner join Konto_osobiste on Przelew.id_konta_nadawcy_osobiste = Konto_osobiste.id_konta where Przelew.id_konta_odbiorcy_firmowe ='"+id_konta+"')";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            while (rs.next()){
                int id_przelewu = rs.getInt("id_przelewu");
                String tytul_przelewu = rs.getString("tytul_przelewu");
                Date data_przelewu = rs.getDate("data_przelewu");
                //DateFormat dateFormat = new SimpleDateFormat("yyyy-mm-dd");  
                //String strdata_przelewu = dateFormat.format(data_przelewu);  
                BigDecimal kwota = rs.getBigDecimal("kwota");
                //int id_konta_nadawcy_firmowe = rs.getInt("id_konta_nadawcy_firmowe");
                String numer_rachunku_nadawcy = rs.getString("numer_rachunku");
                przelewy.add(new Przelew(id_przelewu, numer_rachunku_nadawcy, "", tytul_przelewu, data_przelewu,
                        kwota));
            }
        }
        return przelewy;
    }
    
    /**
     * Sprawdza czy podane id_konta odpowiada jakiemuś koncie osobistemu. Jeśli tak zwraca true, wpp false.
     */
    public boolean czyKontoOsobiste(int id_konta){
        try 
        {
            String query = "select * from Konto_osobiste where Konto_osobiste.id_konta ='"+id_konta+"' ";
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery(query);
            return rs.next();
            
        } 
        catch (SQLException e) 
        {
            e.printStackTrace();
        }
        return false;
    }
    
    
    /**
     * Sprawdza czy w bazie danych istnieje konto o podanym numerze rachunku. Jeśli tak zwraca true, false wpp.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. 
     */
    public boolean czyIstniejeKonto(String numer_rachunku) throws SQLException
    {
       
        String query = "select id_konta from Konto_osobiste where Konto_osobiste.numer_rachunku ='"+numer_rachunku+"' ";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        if (rs.next()) 
            return true;
        String query2 = "select id_konta from Konto_firmowe where Konto_firmowe.numer_rachunku ='"+numer_rachunku+"' ";
        Statement st2 = con.createStatement();
        ResultSet rs2 = st2.executeQuery(query2);
        return rs2.next();
   }
    
    /**
     * Wykonuje przelew z konta o podanym id_konta na konto o podanym numer_rachunku o tytule tytul_przelewu i kwocie kwota. Uaktualnia saldo odpowiednich kont i tworzy nowy wpis w tabeli przechowującecj informacje o przelewach.
     * W wyniku błędu związanego z komunikacją z bazą danych rzucany jest wyjatek SQLException. Jeśli saldo konta jest mniejsze niż kwota na jaką ma zostać wykonany przelew, to rzucany jest wyjątek ArithmeticException.
     */
    public void wykonaniePrzelewu(int id_konta, String numer_rachunku, String tytul_przelewu, BigDecimal kwota) throws SQLException, ArithmeticException
    {
        BigDecimal saldo = this.pobranie_salda(id_konta);
    
        boolean czyKontoOsobiste = czyKontoOsobiste(id_konta);
        if (czyKontoOsobiste){
            if(saldo.compareTo(kwota)>=0){
                String query = "select id_konta, saldo from Konto_osobiste where Konto_osobiste.numer_rachunku ='"+numer_rachunku+"' ";
                Statement st = con.createStatement();
                ResultSet rs = st.executeQuery(query);
                boolean czyKontoOsobisteNrRachunku = rs.next();
                int id_konta_odbiorcy = 0;
                BigDecimal saldo_odbiorcy = new BigDecimal(0);
                if (czyKontoOsobisteNrRachunku) {
                    do {
                        id_konta_odbiorcy = rs.getInt("id_konta");
                        saldo_odbiorcy = rs.getBigDecimal("saldo");
                    }
                    while (rs.next());
                    BigDecimal noweSaldoNadawcy = saldo.subtract(kwota);
                    BigDecimal noweSaldoOdbiorcy = saldo_odbiorcy.add(kwota);
                    PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
                    preparedStatement.setBigDecimal(1, noweSaldoNadawcy);
                    preparedStatement.setInt(2, id_konta);
                    preparedStatement.executeUpdate();
                    
                    PreparedStatement preparedStatement2 = con.prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
                    preparedStatement2.setBigDecimal(1, noweSaldoOdbiorcy);
                    preparedStatement2.setInt(2,id_konta_odbiorcy);
                    preparedStatement2.executeUpdate();
                    
                    PreparedStatement preparedStatement3 = con
                        .prepareStatement("insert into Przelew(id_konta_nadawcy_osobiste, id_konta_odbiorcy_osobiste, tytul_przelewu, data_przelewu, kwota) values (?, ?, ?, ?, ?)");
                    preparedStatement3.setInt(1, id_konta);
                    preparedStatement3.setInt(2, id_konta_odbiorcy);  
                    preparedStatement3.setString(3, tytul_przelewu);  
                    Timestamp ts = new Timestamp(System.currentTimeMillis());
                    Date data_przelewu = new Date(ts.getTime());  
                    preparedStatement3.setDate(4, data_przelewu);
                    preparedStatement3.setBigDecimal(5, kwota);
                    preparedStatement3.executeUpdate();
                    
                }
                if(!czyKontoOsobisteNrRachunku){
                    String query2 = "select id_konta, saldo from Konto_firmowe where Konto_firmowe.numer_rachunku ='"+numer_rachunku+"' ";
                    Statement statement = con.createStatement();
                    ResultSet resultset = st.executeQuery(query2);
                    int id_konta_odbiorcy_firmowe = 0;
                    BigDecimal saldo_odbiorcy_firmowe = new BigDecimal(0);
                    while (resultset.next()){
                        id_konta_odbiorcy_firmowe = resultset.getInt("id_konta");
                        saldo_odbiorcy_firmowe = resultset.getBigDecimal("saldo");
                        
                        
                    }
                    BigDecimal noweSaldoNadawcy = saldo.subtract(kwota);
                    BigDecimal noweSaldoOdbiorcy = saldo_odbiorcy_firmowe.add(kwota);
                    PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
                    preparedStatement.setBigDecimal(1, noweSaldoNadawcy);
                    preparedStatement.setInt(2, id_konta);
                    preparedStatement.executeUpdate();
                    
                    PreparedStatement preparedStatement2 = con.prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
                    preparedStatement2.setBigDecimal(1, noweSaldoOdbiorcy);
                    preparedStatement2.setInt(2,id_konta_odbiorcy_firmowe);
                    preparedStatement2.executeUpdate();
                    
                    PreparedStatement preparedStatement3 = con
                        .prepareStatement("insert into Przelew(id_konta_nadawcy_osobiste, id_konta_odbiorcy_firmowe, tytul_przelewu, data_przelewu, kwota) values (?, ?, ?, ?, ? )");
                    preparedStatement3.setInt(1, id_konta);
                    preparedStatement3.setInt(2, id_konta_odbiorcy_firmowe);  
                    preparedStatement3.setString(3, tytul_przelewu);  
                    Timestamp ts = new Timestamp(System.currentTimeMillis());
                    Date data_przelewu = new Date(ts.getTime());  
                    preparedStatement3.setDate(4, data_przelewu);
                    preparedStatement3.setBigDecimal(5, kwota);
                    preparedStatement3.executeUpdate();
                }

            }else{
                throw new ArithmeticException();
            }
        }
        if (!czyKontoOsobiste){
            if(saldo.compareTo(kwota)>=0){
                String query = "select id_konta, saldo from Konto_osobiste where Konto_osobiste.numer_rachunku ='"+numer_rachunku+"' ";
                Statement st = con.createStatement();
                ResultSet rs = st.executeQuery(query);
                boolean czyKontoOsobisteNrRachunku = rs.next();
                int id_konta_odbiorcy = 0;
                BigDecimal saldo_odbiorcy = new BigDecimal(0);
                
                
                if (czyKontoOsobisteNrRachunku) {
                    do {
                        id_konta_odbiorcy = rs.getInt("id_konta");
                        saldo_odbiorcy = rs.getBigDecimal("saldo");
                        System.out.print(" saldo: " + saldo_odbiorcy);
                        System.out.print(" id_konta_odbiorcy_firmowe: " + id_konta_odbiorcy);
                    }
                    while (rs.next());
                    BigDecimal noweSaldoNadawcy = saldo.subtract(kwota);
                    BigDecimal noweSaldoOdbiorcy = saldo_odbiorcy.add(kwota);
                    PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
                    preparedStatement.setBigDecimal(1, noweSaldoNadawcy);
                    preparedStatement.setInt(2, id_konta);
                    preparedStatement.executeUpdate();
                    
                    PreparedStatement preparedStatement2 = con.prepareStatement("update Konto_osobiste set saldo = ? where id_konta = ?");
                    preparedStatement2.setBigDecimal(1, noweSaldoOdbiorcy);
                    preparedStatement2.setInt(2,id_konta_odbiorcy);
                    preparedStatement2.executeUpdate();
                    
                    PreparedStatement preparedStatement3 = con
                        .prepareStatement("insert into Przelew(id_konta_nadawcy_firmowe, id_konta_odbiorcy_osobiste, tytul_przelewu, data_przelewu, kwota) values (?, ?, ?, ?, ?)");
                    preparedStatement3.setInt(1, id_konta);
                    preparedStatement3.setInt(2, id_konta_odbiorcy);  
                    preparedStatement3.setString(3, tytul_przelewu);  
                    Timestamp ts = new Timestamp(System.currentTimeMillis());
                    Date data_przelewu = new Date(ts.getTime());  
                    preparedStatement3.setDate(4, data_przelewu);
                    preparedStatement3.setBigDecimal(5, kwota);
                    preparedStatement3.executeUpdate();
                    
                }
                if(!czyKontoOsobisteNrRachunku){
                    String query2 = "select id_konta, saldo from Konto_firmowe where Konto_firmowe.numer_rachunku ='"+numer_rachunku+"' ";
                    Statement statement = con.createStatement();
                    ResultSet resultset = st.executeQuery(query2);
                    int id_konta_odbiorcy_firmowe = 0;
                    BigDecimal saldo_odbiorcy_firmowe = new BigDecimal(0);
                    while (resultset.next()){
                        id_konta_odbiorcy_firmowe = resultset.getInt("id_konta");
                        saldo_odbiorcy_firmowe = resultset.getBigDecimal("saldo");
                        
                    }
                    BigDecimal noweSaldoNadawcy = saldo.subtract(kwota);
                    BigDecimal noweSaldoOdbiorcy = saldo_odbiorcy_firmowe.add(kwota);
                    PreparedStatement preparedStatement = con
                            .prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
                    preparedStatement.setBigDecimal(1, noweSaldoNadawcy);
                    preparedStatement.setInt(2, id_konta);
                    preparedStatement.executeUpdate();
                    
                    PreparedStatement preparedStatement2 = con.prepareStatement("update Konto_firmowe set saldo = ? where id_konta = ?");
                    preparedStatement2.setBigDecimal(1, noweSaldoOdbiorcy);
                    preparedStatement2.setInt(2,id_konta_odbiorcy_firmowe);
                    preparedStatement2.executeUpdate();
                    
                    PreparedStatement preparedStatement3 = con
                        .prepareStatement("insert into Przelew(id_konta_nadawcy_firmowe, id_konta_odbiorcy_firmowe, tytul_przelewu, data_przelewu, kwota) values (?, ?, ?, ?, ? )");
                    preparedStatement3.setInt(1, id_konta);
                    preparedStatement3.setInt(2, id_konta_odbiorcy_firmowe);  
                    preparedStatement3.setString(3, tytul_przelewu);  
                    Timestamp ts = new Timestamp(System.currentTimeMillis());
                    Date data_przelewu = new Date(ts.getTime());  
                    preparedStatement3.setDate(4, data_przelewu);
                    preparedStatement3.setBigDecimal(5, kwota);
                    preparedStatement3.executeUpdate();
                }

            }
            else{
                throw new ArithmeticException();
            }
        }    
    }
    
}
