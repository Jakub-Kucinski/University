package projekt;
import java.io.*;
import java.sql.Array;
import java.util.ArrayList;

/**
 * Klasa odpowiadająca za interfejs programu podczas logowania się użytkownika.
 */
public class Logowanie
{
    /**
     * Wyświetla użytkownikowi informajce o logowaniu. Nastpęnie wczytuje od użytkownika dane do momentu otrzymania Stringa "1" lub "2", które oznaczają na jakie konto użytkownik chce się zalogować.
     * 1 - osobiste
     * 2 - firmowe
     * Zwraca liczbę typu int odpowiadającą wyborowi użytkownika.
     */
    public int wybor_trybu_logowania()
    {
        Console c = System.console();
        if (c == null) 
        {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        int res = 0;
        System.out.print(
                "\nWybierz rodzaj konta, na które chcesz się zalogować podając odpowiedni numer:\n1. Konto osobiste\n2. Konto firmowe\n");
        String s;
        do
        {
            try
            {
                s = c.readLine();
                if(s.length()>1)
                {
                    System.out.print("\nNiepoprawny format\n");
                }
                else
                {
                    if(s.charAt(0) == '2' || s.charAt(0) == '1')
                    {
                        res = s.charAt(0) - '0';
                        b = false;
                    }
                    else
                    {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                System.out.print("\nNiepoprawny format\n");
            }
        } while (b);
        return res;
    }

    /**
     * Wczytuje od użytkownika numer klienta, który chce użyć do zalogwania na konto
     */
    public int wczytywanie_numeru_klienta()
    {
        System.out.print("\nPodaj numer klienta\n");
        return this.wczytywanie_int();
    }

    /**
     * Przyjmuje jako argument ArrayList<Integer> konta odpowiadają id_konta dla kont na które użytkownik może chcieć się zalogować (przy logowaniu na konto firmowe, po podaniu poprawnych danych logowania).
     * ArrayList<String> nazwy_firm oraz ArrayList<String> numery_rachunkow przechowuja odpowiedni informacje o nazwach firm i ich numerach rachunkowych.
     * Metoda wypisuje informacje zawarte w 2. i 3. argumencie, wczytuje liczbę z zakresu 1 do nazwy_firm.size() odpwowiadającą wybranemu przez użytkownika koncie. Zwraca tą liczbę
     */
    public int wczytywanie_indeksu_sposrod_dostepnych_kont(ArrayList<Integer> konta, ArrayList<String> nazwy_firm, ArrayList<String> numery_rachunkow)
    {
        Boolean b = true;
        int n = nazwy_firm.size();
        String[] firmy = new String[n]; 
        firmy = nazwy_firm.toArray(firmy);
        String[] rachunki = new String[n];
        rachunki = numery_rachunkow.toArray(rachunki);
        System.out.println("Wybierz odpowiednie konto podając odpowiadający mu numer porządkowy:");
        int liczba;
        for (int i = 0; i < n; i++)
        {
            int plus1 = i+1;
            System.out.println(plus1 + ". " + firmy[i] + ", " +  rachunki[i]);
        }
        do
        {
            liczba = wczytywanie_int();
            if (liczba > n || liczba < 1)
            {
                System.out.println("\nNiepoprawny numer");
            }
            else
            {
                b = false;
            }
        } while (b);
        return konta.get(n-1);
    }

    /**
     * Metoda wczytuje od użytkownika hasło, którego chce użyć do zalogowania się do konta (musi składać się z cyfr i liter). Zwraca String będący jego reprezentacją.
     */
    public String wczytywanie_hasla()
    {
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        String s = "";
        System.out.print("\nPodaj haslo\n");
        do {
            b = false;
            try
            {
                s = c.readLine();
                int len = s.length();
                for (int i = 0; i < len; i++) 
                {
                    if (!Character.isDigit(s.charAt(i)) && !Character.isLetter(s.charAt(i))) 
                    {
                        System.out.print("\nNiepoprawny format\n");
                        b = true;
                        break;
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                System.out.print("\nNiepoprawny format\n");
            }
            
        } while (b);
        return s;
    }

    /**
     * Wczytuje od użytkownika dane do momentu podania Stringa, który może zostać sparsowany do inta. Zwraca tego inta.
     */
    public int wczytywanie_int()
    {
        int liczba = 0;
        Console c = System.console();
        if (c == null) {
            System.err.println("Brak konsoli");
            System.exit(1);
        }
        boolean b = true;
        String s = "";
        do {
            try
            {
                s = c.readLine();
                if (s.length() > 11) {
                    System.out.print("\nNiepoprawny format\n");
                } 
                else 
                {
                    try 
                    {
                        liczba = Integer.parseInt(s);
                        b = false;
                    } catch (NumberFormatException e) 
                    {
                        System.out.print("\nNiepoprawny format\n");
                    }
                }
            }catch(StringIndexOutOfBoundsException e)
            {
                System.out.print("\nNiepoprawny format\n");
            }
            
        } while (b);
        return liczba;
    }
    
}