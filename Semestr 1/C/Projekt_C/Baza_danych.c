#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "Baza_danych.h"

int Baza_logowanie(char * login, char * haslo)
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
    sprintf(str, "SELECT COUNT(Id_uzytkownika) FROM Uzytkownicy WHERE Login='%s' AND Haslo='%s'", login, haslo);
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

int Baza_lista_przedmiotow()
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
    if(mysql_query(conn, "SELECT * FROM Przedmioty ORDER BY Id_przedmiotu"))
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

int Baza_czy_id_przedmiotu(char * numer)
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
    sprintf(str, "SELECT COUNT(Id_przedmiotu) FROM Przedmioty WHERE Id_przedmiotu=%s", numer);
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


int Baza_lista_aktywnosci()
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
    if(mysql_query(conn, "SELECT * FROM Aktywnosci ORDER BY Id_aktywnosci"))
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

int Baza_czy_id_aktywnosci(char * numer)
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
    sprintf(str, "SELECT COUNT(Id_aktywnosci) FROM Aktywnosci WHERE Id_aktywnosci=%s", numer);
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

int Baza_id_uzytkownika(char * login, char * id_uzytkownika)
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
    sprintf(str, "SELECT Id_uzytkownika FROM Uzytkownicy WHERE Login='%s'", login);

    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    sscanf(row[0], "%s", id_uzytkownika);
    int czy_jest=0;
    sscanf(row[0], "%d", &czy_jest);

    mysql_free_result(res);
    mysql_close(conn);
    if(czy_jest==0)
    {
        return 1;
    }
    return 0;
}

int Baza_dodawanie_rejestru(char * login, char * id_przedmiotu, char * id_aktywnosci, char * czas_nauki, char * data)
{
    MYSQL *conn;
    MYSQL_RES *res;
    //MYSQL_ROW row;
    char id_uzytkownika[52];
    int k=Baza_id_uzytkownika(login, id_uzytkownika);
    if(k==1) return 1;

    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, SERVER, USER, PASS, DB, 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    char str[1000];
    sprintf(str, "INSERT INTO Rejestry (Id_uzytkownika, Czas_nauki, Data, Id_przedmiotu, Id_aktywnosci) VALUES (%s, '%s', '%s', %s, %s);",
            id_uzytkownika, czas_nauki, data, id_przedmiotu, id_aktywnosci);

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

int Baza_lista_rejestrow(char * login)
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
    sprintf(str, " SELECT Rejestry.Id_rejestru, Uzytkownicy.Login, Przedmioty.Nazwa_przedmiotu, Aktywnosci.Nazwa_aktywnosci, Rejestry.Data, Rejestry.Czas_nauki FROM (((Rejestry INNER JOIN Uzytkownicy ON (Rejestry.Id_uzytkownika=Uzytkownicy.Id_uzytkownika)) INNER JOIN Przedmioty ON (Rejestry.Id_przedmiotu=Przedmioty.Id_przedmiotu)) INNER JOIN Aktywnosci ON (Rejestry.Id_aktywnosci=Aktywnosci.Id_aktywnosci)) WHERE Uzytkownicy.Login='%s' ORDER BY Rejestry.Id_rejestru DESC LIMIT 10", login);

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

int Baza_ile_rejestrow(char * id_uzytkownika)
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
    sprintf(str, "SELECT COUNT(Id_rejestru) FROM Rejestry WHERE Id_uzytkownika=%s", id_uzytkownika);
    if(mysql_query(conn, str))
    {
        printf("%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
    res=mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int ile=0;
    sscanf(row[0], "%d", &ile);
    mysql_free_result(res);
    mysql_close(conn);
    return ile;
}

int Baza_czy_id_rejestru(char * numer, char * id_uzytkownika)
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
    sprintf(str, "SELECT COUNT(Id_rejestru) FROM Rejestry WHERE Id_rejestru=%s AND Id_uzytkownika=%s", numer, id_uzytkownika);
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

int Baza_usuwanie_rejestru(char * numer)
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
    sprintf(str, "DELETE FROM Rejestry WHERE Id_rejestru=%s", numer);
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

int Baza_zmiana_hasla(char * login, char * haslo)
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
    char id_uzytkownika[52];
    Baza_id_uzytkownika(login, id_uzytkownika);
    char str[1000];
    sprintf(str, "UPDATE Uzytkownicy SET Haslo='%s' WHERE Login='%s'", haslo, login);
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
