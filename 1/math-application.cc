
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

    void GroupPanel::load(const BinoprGroup<3,double,Binopr>& grp)
    {
        Gtk::TreeModel::Row row;
        for(size_t i = 0; i < grp.size(); i++)
        {
            row = *(ref_tree->append());
            row[columns.index] = i;
            row[columns.evaluation] = grp[i]->evaluation;
        }
    }


    EC::EC()
    {
    }

    EC::~EC()
    {
    }








    MathEC::MathEC() : vars(3), town(vars),iteration(0),iterations(100000),status(false)
    {
        int w,h;
        get_size(w,h);
        /*Gtk::MessageDialog dialog(*this, "Message dialog", true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        dialog.set_title("Title");
        std::string msg = "Ancho : ";
        msg += std::to_string(w);
        dialog.set_message(msg);
        dialog.set_secondary_text("Secondary message");
        dialog.set_default_response(Gtk::RESPONSE_YES);
        int result = dialog.run();*/

        //paned_scroll.set_size_request(get_width()/4,get_height());
        paned_scroll.set_size_request(w/3,h);
        paned_scroll.add(group_tree);
        //paned_scroll.set_min_content_width(get_width()/3);
        //paned_scroll.set_border_width(10);
        //paned_scroll.set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS );
        paned.add1(paned_scroll);

        Binopr<3,double>::init_randsys(100);

        //vars.resize(3);//cantidad de resgistro
        vars[0][0] = 1.2;
        vars[0][1] = 65.964;
        vars[0][2] = 198.1254832;
        vars[1][0] = 9653.264;
        vars[1][1] = 1.f/2365.f;
        vars[1][2] = 198.1254832;
        vars[2][0] = 0.5;
        vars[2][1] = 0.7;
        vars[2][2] = 0.83;

        town.populate_random();
        load(town);

        //https://docs.huihoo.com/gtkmm/gtkmm-2.4/tutorial/html/sec-menus-examples.html
        m_refActionGroup = Gtk::ActionGroup::create();

        m_refActionGroup->add(Gtk::Action::create("Iniciar", Gtk::Stock::NEW, "_New", "Create a new file"), sigc::mem_fun(*this, &MathEC::on_menu_start));
        m_refActionGroup->add(Gtk::Action::create("Finalizar",Gtk::Stock::NEW, "New Foo", "Create a new foo"), sigc::mem_fun(*this, &MathEC::on_menu_stop));

        show_all_children();
    }

    MathEC::~MathEC()
    {
    }
    void MathEC::load(const BinoprGroup<3,double,Binopr>& grp)
    {
        group_tree.load(grp);
    }
    bool MathEC::running()
    {
        for(iteration = 0; iteration < iterations; iteration++)
        {
            town.evaluate();
            //town.print(std::cout);
            //town.resumen(std::cout);
            //std::cout << "\n\n";
            town.pair();
        }

        return true;
    }

    void MathEC::on_menu_start()
    {
      hide(); //Closes the main window to stop the Gtk::Main::run().
    }

    void MathEC::on_menu_stop()
    {
       std::cout << "A File|New menu item was selected." << std::endl;
    }
}
