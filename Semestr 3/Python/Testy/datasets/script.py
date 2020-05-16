import pandas as pd
import numpy
import mysql.connector as mysql


# mydb = mysql.connect(
#   host="localhost",
#   user="root",
#   passwd="011235",
#   database="movies_rating",
#   use_pure=True
# )

# cursor = mydb.cursor()
# cursor.close()


ratings = pd.read_csv("ratings.csv", encoding='utf-8', engine="python",
                      sep=',', dtype={"user_id": int, "movie_id": int,
                                      "rating": float, "timestamp": int},)

print(ratings)

c = ratings[["rating", "movie_id"]].groupby(["movie_id"]).agg(["count"])
print(c)
c = c.sort_values(by=[("rating", "count")], ascending=False).head(n=100)

print(c)
i = 0

b = c[("rating", "count")]

print(b.index.values)

# n = c.to_numpy().flatten()
# print(n)
# print(c.columns)
# print(c["count"])
interesting = ratings["movie_id"].isin(b.index.values)
# is_less_100 = ratings["movieId"] <= 100
ratings = ratings[interesting]
print(ratings)
# movies = pd.read_csv("movies.csv", encoding='utf-8', engine="python")
# movies = movies.head(100)
# print(ratings.head(n=5))


table = pd.pivot_table(ratings, index=["user_id"], columns=["movie_id"], values=["rating"], dropna=True)

print(table)

# print(ratings)

# print(table.head())

# export_csv = table.to_csv("test.csv", index=None, header=True)


