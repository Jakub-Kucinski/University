import global_variables
import database_handler
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Logging_In_Box(Gtk.Box):
    """Box zawiera widok logowania."""

    def __init__(self, window):
        """Tworzy Box zawierający widok logowania.

        Wywołuje konstruktor nadklasy Gtk.Box. Ustawia wartość zmiennej globalnej
        USER_ID na None, tworzy Entry do pobrania loginu i hasła użytkownika, 
        CheckButton umozliwiający odkrycie/ukrycie hasła, Buttony umożliwiające
        zalogowanie się, tworzenie nowego konta oraz wyjście z aplikacji.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        global_variables.USER_ID = None

        self.entry_login = Gtk.Entry()
        self.entry_login.set_text("Login")
        self.entry_login.set_max_length(100)
        self.pack_start(self.entry_login, False, False, 0)

        self.hbox = Gtk.Box(spacing=6)
        self.pack_start(self.hbox, False, False, 0)

        self.entry_password = Gtk.Entry()
        self.entry_password.set_text("Hasło")
        self.entry_password.set_max_length(100)
        self.entry_password.set_visibility(False)
        self.hbox.pack_start(self.entry_password, True, True, 0)

        self.check_visible = Gtk.CheckButton("Pokaż")
        self.check_visible.connect("toggled", self.on_visible_toggled)
        self.check_visible.set_active(False)
        self.hbox.pack_start(self.check_visible, False, False, 0)

        self.button_submit = Gtk.Button(label="Zaloguj")
        self.pack_start(self.button_submit, False, False, 0)
        self.button_submit.connect("clicked", self.on_button_submit_clicked)

        self.button_register = Gtk.Button(label="Utwórz konto")
        self.pack_start(self.button_register, False, False, 0)
        self.button_register.connect(
            "clicked", self.on_button_register_clicked)

        self.button_quit_app = Gtk.Button(label="Wyjdź z aplikacji")
        self.pack_start(self.button_quit_app, False, False, 0)
        self.button_quit_app.connect(
            "clicked", self.on_button_quit_app_clicked)

        self.popover = Gtk.Popover()
        self.popover.add(Gtk.Label("Błędny login lub hasło"))
        self.popover.set_position(Gtk.PositionType.BOTTOM)

    def on_visible_toggled(self, button):
        """Zmienia widoczność hasła po kliknięciu przycisku."""
        value = button.get_active()
        self.entry_password.set_visibility(value)

    def on_button_register_clicked(self, widget):
        """Przechodzi do widoku rejestracji po kliknięciu przycisku"""
        self.window.set_register()

    def on_button_submit_clicked(self, widget):
        """Po kliknięciu przycisku, sprawdza poprawności danych logowania.

        Jeśli są poprawne, przechodzi do widoku wyboru akcji, 
        w przeciwnym wypadku wyświetla komunikat o podaniu błędnych danych.
        """
        login = self.entry_login.get_text()
        password = self.entry_password.get_text()
        database = database_handler.Database_Handler()
        global_variables.USER_ID = database.get_user_id_from_login_and_passwd(
            login, password)
        if global_variables.USER_ID is not None:
            self.window.set_action_selection()
        else:
            self.popover.set_relative_to(self.button_submit)
            self.popover.show_all()
            self.popover.popup()

    def on_button_quit_app_clicked(self, widget):
        """Zamyka aplikację po kliknięciu przycisku."""
        self.window.set_quiting_app()
