package projekt;
import java.math.BigDecimal;
import java.sql.Date;

/**
 * Podklasa klasy Konto, przechowuje informacje o koncie firmowym
 */
public class Konto_osobiste extends Konto {
    private String haslo;
    private Klient wlasciciel;

    public Konto_osobiste() {
    }

    public Konto_osobiste(Integer id_konta, String numer_rachunku, Date data_zalozenia, BigDecimal saldo,
            String haslo, Klient wlasciciel) {
        super(id_konta, numer_rachunku, data_zalozenia, saldo);
        this.haslo = haslo;
        this.wlasciciel = wlasciciel;
    }
    
    public Klient getWlasciciel() {
        return wlasciciel;
    }

    public void setWlasciciel(Klient wlasciciel) {
        this.wlasciciel = wlasciciel;
    }

    public String getHaslo() {
        return haslo;
    }

    public void setHaslo(String haslo) {
        this.haslo = haslo;
    }
    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_konta i haslo
     */
    @Override
    public String toString() {
        return "\nKonto_osobiste: " + super.toString() + "\n\n" + wlasciciel.toString();
    }

}