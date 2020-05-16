using System;

class IntStream
{
    protected int current;
    protected bool is_end;
    
    virtual public int next()
    {
        if(this.current==Int32.MaxValue)
        {
            this.is_end=true;
            return this.current;
        }
        else
        {
            this.current++;
            return this.current-1;
        }
    }
    public bool eos()
    {
        return this.is_end;
    }
    virtual public void reset()
    {
        this.is_end=false;
        this.current=0;
    }
    public IntStream()
    {
        this.current=0;
        this.is_end=false;
    }
}

class PrimeStream : IntStream
{
    bool is_prime(int n)
    {
        for(int k=3; k*k<=n; k=k+2)
        {
            if(n % k == 0)
                return false;
        }
        return true;
    }
    override public int next()
    {
        if(eos())
            return base.current;
        if(base.current == 2)
        {
            base.current++;
            return 2;
        }
        for(int i=base.current+2; i<Int32.MaxValue; i=i+2)
        {
            if(is_prime(i))
            {
                int pom=base.current;
                base.current=i;
                return pom;
            }
        }
        base.is_end=true;
        return base.current;
    }
    override public void reset()
    {
        base.is_end=false;
        base.current=2;
    }
    public PrimeStream()
    {
        base.current=2;
        base.is_end=false;
    }
}

class RandomStream : IntStream
{
    override public int next()
    {
        Random rnd = new Random((int)DateTime.Now.Ticks);
        int pom = base.current;
        base.current = rnd.Next();
        return pom;
    }
    override public void reset()
    {
        base.is_end = false;
        Random rnd = new Random();
        base.current = rnd.Next();
    }
    public RandomStream()
    {
        Random rnd = new Random();
        base.current = rnd.Next();
        base.is_end = false;
    }
}

class RandomWordStream
{
    PrimeStream length = new PrimeStream();

    public string next()
    {
        RandomStream randomchar = new RandomStream();
        string word = "";
        int pom = length.next();
        for(int i=0; i < pom; i++)
        {
            int znak=randomchar.next();
            znak=(znak % 26) + 65;
            word += (char) znak;
        }
        return word;
    }
}

class MojProgram 
{
    public static void Main() 
    {
        //RandomStream test = new RandomStream();
        RandomWordStream test = new RandomWordStream();
        for(int i=0; i<9; i++)
        {
            //test.next();
            Console.WriteLine("Numer slowa: {0}     Slowo: {1}", i+1, test.next());
        }
    }
}