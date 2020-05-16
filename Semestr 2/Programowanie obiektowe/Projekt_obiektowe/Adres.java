package projekt;
/**
 * Klasa przechowuje informację o adresie klienta
 */
public class Adres
{
    private Integer id_adresu;
    private String panstwo;
    private String miasto;
    private String ulica;
    private String numer_budynku;
    private String numer_lokalu;

    /**
     * Konstruktor bezargumentowy, przypisuje domyślne wartosci do pól
     */
    public Adres()
    {
        this.id_adresu = 0;
        this.panstwo = this.miasto = this.ulica = this.numer_budynku = this.numer_lokalu = "";
    }


    /**
     * Konstruktor, tworzy obiekt klasy Adres odpowiednio zainicjalizowanymi wszystkimi polami
     */
    public Adres(Integer id_adresu, String panstwo, String miasto, String ulica, String numer_budynku,
            String numer_lokalu) {
        this.id_adresu = id_adresu;
        this.panstwo = panstwo;
        this.miasto = miasto;
        this.ulica = ulica;
        this.numer_budynku = numer_budynku;
        this.numer_lokalu = numer_lokalu;
    }

    public Integer getId_adresu() {
        return id_adresu;
    }

    public void setId_adresu(Integer id_adresu) {
        this.id_adresu = id_adresu;
    }

    public String getPanstwo() {
        return panstwo;
    }

    public void setPanstwo(String panstwo) {
        this.panstwo = panstwo;
    }

    public String getMiasto() {
        return miasto;
    }

    public void setMiasto(String miasto) {
        this.miasto = miasto;
    }

    public String getUlica() {
        return ulica;
    }

    public void setUlica(String ulica) {
        this.ulica = ulica;
    }

    public String getNumer_budynku() {
        return numer_budynku;
    }

    public void setNumer_budynku(String numer_budynku) {
        this.numer_budynku = numer_budynku;
    }

    public String getNumer_lokalu() {
        return numer_lokalu;
    }

    public void setNumer_lokalu(String numer_lokalu) {
        this.numer_lokalu = numer_lokalu;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_adresu
     */
    @Override
    public String toString() {
        return "Adres: " + "\npanstwo - " + panstwo +  "\nmiasto - " + miasto + "\nulica - " + ulica + "\nnumer_budynku - " + numer_budynku
                + "\nnumer_lokalu - " + numer_lokalu;
    }

    
}