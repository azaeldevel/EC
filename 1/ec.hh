#ifndef OCTETOS_EC_V1_HH_INCLUDED
#define OCTETOS_EC_V1_HH_INCLUDED

#include <core/3/array.hh>
#include <core/3/ast.hh>
#include <random>

namespace oct::ec::v1
{
    namespace core = oct::core::v3;
    namespace ec = oct::ec::v1;

    /**
    *\brief Inteface para representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::number N = float>
    struct single
    {

    public:
        virtual N evaluate() const= 0;
    };

    /**
    *\brief Representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::number N = float>
    struct arithmetic : public single<N>
    {
    public:
        typedef single<N> SINGLE_BASE;

    public:
        arithmetic() = default;
        arithmetic(core::ast::node<N>& nin) : node(nin),auto_free(false)
        {
        }
        arithmetic(core::ast::node<N>* nin) : node(nin),auto_free(false)
        {
        }
        arithmetic(core::ast::node<N>* nin,bool free) : node(nin),auto_free(free)
        {
        }
        ~arithmetic()
        {
            if(auto_free)
            {
                delete node;
                node = NULL;
            }
        }

    public:
        virtual N evaluate() const
        {
            return 0;
        }

        static core::ast::node<N>* populate_generic(std::mt19937& generator,std::uniform_int_distribution<>& operation,std::bernoulli_distribution  nesting,std::uniform_real_distribution<>& constant)
        {
            int opr = operation(generator);
            bool netsa = nesting(generator);
            bool netsb = nesting(generator);

            switch(opr)
            {
            case 1:
                if(netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::addition,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::addition,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::addition,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::addition,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                break;
            case 2:
                if(netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::subtraction,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::subtraction,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::subtraction,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::subtraction,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                break;
            case 3:
                if(netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::product,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::product,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::product,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::product,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                break;
            case 4:
                if(netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::quotient,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::quotient,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::quotient,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                else if(!netsa and !netsb)
                {
                    return (core::ast::node<N>*)new core::ast::arithmetic<N>(core::ast::typen::quotient,new core::ast::numeric<N>(constant(generator)),new core::ast::numeric<N>(constant(generator)));
                }
                break;
            }


            return NULL;
        }

    public:
        core::ast::node<N>* node;
        bool auto_free;

    public:

    };


    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<class T,core::number N = float>
    struct Town : public core::array<T>
    {
    public:
        typedef  core::array<T> TOWN_BASE;

    public:
        Town() = default;
        Town(size_t s) : TOWN_BASE(s),auto_free(false)
        {
        }

    public:
        bool auto_free;
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N = float>
    struct City : public core::array<Town<T>>
    {
    public:
        typedef core::array<Town<T>> CITY_BASE;

    public:
        City() = default;
        City(size_t s) : CITY_BASE(s)
        {
        }
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N = float>
    struct State : public core::array<City<T>>
    {
    public:
        typedef core::array<City<T>> STATE_BASE;

    public:
        State() = default;
        State(size_t s) : STATE_BASE(s)
        {
        }
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N = float>
    struct Country : public core::array<State<T>>
    {
    public:
        typedef core::array<State<T>> COUNTRY_BASE;

    public:
        Country() = default;
        Country(size_t s) : COUNTRY_BASE(s)
        {
        }
    };

    /*template<class T,core::number N = float>
    struct Population : public Breed<T,N>
    {
    public:
        typedef Breed<T,N> BREED_BASE;

    public:
        Population() = default;
        Population(size_t s) : BREED_BASE(s)
        {
        }

    };*/

}

#endif // EC_HH_INCLUDED
