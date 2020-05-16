package projekt;
import java.math.BigDecimal;
import java.util.*;
import java.sql.Date;
/**
 * Klasa Lokata przechowuje informacje o lokacie związanej z pewnym kontem.
 */
public class Lokata
{
    private Integer id_lokaty;
    private Integer id_konto_firmowe;
    private Integer id_konto_osobiste;
    private String nazwa_lokaty;
    private BigDecimal kwota;
    private BigDecimal oprocentowanie;
    private Date data_zalozenia;
    private Date data_zakonczenia;

    /**
     * Konstuktor nieprzypisujący wartości do pól id_konto_firmowe i id_konto_osobiste
     */
    public Lokata(Integer id_lokaty, String nazwa_lokaty, BigDecimal kwota, BigDecimal oprocentowanie, Date data_zalozenia, Date data_zakonczenia)
    {
        this.id_lokaty = id_lokaty;
        this.nazwa_lokaty = nazwa_lokaty;
        this.kwota = kwota;
        this.oprocentowanie = oprocentowanie;
        this.data_zalozenia = data_zalozenia;
        this.data_zakonczenia = data_zakonczenia;
    }

     /**
     * Konstuktor uzupełniający wszystkie pola.
     */
    public Lokata(Integer id_lokaty, Integer id_konto_firmowe, Integer id_konto_osobiste, String nazwa_lokaty, BigDecimal kwota, BigDecimal oprocentowanie, Date data_zalozenia,
            Date data_zakonczenia) {
        this.id_lokaty = id_lokaty;
        this.id_konto_firmowe = id_konto_firmowe;
        this.id_konto_osobiste = id_konto_osobiste;
        this.nazwa_lokaty = nazwa_lokaty;
        this.kwota = kwota;
        this.oprocentowanie = oprocentowanie;
        this.data_zalozenia = data_zalozenia;
        this.data_zakonczenia = data_zakonczenia;
    }


    public Integer getId_lokaty() {
        return id_lokaty;
    }

    public void setId_lokaty(Integer id_lokaty) {
        this.id_lokaty = id_lokaty;
    }

    public Integer getId_konto_firmowe() {
        return id_konto_firmowe;
    }

    public void setId_konto_firmowe(Integer id_konto_firmowe) {
        this.id_konto_firmowe = id_konto_firmowe;
    }

    public Integer getId_konto_osobiste() {
        return id_konto_osobiste;
    }

    public void setId_konto_osobiste(Integer id_konto_osobiste) {
        this.id_konto_osobiste = id_konto_osobiste;
    }

    public String getNazwa_lokaty() {
        return nazwa_lokaty;
    }

    public void setNazwa_lokaty(String nazwa_lokaty) {
        this.nazwa_lokaty = nazwa_lokaty;
    }

    public BigDecimal getKwota() {
        return kwota;
    }

    public void setKwota(BigDecimal kwota) {
        this.kwota = kwota;
    }

    public BigDecimal getOprocentowanie() {
        return oprocentowanie;
    }

    public void setOprocentowanie(BigDecimal oprocentowanie) {
        this.oprocentowanie = oprocentowanie;
    }

    public Date getData_zalozenia() {
        return data_zalozenia;
    }

    public void setData_zalozenia(Date data_zalozenia) {
        this.data_zalozenia = data_zalozenia;
    }

    public Date getData_zakonczenia() {
        return data_zakonczenia;
    }

    public void setData_zakonczenia(Date data_zakonczenia) {
        this.data_zakonczenia = data_zakonczenia;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pola id_konto_firmowe i id_konto_osobiste.
     */
    @Override
    public String toString() {
        return "\nLokata: " + "\nid_lokaty - " + id_lokaty + "\nnazwa lokaty - " + nazwa_lokaty + "\nkwota - " + kwota + "\noprocentowanie - " + oprocentowanie + "%" +
        "\ndata_zalozenia - " + data_zalozenia + "\ndata_zakonczenia - " + data_zakonczenia + "\n";
    }

}