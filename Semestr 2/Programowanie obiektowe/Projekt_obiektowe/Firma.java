package projekt;
/**
 * Klasa przechowuje informacje o firmie
 */
public class  Firma
{
    private Integer id_firmy;
    private String nazwa_firmy;
    private String NIP;

    /**
     * Konstruktor
     */
    public Firma(Integer id_firmy, String nazwa_firmy, String NIP) {
        this.id_firmy = id_firmy;
        this.nazwa_firmy = nazwa_firmy;
        this.NIP = NIP;
    }

    public String getNazwa_firmy() {
        return nazwa_firmy;
    }

    public void setNazwa_firmy(String nazwa_firmy) {
        this.nazwa_firmy = nazwa_firmy;
    }

    public String getNIP() {
        return NIP;
    }

    public void setNIP(String NIP) {
        this.NIP = NIP;
    }

    public Integer getId_firmy() {
        return id_firmy;
    }

    public void setId_firmy(Integer id_firmy) {
        this.id_firmy = id_firmy;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_firmy
     */
    @Override
    public String toString() {
        return "\nnazwa_firmy - " + nazwa_firmy + "\nNIP - " + NIP;
    }
    
}