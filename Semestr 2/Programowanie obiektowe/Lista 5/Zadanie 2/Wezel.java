public class Wezel extends Wyrazenie
{
    Wyrazenie w1;
    Wyrazenie w2;
    public Wyrazenie pochodna()
    {
        return new Wyrazenie();
    }
    public String toString()
    {
        return super.toString();
    }
    public int oblicz()
    {
        return 0;
    }
    Wezel(Wyrazenie a, Wyrazenie b)
    {
        this.w1 = a;
        this.w2 = b;
    }
}