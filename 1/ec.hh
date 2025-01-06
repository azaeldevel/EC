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

    /*template<core::number N, class T>
    struct TownComparer
    {
        bool operator()(N* a,N* b) const
        {
            return  *a < *b;
        }
    };*/
    /*constexpr bool cmpfun(float* a,float* b)
    {
        return  *a < *b;
    };*/
    /*struct comp
    {
        template <typename T>
        bool operator()(const T& l, const T& r) const
        {
            return *l.first < *r.first;
        }
    };*/

    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<core::number N, class T>
    struct Town : public std::map<N*,T*>
    {
    public:
        typedef  std::map<N,T> TOWN_BASE;

    public:
        Town() = default;


        virtual void evaluate()
        {
            for (auto const& o : *this)
            {
                std::cout << "evaluate : ";
                std::cout << o.second->evaluate();
                std::cout << "\n";
            }
            /*auto cmpfun = [](const auto& a,const auto& b)
            {
                return  *a < *b;
            };*/
            //std::sort(this->begin(),this->end());
        }


    public:
        bool auto_free;
    };


}

#endif // EC_HH_INCLUDED
