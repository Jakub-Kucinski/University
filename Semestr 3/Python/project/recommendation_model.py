from surprise import Dataset
from surprise import Reader
from surprise import KNNWithMeans
import pandas as pd
import database_handler
import global_variables
import os
from surprise import KNNBasic


class Recommendation_model():
    """Model rekomendacyjny"""
    def __init__(self):
        """Tworzy model rekomendujący na podstawie algorytmu KNN z podobieństwem cosinusowym.

        Pobiera dodane oceny z bazy danych i przy wykorzystaniu KNNWithMeans konstruuje model
        rekomendujący. Następnie tworzy listę wszystkich nieocenionych przez zalogowanego 
        użytkownika obiektów z tymi obiektami i ich przewidywanymi ocenami. Sortuje ją 
        w kolejności malejącej względem przewidywanej oceny.
        """
        database = database_handler.Database_Handler()

        SQL_Query = database.get_all_ratings()
        df = pd.DataFrame(SQL_Query, columns=['user_id', 'movie_id', 'rating'])
        export_csv = df.to_csv("recommendation_model_data.csv", index=None, header=False)

        reader = Reader(line_format='user item rating', sep=',')
        data = Dataset.load_from_file('recommendation_model_data.csv', reader=reader)
        os.remove("recommendation_model_data.csv")

        sim_options = {
            "name": "cosine",
            "user_based": True,
        }
        self.algo = KNNWithMeans(sim_options=sim_options)
        trainset = data.build_full_trainset()
        self.algo.fit(trainset)

        self.not_rated_movies = database.get_user_all_not_rated_movies_only_id(
            global_variables.USER_ID)
        self.not_rated_movies = [row[0] for row in self.not_rated_movies] 

        self.list_of_id_and_rating = [(movie_id, self.algo.predict(
            str(global_variables.USER_ID), str(movie_id)).est
            ) for movie_id in self.not_rated_movies]

        self.list_of_id_and_rating = sorted(self.list_of_id_and_rating, reverse=True, key=lambda tup: tup[1])
        
    def get_next_recommended_movie_id(self):
        """"Generator kolejnych rekomendowanych obiektów"""
        for row in self.list_of_id_and_rating:
            yield row[0]
