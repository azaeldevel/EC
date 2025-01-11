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

    class Panel : public Gtk::TreeView
    {
    };

    class GroupPanel : public Panel
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

        void load(const BinoprGroup<3,double,Binopr>& );
        void clear();
    public:
        GroupPanel();

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


    class Worker
    {
    public:
        Worker();

        // Thread function.
        void do_work(EC* caller)
        {
            {
                std::lock_guard<std::mutex> lock(m_Mutex);
                m_has_stopped = false;
                m_fraction_done = 0.0;
                m_message = "";
            } // The mutex is unlocked here by lock's destructor.

            // Simulate a long calculation.
            for (int i = 0; ; ++i) // do until break
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(250));

                {
                    std::lock_guard<std::mutex> lock(m_Mutex);

                    m_fraction_done += 0.01;

                    if (i % 4 == 3)
                    {
                        std::ostringstream ostr;
                        ostr << (m_fraction_done * 100.0) << "% done\n";
                        m_message += ostr.str();
                        std::cout << ostr.str();
                    }

                    if (m_fraction_done >= 1.0)
                    {
                        m_message += "Finished";
                        break;
                    }
                    if (m_shall_stop)
                    {
                        m_message += "Stopped";
                        break;
                    }
                }

                caller->notify();
            }

            {
                std::lock_guard<std::mutex> lock(m_Mutex);
                m_shall_stop = false;
                m_has_stopped = true;
            }

            caller->notify();
        }

        void get_data(double* fraction_done, Glib::ustring* message) const;
        void stop_work();
        bool has_stopped() const;

    private:
        // Synchronizes access to member data.
        mutable std::mutex m_Mutex;

        // Data used by both GUI thread and worker thread.
        bool m_shall_stop;
        bool m_has_stopped;
        double m_fraction_done;
        Glib::ustring m_message;
    };


    class MathEC : public EC
    {
    public:
        MathEC();
        virtual ~MathEC();

    private:
        GroupPanel group_tree;
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
        size_t iteration,iterations;

        std::thread* m_WorkerThread;
        Worker m_Worker;
        Glib::Dispatcher m_Dispatcher;
        void load(const BinoprGroup<3,double,Binopr>& );

    };
}



#endif // MATH-APPLICATION_HH_INCLUDED
