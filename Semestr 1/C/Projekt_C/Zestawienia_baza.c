#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "Zestawienia_baza.h"
#include "Baza_danych.h"


int Zestawienia_skrot_baza_111()
{
    char widok[1000]="CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci";

    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_112(char * aktywnosc)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", aktywnosc);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_121(char * przedmiot)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", przedmiot);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_122(char * przedmiot, char * aktywnosc)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s AND Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", przedmiot, aktywnosc);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_211(char * id_uzytkownika)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_uzytkownika=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", id_uzytkownika);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_212(char * id_uzytkownika, char * aktywnosc)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_uzytkownika=%s AND Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", id_uzytkownika, aktywnosc);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_221(char * id_uzytkownika, char * przedmiot)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s AND Id_uzytkownika=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", przedmiot, id_uzytkownika);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_222(char * id_uzytkownika, char * przedmiot, char * aktywnosc)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s AND Id_uzytkownika=%s AND Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_przedmiotu, Id_aktywnosci", przedmiot, id_uzytkownika, aktywnosc);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM (((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_rejestry_111(char * login)
{
    char str[1000];
    sprintf(str, "SELECT Rejestry.Id_rejestru, Uzytkownicy.Login, Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, Rejestry.Data, Rejestry.Czas_nauki FROM (((Rejestry INNER JOIN Uzytkownicy ON (Rejestry.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Rejestry.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Rejestry.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) WHERE Uzytkownicy.Login='%s' ORDER BY Rejestry.Id_rejestru", login);
    wypisz_rejestry(str);
    return 0;
}

int Zestawienia_skrot_baza_rejestry_112(char * login, char * aktywnosc)
{
    char str[1000];
    sprintf(str, "SELECT Rejestry.Id_rejestru, Uzytkownicy.Login, Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, Rejestry.Data, Rejestry.Czas_nauki FROM (((Rejestry INNER JOIN Uzytkownicy ON (Rejestry.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Rejestry.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Rejestry.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) WHERE Uzytkownicy.Login='%s' AND Aktywnosci.Id_aktywnosci=%s ORDER BY Rejestry.Id_rejestru", login, aktywnosc);
    wypisz_rejestry(str);
    return 0;
}

int Zestawienia_skrot_baza_rejestry_121(char * login, char * przedmiot)
{
    char str[1000];
    sprintf(str, "SELECT Rejestry.Id_rejestru, Uzytkownicy.Login, Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, Rejestry.Data, Rejestry.Czas_nauki FROM (((Rejestry INNER JOIN Uzytkownicy ON (Rejestry.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Rejestry.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Rejestry.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) WHERE Uzytkownicy.Login='%s' AND Przedmioty.Id_przedmiotu=%s ORDER BY Rejestry.Id_rejestru", login, przedmiot);
    wypisz_rejestry(str);
    return 0;
}

int Zestawienia_skrot_baza_rejestry_122(char * login, char * przedmiot, char * aktywnosc)
{
    char str[1000];
    sprintf(str, "SELECT Rejestry.Id_rejestru, Uzytkownicy.Login, Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, Rejestry.Data, Rejestry.Czas_nauki FROM (((Rejestry INNER JOIN Uzytkownicy ON (Rejestry.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Rejestry.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Rejestry.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) WHERE Uzytkownicy.Login='%s' AND Przedmioty.Id_przedmiotu=%s AND Aktywnosci.Id_aktywnosci=%s ORDER BY Rejestry.Id_rejestru", login, przedmiot, aktywnosc);
    wypisz_rejestry(str);
    return 0;
}

int Zestawienia_skrot_baza_przedmioty_11()
{
    char widok[1000]="CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry GROUP BY Id_uzytkownika, Id_przedmiotu";

    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) GROUP BY Przedmioty.Nazwa_przedmiotu ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_przedmioty_12(char * przedmiot)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s GROUP BY Id_uzytkownika, Id_przedmiotu", przedmiot);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) GROUP BY Przedmioty.Nazwa_przedmiotu ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_przedmioty_21(char * id_uzytkownika)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_uzytkownika=%s GROUP BY Id_uzytkownika, Id_przedmiotu", id_uzytkownika);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) GROUP BY Przedmioty.Nazwa_przedmiotu ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_przedmioty_22(char * przedmiot, char * id_uzytkownika)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_przedmiotu, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_przedmiotu=%s AND Id_uzytkownika=%s GROUP BY Id_uzytkownika, Id_przedmiotu", przedmiot, id_uzytkownika);
    char str[1000]="SELECT Przedmioty.Nazwa_przedmiotu, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Suma_czasu_uzytkownikow.Id_przedmiotu=Przedmioty.Id_przedmiotu)) GROUP BY Przedmioty.Nazwa_przedmiotu ORDER BY Przedmioty.Nazwa_przedmiotu";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_aktywnosci_11()
{
    char widok[1000]="CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry GROUP BY Id_uzytkownika, Id_aktywnosci";

    char str[1000]="SELECT Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_aktywnosci_12(char * aktywnosc)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_aktywnosci", aktywnosc);
    char str[1000]="SELECT Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Sredni_czas FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_aktywnosci_21(char * id_uzytkownika)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_uzytkownika=%s GROUP BY Id_uzytkownika, Id_aktywnosci", id_uzytkownika);
    char str[1000]="SELECT Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int Zestawienia_skrot_baza_aktywnosci_22(char * aktywnosc, char * id_uzytkownika)
{
    char widok[1000];
    sprintf(widok, "CREATE OR REPLACE VIEW Suma_czasu_uzytkownikow AS SELECT Id_uzytkownika, Id_aktywnosci, SUM(TIME_TO_SEC(Czas_nauki)) AS Suma_czasu FROM Rejestry WHERE Id_uzytkownika=%s AND Id_aktywnosci=%s GROUP BY Id_uzytkownika, Id_aktywnosci", id_uzytkownika, aktywnosc);
    char str[1000]="SELECT Aktywnosci.Nazwa_aktywnosci, SEC_TO_TIME(AVG(Suma_czasu_uzytkownikow.Suma_czasu)) AS Suma_czasu_nauki_uzytkownika FROM ((Suma_czasu_uzytkownikow INNER JOIN Uzytkownicy ON (Suma_czasu_uzytkownikow.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Aktywnosci ON (Suma_czasu_uzytkownikow.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) GROUP BY Aktywnosci.Nazwa_aktywnosci ORDER BY Aktywnosci.Nazwa_aktywnosci";
    wypisz(widok, str);
    return 0;
}

int wypisz(char * widok, char * str)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    if(mysql_query(conn, widok))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    unsigned int n_cols = mysql_num_fields(res);
    MYSQL_FIELD *field = NULL;
    printf("\n");
    printf("|");
    do
    {
        field = mysql_fetch_field(res);
        if (field) printf(" %s |", field->name);
    }while(field);

    printf("\n----------------------------------------------------------------------------------\n");
    do
    {
        row=mysql_fetch_row(res);
        if(row)
        {
            printf("|");
            for(unsigned int kol=0; kol<n_cols; kol++)
                printf(" %s |", row[kol]);
            printf("\n");
        }
     }while(row);
    printf("\n");
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int wypisz_rejestry(char *str)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    unsigned int n_cols = mysql_num_fields(res);
    MYSQL_FIELD *field = NULL;
    printf("\n");
    printf("|");
    do
    {
        field = mysql_fetch_field(res);
        if (field) printf(" %s |", field->name);
    }while(field);

    printf("\n----------------------------------------------------------------------------------\n");
    do
    {
        row=mysql_fetch_row(res);
        if(row)
        {
            printf("|");
            for(unsigned int kol=0; kol<n_cols; kol++)
                printf(" %s |", row[kol]);
            printf("\n");
        }
    }while(row);
    printf("\n");
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
