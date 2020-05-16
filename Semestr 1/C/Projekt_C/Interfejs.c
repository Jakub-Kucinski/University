#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Baza_danych.h"
#include "Interfejs.h"

void interfejs_logowanie(char login[52])
{
    int czy;
    do
    {
        czy=1;
        char haslo[52];
        printf("Proszę podac login:\n");
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

        printf("Proszę podać hasło:\n");
        do
        {
            k=1;
            fgets(haslo, 51, stdin);
            if(haslo[0]=='\0' || haslo[0]=='\n') k=0;
            for(int i=0; i<52; i++)
            {
                if(isdigit(haslo[i])==0 && isalpha(haslo[i])==0)
                {
                    if(haslo[i]!='\n' && haslo[i]!='\0')
                    {
                        k=0;
                    }
                    break;
                }
            }
            if(k==0) printf("Niepoprawny format. Proszę ponownie podać hasło:\n");
        }while(k==0);

        for(int i=0; i<52; i++)
        {
            if(haslo[i]=='\n')
            {
                haslo[i]='\0';
                break;
            }
            else
            {
                if(haslo[i]=='\0')
                    break;
            }
        }
        if(Baza_logowanie(login, haslo)!=0)
        {
            printf("Poprawne dane logowania.\n\n");
        }
        else
        {
            printf("Niepoprawny login lub hasło.\n\n");
            czy=0;
        }
    }while(czy==0);
}

int interfejs_funkcjonalnosci()
{
    printf("\nProszę wybrać akcję spośród podanych wpisując odpowiadający jej numer:\n");
    printf("0 Wyjście z programu\n");
    printf("1 Dodanie nowego rejestru\n");
    printf("2 Wyświetlenie i usuwanie rejestrów użytkownika\n");
    printf("3 Generowanie zestawień\n");
    printf("4 Zmiana hasła\n");
    char wejscie[52];
    int k;

    do
    {
        k=1;
        fgets(wejscie, 51, stdin);
        if(wejscie[0]<'0' || wejscie[0]>'4')
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
    return 4;
}

int interfejs_dodanie_nowego_rejestru(char * login)
{
    printf("\nWybierz przedmiot z listy wpisując jego numer\n");
    Baza_lista_przedmiotow();
    char przedmiot[52];
    int k;

    do
    {
        k=1;
        fgets(przedmiot, 51, stdin);
        if(przedmiot[0]=='\0' || przedmiot[0]=='\n') k=2;
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

    printf("\nWybierz aktywność z listy wpisując jej numer\n");
    Baza_lista_aktywnosci();

    char aktywnosc[52];
    do
    {
        k=1;
        fgets(aktywnosc, 51, stdin);
        if(aktywnosc[0]=='\0' || aktywnosc[0]=='\n') k=2;
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

    printf("\nPodaj czas nauki w formacie HH:MM\n");
    char czas[52];

    do
    {
        k=1;
        fgets(czas, 51, stdin);
        if(!(isdigit(czas[0])) || !(isdigit(czas[1])) || !(czas[2]==':') || !(czas[3]>='0' && czas[3]<='5') || !(isdigit(czas[4])) || !(czas[5]=='\n' || czas[5]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
        else
        {
            czas[5]='\0';
        }
    }while(k!=1);

    printf("\nPodaj datę w formacie YYYY-MM-DD\n");

    char data[52];
    do
    {
        k=1;
        fgets(data, 51, stdin);
        if(!(isdigit(data[0])) || !(isdigit(data[1])) || !(isdigit(data[2])) || !(isdigit(data[3]))
        || !(data[4]=='-') || !(isdigit(data[5])) || !(isdigit(data[6]))
        || !(data[7]=='-') || !(isdigit(data[8])) || !(isdigit(data[9]))
        || !(data[10]=='\n' || data[10]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
        else
        {
            k=poprawna_data(data);
            if(k==0) printf("Nieprawidłowa data\n");
            data[10]='\0';
        }
    }while(k!=1);

    printf("\nCzy na pewno dodać podany rejestr do bazy?\n1 Nie\n2 Tak\n");
    char wejscie[52];
    do
    {
        k=1;
        fgets(wejscie, 51, stdin);
        if(!(wejscie[0]=='1' || wejscie[0]=='2') || !(wejscie[1]=='\n' || wejscie[1]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
    }while(k!=1);
    if(wejscie[0]=='2')
    {
        k=Baza_dodawanie_rejestru(login, przedmiot, aktywnosc, czas, data);
        if(k==0)
            printf("\nRejestr został pomyślnie dodany do bazy danych\n\n");
        else
            printf("\nBłąd dodawania rejestru");
    }
    else
    {
        printf("\nAnulowano dodawanie rejestru do bazy danych\n\n");
    }
    return 0;
}

int poprawna_data(char * data)
{
    int rok=0;
    for(int i=0; i<4; i++)
    {
        rok=rok*10+(data[i]-'0');
    }
    if(rok>2019 || rok <2018) return 0;
    int miesiac=(data[5]-'0')*10 + (data[6]-'0');
    if(miesiac>12 || miesiac <1) return 0;
    int dzien=(data[8]-'0')*10 + (data[9]-'0');
    if(dzien>31 || dzien <1) return 0;
    if((miesiac==2 && dzien>28) || ((miesiac==4 || miesiac ==6 || miesiac ==9 || miesiac==11) && dzien>30)) return 0;
    return 1;
}

int interfejs_wyswietlanie_rejestrow(char * login)
{

    Baza_lista_rejestrow(login);

    int k;
    printf("\nJaką akcję chcesz wykonać?\n0 Powrót do menu akcji\n1 Usunąć wybrany rejestr\n");
    char wejscie[52];
    do
    {
        k=1;
        fgets(wejscie, 51, stdin);
        if(!(wejscie[0]=='0' || wejscie[0]=='1')  || !(wejscie[1]=='\n' || wejscie[1]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
    }while(k!=1);

    if(wejscie[0]=='1')
    {
        char id_uzytkownika[52];
        if(Baza_id_uzytkownika(login, id_uzytkownika))
        {
            printf("\nBłąd loginu\n");
            exit(1);
        }
        if(Baza_ile_rejestrow(id_uzytkownika)==0)
        {
            printf("\nBrak rejestrów - opcja niedostępna\n");
            return 0;
        }
        printf("\nPodaj id_rejestru, który chcesz usunąć\n");
        char id_rejestru[52];
        do
        {
            k=1;
            fgets(id_rejestru, 51, stdin);
            if(id_rejestru[0]=='\0' || id_rejestru[0]=='\n') k=2;
            for(int i=0; i<52; i++)
            {
                if(isdigit(id_rejestru[i])==0)
                {
                    if(id_rejestru[i]!='\n' && id_rejestru[i]!='\0')
                    {
                        k=2;
                    }
                    break;
                }
            }
            if(k==2) printf("Niepoprawny format\n");
            else
            {
                k=Baza_czy_id_rejestru(id_rejestru, id_uzytkownika);
                if(k==0) printf("Brak rejestru o podanym numerze\n");
            }
        }while(k!=1);
        printf("\nCzy na pewno chcesz usunąć wybrany rejestr?\n1 Nie\n2 Tak\n");
        do
        {
            k=1;
            fgets(wejscie, 51, stdin);
            if(!(wejscie[0]=='1' || wejscie[0]=='2')  || !(wejscie[1]=='\n' || wejscie[1]=='\0'))
            {
                k=0;
                printf("Niepoprawny format\n");
            }
        }while(k!=1);
        if(wejscie[0]=='2')
        {
            Baza_usuwanie_rejestru(id_rejestru);
            printf("\nRejestr został pomyślnie usunięty\n");
        }
        else
        {
            printf("\nAnulowano usuwanie rejestru z bazy danych\n");
        }
    }
    printf("\n");
    return 0;
}

int interfejs_zmiana_hasla(char * login)
{
    printf("\nProszę podać nowe hasło:\n");
    char haslo[52];
    int k;
    do
    {
        k=1;
        fgets(haslo, 51, stdin);
        if(haslo[0]=='\0' || haslo[0]=='\n') k=0;
        for(int i=0; i<52; i++)
        {
            if(isdigit(haslo[i])==0 && isalpha(haslo[i])==0)
            {
                if(haslo[i]!='\n' && haslo[i]!='\0')
                {
                    k=0;
                }
                break;
            }
        }
        if(k==0) printf("Niepoprawny format. Proszę ponownie podać hasło:\n");
    }while(k==0);

    for(int i=0; i<52; i++)
    {
        if(haslo[i]=='\n')
        {
            haslo[i]='\0';
            break;
        }
        else
        {
            if(haslo[i]=='\0')
                break;
        }
    }

    char wejscie[52];
    printf("\nCzy na pewno chcesz zmienić hasło?\n1 Nie\n2 Tak\n");
    do
    {
        k=1;
        fgets(wejscie, 51, stdin);
        if(!(wejscie[0]=='1' || wejscie[0]=='2')  || !(wejscie[1]=='\n' || wejscie[1]=='\0'))
        {
            k=0;
            printf("Niepoprawny format\n");
        }
    }while(k!=1);
    if(wejscie[0]=='2')
    {
        Baza_zmiana_hasla(login, haslo);
        printf("\nHasło zostało pomyślnie zmienione\n");
    }
    else
    {
        printf("\nAnulowano zmianę hasła\n");
    }
    return 0;
}
