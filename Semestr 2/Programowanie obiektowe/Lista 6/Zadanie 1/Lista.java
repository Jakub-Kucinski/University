package paczka;
import java.io.*;
import java.util.*;
import java.lang.*;
import java.io.Serializable;


public class Lista implements Serializable
{
    public Elem start;
    public Elem end;

    public class Elem implements Serializable
    {
        public int val;
        public Elem prev;
        public Elem next;
        public Elem()
        {
            this.prev = null;
            this.next = null;
            val = 0;
        }
    }
    public void write_all()
    {
        Elem pom = start;
        while(pom != null)
        {
            System.out.println(pom.val);
            pom = pom.next;
        }
    }
    public boolean is_empty()
    {
        return this.start == null;
    }
    public void add_end(int element)
    {
        if (this.end == null)
        {
            this.end = new Elem();
            this.start = this.end;
            this.end.val = element;
        }
        else
        {
            this.end.next = new Elem();
            this.end.next.val = element;
            this.end.next.prev = this.end;
            this.end = this.end.next;
            
        }
    }
    public void add_start(int element)
    {
        if (this.start == null)
        {
            this.start = new Elem();
            this.end = this.start;
            this.start.val= element;
        }
        else
        {
            this.start.prev = new Elem();
            this.start.prev.val = element;
            this.start.prev.next = this.start;
            this.start = this.start.prev;
        }
    }
    public int pop_end()
    {
        if (this.end == null)
            return 0;
        if (this.start == this.end)
        {
            this.start = null;
            int pom = this.end.val;
            this.end = null;
            return pom;
        }
        else
        {
            int pom = this.end.val;
            this.end = this.end.prev;
            this.end.next = null;
            return pom;
        }
    }
    public int pop_start()
    {
        if (this.start == null)
            return 0;
        if (this.start == this.end)
        {
            this.start = null;
            int pom = this.end.val;
            this.end = null;
            return pom;
        }
        else
        {
            int pom = this.start.val;
            this.start = this.start.next;
            this.start.prev = null;
            return pom;
        }
    }
    public Lista()
    {
        this.start = null;
        this.end = null;
    }
}
