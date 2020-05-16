import global_variables
import action_selection
import listing_objects
import logging_in
import selecting_object_to_rate
import listing_user_rating
import register
import deleting_rating
import changing_rating
import adding_rating
import recommendation
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk


class App_Window(Gtk.Window):
    """Okno aplikacji, dziedziczy po Gtk.Window.
    
    Zawiera metody odpowiedzialne za zmienę widoku na odpowiednie intefejsy.
    """

    def __init__(self):
        """Tworzy główne okno aplikacji. 
        
        Wywołuje konstruktor nadklasy, ustawia tytuł, zamykanie okna,
        ustawia widok na interfejs logowania.
        """
        Gtk.Window.__init__(self, title="System rekomendujący")
        self.connect("destroy", Gtk.main_quit)
        self.set_border_width(10)
        self.box = Gtk.Box()
        self.add(self.box)
        self.set_logging_in()

    def change_box_in_self(self, new_box):
        """Zmienia zawarty w oknie box na przekazany w argumencie new_box."""
        self.remove(self.box)
        self.box = new_box
        self.add(self.box)
        self.show_all()

    def set_logging_in(self):
        """Ustawia widok na interfejs logowania."""
        global_variables.USER_ID = None
        self.change_box_in_self(
            logging_in.Logging_In_Box(self))

    def set_action_selection(self):
        """Ustawia widok na interfejs wyboru akcji."""
        self.change_box_in_self(
            action_selection.Action_Selection_Box(self))

    def set_listing_objects(self):
        """Ustawia widok na interfejs przeglądania obiektów."""
        self.change_box_in_self(
            listing_objects.Listing_Objects_Box(self))

    def set_listing_user_rating(self):
        """Ustawia widok na interfejs przeglądania dodanych 
        przez użytkownika ocen obiektów.
        """
        self.change_box_in_self(
            listing_user_rating.Listing_User_Rating_Box(self))

    def set_selecting_object_to_rate(self):
        """Ustawia widok na interfejs wyboru obiektu do wystawienia oceny."""
        self.change_box_in_self(
            selecting_object_to_rate.Selectiong_Object_To_Rate_Box(self))

    def set_recommendation(self):
        """Ustawia widok na interfejs pobierania rekomendacji obiektów."""
        self.change_box_in_self(
            recommendation.Recommendation_Box(self))

    def set_register(self):
        """Ustawia widok na interfejs tworzenia nowego konta."""
        self.change_box_in_self(
            register.Register_Box(self))

    def set_deleting_rating(self, movie_id, title, rating, genres):
        """Ustawia widok na interfejs usuwania dodanej oceny."""
        self.change_box_in_self(deleting_rating.Deleting_Rating_Box(
            self, movie_id, title, rating, genres))

    def set_changing_rating(self, movie_id, title, rating, genres):
        """Ustawia widok na interfejs zmiany dodanej oceny."""
        self.change_box_in_self(changing_rating.Changing_Rating_Box(
            self, movie_id, title, rating, genres))

    def set_adding_rating(self, movie_id, title, genres):
        """Ustawia widok na interfejs dodawania nowej oceny."""
        self.change_box_in_self(adding_rating.Adding_Rating_Box(
            self, movie_id, title, genres))

    def set_quiting_app(self):
        """Zamyka okno."""
        self.destroy()


if __name__ == "__main__":
    App_Window()
    Gtk.main()
