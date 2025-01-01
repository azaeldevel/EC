#ifndef OCTETOS_EC_V1_HH_INCLUDED
#define OCTETOS_EC_V1_HH_INCLUDED

#include <core/3/array.hh>
#include <core/3/ast.hh>
#include <random>

namespace oct::ec::v1
{
    namespace core = oct::core::v3;

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
    template<core::number N = float>
    struct Arithmetic : public Single<N>
    {
    public:
        typedef Single<N> SINGLE_BASE;

    public:
        Arithmetic() = default;
        Arithmetic(const core::ast::Node<>& nin) : node(nin)
        {
        }
        Arithmetic(core::ast::Node<>&& nin)
        {
        }

    public:
        virtual N evaluate() const
        {
            return 0;
        }


        static core::ast::Node<> populate_generic(std::mt19937& generator,std::uniform_int_distribution<>& operation,std::uniform_int_distribution<>& width,std::uniform_int_distribution<>& deep,std::bernoulli_distribution  nesting)
        {
            core::ast::Node<> root;
            root.resize(width(generator));
            int tree_deep = deep(generator);

            for(size_t i = 0; i < root.size(); i++)
            {
                switch(operation(generator))
                {
                case 1://suma
                    core::ast::arithmetic<float>(core::ast::typen::addition);
                    break;
                }
            }

            return root;
        }

    public:
        core::ast::Node<> node;

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
        Town(size_t s) : TOWN_BASE(s)
        {
        }
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
