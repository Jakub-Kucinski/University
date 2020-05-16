import database_handler
import global_variables
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Listing_User_Rating_Box(Gtk.Box):
    """Box zawiera widok przeglądania, zmiany lub usuwania ocen dodanych przez użytkownika."""

    def __init__(self, window):
        """Tworzy Box zawierający widok przeglądania, zmiany lub usuwania ocen dodanych przez użytkownika.

        Wywołuje konstruktor nadklasy Gtk.Box. Dodaje przyciski umożliwiające
        filtrowane obiektów, przyciski dające wybór zmiany i usunięcia oceny, 
        pobiera dane ocen i ocenionych obiektów, tworzy widok listy obiektów, 
        dodaje przycisk umożliwiający powrót do poprzedniego widoku.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        self.set_data()

        self.add_filter_menu()

        self.add_change_delete_buttons()

        self.box_with_grid = Gtk.Box()
        self.pack_start(self.box_with_grid, True, True, 0)

        self.grid = Gtk.Grid()
        self.grid.set_column_homogeneous(True)
        self.grid.set_row_homogeneous(True)

        self.box_with_grid.pack_start(self.grid, True, True, 0)

        self.objects_list_store = Gtk.ListStore(int, str, float, str)
        if self.data is not None:
            for elem in self.data:
                self.objects_list_store.append(list(elem))

        self.objects_filter = self.objects_list_store.filter_new()
        self.objects_filter.set_visible_func(self.object_filter_func)

        self.treeview = Gtk.TreeView.new_with_model(self.objects_filter)
        select = self.treeview.get_selection()
        select.connect("changed", self.on_tree_selection_changed)
        for i, column_title in enumerate(
                ["Id_filmu", "Tytuł", "Ocena", "Gatunek"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(column_title, renderer, text=i)
            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist, 0, 0, 8, 10)
        self.scrollable_treelist.add(self.treeview)

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect("clicked", self.on_button_back_clicked)

    def set_data(self):
        """Pobiera dane ocen i ocenionych przez użytkownika obiektów."""
        database = database_handler.Database_Handler()
        self.data = database.get_user_ratings(global_variables.USER_ID)

    def add_change_delete_buttons(self):
        """Dodaje dwa RadioButton umożliwiające użytkownikowi wybór między
        zmianą i usunięciem dodanej oceny.
        """
        self.state = "Change"

        self.hbox = Gtk.Box(spacing=6)
        self.add(self.hbox)

        self.button_change = Gtk.RadioButton.new_with_label_from_widget(
            None, "Zmień")
        self.button_change.connect("toggled", self.on_button_toggled, "Change")
        self.hbox.pack_start(self.button_change, False, False, 0)

        self.button_delete = Gtk.RadioButton.new_from_widget(
            self.button_change)
        self.button_delete.set_label("Usuń")
        self.button_delete.connect("toggled", self.on_button_toggled, "Delete")
        self.hbox.pack_start(self.button_delete, False, False, 0)

    def add_filter_menu(self):
        """"Dodaje Entry do pobrania frazy, którą mają zawierać nazwy 
        wyświetlanych obiektów, przycisk do usunięcia filtrowania
        według frazy i przycisk potwierdzający wyszukiwanie.
        """
        self.label_select = Gtk.Label("Wyszukaj nazwę obiektu.")
        self.pack_start(self.label_select, False, False, 0)

        self.filter_box = Gtk.Box(spacing=6)
        self.pack_start(self.filter_box, False, False, 0)

        self.text_filter = ""
        self.entry_filter = Gtk.Entry()
        self.entry_filter.set_text("")
        self.entry_filter.set_max_length(100)
        self.filter_box.pack_start(self.entry_filter, True, True, 0)

        self.button_clear = Gtk.Button(label="Wyczyść")
        self.filter_box.pack_start(self.button_clear, False, False, 0)
        self.button_clear.connect("clicked", self.on_button_clear_clicked)

        self.button_submit = Gtk.Button(label="Wyszukaj")
        self.filter_box.pack_start(self.button_submit, False, False, 0)
        self.button_submit.connect("clicked", self.on_button_submit_clicked)

        self.label_select = Gtk.Label("Klikając, wybierz z listy obiekt " +
            "którego ocenę chcesz usunąć lub zmienić:")
        self.pack_start(self.label_select, False, False, 0)

    def on_tree_selection_changed(self, selection):
        """Po kliknięciu na wybrany obiekt, następuje pobranie danych 
        wybranego obiektu, a następnie przejście do widoku
        usuwania oceny, jeśli zaznaczony był przycisk usuwania oceny
        albo zmiany oceny, jeśli zaznaczony był przycisk zmiany oceny"""
        model, treeiter = selection.get_selected()
        if treeiter is not None:
            if self.state == "Delete":
                self.window.set_deleting_rating(
                    model[treeiter][0], model[treeiter][1],
                    model[treeiter][2], model[treeiter][3])
            if self.state == "Change":
                self.window.set_changing_rating(
                    model[treeiter][0], model[treeiter][1],
                    model[treeiter][2], model[treeiter][3])

    def object_filter_func(self, model, iter, data):
        """Sprawdza czy nazwa obiektu zawiera wskazaną frazę.
        Jeśli zawiera, zwraca True, w przeciwnym przypadku False.
        """
        return self.text_filter in model[iter][1]

    def on_button_submit_clicked(self, widget):
        """Po kliknięciu, pobiera frazę, która ma występować w nazwach
        wyszukiwanych obiektów, następnie filtruje listę obiektów według
        pobranej frazy.
        """
        self.text_filter = self.entry_filter.get_text()
        self.objects_filter.refilter()

    def on_button_clear_clicked(self, widget):
        """Po kliknięciu, usuwa filtrowaną frazę i wyświetla listę wszystkich
        ocen i ocenionych obiektów.
        """
        self.text_filter = ""
        self.entry_filter.set_text("")
        self.objects_filter.refilter()

    def on_button_back_clicked(self, widget):
        """Przechodzi do widoku wyboru akcji po kliknięciu przycisku."""
        self.window.set_action_selection()

    def on_button_toggled(self, button, name):
        """Po aktywacji któregoś z przycisków odpowiadających wyborowi usunięcia
        lub zmiany oceny, aktualizuje informacje o aktualnie włączonym przycisku.
        """
        if button.get_active():
            self.state = name
