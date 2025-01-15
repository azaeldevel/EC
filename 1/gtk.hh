#ifndef OCTETOS_GTK_HH_INCLUDED
#define OCTETOS_GTK_HH_INCLUDED


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

    template<typename T>
    class Worker
    {
    public:
        Worker() = default;
        Worker(T& d) : data(&d),m_Mutex(new std::mutex),auto_free(true), m_shall_stop(false), m_has_stopped(false)
        {
        }
        Worker(T& d,std::mutex& mux) : data(&d),m_Mutex(&mux),auto_free(false), m_shall_stop(false), m_has_stopped(false)
        {
        }
        virtual ~Worker()
        {
            if(auto_free) delete m_Mutex;
        }


        void stop_work()
        {
            std::lock_guard<std::mutex> lock(*m_Mutex);
            m_shall_stop = true;
        }
        bool has_stopped() const
        {
          std::lock_guard<std::mutex> lock(*m_Mutex);
          return m_has_stopped;
        }

    protected:
        T* data;
        mutable std::mutex* m_Mutex;
        bool auto_free;
        bool m_shall_stop;
        bool m_has_stopped;
    };

    /**
    *
    *
    */
    class TreeView : public Gtk::TreeView
    {
    };

}



#endif // MATH-APPLICATION_HH_INCLUDED
