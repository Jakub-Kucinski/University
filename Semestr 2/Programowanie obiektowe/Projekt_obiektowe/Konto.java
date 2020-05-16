package projekt;
import java.math.BigDecimal;
import java.util.*;
import java.sql.Date;
/**
 * Klasa abstrakcyjna po której dziedziczą klasy Konto_firmowe i Konto_osobiste
 */
abstract class Konto
{
    protected Integer id_konta;
    protected String numer_rachunku;
    protected Date data_zalozenia;
    protected BigDecimal saldo;

    public Konto() {
    }
    /**
     * Konstuktor uzupełniający wszystkie pola.
     */
    public Konto(Integer id_konta, String numer_rachunku, Date data_zalozenia, BigDecimal saldo) {
        this.id_konta = id_konta;
        this.numer_rachunku = numer_rachunku;
        this.data_zalozenia = data_zalozenia;
        this.saldo = saldo;
    }

    public Integer getId_konta() {
        return id_konta;
    }

    public void setId_konta(Integer id_konta) {
        this.id_konta = id_konta;
    }

    public String getNumer_rachunku() {
        return numer_rachunku;
    }

    public void setNumer_rachunku(String numer_rachunku) {
        this.numer_rachunku = numer_rachunku;
    }

    public Date getData_zalozenia() {
        return data_zalozenia;
    }

    public void setData_zalozenia(Date data_zalozenia) {
        this.data_zalozenia = data_zalozenia;
    }

    public BigDecimal getSaldo() {
        return saldo;
    }

    public void setSaldo(BigDecimal saldo) {
        this.saldo = saldo;
    }

    /**
     * Zwraca obiekt klasy String, który zawiera czytelną informację o polach obiektu, pomijając pole id_konta
     */
    @Override
    public String toString() {
        return "\nnumer_rachunku - " + numer_rachunku + "\ndata_zalozenia - " + data_zalozenia 
                + "\nsaldo - " + saldo;
    }

}