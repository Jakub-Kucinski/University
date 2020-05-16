#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#define SERVER "localhost"
#define USER   "root"
#define PASS   "011235"
#define DB     "System_rejestracji"

int Baza_logowanie(char * login, char * haslo);
int Baza_lista_przedmiotow();
int Baza_czy_id_przedmiotu(char * numer);
int Baza_lista_aktywnosci();
int Baza_czy_id_aktywnosci(char * numer);
int Baza_dodawanie_rejestru(char * login, char * id_przedmiotu, char * id_aktywnosci, char * czas_nauki, char * data);
int Baza_id_uzytkownika(char * login, char * id_uzytkownika);
int Baza_lista_rejestrow(char * login);
int Baza_ile_rejestrow(char * id_uzytkownika);
int Baza_czy_id_rejestru(char * numer, char * id_uzytkownika);
int Baza_usuwanie_rejestru(char * numer);
int Baza_zmiana_hasla(char * login, char * haslo);
