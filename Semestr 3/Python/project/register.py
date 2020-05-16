import global_variables
import database_handler
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Register_Box(Gtk.Box):
    """Box zawiera widok rejestracji nowego konta."""

    def __init__(self, window):
        """Tworzy Box zawierający widok rejestracji nowego konta.

        Wywołuje konstruktor nadklasy Gtk.Box. Tworzy Entry do pobrania loginu 
        i hasła użytkownika, CheckButton umozliwiający odkrycie/ukrycie hasła, 
        Buttony umożliwiające zarejestrowanie się, powrotu do poprzedniego widoku
        oraz wyjście z aplikacji.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

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
        self.hbox.pack_start(self.entry_password, False, False, 0)

        self.check_visible = Gtk.CheckButton("Pokaż")
        self.check_visible.connect("toggled", self.on_visible_toggled)
        self.check_visible.set_active(False)
        self.hbox.pack_start(self.check_visible, True, True, 0)

        self.button_submit = Gtk.Button(label="Zarejestruj się")
        self.pack_start(self.button_submit, False, False, 0)
        self.button_submit.connect(
            "clicked", self.on_button_submit_clicked)

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect(
            "clicked", self.on_button_back_clicked)

        self.button_quit_app = Gtk.Button(label="Wyjdź z aplikacji")
        self.pack_start(self.button_quit_app, False, False, 0)
        self.button_quit_app.connect(
            "clicked", self.on_button_quit_app_clicked)

        self.popover = Gtk.Popover()
        self.popover.add(Gtk.Label("Login jest już zajęty"))
        self.popover.set_position(Gtk.PositionType.BOTTOM)

    def on_button_submit_clicked(self, widget):
        """Po kliknięciu przycisku, sprawdza dostępność danych rejestracji.

        Jeśli login jest zajęty, wyświetla komunikat o już zajętym loginie,
        w przeciwnym wypadku tworzy nowe konto i wyświetla komunikat
        o pomyślnej rejestracji.
        """
        login = self.entry_login.get_text()
        password = self.entry_password.get_text()
        database = database_handler.Database_Handler()
        id = database.get_user_id_from_login(login)
        if id is None:
            global_variables.USER_ID = database.register_new_user(
                login, password)
            dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Konto zostało pomyślnie zarejestrowane")
            dialog.run()
            dialog.destroy()
            self.window.set_action_selection()
        else:
            self.popover.set_relative_to(self.button_submit)
            self.popover.show_all()
            self.popover.popup()

    def on_visible_toggled(self, button):
        """Zmienia widoczność hasła po kliknięciu przycisku."""
        value = button.get_active()
        self.entry_password.set_visibility(value)

    def on_button_back_clicked(self, widget):
        """Przechodzi do widoku logowania po kliknięciu przycisku"""
        self.window.set_logging_in()

    def on_button_quit_app_clicked(self, widget):
        """Zamyka aplikację po kliknięciu przycisku."""
        self.window.set_quiting_app()
