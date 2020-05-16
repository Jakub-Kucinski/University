public class Program 
{
    public static void main(String[] args) throws InterruptedException 
    {

        Buffer<Integer> buff = new Buffer<Integer>(1000);

        Thread t1 = new Thread(new Runnable() 
        {
            public void run() 
            {
                try 
                {
                    Integer value = 0;
                    while (true) 
                    {
                        buff.add(value);
                        System.out.println("Add " + value);
                        value ++;
                        //Thread.sleep(10);
                    }
    
                } catch (InterruptedException e) 
                {
                    e.printStackTrace();
                }
            }
        });

        Thread t2 = new Thread(new Runnable() 
        {
            public void run() 
            {
                try 
                {
                    while (true) 
                    {
                        Integer value = buff.pop();
                        System.out.println("Pop " + value);
                        //Thread.sleep(10);
                    }
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
  
    