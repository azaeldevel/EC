
#include "ec-gtk.hh"
#include <gtkmm/application.h>



//namespace core = oct::core::v3;
namespace ec = oct::ec::v1;

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    ec::MathEC appEC;

    //Shows the window and returns when it is closed.
    return app->run(appEC);
}
