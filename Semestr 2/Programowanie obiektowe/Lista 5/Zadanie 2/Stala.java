public class Stala extends Wyrazenie
{
    public Wyrazenie pochodna()
    {
        return new Stala(0);
    }
    private int n;
    public String toString()
    {
        return "" + this.n;
    }
    public int oblicz()
    {
        return this.n;
    }
    Stala(int k)
    {
        this.n = k;
    }
}