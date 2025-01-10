
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
        /*Gtk::TreeModel::Row row = *(ref_tree->append());
        row[columns.index] = 1;
        row[columns.evaluation] = 1.0;

        row = *(ref_tree->append());
        row[columns.index] = 2;
        row[columns.evaluation] = 2.0;*/

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
    void GroupPanel::clear()
    {
        ref_tree->clear();
    }


    EC::EC()
    {
    }

    EC::~EC()
    {
    }








    MathEC::MathEC() : vars(3), town(vars),iteration(0),iterations(100000),m_shall_stop(false),m_has_stopped(false)
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
        //load(town);

        //https://docs.huihoo.com/gtkmm/gtkmm-2.4/tutorial/html/sec-menus-examples.html
        m_refActionGroup = Gtk::ActionGroup::create();
        m_refActionGroup->add(Gtk::Action::create("ContextMenu", "Context Menu"));

        m_refActionGroup->add(Gtk::Action::create("ContextBegin", "Iniciar"),sigc::mem_fun(*this, &MathEC::do_work));

        m_refActionGroup->add(Gtk::Action::create("ContextEnd", "Finalizar"),Gtk::AccelKey("<control>P"), sigc::mem_fun(*this, &MathEC::stop_work));

        m_refActionGroup->add(Gtk::Action::create("ContextStatus", "Estado"),sigc::mem_fun(*this, &MathEC::on_menu_popup_status));


        m_refUIManager = Gtk::UIManager::create();
        m_refUIManager->insert_action_group(m_refActionGroup);

        add_accel_group(m_refUIManager->get_accel_group());

        //Layout the actions in a menubar and toolbar:
        Glib::ustring ui_info =
            "<ui>"
            "  <popup name='PopupMenu'>"
            "    <menuitem action='ContextBegin'/>"
            "    <menuitem action='ContextEnd'/>"
            "    <menuitem action='ContextStatus'/>"
            "  </popup>"
            "</ui>";

        std::auto_ptr<Glib::Error> ex;
        m_refUIManager->add_ui_from_string(ui_info);
        if(ex.get())
        {
            std::cerr << "building menus failed: " <<  ex->what();
        }

        //Get the menu:
        m_pMenuPopup = dynamic_cast<Gtk::Menu*>(m_refUIManager->get_widget("/PopupMenu"));
        if(!m_pMenuPopup) g_warning("menu not found");

        show_all_children();
    }

    MathEC::~MathEC()
    {
        m_has_stopped = true;
    }


    bool MathEC::has_stopped()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        return m_has_stopped;
    }
    void MathEC::stop_work()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_shall_stop = true;
    }
    void MathEC::on_menu_popup_status()
    {
    }

    bool MathEC::on_button_press_event(GdkEventButton* event)
    {
        if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
        {
            if(m_pMenuPopup) m_pMenuPopup->popup(event->button, event->time);
            return true; //It has been handled.
        }
        else return false;
    }
    void MathEC::do_work()
    {
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_has_stopped = false;
        }

        for(iteration = 0; iteration < iterations; iteration++)
        {
            std::cout << "iteration : " << iteration << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            {
                std::lock_guard<std::mutex> lock(m_Mutex);
                std::cout << "evaluando...\n";
                town.resumen(std::cout);
                town.evaluate();
                group_tree.clear();
                group_tree.load(town);
                if(m_shall_stop)
                {
                    break;
                }

                town.pair();
            }
            notify_callbacks();
        }
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_shall_stop = false;
            m_has_stopped = true;
        }
        notify_callbacks();
    }
    void MathEC::load(const BinoprGroup<3,double,Binopr>& grp)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        group_tree.load(grp);

    }


}
