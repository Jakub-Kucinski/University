#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "Zestawienia_baza.h"
#include "Baza_danych.h"
#include "Admin_baza.h"

int Admin_baza_czy_zajety_login(char * login)
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
    char str[1000];
    sprintf(str, "SELECT COUNT(Id_uzytkownika) FROM Uzytkownicy WHERE Login='%s'", login);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int czy_jest=0;
    sscanf(row[0], "%d", &czy_jest);
    mysql_free_result(res);
    mysql_close(conn);

    if(czy_jest==0)
    {
        return 0;
    }
    return 1;
}

int Admin_baza_czy_przedmiot_istnieje(char * przedmiot)
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
    char str[1000];
    sprintf(str, "SELECT COUNT(Id_przedmiotu) FROM Przedmioty WHERE Nazwa_przedmiotu='%s'", przedmiot);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int czy_jest=0;
    sscanf(row[0], "%d", &czy_jest);
    mysql_free_result(res);
    mysql_close(conn);

    if(czy_jest==0)
    {
        return 0;
    }
    return 1;
}

int Admin_baza_czy_aktywnosc_istnieje(char * aktywnosc)
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
    char str[1000];
    sprintf(str, "SELECT COUNT(Id_aktywnosci) FROM Aktywnosci WHERE Nazwa_aktywnosci='%s'", aktywnosc);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int czy_jest=0;
    sscanf(row[0], "%d", &czy_jest);
    mysql_free_result(res);
    mysql_close(conn);

    if(czy_jest==0)
    {
        return 0;
    }
    return 1;
}

int Admin_baza_lista_loginow()
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
    if(mysql_query(conn, "SELECT Id_uzytkownika, Login FROM Uzytkownicy ORDER BY Login"))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    unsigned int n_cols = mysql_num_fields(res);
    MYSQL_FIELD *field = NULL;

    do
    {
        field = mysql_fetch_field(res);
        if (field) printf("%s\t", field->name);
    }while(field);

    printf("\n");
    do
    {
        row=mysql_fetch_row(res);
        if(row)
        {
            for(unsigned int kol=0; kol<n_cols; kol++)
                printf("%s\t", row[kol]);
            printf("\n");
        }
     }while(row);

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int Admin_baza_dodawanie_nowego_uzytkownika(char * login, char * haslo)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "INSERT INTO Uzytkownicy (Login, Haslo) VALUES ('%s', '%s');", login, haslo);

    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int Admin_baza_dodawanie_nowego_przedmiotu(char * przedmiot)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "INSERT INTO Przedmioty (Nazwa_przedmiotu) VALUES ('%s');", przedmiot);

    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int Admin_baza_dodawanie_nowej_aktywnosci(char * aktywnosc)
{

    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "INSERT INTO Aktywnosci (Nazwa_aktywnosci) VALUES ('%s');", aktywnosc);

    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int Admin_baza_czy_id_uzytkownika_istnieje(char * id_uzytkownika)
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
    char str[1000];
    sprintf(str, "SELECT COUNT(Id_uzytkownika) FROM Uzytkownicy WHERE Id_uzytkownika=%s", id_uzytkownika);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int czy_jest=0;
    sscanf(row[0], "%d", &czy_jest);
    mysql_free_result(res);
    mysql_close(conn);

    if(czy_jest==0)
    {
        return 0;
    }
    return 1;
}

int Admin_baza_zmiana_nazwy_uzytkownika(char * id_uzytkownika, char * login)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "UPDATE Uzytkownicy SET Login='%s' WHERE Id_uzytkownika=%s", login, id_uzytkownika);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int Admin_baza_zmiana_nazwy_przedmiotu(char * id_przedmiotu, char * nazwa_przedmiotu)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "UPDATE Przedmioty SET Nazwa_przedmiotu='%s' WHERE Id_przedmiotu=%s", nazwa_przedmiotu, id_przedmiotu);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int Admin_baza_zmiana_nazwy_aktywnosci(char * id_aktywnosci, char * nazwa_aktywnosci)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "UPDATE Aktywnosci SET Nazwa_aktywnosci='%s' WHERE Id_aktywnosci=%s", nazwa_aktywnosci, id_aktywnosci);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int Admin_baza_usuwanie_uzytkownika(char * id_uzytkownika)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "DELETE FROM Rejestry WHERE Id_uzytkownika=%s", id_uzytkownika);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);

    sprintf(str, "DELETE FROM Uzytkownicy WHERE Id_uzytkownika=%s", id_uzytkownika);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int Admin_baza_usuwanie_przedmiotu(char * id_przedmiotu)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "DELETE FROM Rejestry WHERE Id_przedmiotu=%s", id_przedmiotu);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);

    sprintf(str, "DELETE FROM Przedmioty WHERE Id_przedmiotu=%s", id_przedmiotu);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int Admin_baza_usuwanie_aktywnosci(char * id_aktywnosci)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "DELETE FROM Rejestry WHERE Id_aktywnosci=%s", id_aktywnosci);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);

    sprintf(str, "DELETE FROM Aktywnosci WHERE Id_aktywnosci=%s", id_aktywnosci);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
