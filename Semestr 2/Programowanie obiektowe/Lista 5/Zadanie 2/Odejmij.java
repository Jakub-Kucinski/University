public class Odejmij extends Wezel
{
    public Wyrazenie pochodna()
    {
        return new Odejmij(super.w1.pochodna(), super.w2.pochodna());
    }
    public String toString()
    {
        return "(" + super.w1.toString() + "-" + super.w2.toString() + ")";
    }
    public int oblicz()
    {
        return super.w1.oblicz() - super.w2.oblicz();
    }
    Odejmij(Wyrazenie a, Wyrazenie b)
    {
        super(a, b);
    }
}