using System;
using ProgramLibrary;

//mcs -t:library Zadanie1.cs
//mcs -r:Zadanie1.dll Zadanie1main.cs
//mono Zadanie1main.exe

class Program
{
    public static void Main() 
    {
        ProgramLibrary.Lista<int> test = new ProgramLibrary.Lista<int>();
        //test.add_end(55);
        //test.add_end(60);
        //Console.WriteLine("{0}", test.end.val);
        //Console.WriteLine("{0}", test.end.prev.val);
        //Console.WriteLine("{0}", test.pop_end());
        
        for (int i=0; i<10; i++)
        {
            if(i%2 == 0)
                test.add_end(i);
            else
                test.add_start(i);
        }
        for (int i=0; i<10; i++)
        {
            if (i%2 == 1)
                Console.WriteLine("{0}", test.pop_end());
            else
                Console.WriteLine("{0}", test.pop_start());
        }
        
    }
}