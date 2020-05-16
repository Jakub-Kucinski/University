public class Podziel extends Wezel
{
    public Wyrazenie pochodna()
    {
        return new Podziel(new Odejmij(new Pomnoz(super.w1.pochodna(), super.w2), 
                                       new Pomnoz(super.w1, super.w2.pochodna())),
                           new Pomnoz(w2, w2));
    }
    public String toString()
    {
        return "(" + super.w1.toString() + "/" + super.w2.toString() + ")";
    }
    public int oblicz()
    {
        return super.w1.oblicz() / super.w2.oblicz();
    }
    Podziel(Wyrazenie a, Wyrazenie b)
    {
        super(a, b);
    }
}