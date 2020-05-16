#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int Admin_baza_czy_zajety_login(char * login);
int Admin_baza_czy_przedmiot_istnieje(char * przedmiot);
int Admin_baza_czy_aktywnosc_istnieje(char * aktywnosc);
int Admin_baza_czy_id_uzytkownika_istnieje(char * id_uzytkownika);
int Admin_baza_lista_loginow();
int Admin_baza_dodawanie_nowego_uzytkownika(char * login, char * haslo);
int Admin_baza_dodawanie_nowego_przedmiotu(char * przedmiot);
int Admin_baza_dodawanie_nowej_aktywnosci(char * aktywnosc);
int Admin_baza_zmiana_nazwy_uzytkownika(char * id_uzytkownika, char * login);
int Admin_baza_zmiana_nazwy_przedmiotu(char * id_przedmiotu, char * nazwa_przedmiotu);
int Admin_baza_zmiana_nazwy_aktywnosci(char * id_aktywnosci, char * nazwa_aktywnosci);
int Admin_baza_usuwanie_uzytkownika(char * id_uzytkownika);
int Admin_baza_usuwanie_przedmiotu(char * id_przedmiotu);
int Admin_baza_usuwanie_aktywnosci(char * id_aktywnosci);
