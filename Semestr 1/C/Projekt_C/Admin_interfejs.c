#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Baza_danych.h"
#include "Zestawienia_baza.h"
#include "Zestawienia_interfejs.h"
#include "Admin_interfejs.h"
#include "Admin_baza.h"

int Admin_interfejs_funkcjonalnosci()
{
    printf("\nProszę wybrać akcję spośród podanych wpisując odpowiadający jej numer:\n");
    printf("0 Wyjście z programu\n");
    printf("1 Dodanie nowego użytkownika\n");
    printf("2 Dodanie nowego przedmiotu\n");
    printf("3 Dodanie nowej aktywności\n");
    printf("4 Zmiana nazwy użytkownika\n");
    printf("5 Zmiana nazwy przedmiotu\n");
    printf("6 Zmiana nazwy aktywności\n");
    printf("7 Usunięcie użytkownika\n");
    printf("8 Usunięcie przedmiotu\n");
    printf("9 Usunięcie aktywności\n");
    char wejscie[52];
    int k;

    do
    {
        k=1;
        fgets(wejscie, 51, stdin);
        if(wejscie[0]<'0' || wejscie[0]>'9')
        {
            k=0;
        }
        if(wejscie[1]!='\n' && wejscie[1]!='\0')
        {
            k=0;
        }
        if(k==0) printf("Niepoprawny format\n");
    }while(k==0);

    if(wejscie[0]=='0')
        return 0;
    if(wejscie[0]=='1')
        return 1;
    if(wejscie[0]=='2')
        return 2;
    if(wejscie[0]=='3')
        return 3;
    if(wejscie[0]=='4')
        return 4;
    if(wejscie[0]=='5')
        return 5;
    if(wejscie[0]=='6')
        return 6;
    if(wejscie[0]=='7')
        return 7;
    if(wejscie[0]=='8')
        return 8;
    return 9;
}

int Admin_interfejs_dodawanie_uzytkownika()
{
    printf("\nLista użytkowników w bazie danych\n");
    Admin_baza_lista_loginow();
    printf("\nProszę podać login nowego użytkownika\n");
    char login[52];
    int k=0;
    do
    {
        k=1;
        czy_login_poprawny(login);
        if(Admin_baza_czy_zajety_login(login)==1)
        {
            printf("\nPodany login jest już zajęty, proszę spróbowac ponownie\n");
            k=0;
        }
        else
        {
            printf("\nPodany login jest wolny\n");
        }
    }while(k==0);
    printf("\nProszę podać hasło nowego użytkownika\n");

    char haslo[52];
    czy_login_poprawny(haslo);


    printf("\nCzy na pewno chcesz dodać użytkownika o podanym loginie i haśle?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano dodawanie nowego użytkownika\n");
    }
    else
    {
        Admin_baza_dodawanie_nowego_uzytkownika(login, haslo);
        printf("\nDodano nowego użytkownika do bazy danych\n");
    }
    return 0;
}

int Admin_interfejs_dodawanie_przedmiotu()
{
    printf("\nLista przedmiotów w bazie danych\n");
    Baza_lista_przedmiotow();
    printf("\nProszę podać nazwę nowego przedmiotu\n");
    char przedmiot[101];
    int k=0;
    do
    {
        k=1;
        fgets(przedmiot, 100, stdin);
        for(int i=0; i<101; i++)
        {
            if(przedmiot[i]=='\n')
            {
                przedmiot[i]='\0';
                break;
            }
            else
            {
                if(przedmiot[i]=='\0')
                    break;
            }
        }
        if(przedmiot[0]=='\0')
        {
            printf("\nPodano pustą nazwę. Proszę spróbować ponownie\n");
            k=0;
        }
        else
        {
        if(Admin_baza_czy_przedmiot_istnieje(przedmiot)==1)
        {
            printf("\nPodany przedmiot już istnieje, proszę spróbowac ponownie\n");
            k=0;
        }
        else
        {
            printf("\nPodanego przedmiotu nie ma jeszcze w bazie danych\n");
        }
        }
    }while(k==0);
    printf("\nCzy na pewno chcesz dodać przedmiot o podanej nazwie?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano dodawanie nowego przedmiotu\n");
    }
    else
    {
        Admin_baza_dodawanie_nowego_przedmiotu(przedmiot);
        printf("\nDodano nowy przedmiot do bazy danych\n");
    }
    return 0;
}

int Admin_interfejs_dodawanie_aktywnosci()
{
    printf("\nLista aktywności w bazie danych\n");
    Baza_lista_przedmiotow();
    printf("\nProszę podać nazwę nowej aktywności\n");
    char aktywnosc[101];
    int k=0;
    do
    {
        k=1;
        fgets(aktywnosc, 100, stdin);
        for(int i=0; i<101; i++)
        {
            if(aktywnosc[i]=='\n')
            {
                aktywnosc[i]='\0';
                break;
            }
            else
            {
                if(aktywnosc[i]=='\0')
                    break;
            }
        }
        if(aktywnosc[0]=='\0')
        {
            printf("\nPodano pustą nazwę. Proszę spróbować ponownie\n");
            k=0;
        }
        else
        {
            if(Admin_baza_czy_aktywnosc_istnieje(aktywnosc)==1)
            {
                printf("\nPodana aktywność już istnieje, proszę spróbowac ponownie\n");
                k=0;
            }
            else
            {
                printf("\nPodanej aktywności nie ma jeszcze w bazie danych\n");
            }
        }
    }while(k==0);
    printf("\nCzy na pewno chcesz dodać aktywność o podanej nazwie?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano dodawanie nowej aktywności\n");
    }
    else
    {
        Admin_baza_dodawanie_nowej_aktywnosci(aktywnosc);
        printf("\nDodano nową aktywność do bazy danych\n");
    }
    return 0;
}

int Admin_interfejs_zmiana_nazwy_uzytkownika()
{
    printf("\nLista użytkowników w bazie danych\n");
    Admin_baza_lista_loginow();
    printf("\nProszę podać wybrane id_użytkownika\n");
    char id_uzytkownika[52];
    int k;
    do
    {
        k=1;
        fgets(id_uzytkownika, 51, stdin);
        if(id_uzytkownika[0]=='\0' || id_uzytkownika[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_uzytkownika[i])==0)
            {
                if(id_uzytkownika[i]!='\n' && id_uzytkownika[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Admin_baza_czy_id_uzytkownika_istnieje(id_uzytkownika);
            if(k==0) printf("Brak użytkownika o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nProszę podać nowy login użytkownika\n");
    char login[52];
    do
    {
        k=1;
        czy_login_poprawny(login);
        if(Admin_baza_czy_zajety_login(login)==1)
        {
            printf("\nPodany login jest już zajęty, proszę spróbowac ponownie\n");
            k=0;
        }
        else
        {
            printf("\nPodany login jest wolny\n");
        }
    }while(k==0);
    printf("\nCzy na pewno chcesz zmienić login wybranego użytkownika?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano zmianę loginu użytkownika\n");
    }
    else
    {
        Admin_baza_zmiana_nazwy_uzytkownika(id_uzytkownika, login);
        printf("\nLogin użytkownika został pomyślnie zmieniony\n");
    }
    return 0;
}

int Admin_interfejs_zmiana_nazwy_przedmiotu()
{
    printf("\nLista przedmiotów w bazie danych\n");
    Baza_lista_przedmiotow();
    printf("\nProszę podać wybrane id_przedmiotu\n");
    char id_przedmiotu[52];
    int k;
    do
    {
        k=1;
        fgets(id_przedmiotu, 51, stdin);
        if(id_przedmiotu[0]=='\0' || id_przedmiotu[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_przedmiotu[i])==0)
            {
                if(id_przedmiotu[i]!='\n' && id_przedmiotu[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_przedmiotu(id_przedmiotu);
            if(k==0) printf("Brak przedmiotu o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nProszę podać nową nazwę przedmiotu\n");
    char przedmiot[101];
    do
    {
        k=1;
        fgets(przedmiot, 100, stdin);
        for(int i=0; i<101; i++)
        {
            if(przedmiot[i]=='\n')
            {
                przedmiot[i]='\0';
                break;
            }
            else
            {
                if(przedmiot[i]=='\0')
                    break;
            }
        }
        if(przedmiot[0]=='\0')
        {
            printf("\nPodano pustą nazwę. Proszę spróbować ponownie\n");
            k=0;
        }
        else
        {
            if(Admin_baza_czy_przedmiot_istnieje(przedmiot)==1)
            {
                printf("\nPodany przedmiot już istnieje, proszę spróbowac ponownie\n");
                k=0;
            }
            else
            {
                printf("\nPodanego przedmiotu nie ma jeszcze w bazie danych\n");
            }
        }
    }while(k==0);
    printf("\nCzy na pewno chcesz zmienić nazwę wybranego przedmiotu?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano zmianę nazwy przedmiotu\n");
    }
    else
    {
        Admin_baza_zmiana_nazwy_przedmiotu(id_przedmiotu, przedmiot);
        printf("\nNazwa przedmiotu została pomyślnie zmieniona\n");
    }
    return 0;
}

int Admin_interfejs_zmiana_nazwy_aktywnosci()
{
    printf("\nLista aktywności w bazie danych\n");
    Baza_lista_aktywnosci();
    printf("\nProszę podać wybrane id_aktywnosci\n");
    char id_aktywnosci[52];
    int k;
    do
    {
        k=1;
        fgets(id_aktywnosci, 51, stdin);
        if(id_aktywnosci[0]=='\0' || id_aktywnosci[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_aktywnosci[i])==0)
            {
                if(id_aktywnosci[i]!='\n' && id_aktywnosci[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_aktywnosci(id_aktywnosci);
            if(k==0) printf("Brak aktywności o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nProszę podać nową nazwę aktywności\n");
    char aktywnosc[101];
    do
    {
        k=1;
        fgets(aktywnosc, 100, stdin);
        for(int i=0; i<101; i++)
        {
            if(aktywnosc[i]=='\n')
            {
                aktywnosc[i]='\0';
                break;
            }
            else
            {
                if(aktywnosc[i]=='\0')
                    break;
            }
        }
        if(aktywnosc[0]=='\0')
        {
            printf("\nPodano pustą nazwę. Proszę spróbować ponownie\n");
            k=0;
        }
        else
        {
            if(Admin_baza_czy_aktywnosc_istnieje(aktywnosc)==1)
            {
                printf("\nPodana aktywność już istnieje, proszę spróbowac ponownie\n");
                k=0;
            }
            else
            {
                printf("\nPodanej aktywności nie ma jeszcze w bazie danych\n");
            }
        }
    }while(k==0);
    printf("\nCzy na pewno chcesz zmienić nazwę wybranej aktywności?\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano zmianę nazwy aktywności\n");
    }
    else
    {
        Admin_baza_zmiana_nazwy_aktywnosci(id_aktywnosci, aktywnosc);
        printf("\nNazwa aktywności została pomyślnie zmieniona\n");
    }
    return 0;
}

int Admin_interfejs_usuwanie_uzytkownika()
{
    printf("\nLista użytkowników w bazie danych\n");
    Admin_baza_lista_loginow();
    printf("\nProszę podać wybrane id_użytkownika\n");
    char id_uzytkownika[52];
    int k;
    do
    {
        k=1;
        fgets(id_uzytkownika, 51, stdin);
        if(id_uzytkownika[0]=='\0' || id_uzytkownika[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_uzytkownika[i])==0)
            {
                if(id_uzytkownika[i]!='\n' && id_uzytkownika[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Admin_baza_czy_id_uzytkownika_istnieje(id_uzytkownika);
            if(k==0) printf("Brak użytkownika o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nCzy na pewno chcesz usunąć wybranego użytkownika i wszystkie związane z tym użytkownikiem rejestry?\n*Operacja jest nieodwracalna*\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano usuwanie użytkownika\n");
    }
    else
    {
        Admin_baza_usuwanie_uzytkownika(id_uzytkownika);
        printf("\nUżytkownik został trwale usunięty z bazy danych\n");
    }
    return 0;
}

int Admin_interfejs_usuwanie_przedmiotu()
{
    printf("\nLista przedmiotów w bazie danych\n");
    Baza_lista_przedmiotow();
    printf("\nProszę podać wybrane id_przedmiotu\n");
    char id_przedmiotu[52];
    int k;
    do
    {
        k=1;
        fgets(id_przedmiotu, 51, stdin);
        if(id_przedmiotu[0]=='\0' || id_przedmiotu[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_przedmiotu[i])==0)
            {
                if(id_przedmiotu[i]!='\n' && id_przedmiotu[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_przedmiotu(id_przedmiotu);
            if(k==0) printf("Brak przedmiotu o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nCzy na pewno chcesz usunąć wybrany przedmiot i wszystkie związane z tym przedmiotem rejestry?\n*Operacja jest nieodwracalna*\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano usuwanie przedmiotu\n");
    }
    else
    {
        Admin_baza_usuwanie_przedmiotu(id_przedmiotu);
        printf("\nPrzedmiot został trwale usunięty z bazy danych\n");
    }
    return 0;
}

int Admin_interfejs_usuwanie_aktywnosci()
{
    printf("\nLista aktywności w bazie danych\n");
    Baza_lista_aktywnosci();
    printf("\nProszę podać wybrane id_aktywnosci\n");
    char id_aktywnosci[52];
    int k;
    do
    {
        k=1;
        fgets(id_aktywnosci, 51, stdin);
        if(id_aktywnosci[0]=='\0' || id_aktywnosci[0]=='\n') k=2;
        for(int i=0; i<52; i++)
        {
            if(isdigit(id_aktywnosci[i])==0)
            {
                if(id_aktywnosci[i]!='\n' && id_aktywnosci[i]!='\0')
                {
                     k=2;
                }
                break;
            }
        }
        if(k==2) printf("Niepoprawny format\n");
        else
        {
            k=Baza_czy_id_aktywnosci(id_aktywnosci);
            if(k==0) printf("Brak aktywności o podanym numerze\n");
        }
    }while(k!=1);

    printf("\nCzy na pewno chcesz usunąć wybraną aktywność i wszystkie związane z tą aktywnością rejestry?\n*Operacja jest nieodwracalna*\n1 Nie\n2 Tak\n");
    k=wczytaj_1_lub_2();
    if(k==1)
    {
        printf("\nAnulowano usuwanie aktywności\n");
    }
    else
    {
        Admin_baza_usuwanie_przedmiotu(id_aktywnosci);
        printf("\nAktywnośc została trwale usunięta z bazy danych\n");
    }
    return 0;
}

int czy_login_poprawny(char * login)
{
    int k;
    do
    {
        k=1;
        fgets(login, 51, stdin);
        if(login[0]=='\0' || login[0]=='\n') k=0;
        for(int i=0; i<52; i++)
        {
            if(isdigit(login[i])==0 && isalpha(login[i])==0)
            {
                if(login[i]!='\n' && login[i]!='\0')
                {
                    k=0;
                }
                break;
            }
        }
        if(k==0) printf("Niepoprawny format. Proszę ponownie podać login:\n");
    }while(k==0);
    for(int i=0; i<52; i++)
    {
        if(login[i]=='\n')
        {
            login[i]='\0';
            break;
        }
        else
        {
            if(login[i]=='\0')
                break;
        }
    }
    return 0;
}
