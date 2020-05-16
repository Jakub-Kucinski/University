public class Buffer<T>
{
    public int max_length;
    public int length;
    
    public class Elem<T>
    {
        public T val;
        public Elem<T> prev;
        public Elem<T> next;
        Elem()
        {
            this.prev = null;
            this.next = null;
        }
    }
    public Elem<T> start;
    public Elem<T> end;

    private void add_start(T element)
    {
        if (this.start == null) {
            this.start = new Elem<T>();
            this.end = this.start;
            this.start.val = element;
        } else {
            this.start.prev = new Elem<T>();
            this.start.prev.val = element;
            this.start.prev.next = this.start;
            this.start = this.start.prev;
        }
        this.length++;
    }
    private T pop_end()
    {
        if (this.end == null)
            return this.end.val;
        if (this.start == this.end) {
            this.start = null;
            T pom = this.end.val;
            this.end = null;
            length--;
            return pom;
        } else {
            T pom = this.end.val;
            this.end = this.end.prev;
            this.end.next = null;
            length--;
            return pom;
        }
    }

    public void add(T value) throws InterruptedException 
    {
        synchronized (this) 
        {
            while (this.length >= max_length) 
                wait();
            this.add_start(value);
            notify();
        }
    }

    public T pop() throws InterruptedException 
    {
        synchronized (this) 
        {
            while (this.length == 0) 
                wait();
            T value = this.pop_end();
            notify();
            return value;
        }
    }

    Buffer(int size)
    {
        this.start = null;
        this.end = null;
        this.max_length = size;
        this.length = 0;
    }
}