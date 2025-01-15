#ifndef OCTETOS_EC_GTK_HH_INCLUDED
#define OCTETOS_EC_GTK_HH_INCLUDED


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
#include "gtk.hh"

namespace oct::ec::v1
{
    class EC : public Application
    {
    public:
        EC();
        virtual ~EC();

        virtual void notify() = 0;

    private:

    };


    template<typename T>
    class WorkerEC : public Worker<T>
    {
    public:
        size_t iteration,iterations;

    public:
        WorkerEC() = default;
        WorkerEC(T& t,size_t its = 1000000) :
            Worker<T>(t),
            iteration(0),
            iterations(its)
        {
        }
        WorkerEC(T& t,std::mutex& mux,size_t its = 1000000) :
            Worker<T>(t,mux),
            iteration(0),
            iterations(its)
        {
        }
        void do_work(EC* caller)
        {
            {
                std::lock_guard<std::mutex> lock(*this->m_Mutex);
                this->m_has_stopped = false;
            }

            while(true)//for(;iteration < iterations; iteration++) // do until break
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(5));
                {
                    std::lock_guard<std::mutex> lock(*this->m_Mutex);
                    if(iteration >= iterations) break;
                    iteration++;
                    //

                    this->data->evaluate();
                    //this->data->print(std::cout);
                    this->data->resumen();
                    //std::cout << "Media : " << this->data->media << "\n";
                    this->data->pair();

                    //grtv->load(*this->data);

                    //
                    if (this->m_shall_stop)
                    {
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                caller->notify();
            }

            {
                std::lock_guard<std::mutex> lock(*this->m_Mutex);
                this->m_shall_stop = false;
                this->m_has_stopped = true;
            }

            //caller->notify();
        }

    };

}



#endif // MATH-APPLICATION_HH_INCLUDED
