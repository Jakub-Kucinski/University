import java.io.*;
import java.util.*; 

public class Wyrazenie implements Arytmetyczne
{
    Singleton hash = Singleton.Instance();
    public Wyrazenie pochodna()
    {
        return new Wyrazenie();
    }
    public void addKeyVal(String s, Integer i)
    {
         this.hash.numbers.put(s, i);
    }
    public int oblicz()
    {
        return 0;
    }
    public String toString()
    {
        return "";
    }
    Wyrazenie() {}
    public static void main(String [] args)
    {
        Wyrazenie wyrazenie = new Dodaj(new Pomnoz(new Stala(4), new Stala(3)), new Pomnoz(new Zmienna("x"), new Zmienna("x")));
        wyrazenie.addKeyVal("x", 5);
        System.out.println(wyrazenie.oblicz());
        Wyrazenie nowe = wyrazenie.pochodna();
        System.out.println(nowe.toString());
        System.out.println(nowe.oblicz());
    }
}
