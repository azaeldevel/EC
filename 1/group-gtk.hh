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
#include "ec-gtk.hh"

namespace oct::ec::v1
{
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
                add(value);
                add(gap);
            }

            Gtk::TreeModelColumn<size_t> index;
            Gtk::TreeModelColumn<double> evaluation;
            Gtk::TreeModelColumn<double> value;
            Gtk::TreeModelColumn<double> gap;
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
                row[columns.value] = grp[i]->value();
                row[columns.gap] = grp[i]->gap();
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
            append_column_numeric("Evaluacion", columns.evaluation,"%.20f");
            append_column_numeric("Valor", columns.value,"%.20f");
            append_column_numeric("Brecha", columns.gap,"%.20f");
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
        Gtk::Label iteration;
        //
        virtual bool on_button_press_event(GdkEventButton* event);
        //
        void on_start_button_clicked();
        void on_stop_button_clicked();
        void on_quit_button_clicked();
        void update_start_stop_buttons();
        virtual void notify();
        void on_notification_from_worker_thread();
        void update_widgets();

    private:
        inputs<double,3> vars;
        BinoprGroup<3,double,Binopr> town;
        std::mutex town_mux;

        std::thread *m_WorkerThread,*m_WorkerThread_tv;
        WorkerEC<BinoprGroup<3,double,Binopr>> m_Worker;
        Glib::Dispatcher m_Dispatcher;
    };
}



#endif // MATH-APPLICATION_HH_INCLUDED
