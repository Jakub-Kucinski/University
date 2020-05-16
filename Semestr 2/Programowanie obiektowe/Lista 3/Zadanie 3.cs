using System;

sealed class TimeNTon
{
    TimeNTon() {}
    static int max = 5;
    static int index = 0;
    static int count = 0;
    static TimeNTon[] instance = new TimeNTon[max];
    public string name;
    public static TimeNTon Instance()
    {
        DateTime now = DateTime.Now;
        if (now.Hour <= 10 && now.Hour >= 12)
        {
            if (count < max)
            {
                instance[index] = new TimeNTon();
                index++;
                count++;
                return instance[index - 1];
            }        
            if (index == max)
            {
                index = 0;
                return instance[index];
            }
            if (index == max - 1)
            {
                index = 0;
                return instance[index];
            }
            index++;
            return instance[index];
        }
        else
        {
            if (count > 0)
                return instance[0];
            instance[index] = new TimeNTon();
            index++;
            count++;
            return instance[index - 1];
        }
    }
}


sealed class Singleton
{
    Singleton() {}
    static Singleton instance;
    public string nazwa;
    public static Singleton Instance()
    {
        if (instance == null)
            instance = new Singleton();
        return instance;
    }
}

class Program
{
    public static void Main() 
    {
        // Singleton a = Singleton.Instance();
        // a.nazwa = "daa";
        // Console.WriteLine("{0}", a.nazwa);
        // TimeNTon test1 = TimeNTon.Instance();
        // TimeNTon test2 = TimeNTon.Instance();
        // TimeNTon test3 = TimeNTon.Instance();
        // test1.name = "Pierwszy";
        // test2.name = "Drugi";
        // test3.name = "Trzeci";
        // Console.WriteLine("{0}", test3.name);
        // Console.WriteLine("{0}", test2.name);
        // Console.WriteLine("{0}", test1.name);

        TimeNTon[] test = new TimeNTon[10];
        for(int i=0; i<10; i++)
        {
            test[i] = TimeNTon.Instance();
            test[i].name += (char) (i+65);
        }
        for(int i=0; i<10; i++)
        {
            Console.WriteLine("{0}", test[i].name);
        }
        DateTime now = DateTime.Now;
        Console.WriteLine("Hour: {0}", now.Hour);
        //Console.WriteLine("{0}", test.nazwa);
    }
}