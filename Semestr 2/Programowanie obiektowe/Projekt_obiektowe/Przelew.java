package projekt;
import java.math.BigDecimal;
import java.sql.Date;
import java.util.*;

/**
 * Klasa Przelew przechowuje informacje o przelewie związanym z pewnymi dwoma kontami.
 */
public class Przelew
{
    private Integer id_przelewu;
    private String numer_rachunku_nadawcy;
    private String numer_rachunku_odbiorcy;
    private String tytul_przelewu;
    private Date data_przelewu;
    private BigDecimal kwota;

    /**
     * Konstuktor uzupełniający wszystkie pola.
     */
    public Przelew(Integer id_przelewu, String numer_rachunku_nadawcy, String numer_rachunku_odbiorcy,
            String tytul_przelewu, Date data_przelewu, BigDecimal kwota) {
        this.id_przelewu = id_przelewu;
        this.numer_rachunku_nadawcy = numer_rachunku_nadawcy;
        this.numer_rachunku_odbiorcy = numer_rachunku_odbiorcy;
        this.tytul_przelewu = tytul_przelewu;
        this.data_przelewu = data_przelewu;
        this.kwota = kwota;
    }

    public Integer getId_przelewu() {
        return id_przelewu;
    }

    public void setId_przelewu(Integer id_przelewu) {
        this.id_przelewu = id_przelewu;
    }
    
    public String getTytul_przelewu() {
        return tytul_przelewu;
    }

    public void setTytul_przelewu(String tytul_przelewu) {
        this.tytul_przelewu = tytul_przelewu;
    }
    
    public Date getData_przelewu() {
        return data_przelewu;
    }

    public void setData_przelewu(Date data_przelewu) {
        this.data_przelewu = data_przelewu;
    }

    public BigDecimal getKwota() {
        return kwota;
    }

    public void setKwota(BigDecimal kwota) {
        this.kwota = kwota;
    }

    public String getNumer_rachunku_nadawcy() {
        return numer_rachunku_nadawcy;
    }

    public void setNumer_rachunku_nadawcy(String numer_rachunku_nadawcy) {
        this.numer_rachunku_nadawcy = numer_rachunku_nadawcy;
    }

    public String getNumer_rachunku_odbiorcy() {
        return numer_rachunku_odbiorcy;
    }

    public void setNumer_rachunku_odbiorcy(String numer_rachunku_odbiorcy) {
        this.numer_rachunku_odbiorcy = numer_rachunku_odbiorcy;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o wszystkich polach obiektu.
     */
    @Override
    public String toString() {
        return "\nPrzelew:" + "\nid_przelewu - " + id_przelewu + "\nnumer_rachunku_nadawcy - " + numer_rachunku_nadawcy
                + "\nnumer_rachunku_odbiorcy - " + numer_rachunku_odbiorcy + "\ntytul_przelewu - " + tytul_przelewu
                + "\ndata_przelewu - " + data_przelewu + "\nkwota - " + kwota + "\n";
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole numer_rachunku_odbiorcy
     */
    public String toStringBezOdbiorcy() {
        return "\nPrzelew:" + "\nid_przelewu - " + id_przelewu + "\nnumer_rachunku_nadawcy - " + numer_rachunku_nadawcy
                + "\ntytul_przelewu - " + tytul_przelewu + "\ndata_przelewu - " + data_przelewu + "\nkwota - " + kwota
                + "\n";
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole numer_rachunku_nadawcy
     */
    public String toStringBezNadawcy() {
        return "\nPrzelew:" + "\nid_przelewu - " + id_przelewu + "\nnumer_rachunku_odbiorcy - "
                + numer_rachunku_odbiorcy + "\ntytul_przelewu - " + tytul_przelewu + "\ndata_przelewu - "
                + data_przelewu + "\nkwota - " + kwota + "\n";
    }
    

}