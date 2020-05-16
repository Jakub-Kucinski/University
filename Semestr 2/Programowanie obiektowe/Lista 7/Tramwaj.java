import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.io.Serializable;

public class Tramwaj extends Pojazd
{
    protected int liczba_wagonow;
    protected int liczba_miejsc_stojacych;
    protected int liczba_miejsc_siedzacych;
    protected JTextField liczba_wagonow2;
    protected JTextField liczba_miejsc_stojacych2;
    protected JTextField liczba_miejsc_siedzacych2;

    public Tramwaj(String nr, String ma, String mo, int lw, int lst, int lsi)
    {
        super(nr, ma, mo);
        this.liczba_wagonow = lw;
        this.liczba_miejsc_siedzacych = lsi;
        this.liczba_miejsc_stojacych = lst;
    }

    public Tramwaj(){}

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object zrodlo = e.getSource();
        if (zrodlo == zapisz)
        {
            super.numer_rejestracyjny = super.numer_rejestracyjny2.getText();
            super.model = super.model2.getText();
            super.marka = super.marka2.getText();
            this.liczba_wagonow = Integer.valueOf(this.liczba_wagonow2.getText());
            this.liczba_miejsc_stojacych = Integer.valueOf(this.liczba_miejsc_stojacych2.getText());
            this.liczba_miejsc_siedzacych = Integer.valueOf(this.liczba_miejsc_siedzacych2.getText());
            System.out.println(this.toString());
            //this.zapisz();
        }
    }


    public void Edycja(String p)
    {
        super.Edycja(p);
    }

    @Override
    protected void add_frame(Container kontener)
    {
        JLabel liczba_wagonow_etykieta = new JLabel("Liczba wagonow");
        kontener.add(liczba_wagonow_etykieta);
        this.liczba_wagonow2 = new JTextField(Integer.toString(this.liczba_wagonow), 40);
        kontener.add(liczba_wagonow2);

        JLabel liczba_miejsc_stojacych_etykieta = new JLabel("Liczba miejsc stojacych");
        kontener.add(liczba_miejsc_stojacych_etykieta);
        this.liczba_miejsc_stojacych2 = new JTextField(Integer.toString(this.liczba_miejsc_stojacych), 40);
        kontener.add(liczba_miejsc_stojacych2);

        JLabel liczba_miejsc_siedzacych_etykieta = new JLabel("Liczba miejsc siedzacych");
        kontener.add(liczba_miejsc_siedzacych_etykieta);
        this.liczba_miejsc_siedzacych2 = new JTextField(Integer.toString(this.liczba_miejsc_siedzacych), 40);
        kontener.add(liczba_miejsc_siedzacych2);
    }


    @Override
    public String toString() {
        return super.toString() + " liczba_miejsc_siedzacych=" + liczba_miejsc_siedzacych
                + ", liczba_miejsc_stojacych="
                + liczba_miejsc_stojacych + ", liczba_wagonow=" + liczba_wagonow;
    }
    
    
}