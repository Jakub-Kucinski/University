import java.io.*;
import java.util.*; 

public class Singleton
{
    private Singleton() {}
    static Singleton instance;
    public Hashtable<String, Integer> numbers = new Hashtable<String, Integer>();
    public static Singleton Instance()
    {
        if (instance == null)
            instance = new Singleton();
        return instance;
    }
}