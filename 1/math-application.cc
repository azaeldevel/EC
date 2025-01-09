
#include "math-application.hh"
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
        set_size_request(800,600);

        if(layout == Layout::left_paned)
        {
            box_main.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
            box_work.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            box_main.add(box_top_panel);
            box_main.add(box_work);

            paned.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            box_work.add(paned);

        }

        add(box_main);
    }

    void Application::on_button_clicked()
    {
      std::cout << "Hello World" << std::endl;
    }


    GroupPanel::GroupPanel()
    {
        //Create the Tree model:
        ref_tree = Gtk::ListStore::create(columns);
        set_model(ref_tree);

        //Fill the TreeView's model
        Gtk::TreeModel::Row row = *(ref_tree->append());
        row[columns.index] = 1;
        row[columns.evaluation] = 1.0;

        row = *(ref_tree->append());
        row[columns.index] = 2;
        row[columns.evaluation] = 2.0;

        append_column("ID", columns.index);
        //append_column("Evaluacion", columns.evaluation);
        //append_column_numeric("Evaluacion", columns.evaluation,"%010d");
        //Display a progress bar instead of a decimal number:
        auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
        int column_eval = append_column("evaluacion", *cell);
        auto hcolumn = get_column(column_eval - 1);
        if(hcolumn)
        {
            hcolumn->add_attribute(cell->property_value(), columns.evaluation);
        }
    }


    EC::EC()
    {
        paned.add(group_tree);
        show_all_children();
    }

    EC::~EC()
    {
    }
}
