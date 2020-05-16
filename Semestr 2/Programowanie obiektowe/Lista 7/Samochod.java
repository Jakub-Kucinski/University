import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.io.Serializable;

public class Samochod extends Pojazd implements ActionListener, Serializable
{
    protected String wlasciciel;
    protected String rocznik;
    protected String kolor;
    protected JTextField wlasciciel2;
    protected JTextField rocznik2;
    protected JTextField kolor2;

    public Samochod(String nr, String ma, String mo, String wl, String ro, String ko)
    {
        super(nr, ma, mo);
        this.wlasciciel = wl;
        this.rocznik = ro;
        this.kolor = ko;
    }

    public Samochod() {}
    
    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object zrodlo = e.getSource();
        if (zrodlo == zapisz)
        {
            super.numer_rejestracyjny = super.numer_rejestracyjny2.getText();
            super.model = super.model2.getText();
            super.marka = super.marka2.getText();
            this.wlasciciel = this.wlasciciel2.getText();
            this.rocznik = this.rocznik2.getText();
            this.kolor = this.kolor2.getText();
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
        JLabel wlasciciel_etykieta = new JLabel("Właściciel");
        kontener.add(wlasciciel_etykieta);
        this.wlasciciel2 = new JTextField(this.wlasciciel, 40);
        kontener.add(wlasciciel2);

        JLabel rocznik_etykieta = new JLabel("Rocznik");
        kontener.add(rocznik_etykieta);
        this.rocznik2 = new JTextField(this.rocznik, 40);
        kontener.add(rocznik2);

        JLabel kolor_etykieta = new JLabel("Kolor");
        kontener.add(kolor_etykieta);
        this.kolor2 = new JTextField(this.kolor, 40);
        kontener.add(kolor2);
    }


    @Override
    public String toString() {
        return super.toString() + " kolor=" + kolor + ", rocznik=" + rocznik + ", wlasciciel=" + wlasciciel;
    }
    
    
}