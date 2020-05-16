from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy import Table, Column, Integer, Boolean, ForeignKey, String
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk

Base = declarative_base()


class App_Window(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Książki")
        self.connect("destroy", Gtk.main_quit)
        self.set_border_width(10)
        self.box = Gtk.Box()
        self.add(self.box)
        self.set_action_selection()

    def set_action_selection(self):
        self.remove(self.box)
        self.box = Action_Selection_Box(self)
        self.add(self.box)
        self.show_all()

    def set_listing_books(self):
        self.remove(self.box)
        self.box = Listing_Books_Box(self)
        self.add(self.box)
        self.show_all()

    def set_listing_friends(self):
        self.remove(self.box)
        self.box = Listing_Friends_Box(self)
        self.add(self.box)
        self.show_all()

    def set_adding_book(self):
        self.remove(self.box)
        self.box = Adding_Book_Box(self)
        self.add(self.box)
        self.show_all()
        
    def set_lending_book(self):
        self.remove(self.box)
        self.box = Lend_Book_Box(self)
        self.add(self.box)
        self.show_all()

    def set_returning_book(self):
        self.remove(self.box)
        self.box = Return_Book_Box(self)
        self.add(self.box)
        self.show_all()

    def set_quiting_app(self):
        self.destroy()
    

class Action_Selection_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wybierz jedną z dostępnych akcji:")
        self.pack_start(choice, False, False, 0)

        self.button_list_books = Gtk.Button(
            label="Wyświetl listę książek")
        self.pack_start(self.button_list_books, False, False, 0)
        self.button_list_books.connect(
            "clicked", self.on_button_list_books_clicked)

        self.button_list_friends = Gtk.Button(
            label="Wyświetl listę znajomych")
        self.pack_start(self.button_list_friends, False, False, 0)
        self.button_list_friends.connect(
            "clicked", self.on_button_list_friends_clicked)

        self.button_add_book = Gtk.Button(
            label="Dodaj nową książkę")
        self.pack_start(self.button_add_book, False, False, 0)
        self.button_add_book.connect(
            "clicked", self.on_button_add_book_clicked)

        self.button_lend_book = Gtk.Button(
            label="Pożycz książkę")
        self.pack_start(self.button_lend_book, False, False, 0)
        self.button_lend_book.connect(
            "clicked", self.on_button_lend_book_clicked)

        self.button_return_book = Gtk.Button(
            label="Oddaj książkę")
        self.pack_start(self.button_return_book, False, False, 0)
        self.button_return_book.connect(
            "clicked", self.on_button_return_book_clicked)

        self.button_quit_app = Gtk.Button(
            label="Wyjdź z aplikacji")
        self.pack_start(self.button_quit_app, False, False, 0)
        self.button_quit_app.connect(
            "clicked", self.on_button_quit_app_clicked)

    def on_button_list_books_clicked(self, widget):
        self.window.set_listing_books()

    def on_button_list_friends_clicked(self, widget):
        self.window.set_listing_friends()

    def on_button_add_book_clicked(self, widget):
        self.window.set_adding_book()

    def on_button_lend_book_clicked(self, widget):
        self.window.set_lending_book()

    def on_button_return_book_clicked(self, widget):
        self.window.set_returning_book()

    def on_button_quit_app_clicked(self, widget):
        self.window.set_quiting_app()


class Adding_Book_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window

        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wprowadź dane książki")
        self.pack_start(choice, False, False, 0)

        self.entry_title = Gtk.Entry()
        self.entry_title.set_text("Tytuł")
        self.entry_title.set_max_length(100)
        self.pack_start(self.entry_title, False, False, 0)

        self.entry_author = Gtk.Entry()
        self.entry_author.set_text("Autor")
        self.entry_author.set_max_length(100)
        self.pack_start(self.entry_author, False, False, 0)

        self.entry_year = Gtk.Entry()
        self.entry_year.set_text("Rok")
        self.entry_year.set_max_length(4)
        self.pack_start(self.entry_year, False, False, 0)

        choice = Gtk.Label("Czy na pewno chcesz dodać książkę?")
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        try:
            year = int(self.entry_year.get_text())
            title = self.entry_title.get_text()
            author = self.entry_author.get_text()
            dodaj_nowa_ksiazke(title, author, year)
        except ValueError:
            dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, "Niepoprawne dane")
            # dialog.format_secondary_text(
            #     "And this is the secondary text that explains things.")
            dialog.run()
            dialog.destroy()
            return
        self.window.set_action_selection()

    def on_button_reject_clicked(self, widget):
        self.window.set_action_selection()


class Listing_Books_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        self.set_data()

        self.box_with_grid = Gtk.Box()
        self.pack_start(self.box_with_grid, True, True, 0)
        self.grid = Gtk.Grid()

        self.refresh_grid_with_treeview()

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect("clicked", self.on_button_back_clicked)

    def set_data(self):
        self.data = list_of_books()

    def refresh_grid_with_treeview(self):
        self.box_with_grid.remove(self.grid)
        self.grid = Gtk.Grid()
        self.grid.set_column_homogeneous(True)
        self.grid.set_row_homogeneous(True)
        self.box_with_grid.pack_start(self.grid, True, True, 0)

        self.objects_list_store = Gtk.ListStore(int, str, str, int, bool, int)
        if self.data is not None:
            for elem in self.data:
                self.objects_list_store.append(list(elem))

        self.treeview = Gtk.TreeView(self.objects_list_store)
        for i, column_title in enumerate(
                ["Id_książki", "Tytuł", "Autor", "Rok", "Czy wypożyczona", "Osoba wypożyczająca"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(column_title, renderer, text=i)
            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist, 0, 0, 8, 10)
        self.scrollable_treelist.add(self.treeview)
        self.window.show_all()

    def on_button_back_clicked(self, widget):
        self.window.set_action_selection()


class Listing_Friends_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window
        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        self.set_data()

        self.box_with_grid = Gtk.Box()
        self.pack_start(self.box_with_grid, True, True, 0)
        self.grid = Gtk.Grid()

        self.refresh_grid_with_treeview()

        self.button_back = Gtk.Button(label="Wstecz")
        self.pack_start(self.button_back, False, False, 0)
        self.button_back.connect("clicked", self.on_button_back_clicked)

    def set_data(self):
        self.data = list_of_friends()

    def refresh_grid_with_treeview(self):
        self.box_with_grid.remove(self.grid)
        self.grid = Gtk.Grid()
        self.grid.set_column_homogeneous(True)
        self.grid.set_row_homogeneous(True)
        self.box_with_grid.pack_start(self.grid, True, True, 0)

        self.objects_list_store = Gtk.ListStore(int, str, str)
        if self.data is not None:
            for elem in self.data:
                self.objects_list_store.append(list(elem))

        self.treeview = Gtk.TreeView(self.objects_list_store)
        for i, column_title in enumerate(
                ["Id_przyjaciela", "Imie", "email"]):
            renderer = Gtk.CellRendererText()
            column = Gtk.TreeViewColumn(column_title, renderer, text=i)
            self.treeview.append_column(column)

        self.scrollable_treelist = Gtk.ScrolledWindow()
        self.scrollable_treelist.set_vexpand(True)
        self.grid.attach(self.scrollable_treelist, 0, 0, 8, 10)
        self.scrollable_treelist.add(self.treeview)
        self.window.show_all()

    def on_button_back_clicked(self, widget):
        self.window.set_action_selection()


class Lend_Book_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window

        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wprowadź id książki i id znajomego, któremu wypożyczasz książkę")
        self.pack_start(choice, False, False, 0)

        self.entry_book_id = Gtk.Entry()
        self.entry_book_id.set_text("Id_książki")
        self.entry_book_id.set_max_length(100)
        self.pack_start(self.entry_book_id, False, False, 0)

        self.entry_friend_id = Gtk.Entry()
        self.entry_friend_id.set_text("Id_znajomego")
        self.entry_friend_id.set_max_length(100)
        self.pack_start(self.entry_friend_id, False, False, 0)

        choice = Gtk.Label("Czy na pewno chcesz wypożyczyć książkę?")
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        try:
            book_id = int(self.entry_book_id.get_text())
            friend_id = int(self.entry_friend_id.get_text())
            wypozycz_ksiazke(book_id, friend_id)
        except ValueError as err:
            dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, str(err))
            # dialog.format_secondary_text(
            #     "And this is the secondary text that explains things.")
            dialog.run()
            dialog.destroy()
            return
        self.window.set_action_selection()

    def on_button_reject_clicked(self, widget):
        self.window.set_action_selection()

class Return_Book_Box(Gtk.Box):
    def __init__(self, window):
        self.window = window

        Gtk.Box.__init__(self, orientation=Gtk.Orientation.VERTICAL, spacing=6)

        choice = Gtk.Label("Wprowadź id książki, która zostaje oddana")
        self.pack_start(choice, False, False, 0)

        self.entry_book_id = Gtk.Entry()
        self.entry_book_id.set_text("Id_książki")
        self.entry_book_id.set_max_length(100)
        self.pack_start(self.entry_book_id, False, False, 0)

        choice = Gtk.Label("Czy na pewno chcesz oddać książkę?")
        self.pack_start(choice, False, False, 0)

        self.button_confirm = Gtk.Button(label="Tak")
        self.pack_start(self.button_confirm, False, False, 0)
        self.button_confirm.connect("clicked", self.on_button_confirm_clicked)

        self.button_reject = Gtk.Button(label="Nie")
        self.pack_start(self.button_reject, False, False, 0)
        self.button_reject.connect("clicked", self.on_button_reject_clicked)

    def on_button_confirm_clicked(self, widget):
        try:
            book_id = int(self.entry_book_id.get_text())
            oddaj_ksiazke(book_id)
        except ValueError as err:
            dialog = Gtk.MessageDialog(self.window, 0, Gtk.MessageType.INFO,
                Gtk.ButtonsType.OK, str(err))
            # dialog.format_secondary_text(
            #     "And this is the secondary text that explains things.")
            dialog.run()
            dialog.destroy()
            return
        self.window.set_action_selection()

    def on_button_reject_clicked(self, widget):
        self.window.set_action_selection()


class Znajomy(Base):
    __tablename__ = 'Znajomy'
    id = Column(Integer, primary_key=True)
    imie = Column(String(20), nullable=False)
    email = Column(String)
    ksiazki = relationship('Ksiazka')

    def info_table(self):
        return [self.id, self.imie, self.email]

    def __repr__(self):
        return "| %s | %s | %s |" % (
            self.id, self.imie, self.email)


class Ksiazka(Base):
    __tablename__ = 'Ksiazka'
    id = Column(Integer, primary_key=True)
    tytul = Column(String)
    autor = Column(String)
    rok = Column(Integer, default=2019)
    czy_wypozyczona = Column(Boolean)
    osoba_pozyczajaca = Column(Integer, ForeignKey("Znajomy.id"), nullable=True)

    def info_table(self):
        return [self.id, self.tytul, self.autor,
            self.rok, self.czy_wypozyczona, self.osoba_pozyczajaca]

    def __repr__(self):
        return "| %s | %s | %s | %s | %s | %s |" % (
            self.id, self.tytul, self.autor,
            self.rok, self.czy_wypozyczona, self.osoba_pozyczajaca)


def dodaj_nowa_ksiazke(tytul_ksiazki, autor_ksiazki, rok_wydania):
    nowa_ksiazka = Ksiazka(tytul=tytul_ksiazki, autor=autor_ksiazki,
                           rok=rok_wydania, czy_wypozyczona=False)
    sesja.add(nowa_ksiazka)
    sesja.commit()


def dodaj_nowego_znajomego(imie_znajomego, email_znajomego):
    nowy_znajomy = Znajomy(imie=imie_znajomego, email=email_znajomego)
    sesja.add(nowy_znajomy)
    sesja.commit()

def list_of_books():
    lista = sesja.query(Ksiazka).all()
    t = []
    for obiekt in lista:
        t.append(obiekt.info_table())
    return t

def list_of_friends():
    lista = sesja.query(Znajomy).all()
    t = []
    for obiekt in lista:
        t.append(obiekt.info_table())
    return t

def wypisz_ksiazki():
    print("| Id książki | Tytuł | Autor | Rok | Czy wypożyczona? | " +
          "Id wypożyczającego znajomego |")
    print("---------------------------------------------------------" +
          "-----------------------------")
    lista = sesja.query(Ksiazka).all()
    for obiekt in lista:
        print(obiekt)


def wypisz_znajomych():
    print("| Id znajomego | Imię | Email |")
    print("-------------------------------")
    lista = sesja.query(Znajomy).all()
    for obiekt in lista:
        print(obiekt)


def wypozycz_ksiazke(id_ksiazki, id_znajomego):
    lista = sesja.query(Ksiazka).filter_by(id=id_ksiazki).first()
    if lista:
        if lista.czy_wypozyczona is True:
            # print("Nie można wypożyczyć książki, bo jest już w wypożyczeniu")
            raise ValueError("Nie można wypożyczyć książki, bo jest już w wypożyczeniu")
            return

        lista2 = sesja.query(Znajomy).filter_by(id=id_znajomego).first()
        if lista2:
            lista.czy_wypozyczona = True
            lista.osoba_pozyczajaca = id_znajomego
            # print("Książka została pomyślnie wypożyczona")
            sesja.commit()
        else:
            # print("Brak znajomego o podanym numerze")
            raise ValueError("Brak znajomego o podanym numerze")
    else:
        # print("Brak książki o podanym numerze")
        raise ValueError("Brak książki o podanym numerze")


def oddaj_ksiazke(id_ksiazki):
    lista = sesja.query(Ksiazka).filter_by(id=id_ksiazki).first()
    if lista:
        if lista.czy_wypozyczona:
            lista.osoba_pozyczajaca = None
            lista.czy_wypozyczona = False
            sesja.commit()
            # print("Książka została pomyślnie oddana")
        else:
            # print("Nie można oddać książki, bo nie jest wypożyczona")
            raise ValueError("Nie można oddać książki, bo nie jest wypożyczona")
    else:
        # print("Brak książki o podanym numerze")
        raise ValueError("Brak książki o podanym numerze")


def program2():
    window = App_Window()
    Gtk.main()

engine = create_engine('sqlite:///zad1.db', echo=False)
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
sesja = Session()

# dodaj_nowa_ksiazke("Ciekawy tytuł", "Popularny autor", 2019)
# dodaj_nowego_znajomego("Kolega", "Tajemniczy@gmail.com")
# wypisz_ksiazki()
# print("\n")
# wypisz_znajomych()
# lista = sesja.query(Znajomy).all()
# for obiekt in lista:
#     print(obiekt, "\t I wypożyczone przez niego książki: ", obiekt.ksiazki)

# wypozycz_ksiazke(1, 1)
# oddaj_ksiazke(1)

program2()
