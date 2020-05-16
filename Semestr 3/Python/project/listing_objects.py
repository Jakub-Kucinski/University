import spin_button_from_min_to_max
import database_handler
import global_variables
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class Listing_Objects_Box(Gtk.Box):
    """Box zawiera widok przeglądania obiektów."""
    
    def __init__(self, window):
        """Tworzy Box zawierający widok przeglądania obiektów.

        Wywołuje konstruktor nadklasy Gtk.Box. Dodaje przyciski umożliwiające
        filtrowane wyszukiwanie obiektów, pobiera dane obiektów, 
        tworzy widok listy obiektów, dodaje przycisk umożliwiający powrót 
        do poprzedniego widoku.
        """
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        self.add_filtering_buttons()

        self.set_data()

        self.box_with_grid = Gtk.Box()
        self.pack_start(self.box_with_grid, True, True, 0)
        self.grid = Gtk.Grid()

        self.refresh_grid_with_treeview()

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect("clicked", self.on_button_back_clicked)

    def set_data(self):
        """Pobiera dane obiektów zawierające podaną frazę w nazwie i 
        średnią ocenę w zakresie podanym przez użytkownika.
        """
        database = database_handler.Database_Handler()
        self.data = database.get_movies_with_phrase_and_range(
            self.text_filter, self.min_val, self.max_val)

    def refresh_grid_with_treeview(self):
        """Usuwa widok listy obiektów i tworzy w jego miejsce nowy,
        zgodny z listą pobranych obiektów.
        """
        self.box_with_grid.remove(self.grid)
        self.grid = Gtk.Grid()
        self.grid.set_column_homogeneous(True)
        self.grid.set_row_homogeneous(True)
        self.box_with_grid.pack_start(self.grid, True, True, 0)

        self.objects_list_store = Gtk.ListStore(int, str, float, int, str)
        if self.data is not None:
            for elem in self.data:
                self.objects_list_store.append(list(elem))

        self.objects_filter = self.objects_list_store.filter_new()
        self.objects_filter.set_visible_func(self.object_filter_func)

        self.treeview = Gtk.TreeView.new_with_model(self.objects_filter)
        for i, column_title in enumerate(["Id_filmu", "Tytuł", "Średnia ocena",
                                          "Liczba ocen", "Gatunek"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(column_title, renderer, text=i)
            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist, 0, 0, 8, 10)
        self.scrollable_treelist.add(self.treeview)
        self.window.show_all()

    def add_filtering_buttons(self):
        """Dodaje przyciski umożliwiające filtrowane wyszukiwanie obiektów.
        
        Tworzy Entry umożliwiające pobranie frazy, którą mają zawierać nazwy wyświetlanych
        obiektów oraz przyciski umożliwiające wprowadzenie zakresu średnich ocen obiektów.
        Dodaje przycisk potwierdzenia wyszukiwania oraz przycisk przywracający wartości
        parametrów wyszukiwania do domyślnych.
        """
        self.label_select = Gtk.Label(
            "Wybierz zakres ocen obiektów, które chcesz wyświetlić.")
        self.pack_start(self.label_select, False, False, 0)

        self.min_val = global_variables.MIN_RANK
        self.max_val = global_variables.MAX_RANK
        self.button_min_val = spin_button_from_min_to_max.Spin_Button_from_min_to_max(
            global_variables.MIN_RANK, global_variables.MAX_RANK, 0.5)
        self.pack_start(self.button_min_val, False, False, 0)
        self.button_max_val = spin_button_from_min_to_max.Spin_Button_from_min_to_max(
            global_variables.MIN_RANK, global_variables.MAX_RANK, 0.5)
        self.button_max_val.set_value(global_variables.MAX_RANK)
        self.pack_start(self.button_max_val, False, False, 0)

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
        self.pack_start(self.button_submit, False, False, 0)
        self.button_submit.connect("clicked", self.on_button_submit_clicked)

    def object_filter_func(self, model, iter, data):
        """Niewykorzystywana funkcja. Filtruje listę pobranych już obiektów na zawierające 
        w nazwie frazę i zakres średnich ocen podanych przez użytkownika.
        """
        return model[iter][2] >= self.min_val and \
            model[iter][2] <= self.max_val and self.text_filter in model[iter][1]

    def on_button_submit_clicked(self, widget):
        """Po kliknięciu, pobiera wartości parametrów wyszukiwania (fraza, zakres),
        następnie wywołuje funkcję set_data do pobrania danych obiektów i odświeża
        widok listy obiektów za pomocą refresh_grid_with_treeview.
        """
        self.min_val = float(self.button_min_val.get_value())
        self.max_val = float(self.button_max_val.get_value())
        self.text_filter = self.entry_filter.get_text()
        self.set_data()
        self.refresh_grid_with_treeview()

    def on_button_back_clicked(self, widget):
        """Przechodzi do widoku wyboru akcji po kliknięciu przycisku."""
        self.window.set_action_selection()

    def on_button_clear_clicked(self, widget):
        """Po kliknięciu, przywraca wartości parametrów wyszukiwania do domyślnych,
        a następnie wywołuje funkcję set_data do pobrania danych obiektów i odświeża
        widok listy obiektów za pomocą refresh_grid_with_treeview.
        """
        self.text_filter = ""
        self.entry_filter.set_text("")
        self.set_data()
        self.refresh_grid_with_treeview()
