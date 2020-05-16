#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void interfejs_logowanie(char login[52]);
int interfejs_funkcjonalnosci();
int interfejs_dodanie_nowego_rejestru(char * login);
int poprawna_data(char * data);
int interfejs_wyswietlanie_rejestrow(char * login);
int interfejs_zmiana_hasla(char * login);
