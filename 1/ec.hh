#ifndef OCTETOS_EC_V1_EC_HH_INCLUDED
#define OCTETOS_EC_V1_EC_HH_INCLUDED

#include <core/3/array.hh>
#include <map>
#include <functional>
#include <bits/stdc++.h>



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

    public:
        N ranking;
    };

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<core::number N, class T>
    struct Town : public core::array<T*>
    {
    public:
        typedef  core::array<T*> TOWN_BASE;

    public:
        Town() = default;


        virtual void evaluate()
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                this->operator[](i)->ranking = this->operator[](i)->evaluate();
            }
            /*for(size_t i = 0; i < this->size(); i++)
            {
                std::cout << "evaluate : ";
                std::cout << this->operator[](i)->ranking;
                std::cout << "\n";
            }*/
            auto cmpfun = [](T* a,T* b)
            {
                return  a->ranking > b->ranking;
            };
            std::sort(this->begin(),this->end(),cmpfun);
            for(size_t i = 0; i < this->size(); i++)
            {
                std::cout << "evaluate : ";
                std::cout << this->operator[](i)->ranking;
                std::cout << "\n";
            }
        }


    public:
        bool auto_free;
    };


}

#endif // EC_HH_INCLUDED
