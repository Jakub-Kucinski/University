package projekt;
/**
 * Przechowuje informacje o kliencie
 */
public class Klient
{
    private Integer id_klienta;
    private Integer numer_klienta;
    private String imie;
    private String nazwisko;
    private String plec;
    private String PESEL;
    private Adres adres_zamieszkania;
    /**
     * Konstruktor uzupełniający jedynie pola imie i nazwisko klas String.
     */
    public Klient(String imie, String nazwisko)
    {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.id_klienta = this.numer_klienta = 0;
        this.plec = this.PESEL = "";
    }
    /**
     * Konstuktor uzupełniający wszystkie pola.
     */
    public Klient(Integer id_klienta, Integer numer_klienta, String imie, String nazwisko, String plec, String PESEL,
            Adres adres_zamieszkania) {
        this.id_klienta = id_klienta;
        this.numer_klienta = numer_klienta;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
        this.PESEL = PESEL;
        this.adres_zamieszkania = adres_zamieszkania;
    }

    public Integer getId_klienta() {
        return id_klienta;
    }

    public void setId_klienta(Integer id_klienta) {
        this.id_klienta = id_klienta;
    }

    public Integer getNumer_klienta() {
        return numer_klienta;
    }

    public void setNumer_klienta(Integer numer_klienta) {
        this.numer_klienta = numer_klienta;
    }
    
    public String getImie() {
        return imie;
    }

    public void setImie(String imie) {
        this.imie = imie;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public void setNazwisko(String nazwisko) {
        this.nazwisko = nazwisko;
    }

    public String getPlec() {
        return plec;
    }

    public void setPlec(String plec) {
        this.plec = plec;
    }

    public String getPESEL() {
        return PESEL;
    }

    public void setPESEL(String PESEL) {
        this.PESEL = PESEL;
    }

    public Adres getAdres_zamieszkania() {
        return adres_zamieszkania;
    }

    public void setAdres_zamieszkania(Adres adres_zamieszkania) {
        this.adres_zamieszkania = adres_zamieszkania;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_klienta
     */
    @Override
    public String toString() {
        return "Klient: " + "\nnumer klienta - " + numer_klienta + "\nimie - " + imie + "\nnazwisko - " + nazwisko + "\nPESEL - " + PESEL
                 + "\nplec - " + plec + "\n\n" + adres_zamieszkania.toString();
    }

 
    
}