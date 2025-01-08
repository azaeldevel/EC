#ifndef MATH_APPLICATION_HH_INCLUDED
#define MATH_APPLICATION_HH_INCLUDED


#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>

namespace oct::ec::v1
{
    class Application : public Gtk::Window
    {
    public:
        enum class Layout
        {
            none,
            generic,

        };

    public:
        Application();
        virtual ~Application();

    protected:
        //Signal handlers:
        void on_button_clicked();

    private:
        Layout layout;

    private:
        //Member widgets:
        Gtk::Box box_main;
        Gtk::Box box_panel;
        Gtk::Box box_work;
        Gtk::Button m_button;


    };
}



#endif // MATH-APPLICATION_HH_INCLUDED
