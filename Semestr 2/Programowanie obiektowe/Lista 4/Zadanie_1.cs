using System;
using System.Collections.Generic;
using System.Collections;

interface ColectionEmpty
{
    bool is_empty();
    int Length{ get;}
}

public class Elem<T>
{
    public T val;
    public Elem<T> prev;
    public Elem<T> next;
    public Elem()
    {
        this.prev = null;
        this.next = null;
        val = default(T);
    }
}

class ListaEnumerator<T>: IEnumerator
{
    Elem<T> lista;
    public ListaEnumerator(Elem<T> lista)
    {
        this.lista = lista;
    }
    public bool MoveNext()
    {
        if (this.lista != null) 
            this.lista = this.lista.next;
        return this.lista != null;
    }
    public object Current 
    {
        get 
        {
            return this.lista.val;
        }
    }
    public void Reset(){}
}

public class Lista<T>: IEnumerable, ColectionEmpty
{
    int length;
    Elem<T> start;
    Elem<T> end;

    public override string ToString()
    {
        Elem<T> pom = start;
        string result = "";
        while(pom != null)
        {
            result += String.Format("{0}", pom.val);
            pom = pom.next;
        }
        return result;
    }
    public T this[int indeks]
    {
        get
        {
            Elem<T> pom = start;
            for(; indeks > 0; indeks--)
            {
                if(pom == null) 
                    return default(T);
                pom = pom.next;
            }
            if(pom == null)
                return default(T);
            return pom.val;
        }
    }
    public IEnumerator GetEnumerator()
    {
        Elem<T> pom = new Elem<T>();
        pom.next = start;
        return new ListaEnumerator<T>(pom);
    }
    public int Length
    {
        get
        {
            return this.length;
        }
    }
    public bool is_empty()
    {
        return this.start == null;
    }
    public void add_end(T element)
    {
        if (this.end == null)
        {
            this.end = new Elem<T>();
            this.start = this.end;
            this.end.val = element;
        }
        else
        {
            this.end.next = new Elem<T>();
            this.end.next.val = element;
            this.end.next.prev = this.end;
            this.end = this.end.next;
        }
        length++;
    }
    public void add_start(T element)
    {
        if (this.start == null)
        {
            this.start = new Elem<T>();
            this.end = this.start;
            this.start.val= element;
        }
        else
        {
            this.start.prev = new Elem<T>();
            this.start.prev.val = element;
            this.start.prev.next = this.start;
            this.start = this.start.prev;
        }
        length++;
    }
    public T pop_end()
    {
        if (this.end == null)
            return default(T);
        if (this.start == this.end)
        {
            this.start = null;
            T pom = this.end.val;
            this.end = null;
            length--;
            return pom;
        }
        else
        {
            T pom = this.end.val;
            this.end = this.end.prev;
            this.end.next = null;
            length--;
            return pom;
        }
    }
    public T pop_start()
    {
        if (this.start == null)
            return default(T);
        if (this.start == this.end)
        {
            this.start = null;
            T pom = this.end.val;
            this.end = null;
            length--;
            return pom;
        }
        else
        {
            T pom = this.start.val;
            this.start = this.start.next;
            this.start.prev = null;
            length--;
            return pom;
        }
    }
    public Lista()
    {
        this.start = null;
        this.end = null;
        this.length = 0;
    }
}

class ListaLeniwa: ColectionEmpty
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
    public bool is_empty()
    {
        return this.list.Count == 0;
    }
    public int Length
    {
        get
        {
            return this.list.Count;
        }
    }
    virtual protected int next()
    {
        Random rnd = new Random((int)DateTime.Now.Ticks);
        return (int)rnd.Next();
    }
}

class Program
{
    public static void Main() 
    {
        Lista<int> test = new Lista<int>();
        for (int i=0; i<10; i++)
        {
            if(i%2 == 0)
                test.add_end(i);
            else
                test.add_start(i);
        }
        foreach(int p in test)
        {
            Console.WriteLine(p);
        }
        Console.WriteLine(test[3]);
        Console.WriteLine(test.ToString());
    }
}