public class Program 
{
    public static void main(String[] args) throws InterruptedException 
    {

        Buffer<Integer> buff = new Buffer<Integer>(1000);

        Thread t1 = new Thread(new Runnable() 
        {

            public void run() {
                try {
                    buff.produce(1);
                } catch (InterruptedException e) 
                {
                    e.printStackTrace();
                }
            }
        });

        Thread t2 = new Thread(new Runnable() 
        {
            public void run() {
                try {
                    buff.consume();
                } catch (InterruptedException e) 
                {
                    e.printStackTrace();
                }
            }
        });

        t1.start();
        t2.start();

        t1.join();
        t2.join();
    }
}
  
    