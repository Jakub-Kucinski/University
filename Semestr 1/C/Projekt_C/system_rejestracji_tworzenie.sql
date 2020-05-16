drop database System_rejestracji;
create database System_rejestracji;
create table System_rejestracji.Uzytkownicy (
	Id_uzytkownika integer not null auto_increment unique,
	Login varchar(50) not null unique,
	Haslo varchar(50) not null,
	primary key (Id_uzytkownika)
	);
create table System_rejestracji.Przedmioty (
	Id_przedmiotu integer not null auto_increment unique,
	Nazwa_przedmiotu varchar(100) not null unique,
	primary key (Id_przedmiotu)
	);
create table System_rejestracji.Aktywnosci (
	Id_aktywnosci integer not null auto_increment unique,
	Nazwa_aktywnosci varchar(100) not null unique,
	primary key (Id_aktywnosci)
	);
create table System_rejestracji.Rejestry (
	Id_rejestru integer not null auto_increment unique,
	Id_uzytkownika integer not null,
	Czas_nauki time not null,
	Data date not null,
	Id_przedmiotu integer not null,
	Id_aktywnosci integer not null,
	primary key (Id_rejestru)
	);

use System_rejestracji;
insert into Przedmioty (Nazwa_przedmiotu) values  ('Algebra'), ('Analiza matematyczna'), ('Analiza matematyczna 2'), ('Architektury systemów komputerowych'), ('Kurs języka C++'), ('Logika dla informatyków'), ('Metody programowania'), ('Podstawowy warsztat informatyka'), ('Programowanie obiektowe'), ('Wstęp do informatyki'), ('Wstęp do programowania w C'), ('Wstęp do programowania w języku Python');

insert into Aktywnosci (Nazwa_aktywnosci) values ('Rozwiązywanie list zadań'), ('Rozwiązywanie zadań ze zbiorów'), ('Roziązywanie kolokwiów z poprzednich lat'), ('Nauka w grupie'), ('Nauka z książek'), ('Uczęszczanie na repetytoria lub konsultacje'), ('Programowanie'), ('Nauka ze źródeł multimedialnych'), ('Nauka ze źródeł internetowych');

insert into Uzytkownicy (Login, Haslo) values ('Admin', '111');
insert into Uzytkownicy (Login, Haslo) values ('30000', '12345');
