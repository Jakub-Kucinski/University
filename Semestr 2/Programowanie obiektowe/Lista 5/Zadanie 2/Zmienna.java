public class Zmienna extends Wyrazenie
{
    public String nazwa;
    public Wyrazenie pochodna()
    {
        return new Stala(1);
    }
    public String toString()
    {
        return this.nazwa;
    }
    public int oblicz()
    {
        return super.hash.numbers.getOrDefault(nazwa, 0);
    }
    Zmienna(String m)
    {
        this.nazwa = m;
    }
}