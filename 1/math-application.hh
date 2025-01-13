#ifndef MATH_APPLICATION_HH_INCLUDED
#define MATH_APPLICATION_HH_INCLUDED


#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/paned.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm.h>
#include <gtkmm/stock.h>
#include <gtkmm/actiongroup.h>

#include "math.hh"
#include "worker.hh"

namespace oct::ec::v1
{
    class Application : public Gtk::Window
    {
    public:
        enum class Layout
        {
            none,
            left_paned,

        };

    public:
        Application();
        virtual ~Application();

        void init();

    protected:
        //Signal handlers:
        void on_button_clicked();

    private:
        Layout layout;

    protected:
        //Member widgets:
        Gtk::Box box_main;
        Gtk::Box box_top_panel;
        Gtk::Box box_work;
        Gtk::Button m_button;
        Gtk::ScrolledWindow paned_scroll;
        Gtk::Paned paned;



    };



    /**
    *
    *
    */
    class TreeView : public Gtk::TreeView
    {
    };

    template<typename T>
    class GroupTV : public TreeView
    {
    public:
        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
        public:

            ModelColumns()
            {
                add(index);
                add(evaluation);
            }

            Gtk::TreeModelColumn<size_t> index;
            Gtk::TreeModelColumn<double> evaluation;
        };

        void load(const T& grp)
        {
            Gtk::TreeModel::Row row;
            for(size_t i = 0; i < (grp.size() - ref_tree->children().size()); i++)
            {
                row = *(ref_tree->append());
                //row[columns.index] = i;
                //row[columns.evaluation] = grp[i]->evaluation * 100.0;
                //std::cout << "Eval : " << grp[i]->evaluation << "\n";
            }

            for(size_t i = 0; i < ref_tree->children().size(); i++)
            {
                row = ref_tree->children()[i];
                row[columns.index] = i + 1;
                row[columns.evaluation] = grp[i]->evaluation;
                //std::cout << "Eval : " << grp[i]->evaluation << "\n";
            }

        }
        void clear()
        {
            ref_tree->clear();
        }

    public:
        GroupTV()
        {
            ref_tree = Gtk::ListStore::create(columns);
            set_model(ref_tree);

            append_column("ID", columns.index);
            append_column_numeric("Evaluacion", columns.evaluation,"%.10f");
            /*
            auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
            int column_eval = append_column("evaluacion", *cell);
            auto hcolumn = get_column(column_eval - 1);
            if(hcolumn)
            {
                hcolumn->add_attribute(cell->property_value(), columns.evaluation);
            }
            */
        }


    protected:
        ModelColumns columns;
        Glib::RefPtr<Gtk::ListStore> ref_tree;
    };


    class EC : public Application
    {
    public:
        EC();
        virtual ~EC();

        virtual void notify() = 0;

    private:

    };


    template<typename T>
    class Worker
    {
    public:
        Worker() = default;

        Worker(T& d) : data(&d), m_shall_stop(false), m_has_stopped(false)
        {
        }


        void stop_work()
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_shall_stop = true;
        }
        bool has_stopped() const
        {
          std::lock_guard<std::mutex> lock(m_Mutex);
          return m_has_stopped;
        }

    protected:
        // Synchronizes access to member data.
        mutable std::mutex m_Mutex;

        // Data used by both GUI thread and worker thread.
        bool m_shall_stop;
        bool m_has_stopped;
        T* data;
    };

    template<typename T>
    class WorkerEC : public Worker<T>
    {
    public:
        size_t iteration,iterations;

    public:
        WorkerEC() = default;
        WorkerEC(T& t,GroupTV<T>& grp) : Worker<T>(t),grtv(&grp)
        {
        }
        void do_work(EC* caller)
        {
            {
                std::lock_guard<std::mutex> lock(this->m_Mutex);
                this->m_has_stopped = false;
            }

            while(true) // do until break
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                {
                    std::lock_guard<std::mutex> lock(this->m_Mutex);
                    //

                    this->data->evaluate();
                    //this->data->print(std::cout);
                    this->data->resumen();
                    //std::cout << "Media : " << this->data->media << "\n";
                    this->data->pair();

                    grtv->load(*this->data);

                    //
                    if (this->m_shall_stop)
                    {
                        break;
                    }
                }

                caller->notify();
            }

            {
                std::lock_guard<std::mutex> lock(this->m_Mutex);
                this->m_shall_stop = false;
                this->m_has_stopped = true;
            }

            caller->notify();
        }

        void load()
        {
            while(true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                {
                    std::lock_guard<std::mutex> lock(this->m_Mutex);
                    grtv->load(*this->data);
                    if (this->m_shall_stop)
                    {
                        break;
                    }
                }
            }
        }

    private:
        GroupTV<T>* grtv;

    };


    class MathEC : public EC
    {
    public:
        MathEC();
        virtual ~MathEC();

    private:
        GroupTV<BinoprGroup<3,double,Binopr>> group_tree;
        Glib::RefPtr<Gtk::UIManager> m_refUIManager;
        Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
        Gtk::Menu* m_pMenuPopup;
        //
        virtual bool on_button_press_event(GdkEventButton* event);
        virtual void on_menu_popup_status();
        //
        void on_start_button_clicked();
        void on_stop_button_clicked();
        void on_quit_button_clicked();
        void update_start_stop_buttons();
        virtual void notify();
        void on_notification_from_worker_thread();

    private:
        inputs<double,3> vars;
        BinoprGroup<3,double,Binopr> town;

        std::thread *m_WorkerThread;//,*m_WorkerThread_tv
        WorkerEC<BinoprGroup<3,double,Binopr>> m_Worker;
        Glib::Dispatcher m_Dispatcher;

    };
}



#endif // MATH-APPLICATION_HH_INCLUDED
