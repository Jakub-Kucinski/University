import global_variables
import database_handler
import spin_button_from_min_to_max
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Adding_Rating_Box(Gtk.Box):
    """Box zawiera widok dodawania oceny."""

    def __init__(self, window, movie_id, title, genres):
        """Tworzy Box zawierający widok dodawania oceny.

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

        choice = Gtk.Label("Czy na pewno chcesz wprowadzić ocenę dla wskazanego filmu?\n \
                    {}, {}, {}".format(movie_id, title, genres))
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        """Po kliknięciu przycisku, dodaje ocenę do bazy danych i wyświetla
        komunikat o pomyślnym dodaniu oceny.
        """
        new_rating = float(self.button_val.get_value())
        database = database_handler.Database_Handler()
        database.add_user_rating(
            global_variables.USER_ID, int(self.movie_id), new_rating)
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Nowa ocena została pomyślnie dodana")
        dialog.run()
        dialog.destroy()
        self.window.set_selecting_object_to_rate()

    def on_button_reject_clicked(self, widget):
        """Po kliknięciu przycisku, przerywa dodawanie oceny i wyświetla
        komunikat o anulowaniu dodawania oceny.
        """
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Anulowano dodawanie nowej oceny")
        dialog.run()
        dialog.destroy()
        self.window.set_selecting_object_to_rate()
