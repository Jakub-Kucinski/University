package paczka;
import java.io.*;
import java.util.*;
public class Program
{
    public static void main(String [] args) throws IOException, ClassCastException, ClassNotFoundException
    {
        Lista l1 = new Lista();
        for (int i = 0; i < 10; i++)
            l1.add_end(i);
        l1.write_all();

        try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("objects.bin"))) {
            outputStream.writeObject(l1);
        }
 
        try (ObjectInputStream input = new ObjectInputStream(new FileInputStream("objects.bin"))) {
            Lista l2 = (Lista) input.readObject();
            l2.write_all();
        }
    }
}
