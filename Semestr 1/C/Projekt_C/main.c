#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include "Interfejs.h"
#include "Zestawienia_interfejs.h"
#include "Admin_interfejs.h"

int main()
{
    char login[52];
    interfejs_logowanie(login);
    int k1=0;
    if(strcmp(login, "Admin")!=0)
        while(1)
        {
            k1=interfejs_funkcjonalnosci(login);
            if(k1==0)
                break;
            if(k1==1)
            {
                interfejs_dodanie_nowego_rejestru(login);
            }
            if(k1==2)
            {
                interfejs_wyswietlanie_rejestrow(login);
            }
            if(k1==3)
            {
                zestawienia_interfejs_wybor(login);
            }
            if(k1==4)
            {
                interfejs_zmiana_hasla(login);
            }
        }
    else
        while(1)
        {
            k1=Admin_interfejs_funkcjonalnosci();
            if(k1==0)
                break;
            if(k1==1)
            {
                Admin_interfejs_dodawanie_uzytkownika();
            }
            if(k1==2)
            {
                Admin_interfejs_dodawanie_przedmiotu();
            }
            if(k1==3)
            {
                Admin_interfejs_dodawanie_aktywnosci();
            }
            if(k1==4)
            {
                Admin_interfejs_zmiana_nazwy_uzytkownika();
            }
            if(k1==5)
            {
                Admin_interfejs_zmiana_nazwy_przedmiotu();
            }
            if(k1==6)
            {
                Admin_interfejs_zmiana_nazwy_aktywnosci();
            }
            if(k1==7)
            {
                Admin_interfejs_usuwanie_uzytkownika();
            }
            if(k1==8)
            {
                Admin_interfejs_usuwanie_przedmiotu();
            }
            if(k1==9)
            {
                Admin_interfejs_usuwanie_aktywnosci();
            }
        }

    return 0;
}
