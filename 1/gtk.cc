
#include "gtk.hh"
#include <iostream>

namespace oct::ec::v1
{

    Application::Application() : layout(Layout::left_paned), m_button("Hello World")   // creates a new button with label "Hello World".
    {
        init();

        // Sets the border width of the window.
        set_border_width(10);
        // When the button receives the "clicked" signal, it will call the
        // on_button_clicked() method defined below.
        m_button.signal_clicked().connect(sigc::mem_fun(*this,&Application::on_button_clicked));

        // This packs the button into the Window (a container).
        //add(m_button);
        // The final step is to display this newly created widget...
        m_button.show();
    }

    Application::~Application()
    {
    }
    void Application::init()
    {
        //set_size_request(800,600);
        set_default_size(800, 600);
        if(layout == Layout::left_paned)
        {
            box_main.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
            box_work.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            box_main.add(box_top_panel);
            box_main.add(box_work);

            box_work.add(paned);
            paned.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

        }

        add(box_main);
    }

    void Application::on_button_clicked()
    {
      std::cout << "Hello World" << std::endl;
    }

}
