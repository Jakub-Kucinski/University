#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Baza_danych.h"
#include "Zestawienia_baza.h"
#include "Zestawienia_interfejs.h"


int zestawienia_interfejs_wybor(char * login)
{
    printf("\nWybierz akcje spośród podanych\n");
    printf("0 Powrot do menu\n");
    printf("1 Wypisanie rejestrów według wybranego przedmiotu lub aktywności\n");
    printf("2 Wygenerowanie zestawienia dla poszczególnych przedmiotów i aktywności\n");
    printf("3 Wygenerowanie zestawienia dla poszczególnych przedmiotów\n");
    printf("4 Wygenerowanie zestawienia dla poszczególnych aktywności\n");
    int k=wczytaj_0_1_2_3_4();
    if(k==1)
    {
        zestawienia_interfejs_wyswietlenie_rejestrow(login);
    }
    if(k==2)
    {
        zestawienia_interfejs_sredni_czas(login);
    }
    if(k==3)
    {
        zestawienia_interfejs_sredni_czas_przedmiotu(login);
    }
    if(k==4)
    {
        zestawienia_interfejs_sredni_czas_aktywnosci(login);
    }
    return 0;
}

int zestawienia_interfejs_sredni_czas_aktywnosci(char * login)
{
    char id_uzytkownika[52];
    Baza_id_uzytkownika(login, id_uzytkownika);
    printf("\nNależy stworzyć zestawienie średniego czasu nauki studentów czy sumy czasu nauki użytkownika?\n1 Średni czas nauki studentów\n2 Suma czasu nauki użytkownika\n");
    int w1=wczytaj_1_lub_2();
    printf("\nWykonać zestawienie dla wszystkich aktywności czy dla wybranej\n1 Wszystkie aktywonści\n2 Wybrana aktywność\n");
    int w3=wczytaj_1_lub_2();
    char aktywnosc[52];
    if(w3==2)
    {
        printf("\nWybierz aktywność z listy wpisując jej numer\n");
        Baza_lista_aktywnosci();
        wczytaj_aktywnosc(aktywnosc);
    }
    if(w1==1)
    {
        if(w3==1)
        {
            Zestawienia_skrot_baza_aktywnosci_11();
        }
        else
        {
            Zestawienia_skrot_baza_aktywnosci_12(aktywnosc);
        }
    }
    else
    {
        if(w3==1)
        {
            Zestawienia_skrot_baza_aktywnosci_21(id_uzytkownika);
        }
        else
        {
            Zestawienia_skrot_baza_aktywnosci_22(aktywnosc, id_uzytkownika);
        }
    }
    return 0;
}


int zestawienia_interfejs_sredni_czas_przedmiotu(char * login)
{
    char id_uzytkownika[52];
    Baza_id_uzytkownika(login, id_uzytkownika);
    printf("\nNależy stworzyć zestawienie średniego czasu nauki studentów czy sumy czasu nauki użytkownika?\n1 Średni czas nauki studentów\n2 Suma czasu nauki użytkownika\n");
    int w1=wczytaj_1_lub_2();
    printf("\nNależy zbudować zestawienie ze wszystkich przedmiotów czy z wybranego?\n1 Wszystkie przedmioty\n2 Wybrany przedmiot\n");
    int w2=wczytaj_1_lub_2();
    char przedmiot[52];
    if(w2==2)
    {
        printf("\nWybierz przedmiot z listy wpisując jej numer\n");
        Baza_lista_przedmiotow();
        wczytaj_przedmiot(przedmiot);
    }
    if(w1==1)
    {
        if(w2==1)
        {
            Zestawienia_skrot_baza_przedmioty_11();
        }
        else
        {
            Zestawienia_skrot_baza_przedmioty_12(przedmiot);
        }
    }
    else
    {
        if(w2==1)
        {
            Zestawienia_skrot_baza_przedmioty_21(id_uzytkownika);
        }
        else
        {
            Zestawienia_skrot_baza_przedmioty_22(przedmiot, id_uzytkownika);
        }
    }
    return 0;
}


int zestawienia_interfejs_wyswietlenie_rejestrow(char * login)
{
    printf("\nNależy wypisać rejestry ze wszystkich przedmiotów czy z wybranego?\n1 Wszystkie przedmioty\n2 Wybrany przedmiot\n");
    int w2=wczytaj_1_lub_2();
    char przedmiot[52];
    if(w2==2)
    {
        printf("\nWybierz przedmiot z listy wpisując jej numer\n");
        Baza_lista_przedmiotow();
        wczytaj_przedmiot(przedmiot);
    }
    printf("\nWypisać rejestry wszystkich aktywności czy wybranej\n1 Wszystkie aktywonści\n2 Wybrana aktywność\n");
    int w3=wczytaj_1_lub_2();
    char aktywnosc[52];
    if(w3==2)
    {
        printf("\nWybierz aktywność z listy wpisując jej numer\n");
        Baza_lista_aktywnosci();
        wczytaj_aktywnosc(aktywnosc);
    }
    if(w2==1)
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_rejestry_111(login);
            }
            else
            {
                Zestawienia_skrot_baza_rejestry_112(login, aktywnosc);
            }
        }
        else
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_rejestry_121(login, przedmiot);
            }
            else
            {
                Zestawienia_skrot_baza_rejestry_122(login, przedmiot, aktywnosc);
            }
        }
    return 0;
}


int zestawienia_interfejs_sredni_czas(char * login)
{
    char id_uzytkownika[52];
    Baza_id_uzytkownika(login, id_uzytkownika);
    printf("\nNależy stworzyć zestawienie średniego czasu nauki studentów czy sumy czasu nauki użytkownika?\n1 Średni czas nauki studentów\n2 Suma czasu nauki użytkownika\n");
    int w1=wczytaj_1_lub_2();
    printf("\nNależy zbudować zestawienie ze wszystkich przedmiotów czy z wybranego?\n1 Wszystkie przedmioty\n2 Wybrany przedmiot\n");
    int w2=wczytaj_1_lub_2();
    char przedmiot[52];
    if(w2==2)
    {
        printf("\nWybierz przedmiot z listy wpisując jej numer\n");
        Baza_lista_przedmiotow();
        wczytaj_przedmiot(przedmiot);
    }
    printf("\nWykonać zestawienie dla wszystkich aktywności czy dla wybranej\n1 Wszystkie aktywonści\n2 Wybrana aktywność\n");
    int w3=wczytaj_1_lub_2();
    char aktywnosc[52];
    if(w3==2)
    {
        printf("\nWybierz aktywność z listy wpisując jej numer\n");
        Baza_lista_aktywnosci();
        wczytaj_aktywnosc(aktywnosc);
    }
    if(w1==1)
    {
        if(w2==1)
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_111();
            }
            else
            {
                Zestawienia_skrot_baza_112(aktywnosc);
            }
        }
        else
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_121(przedmiot);
            }
            else
            {
                Zestawienia_skrot_baza_122(przedmiot, aktywnosc);
            }
        }
    }
    else
    {
        if(w2==1)
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_211(id_uzytkownika);
            }
            else
            {
                Zestawienia_skrot_baza_212(id_uzytkownika, aktywnosc);
            }
        }
        else
        {
            if(w3==1)
            {
                Zestawienia_skrot_baza_221(id_uzytkownika, przedmiot);
            }
            else
            {
                Zestawienia_skrot_baza_222(id_uzytkownika, przedmiot, aktywnosc);
            }
        }
    }
    return 0;
}

int wczytaj_0_1_2_3_4()
{
    char wybor[52];
    int k=1;
    do
    {
        k=1;
        fgets(wybor, 51, stdin);
        if(!(wybor[0]=='0' || wybor[0]=='1' || wybor[0]=='2' || wybor[0]=='3' || wybor[0]=='4') || !(wybor[1]=='\n' || wybor[1]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
    }while(k!=1);
    if(wybor[0]=='1')
    {
        return 1;
    }
    if(wybor[0]=='2')
    {
        return 2;
    }
    if(wybor[0]=='3')
    {
        return 3;
    }
    if(wybor[0]=='4')
    {
        return 4;
    }
    return 0;
}

int wczytaj_1_lub_2()
{
    char wybor[52];
    int k=1;
    do
    {
        k=1;
        fgets(wybor, 51, stdin);
        if(!(wybor[0]=='1' || wybor[0]=='2') || !(wybor[1]=='\n' || wybor[1]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
    }while(k!=1);
    if(wybor[0]=='1')
    {
        return 1;
    }
    return 2;
}

int wczytaj_przedmiot(char * przedmiot)
{
    int k;
    do
    {
        k=1;
        fgets(przedmiot, 51, stdin);
        for(int i=0; i<52; i++)
        {
            if(isdigit(przedmiot[i])==0)
            {
                if(przedmiot[i]!='\n' && przedmiot[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_przedmiotu(przedmiot);
            if(k==0) printf("Brak przedmiotu o podanym numerze\n");
        }
    }while(k!=1);
    return 0;
}

int wczytaj_aktywnosc(char * aktywnosc)
{
    int k=1;
    do
    {
        k=1;
        fgets(aktywnosc, 51, stdin);
        for(int i=0; i<52; i++)
        {
            if(isdigit(aktywnosc[i])==0)
            {
                if(aktywnosc[i]!='\n' && aktywnosc[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_aktywnosci(aktywnosc);
            if(k==0) printf("Brak aktywnosci o podanym numerze\n");
        }
    }while(k!=1);
    return 0;
}
