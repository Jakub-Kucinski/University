from surprise import SVD
from surprise import Dataset
from surprise import Reader
from surprise import KNNBasic
from surprise import BaselineOnly
from surprise import NormalPredictor
from surprise.model_selection import cross_validate
from surprise import KNNWithMeans

# Load the movielens-100k dataset (download it if needed).
# data = Dataset.load_builtin('ml-100k')

# file_path = os.path.expanduser('ratings.csv')
reader = Reader(line_format='user item rating timestamp', sep=',')
data = Dataset.load_from_file('ratings2.csv', reader=reader)
# reader = Reader(line_format='user item rating timestamp', sep='\t')
# data = Dataset.load_from_file('~/.surprise_data/ml-100k/ml-100k/u.data', reader=reader)


# Use the famous SVD algorithm.
# algo = SVD()


# To use item-based cosine similarity
sim_options = {
    "name": "cosine",
    "user_based": True,  # Compute  similarities between items
}
algo = KNNWithMeans(sim_options=sim_options)
# algo = KNNBasic()
# algo = BaselineOnly()
# algo = NormalPredictor()

trainset = data.build_full_trainset()

algo.fit(trainset)

# Run 5-fold cross-validation and print results.
# cross_validate(algo, data, measures=['RMSE', 'MAE'], cv=5, verbose=True)

uid = str(196)  # raw user id (as in the ratings file). They are **strings**!
iid = str(302)  # raw item id (as in the ratings file). They are **strings**!

# get a prediction for specific users and items.
pred = algo.predict(uid, iid, verbose=True)
pred = algo.predict(str(1), str(1), verbose=True)

for i in range(100):
    print(i, algo.predict(str(1), str(i)).est)
