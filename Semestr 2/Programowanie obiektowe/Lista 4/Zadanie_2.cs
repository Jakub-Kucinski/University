using System;
using System.Collections;

class PrimeCollection: IEnumerable
{
    int prime=2;
    public IEnumerator GetEnumerator()
    {
        return new PrimeEnumerator(prime);
    }
}

class PrimeEnumerator: IEnumerator
{
    int prime;
    public PrimeEnumerator(int prime)
    {
        this.prime = prime;
    }
    public bool MoveNext()
    {
        if(this.prime < 0) 
        {
            return false;
        }
        for(int i = this.prime + 1; i > 0; i++)
        {
            if(this.Is_Prime(i))
            {
                this.prime = i;
                return true;
            }
        }
        return false;
    }
    private bool Is_Prime(int p)
    {
        if(p == 2)
            return true;
        if(p % 2 == 0)
            return false;
        for(int i = 3; i*i <= p; i = i+2)
        {
            if(p % i == 0)
                return false;
        }
        return true;
    }
    public object Current
    {
        get
        {
            return prime;
        }
    }
    public void Reset()
    {
        this.prime = 2;
    }
}

class Program
{
    public static void Main()
    {
        PrimeCollection pc = new PrimeCollection();
        foreach(int p in pc)
        {
            Console.WriteLine(p);
        }
    }
}