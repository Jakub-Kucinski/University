import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class SpinButtonWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="SpinButton Demo")
        self.set_border_width(10)

        hbox = Gtk.Box(spacing=6)
        self.add(hbox)

        self.spinbutton = Gtk.SpinButton()
        self.spinbutton.set_adjustment(Gtk.Adjustment(1.0, 1.0, 5.0, 0.5, 10, 0))
        hbox.pack_start(self.spinbutton, False, False, 0)

        self.spinbutton.set_numeric(True)
        self.spinbutton.set_digits(1)


win = SpinButtonWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
