#ifndef OCTETOS_EC_V1_EC_HH_INCLUDED
#define OCTETOS_EC_V1_EC_HH_INCLUDED

#include <core/3/array.hh>
#include <map>
#include <functional>
#include <bits/stdc++.h>
#include <type_traits>



namespace oct::ec::v1
{
    namespace core = oct::core::v3;

    /**
    *\brief Inteface para representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::number N>
    struct Single
    {
        virtual ~Single()
        {
        }

    public:
        virtual N evaluate() const = 0;
        virtual void print(std::ostream& out) const = 0;

    public:
        N evaluation;
    };

    template<class T>
    concept single = std::is_base_of<Single<float>, T>::value;

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<core::number N, class T>
    struct Group : public core::array<T*>
    {
    public:
        typedef  core::array<T*> TOWN_BASE;

    public:
        Group() = default;
        virtual ~Group()
        {
            if(this->auto_free)
            {
                for (size_t i = 0; i < this->size();i++)
                {
                    delete this->operator[](i);
                    this->operator[](i) = NULL;
                }
                this->auto_free = false;
            }
        }

        virtual void evaluate() = 0;
        virtual void print(std::ostream& out) const = 0;
        virtual void pair() = 0;

    public:
        bool auto_free;
    };

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<core::number N, class T>
    struct Community : public core::array<Group<N,T>*>
    {
    public:
        typedef core::array<Group<N,T>*> CITY_BASE;

    public:
        Community() = default;
        virtual ~Community()
        {
            if(this->auto_free)
            {
                for (size_t i = 0; i < this->size();i++)
                {
                    delete this->operator[](i);
                    this->operator[](i) = NULL;
                }
                this->auto_free = false;
            }
        }

        virtual void evaluate() = 0;
        //virtual void print(std::ostream& out) const = 0;
        //virtual void pair() = 0;

    public:
        bool auto_free;
    };


}

#endif // EC_HH_INCLUDED
