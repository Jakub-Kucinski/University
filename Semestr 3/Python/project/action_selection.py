import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Action_Selection_Box(Gtk.Box):
    """Box zawiera widok wyboru akcji."""

    def __init__(self, window):
        """Tworzy Box zawierający widok wyboru akcji.

        Wywołuje konstruktor nadklasy Gtk.Box. Tworzy przyciski odpowiadające
        wyborze dostępnych akcji, kolejno: wyświetlenie listy obiektów, 
        wyświetlenie, usunięcie lub zmiana dodanej oceny, 
        dodanie nowej oceny, zarekomendowanie obiektu, wylogowanie się
        i wyjście z aplikacji.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wybierz jedną z dostępnych akcji:")
        self.pack_start(choice, False, False, 0)

        self.button_list_objects = Gtk.Button(
            label="Wyświetl listę obiektów")
        self.pack_start(self.button_list_objects, False, False, 0)
        self.button_list_objects.connect(
            "clicked", self.on_button_list_objects_clicked)

        self.button_list_added_ratings = Gtk.Button(
            label="Wyświetl, usuń lub zmień dodane oceny")
        self.pack_start(self.button_list_added_ratings, False, False, 0)
        self.button_list_added_ratings.connect(
            "clicked", self.on_button_list_added_ratings_clicked)

        self.button_add_new_rating = Gtk.Button(
            label="Dodaj nową ocenę")
        self.pack_start(self.button_add_new_rating, False, False, 0)
        self.button_add_new_rating.connect(
            "clicked", self.on_button_add_new_rating_clicked)

        self.button_recommend_an_object = Gtk.Button(
            label="Zarekomenduj obiekt")
        self.pack_start(self.button_recommend_an_object, False, False, 0)
        self.button_recommend_an_object.connect(
            "clicked", self.on_button_recommend_an_object_clicked)

        self.button_log_out = Gtk.Button(
            label="Wyloguj")
        self.pack_start(self.button_log_out, False, False, 0)
        self.button_log_out.connect(
            "clicked", self.on_button_log_out_clicked)

        self.button_quit_app = Gtk.Button(
            label="Wyjdź z aplikacji")
        self.pack_start(self.button_quit_app, False, False, 0)
        self.button_quit_app.connect(
            "clicked", self.on_button_quit_app_clicked)

    def on_button_list_objects_clicked(self, widget):
        """Przechodzi do widoku przeglądania obiektów 
        po kliknięciu przycisku
        """
        self.window.set_listing_objects()

    def on_button_list_added_ratings_clicked(self, widget):
        """Przechodzi do widoku przeglądania dodanych ocen 
        po kliknięciu przycisku
        """
        self.window.set_listing_user_rating()

    def on_button_add_new_rating_clicked(self, widget):
        """Przechodzi do widoku dodawania nowej oceny
        po kliknięciu przycisku
        """
        self.window.set_selecting_object_to_rate()

    def on_button_recommend_an_object_clicked(self, widget):
        """Przechodzi do widoku pobierania rekomendacji 
        po kliknięciu przycisku
        """
        self.window.set_recommendation()

    def on_button_log_out_clicked(self, widget):
        """Przechodzi do widoku logowania po kliknięciu przycisku
        """
        self.window.set_logging_in()

    def on_button_quit_app_clicked(self, widget):
        """Zamyka aplikację po kliknięciu przycisku
        """
        self.window.set_quiting_app()
