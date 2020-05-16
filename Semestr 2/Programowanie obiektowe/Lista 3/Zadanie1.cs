using System;

namespace ProgramLibrary
{
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

    public class Lista<T>
    {
        public Elem<T> start;
        public Elem<T> end;
        public int is_empty()
        {
            if (this.start == null)
                return 1;
            return 0;
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
                return pom;
            }
            else
            {
                T pom = this.end.val;
                this.end = this.end.prev;
                this.end.next = null;
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
                return pom;
            }
            else
            {
                T pom = this.start.val;
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
}