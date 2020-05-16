import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.io.Serializable;

public class Pojazd implements ActionListener, Serializable
{
    protected String numer_rejestracyjny;
    protected String marka;
    protected String model;
    protected JButton zapisz;
    protected JTextField numer_rejestracyjny2;
    protected JTextField marka2;
    protected JTextField model2;
    protected String plik;

    public Pojazd(String nr, String ma, String mo) {
        this.numer_rejestracyjny = nr;
        this.marka = ma;
        this.model = mo;
    }

    public Pojazd() {
    }

    @Override
    public String toString() {
        return "marka=" + marka + ", model=" + model + ", numer_rejestracyjny=" + numer_rejestracyjny;
    }

    public void actionPerformed(ActionEvent e)
    {
        Object zrodlo = e.getSource();
        if (zrodlo == zapisz)
        {
            this.numer_rejestracyjny = this.numer_rejestracyjny2.getText();
            this.model = this.model2.getText();
            this.marka = this.marka2.getText();
            System.out.println(this.toString());
            //this.zapisz();
        }
    }
    
    public void Edycja(String p)
    {
        this.plik = p;
        JFrame frame = new JFrame("Edycja pojazdu");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout = new GridLayout(4, 2);
        kontener.setLayout(layout);

        JLabel numer_rejestracyjny_etykieta = new JLabel("Numer rejestracyjny");
        kontener.add(numer_rejestracyjny_etykieta);
        this.numer_rejestracyjny2 = new JTextField(this.numer_rejestracyjny, 40);
        kontener.add(numer_rejestracyjny2);

        JLabel marka_etykieta = new JLabel("Marka");
        kontener.add(marka_etykieta);
        this.marka2 = new JTextField(this.marka, 40);
        kontener.add(marka2);

        JLabel model_etykieta = new JLabel("Model");
        kontener.add(model_etykieta);
        this.model2 = new JTextField(this.model, 40);
        kontener.add(model2);

        this.add_frame(kontener);

        this.zapisz = new JButton("Zapisz");
        zapisz.addActionListener(this);
        kontener.add(zapisz);

        frame.pack();
        frame.setVisible(true);
    }

    protected void add_frame(Container kontener)
    {
        ;
    }
    
    public void zapisz() throws FileNotFoundException, IOException, ClassNotFoundException
    {
        try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(plik))) 
        {
            outputStream.writeObject(this);
            outputStream.close();
        }
        catch (FileNotFoundException e)
        {
            ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("objects.bin"));
            outputStream.writeObject(this);
            outputStream.close();
        }
    }

    // public Pojazd czytaj(String plik) throws FileNotFoundException, IOException, ClassNotFoundException {
    //     ObjectInputStream input = new ObjectInputStream(new FileInputStream(plik));
    //     Pojazd p = (Pojazd) input.readObject();
    //     return p;
    // }

    public static void main(String [] args) throws IOException, ClassCastException, ClassNotFoundException
    {
        // Pojazd pojazd;
        // try (ObjectInputStream input = new ObjectInputStream(new FileInputStream(args[0]))) {
        //     pojazd = (Pojazd) input.readObject();
        //     pojazd.Edycja(args[0]);
        // }
        // catch (FileNotFoundException e)
        // {
        //     pojazd = new Pojazd();
        //     pojazd.Edycja("objects.bin");
        // }

        // Samochod samochod;
        // try (ObjectInputStream input = new ObjectInputStream(new FileInputStream(args[0]))) {
        //     samochod = (Samochod) input.readObject();
        //     samochod.Edycja(args[0]);
        // }
        // catch (FileNotFoundException e)
        // {
        //     samochod = new Samochod();
        //     samochod.Edycja("objects.bin");
        // }

        Tramwaj tramwaj;
        try (ObjectInputStream input = new ObjectInputStream(new FileInputStream(args[0]))) {
            tramwaj = (Tramwaj) input.readObject();
            tramwaj.Edycja(args[0]);
        }
        catch (FileNotFoundException e)
        {
            tramwaj = new Tramwaj();
            tramwaj.Edycja("objects.bin");
        }

        // System.out.println(pojazd.toString());
        // try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("objects.bin"))) {
        //     outputStream.writeObject(pojazd);
        // }
    }
}