import database_handler
import global_variables
import spin_button_from_min_to_max
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Changing_Rating_Box(Gtk.Box):
    """Box zawiera widok zmiany oceny."""
    def __init__(self, window, movie_id, title, rating, genres):
        """Tworzy Box zawierający widok zmiany oceny.

        Wywołuje konstruktor nadklasy Gtk.Box. Tworzy przycisk umożliwiający
        wprowadzenie przez użytkownika nowej oceny oraz przyciski odpowiadające
        potwierdzeniu i przerwaniu dodawania nowej oceny.
        """
        self.window = window
        self.movie_id = movie_id

        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wprowadź nową ocenę")
        self.pack_start(choice, False, False, 0)

        self.button_val = spin_button_from_min_to_max.Spin_Button_from_min_to_max(
            global_variables.MIN_RANK, global_variables.MAX_RANK, 0.5)
        self.pack_start(self.button_val, False, False, 0)
        self.button_val.set_snap_to_ticks(True)

        choice = Gtk.Label("Czy na pewno chcesz zmienić wskazaną ocenę?\n \
                    {}, {}, {}, {}".format(movie_id, title, rating, genres))
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        """Po kliknięciu przycisku, zmienia ocenę w bazie danych i wyświetla
        komunikat o pomyślnej zmianie oceny.
        """
        new_rating = float(self.button_val.get_value())
        database = database_handler.Database_Handler()
        database.change_user_rating(
            global_variables.USER_ID, int(self.movie_id), new_rating)
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
            Gtk.ButtonsType.OK, "Pomyślnie zmieniono ocenę")
        dialog.run()
        dialog.destroy()
        self.window.set_listing_user_rating()

    def on_button_reject_clicked(self, widget):
        """Po kliknięciu przycisku, przerywa zmianę oceny i wyświetla
        komunikat o anulowaniu zmiany oceny.
        """
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Anulowano zmianę oceny")
        dialog.run()
        dialog.destroy()
        self.window.set_listing_user_rating()
