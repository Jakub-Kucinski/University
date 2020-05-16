#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int wypisz(char * widok, char * str);
int wypisz_rejestry(char *str);

int Zestawienia_skrot_baza_111();
int Zestawienia_skrot_baza_112(char * aktywnosc);
int Zestawienia_skrot_baza_121(char * przedmiot);
int Zestawienia_skrot_baza_122(char * przedmiot, char * aktywnosc);
int Zestawienia_skrot_baza_211(char * id_uzytkownika);
int Zestawienia_skrot_baza_212(char * id_uzytkownika, char * aktywnosc);
int Zestawienia_skrot_baza_221(char * id_uzytkownika, char * przedmiot);
int Zestawienia_skrot_baza_222(char * id_uzytkownika, char * przedmiot, char * aktywnosc);
int Zestawienia_skrot_baza_rejestry_111(char * login);
int Zestawienia_skrot_baza_rejestry_112(char * login, char * aktywnosc);
int Zestawienia_skrot_baza_rejestry_121(char * login, char * przedmiot);
int Zestawienia_skrot_baza_rejestry_122(char * login, char * przedmiot, char * aktywnosc);
int Zestawienia_skrot_baza_przedmioty_11();
int Zestawienia_skrot_baza_przedmioty_12(char * przedmiot);
int Zestawienia_skrot_baza_przedmioty_21(char * id_uzytkownika);
int Zestawienia_skrot_baza_przedmioty_22(char * przedmiot, char * id_uzytkownika);
int Zestawienia_skrot_baza_aktywnosci_11();
int Zestawienia_skrot_baza_aktywnosci_12(char * aktywnosc);
int Zestawienia_skrot_baza_aktywnosci_21(char * id_uzytkownika);
int Zestawienia_skrot_baza_aktywnosci_22(char * aktywnosc, char * id_uzytkownika);
