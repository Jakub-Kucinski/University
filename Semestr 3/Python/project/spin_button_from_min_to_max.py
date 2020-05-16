import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk


class Spin_Button_from_min_to_max(Gtk.SpinButton):
    """SpinButton o specjalnie dobranych parametrach i właściwościach."""

    def __init__(self, min, max, step):
        """Tworzy SpinButton typu numerycznego o podanym zakresie i korku.

        Wywołuje konstruktor nadklasy Gtk.Box ustawiając jego wartość minimalną,
        maksymalną i krok. Następnie ustawia typ numeryczny i liczbę wyświetlanych
        cyfr po przecinku na 1.
        """
        Gtk.SpinButton.__init__(self)
        self.set_adjustment(Gtk.Adjustment(min, min, max, step, 10, 0))
        self.set_numeric(True)
        self.set_digits(1)
