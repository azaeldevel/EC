#ifndef OCTETOS_EC_V1_EC_HH_INCLUDED
#define OCTETOS_EC_V1_EC_HH_INCLUDED

#include <core/3/array.hh>


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
        virtual N evaluate() const = 0;
    };

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<class T>
    struct Town : public core::array<T>
    {
    public:
        typedef  core::array<T> TOWN_BASE;

    public:
        Town() = default;


        virtual void evaluate()
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                std::cout << "evaluate : ";
                std::cout << this->operator[](i).evaluate();
                std::cout << "\n";
            }
        }


    public:
        bool auto_free;
    };

    /**
    *\brief Es el conjunto de Pueblos
    */
    template<class T>
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

}

#endif // EC_HH_INCLUDED
