#ifndef MATH_APPLICATION_HH_INCLUDED
#define MATH_APPLICATION_HH_INCLUDED


#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/paned.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/cellrendererprogress.h>

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

    private:
        GroupPanel group_tree;
    };
}



#endif // MATH-APPLICATION_HH_INCLUDED
