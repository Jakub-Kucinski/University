Jakub Kuciński

Do pisania projektu używałem Pythona 3.7.5.
W pliku requirements.txt znajdują się biblioteki, które miałem zainstalowane
w środowisku utworzonym przez Anacondę i dodatkowe dodane przeze mnie.

Program wymaga posiadania bazy danych mysql.

Pliki movies2.csv i ratings2.csv zawierają dane, którymi wypełniłem bazę.
Do zbudowania bazy należy użyć skryptu create_database.py.
Trzeba jednak w dwóch wywołaniach funkcji connect ręcznie zamienić wartości parametrów
user i passwd na takie, by możliwe było zalogowanie się do lokalnego serwera mysql.
Należy się też upewnić, że nie ma bazy danych o nazwie recommendation_system,
bo zostanie ona usunięta przez skrypt.
Analogicznie w pliku global_variables.py należy zmienić wartości user i passwd,
by moduł database_handler działał poprawnie.

Struktura hierarchiczna plików (kolejność odpowiada kolejności ukazywania się interfejsów w aplikacji):

- app_window
--logging_in
---register
---action_selection
----listing_objects
-----spin_button_from_min_to_max
----listing_user_rating
-----deleting_rating
-----changing_rating
----selecting_object_to_rate
-----adding_rating
----recommendation
-----recommendation_model

-global_variables
-database_handler

Prawdopodobnie najłatwiej zrozumieć kod czytając go w kolejności DFS.
