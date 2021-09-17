
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "clock.h"
#include "timePanel.h"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "gtk.clock");

    Gtk::Window window;
    window.set_title("C++ (GTK) Clock");
    window.set_border_width(5);
    window.set_default_size(400, 300);
    
    auto timePanel = Gtk::make_managed<TimePanel>();
    window.add(*timePanel);
    window.show_all();

    return app->run(window); 
} 
