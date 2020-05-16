from surprise import Dataset
from surprise import Reader
from surprise import KNNWithMeans
import pandas as pd
import database_handler
import global_variables
import recommendation_model
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Recommendation_Box(Gtk.Box):
    """Box zawiera widok pobierania rekomendacji obiektów."""
    def __init__(self, window):
        """Tworzy Box zawierający widok pobierania rekomendacji obiektów.

        Wywołuje konstruktor nadklasy Gtk.Box. Jeśli użytkownik dodał pewną liczbę ocen, 
        to buduje model rekomendujący, dodaje przyciski do uzyskiwania rekomendacji,
        tworzy widok listy kolejnych rekomendacji oraz przycisk powrotu do poprzedniego widoku.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)
        database = database_handler.Database_Handler()
        if database.is_user_id_in_rating(global_variables.USER_ID) is None:
            self.pack_start(Gtk.Label(
                "Aby wyświetlić rekomendacje, musisz najpierw dodać oceny"), False, False, 0)
        else:
            self.model = recommendation_model.Recommendation_model()
            self.add_recommendation_buttons()
            self.scrolled_window = Gtk.ScrolledWindow()
            self.pack_start(self.scrolled_window, True, True, 0)
            self.listbox = Gtk.ListBox()
            self.listbox.set_selection_mode(Gtk.SelectionMode.NONE)
            self.scrolled_window.add_with_viewport(self.listbox)

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect("clicked", self.on_button_back_clicked)

    def add_recommendation_buttons(self):
        """Dodaje przycisk umożliwiający pobranie kolejnej rekomendacji.
        """
        self.next_movie = self.model.get_next_recommended_movie_id()
        self.pack_start(Gtk.Label("Kliknij przycisk, by dostać rekomendację"), False, False, 0)
        self.button_next_recommendation = Gtk.Button(label="Następny")
        self.pack_start(self.button_next_recommendation, False, False, 0)
        self.button_next_recommendation.connect(
            "clicked", self.on_button_next_recommendation_clicked)

    def on_button_next_recommendation_clicked(self, widget):
        """"Po kliknięciu, pobiera dane dotyczące kolejnego rekomendowanego obiektu
        i dodaje go do widoku listy rekomendowanych obiektów.
        """
        database = database_handler.Database_Handler()
        movie_info = database.get_movie_info_from_id(next(self.next_movie))
        row = Gtk.ListBoxRow()
        movie_info = database.get_movie_info_from_id(next(self.next_movie))
        label = Gtk.Label(str(movie_info[0]) + ", "
            + str(movie_info[1]) + ", " + str(movie_info[2]))
        label.set_selectable(True)
        row.add(label)
        self.listbox.add(row)
        self.show_all()

    def on_button_back_clicked(self, widget):
        """Przechodzi do widoku wyboru akcji po kliknięciu przycisku"""
        self.window.set_action_selection()
