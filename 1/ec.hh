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
    template<core::index auto S = 1,core::number N = float>
    struct Arithmetic : public Single<N>
    {
    public:
        typedef Single<N> SINGLE_BASE;

    public:
        Arithmetic() = default;
        Arithmetic(core::ast::node<N>& nin) : node(nin),auto_free(false)
        {
        }
        Arithmetic(core::ast::node<N>* nin) : node(nin),auto_free(false)
        {
        }
        Arithmetic(core::ast::node<N>* nin,bool free) : node(nin),auto_free(free)
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


        static core::ast::node<N>* create_node(std::mt19937& generator,std::uniform_int_distribution<>& operation,std::bernoulli_distribution  nesting,std::uniform_real_distribution<>& constant,std::uniform_int_distribution<>& svar)
        {
            int opr = operation(generator);
            bool netsa = nesting(generator);
            bool netsb = nesting(generator);

            switch(opr)
            {
            case 1:
                if(netsa and netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::quotient,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::product,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::quotient,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                break;
            case 2:
                if(netsa and netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::subtraction,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::product,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                break;
            case 3:
                if(netsa and netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::quotient,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::subtraction,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                break;
            case 4:
                if(netsa and netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::quotient,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::product,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Arithmetic<N>* da = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Arithmetic<N>* db = new core::ast::Arithmetic<N>(core::ast::typen::addition,new core::ast::Numeric<N>(constant(generator)),new core::ast::Numeric<N>(constant(generator)));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(constant(generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(constant(generator));
                    return (core::ast::node<N>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                break;
            case 5:
                return (core::ast::node<N>*) new core::ast::Numeric<N>(constant(generator));
            case 6:
                return NULL;//(core::ast::node<N>*) &varaibles[svar(generator)]
            }

            return NULL;
        }

    public:
        core::ast::node<N>* node;
        bool auto_free;

    public:
        core::ast::Numeric<N> varaibles[S];

    public:
        static inline std::random_device rd;
        static inline std::mt19937 generator = std::mt19937(rd());
        static inline std::uniform_int_distribution<> operation = std::uniform_int_distribution<>(1, 6);
        static inline std::uniform_real_distribution<> constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
        static inline std::bernoulli_distribution nesteing = std::bernoulli_distribution(0.75);
        static inline std::uniform_int_distribution<> svariable = std::uniform_int_distribution<>(1, S);

        static void init_randsys()
        {
            //rd = std::random_device("una prueva interesantes....");
            //generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            //operation = std::uniform_int_distribution<>(1, 6);
            //constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            //nesteing = std::bernoulli_distribution(0.75);
            //svariable = std::uniform_int_distribution<>(1, 3);
        }
    };


    //template<core::index auto S = 1,core::number N = float> std::random_device Arithmetic<S<N>::rd;

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
        Town(size_t s) : TOWN_BASE(s),auto_free(true)
        {
        }

        void populate(size_t s)
        {
            this->resize(s);
            for(size_t i = 0; i < s; i++)
            {

            }
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
