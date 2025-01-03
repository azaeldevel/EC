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
    struct Single
    {

    public:
        virtual N evaluate() const= 0;
    };

    /**
    *\brief Representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::index auto S,core::number N>
    struct Arithmetic : public Single<N>
    {
    public:
        typedef Single<N> SINGLE_BASE;

    public:
        Arithmetic() = default;
        Arithmetic(core::ast::node<>& nin) : node(nin),auto_free(false)
        {
        }
        Arithmetic(core::ast::node<>* nin) : node(nin),auto_free(false)
        {
        }
        Arithmetic(core::ast::node<>* nin,bool free) : node(nin),auto_free(free)
        {
        }
        ~Arithmetic()
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

        void rand_node(core::ast::Variable<N> (&variables)[S])
        {
            switch(randon_node(generator))
            {
            case 1:
                node = rand_op(variables);
                break;
            case 2:
                node = &variables[svariable(generator)];
                break;
            case 3:
                node = new core::ast::Numeric<N>(constant(generator));
                break;
            default:
                node = rand_op(variables);
                break;
            }
        }
        void rand_op(core::ast::Variable<N> (&variables)[S])
        {
            int opr = Arithmetic<S,N>::operation(generator);
            opr = opr + ((int)core::ast::typen::arithmetic);

            core::ast::Numeric<N>* a;
            if(nesting(generator))
            {
                a = &variables[svariable(generator)];
            }
            else
            {
                a = new core::ast::Numeric<N>(constant(generator));
            }

            core::ast::Numeric<N>* b;
            if(nesting(generator))
            {
                b = &variables[svariable(generator)];
            }
            else
            {
                b = new core::ast::Numeric<N>(constant(generator));
            }

            node = new core::ast::Arithmetic<N>(core::ast::typen(opr),a,b);
        }

    public:
        core::ast::node<>* node;
        bool auto_free;

    public:


    public:
        static inline std::random_device rd;
        static inline std::mt19937 generator;
        static inline std::uniform_int_distribution<> operation;
        static inline std::uniform_real_distribution<> constant;
        static inline std::bernoulli_distribution nesting;
        static inline std::uniform_int_distribution<> svariable;
        static inline std::uniform_int_distribution<> randon_node;

        static void init_randsys()
        {
            generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            operation = std::uniform_int_distribution<>(1, 4);
            constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            nesting = std::bernoulli_distribution(0.75);
            svariable = std::uniform_int_distribution<>(0, S - 1);
            randon_node = std::uniform_int_distribution<>(1, 3);//operacion,variable,constante
        }
    };

    template<core::index auto S,core::number N>
    static core::ast::node<>* create_oper()
    {
        int opr = Arithmetic<S,N>::operation(Arithmetic<S,N>::generator);
        bool netsa = Arithmetic<S,N>::nesting(Arithmetic<S,N>::generator);
        bool netsb = Arithmetic<S,N>::nesting(Arithmetic<S,N>::generator);

        switch(opr)
        {
            case 1:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                break;
            case 2:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                break;
            case 3:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                break;
            case 4:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                break;
        }

            return NULL;
    }

    //template<core::index auto S = 1,core::number N = float> std::random_device Arithmetic<S<N>::rd;

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<class T,core::number N>
    struct Town : public core::array<T>
    {
    public:
        typedef  core::array<T> TOWN_BASE;

    public:
        Town() = default;
        Town(size_t s) : TOWN_BASE(s),auto_free(true)
        {
        }

        void populate(size_t s)
        {
            this->resize(s);
            for(size_t i = 0; i < s; i++)
            {
                this->operator[](i) = new T(T::create_node(),true);
            }
        }

    public:
        bool auto_free;
    };



    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N>
    struct City : public core::array<Town<T,N>>
    {
    public:
        typedef core::array<Town<T,N>> CITY_BASE;

    public:
        City() = default;
        City(size_t s) : CITY_BASE(s)
        {
        }
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N>
    struct State : public core::array<City<T,N>>
    {
    public:
        typedef core::array<City<T,N>> STATE_BASE;

    public:
        State() = default;
        State(size_t s) : STATE_BASE(s)
        {
        }
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T,core::number N>
    struct Country : public core::array<State<T,N>>
    {
    public:
        typedef core::array<State<T,N>> COUNTRY_BASE;

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
