#ifndef OCTETOS_EC_V1_HH_INCLUDED
#define OCTETOS_EC_V1_HH_INCLUDED

#include <core/3/array.hh>


namespace oct::ec::v1
{
    namespace core = oct::core::v3;

    template<core::number N = float>
    struct Single
    {

    public:
        virtual N evaluate() const
        {
            return 0;
        }
    };


    template<class T,core::number N = float>
    struct Breed : public core::array<T>
    {
    public:
        typedef  core::array<T> BREED_BASE;

    public:
        Breed() = default;
        Breed(size_t s) : BREED_BASE(s)
        {
        }
    };

    template<class T,core::number N = float>
    struct Population : public Breed<T,N>
    {
    public:
        typedef Breed<T,N> BREED_BASE;

    public:
        Population() = default;
        Population(size_t s) : BREED_BASE(s)
        {
        }

    };

}

#endif // EC_HH_INCLUDED
