

#ifndef EC_PROGRAM_HH
#define EC_PROGRAM_HH

#include <list>
#include <vector>

#include "ec.hh"


namespace oct::ec::prog
{

    template<typename T> class Plus : public std::vector<T>
    {
    public:
        Plus(const T& a, const T& b) : std::vector<T>(2)
        {
            std::vector<T>::at(0) = a;
            std::vector<T>::at(1) = b;
        }

        operator T()
        {
            return std::vector<T>::front() + std::vector<T>::back();
        }
    };
    template<typename T> class Rest : public std::vector<T>
    {
    public:
        Rest(const T& a, const T& b) : std::vector<T>(2)
        {
            std::vector<T>::at(0) = a;
            std::vector<T>::at(1) = b;
        }

        operator T()
        {
            return std::vector<T>::front() - std::vector<T>::back();
        }
    };

    template<typename T> class Expresion : public std::list<std::vector<T>>
    {
    public:

        operator T()
        {

        }
    };



}

#endif
