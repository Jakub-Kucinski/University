import mysql.connector as mysql
import global_variables
import pandas as pd


class Database_Handler():
    """Klasa odpowiadająca za komunikację z bazą danych."""

    def __init__(self):
        """Tworzy obiekt do komunikacji z bazą danych.
        
        Nawiązuje połączenie z bazą danych, z globalnie zdefiniowanymi parametrami:
        host, user, passwd, database, use_pure.
        """
        self.mydb = mysql.connect(
            host=global_variables.host,
            user=global_variables.user,
            passwd=global_variables.passwd,
            database=global_variables.database,
            use_pure=global_variables.use_pure
        )

    def get_user_id_from_login(self, login):
        """"Zwraca id użytkownika o podanym loginie, jeśli taki nie istnieje, zwraca None."""
        cursor = self.mydb.cursor()
        cursor.execute("SELECT user_id FROM User WHERE login = '{}'".format(
            login))
        result = cursor.fetchone()
        cursor.close()
        if result is None:
            return None
        return result[0]

    def get_user_id_from_login_and_passwd(self, login, password):
        """Zwraca id użytkownika o podanym loginie i haśle, jeśli taki nie istnieje,
        zwraca None.
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT user_id FROM User \
            WHERE login = '{}' AND password = '{}'".format(login, password))
        result = cursor.fetchone()
        cursor.close()
        if result is None:
            return None
        return result[0]

    def register_new_user(self, login, password):
        """Dodaje do bazy danych nowego użytkownika o podanym loginie i haśle,
        o ile login nie jest już zajęty. Jeśli użytkownik o tym loginie już istnieje, 
        zwraca None, jeśli nie, po dodaniu zwraca jego id.
        """
        if self.get_user_id_from_login(login) is not None:
            return None
        cursor = self.mydb.cursor()
        cursor.execute("""INSERT INTO User (login, password)
                       VALUES("{}", "{}")""".format(login, password))
        self.mydb.commit()
        return cursor.lastrowid

    def get_user_ratings(self, user_id):
        """Zwraca w postaci listy oceny i informacje o ocenionych filmach przez użytkownika o id = user_id.
        Każdy element listy jest postaci [id_filmu, nazwa_filmu, ocena, gatunek].
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT Movie_rating.movie_id, Movie.title, Movie_rating.rating, Movie.genres \
            FROM Movie INNER JOIN Movie_rating ON \
            Movie.movie_id = Movie_rating.movie_id \
            WHERE Movie_rating.user_id = {}".format(user_id))
        result = cursor.fetchall()
        cursor.close()
        return result

    def delete_user_rating(self, user_id, movie_id):
        """Usuwa z bazy danych wpis z oceną filmu o podanym id = movie_id 
        użytkownika o id = user_id.
        """
        cursor = self.mydb.cursor()
        cursor.execute("DELETE FROM Movie_rating \
            WHERE Movie_rating.user_id = {} \
            AND Movie_rating.movie_id = {}" .format(user_id, movie_id))
        self.mydb.commit()
        cursor.close()

    def change_user_rating(self, user_id, movie_id, rating):
        """Zmienia w bazie wpis z oceną filmu o podanym id = movie_id 
        użytkownika o id = user_id na ocenę rating.
        """
        cursor = self.mydb.cursor()
        cursor.execute("UPDATE Movie_rating \
            SET Movie_rating.rating = {} \
            WHERE Movie_rating.user_id = {} \
            AND Movie_rating.movie_id = {}" .format(rating, user_id, movie_id))
        self.mydb.commit()
        cursor.close()

    def get_movies_with_phrase_and_range(self, phrase, min_rating, max_rating):
        """Zwraca w postaci listy informacje o filmach, których nazwa zawiera phrase, 
        a średnia ocena jest nie mniejsza od min_rating i nie większa od max_rating.
        Elementy listy są postaci [id_filmu, nazwa_filmu, średnia_ocena, liczba_oceb, gatunek].
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT Movie.movie_id, Movie.title, ROUND(AVG(Movie_rating.rating), 2), \
            COUNT(Movie_rating.movie_id), Movie.genres \
            FROM Movie INNER JOIN Movie_rating ON \
            Movie.movie_id = Movie_rating.movie_id \
            WHERE Movie.title LIKE '" + '%' + phrase + '%' + "' \
            GROUP BY Movie.movie_id, Movie.title, Movie.genres \
            HAVING ROUND(AVG(Movie_rating.rating), 2) >= " + str(min_rating) + " \
            AND ROUND(AVG(Movie_rating.rating), 2) <= " + str(max_rating) + " \
            ORDER BY COUNT(Movie_rating.movie_id) DESC \
            LIMIT 100")
        result = cursor.fetchall()
        cursor.close()
        return result

    def get_movies_with_phrase_no_range_not_rated(self, user_id, phrase):
        """Zwraca w postaci listy informacje o filmach, których nazwa zawiera phrase i nie zostały
        ocenione przez użytkownika o id = user_id. Elementy listy są postaci 
        [id_filmu, nazwa_filmu, średnia_ocena, liczba_oceb, gatunek].
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT Movie.movie_id, Movie.title, Movie.genres \
            FROM Movie \
            WHERE Movie.title LIKE '" + '%' + phrase + '%' + "' \
            AND Movie.movie_id NOT IN (SELECT Movie_rating.movie_id \
            FROM Movie_rating \
            WHERE Movie_rating.user_id = " + str(user_id) + ") \
            LIMIT 100")
        result = cursor.fetchall()
        cursor.close()
        return result

    def add_user_rating(self, user_id, movie_id, rating):
        """Dodaje do bazy danych ocenę rating od użytkownika user_id o filmie movie_id."""
        cursor = self.mydb.cursor()
        cursor.execute("INSERT INTO Movie_rating (user_id, movie_id, rating) \
            VALUES ({}, {}, {})".format(user_id, movie_id, rating))
        self.mydb.commit()
        cursor.close()

    def get_all_ratings(self):
        """Zwraca w postaci listy oceny wszystkich filmów przez wszystkich użytkowników.
        Elementy listy są postaci [id_użytkownika, id_filmu, ocena].
        """
        return pd.read_sql_query("SELECT user_id, movie_id, rating \
            FROM Movie_rating" , self.mydb)

    def is_user_id_in_rating(self, user_id):
        """Sprawdza czy użytkownik o podanym id = user_id dodał jakąś ocenę.
        Jeśli tak, zwraca pierwszą z nich, w przeciwnym przypadku None.
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT user_id FROM Movie_rating WHERE user_id = {} LIMIT 1".format(
            user_id))
        result = cursor.fetchone()
        cursor.close()
        if result is None:
            return None
        return result[0]

    def get_user_all_not_rated_movies_only_id(self, user_id):
        """Zwraca w postaci listy id filmów, które nie zostały jeszcze ocenione 
        przez użytkownika o id = user_id.
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT DISTINCT Movie.movie_id \
            FROM Movie \
            WHERE Movie.movie_id NOT IN (SELECT Movie_rating.movie_id \
            FROM Movie_rating \
            WHERE Movie_rating.user_id = " + str(user_id) + ")")
        result = cursor.fetchall()
        cursor.close()
        return result

    def get_movie_info_from_id(self, movie_id):
        """Zwraca informacje o filmie o id = movie_id. Wynik jest postaci
        [id_filmu, tytuł, gatunek].
        """
        cursor = self.mydb.cursor()
        cursor.execute("SELECT Movie.movie_id, Movie.title, Movie.genres \
            FROM Movie \
            WHERE Movie.movie_id = {}".format(movie_id))
        result = cursor.fetchone()
        cursor.close()
        return result
