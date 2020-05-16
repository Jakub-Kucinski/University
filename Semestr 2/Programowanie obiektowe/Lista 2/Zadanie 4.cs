using System;
using System.Collections.Generic;

class ListaLeniwa
{
    protected IList<int> list = new List<int>();

    public int element(int i)
    {
        if(i<1)
        {
            Console.WriteLine("Nie ma elementu o numerze mniejszym niż 1");
            return Int32.MinValue;
        }
        if(this.list.Count < i)
        {
            for(int j=this.list.Count; j<i; j++)
            {
                this.list.Add(this.next());
            }
        }
        return this.list[i-1];
    }
    public int size()
    {
        return this.list.Count;
    }
    virtual protected int next()
    {
        Random rnd = new Random((int)DateTime.Now.Ticks);
        return (int)rnd.Next();
    }
}


class Pierwsze : ListaLeniwa
{
    override protected int next()
    {
        if(size() == 0)
            return 2;
        if(size() == 1)
            return 3;
        if(base.list[size()-1] == Int32.MaxValue) return Int32.MaxValue;
        for(int i=base.list[size()-1]+2; i<Int32.MaxValue; i=i+2)
        {
            if(prime(i)) return i;
        }
        return Int32.MaxValue;
    }
    private bool prime(int n)
    {
        if(n < 2) return false;
        if(n == 2) return true;
        if(n % 2 == 0) return false;
        for(int i=3; i*i <= n; i++)
        {
            if(n % i == 0) return false;
        }
        return true;
    }
}


class Program
{
    public static void Main() 
    {
        Pierwsze test = new Pierwsze();
        Console.WriteLine("Rozmiar:{0}", test.size());
        for(int i=1; i<11; i=i+2)
        {
            Console.WriteLine("Numer slowa: {0}     Rozmiar:{2}     Element: {1}", i, test.element(i), test.size());

        }
    }
}