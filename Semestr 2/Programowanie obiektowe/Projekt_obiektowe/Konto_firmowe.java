package projekt;
import java.math.BigDecimal;
import java.sql.Date;
import java.util.Arrays;
import java.util.Hashtable;

/**
 * Podklasa klasy Konto, przechowuje informacje o koncie firmowym
 */
public class Konto_firmowe extends Konto {
    private Klient[] wlasciciele;
    private Firma firma;


    public Konto_firmowe() {
    }
    
    public Konto_firmowe(Integer id_konta, String numer_rachunku, Date data_zalozenia, BigDecimal saldo, Klient[] wlasciciele, Firma firma) {
        super(id_konta, numer_rachunku, data_zalozenia, saldo);
        this.wlasciciele = wlasciciele;
        this.firma = firma;
    }

    public Klient[] getWlasciciele() {
        return wlasciciele;
    }

    public void setWlasciciele(Klient[] wlasciciele) {
        this.wlasciciele = wlasciciele;
    }

    public Firma getFirma() {
        return firma;
    }

    public void setFirma(Firma firma) {
        this.firma = firma;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_konta i wypisując jedynie pole imie i nazwisko wlascicieli
     */
    @Override
    public String toString() {
        String s = "\nKonto_firmowe: " + firma.toString() + super.toString() + "\n\n Wlasciciele:";
        for (Klient klient : wlasciciele) {
            s = s + "\n" + klient.getNazwisko() + " " + klient.getImie();
        }
        return s;
    }

    
}