import database_handler
import global_variables
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Deleting_Rating_Box(Gtk.Box):
    """Box zawiera widok usuwania oceny."""

    def __init__(self, window, movie_id, title, rating, genres):
        """Tworzy Box zawierający widok usuwania oceny.

        Wywołuje konstruktor nadklasy Gtk.Box. Tworzy przyciski odpowiadające
        potwierdzeniu i przerwaniu usuwania oceny.
        """
        self.window = window
        self.movie_id = movie_id

        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Czy na pewno chcesz usunąc wskazaną ocenę?\n \
            {}, {}, {}, {}".format(movie_id, title, rating, genres))
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        """Po kliknięciu przycisku, usuwa ocenę z bazy danych i wyświetla
        komunikat o pomyślnym usunięciu oceny.
        """
        database = database_handler.Database_Handler()
        database.delete_user_rating(
            global_variables.USER_ID, int(self.movie_id))
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Pomyślnie usunięto ocenę")
        dialog.run()
        dialog.destroy()
        self.window.set_listing_user_rating()

    def on_button_reject_clicked(self, widget):
        """Po kliknięciu przycisku, przerywa usuwanie oceny i wyświetla
        komunikat o anulowaniu usuwania oceny.
        """
        dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Anulowano usuwanie oceny")
        dialog.run()
        dialog.destroy()
        self.window.set_listing_user_rating()
