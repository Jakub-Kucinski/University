import mysql.connector as mysql
import pandas as pd
import csv

mydb = mysql.connect(
  host="localhost",
  user="root",
  passwd="011235",
  use_pure=True
)
cursor = mydb.cursor()
try:
    cursor.execute("DROP DATABASE recommendation_system")
except Exception:
    pass
cursor.execute("CREATE DATABASE recommendation_system")
cursor.close()

mydb = mysql.connect(
  host="localhost",
  user="root",
  passwd="011235",
  database="recommendation_system",
  use_pure=True
)
cursor = mydb.cursor()

cursor.execute("""CREATE TABLE Movie(
    movie_id int,
    title varchar(1000),
    genres varchar(1000),
    PRIMARY KEY (movie_id)
)""")
mydb.commit()

cursor.execute("""CREATE TABLE User(
    user_id int AUTO_INCREMENT,
    login varchar(100),
    password varchar(100),
    PRIMARY KEY (user_id)
)""")
mydb.commit()

cursor.execute("ALTER TABLE User AUTO_INCREMENT=611;")
mydb.commit()

cursor.execute("""CREATE TABLE Movie_rating(
    user_id int,
    movie_id int,
    rating float
)""")
mydb.commit()


with open('movies2.csv') as csvfile:
    csv_data = csv.reader(csvfile, delimiter=',', quotechar='"')
    for row in csv_data:
        cursor.execute("""INSERT INTO Movie(movie_id,
              title, genres)
              VALUES({}, "{}", "{}")""".format(row[0], row[1], row[2]))

with open('ratings2.csv') as csvfile:
    csv_data = csv.reader(csvfile, delimiter=',')
    for row in csv_data:
        cursor.execute("""INSERT INTO Movie_rating(user_id,
              movie_id, rating)
              VALUES({}, {}, {})""".format(row[0], row[1], row[2]))

mydb.commit()
cursor.close()
