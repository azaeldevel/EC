

#ifndef EC_PROGRAM_HH
#define EC_PROGRAM_HH

#include <list>
#include <vector>

#include "ec.hh"


namespace oct::ec::prog::ops
{
    template<typename T> class Operation : public std::vector<T>
    {
    public:
        Operation(unsigned int ops) : std::vector<T>(ops)
        {
        }

        virtual operator T() const = 0;
    };

    template<typename T> class Plus : public Operation<T>
    {
    public:
        Plus(const T& a, const T& b) : Operation<T>(2)
        {
            std::vector<T>::at(0) = a;
            std::vector<T>::at(1) = b;
        }

        virtual operator T() const
        {
            return std::vector<T>::front() + std::vector<T>::back();
        }
    };
    template<typename T> class Rest : public Operation<T>
    {
    public:
        Rest(const T& a, const T& b) : Operation<T>(2)
        {
            std::vector<T>::at(0) = a;
            std::vector<T>::at(1) = b;
        }

        virtual operator T() const
        {
            return std::vector<T>::front() - std::vector<T>::back();
        }
    };

}
namespace oct::ec::prog::expr
{
    template<typename T> class Operation : public std::vector<ops::Operation<T>*>
    {
    public:
        Operation(unsigned int ops) : std::vector<ops::Operation<T>*>(ops)
        {
        }

        virtual operator T() const = 0;
    };

    template<typename T> class Plus : public Operation<T>
    {
    public:
        Plus(ops::Operation<T>& a, ops::Operation<T>& b) : Operation<T>(2)
        {
            std::vector<ops::Operation<T>*>::at(0) = &a;
            std::vector<ops::Operation<T>*>::at(1) = &b;
        }

        virtual operator T() const
        {
            return *std::vector<ops::Operation<T>*>::front() + *std::vector<ops::Operation<T>*>::back();
        }
    };
    template<typename T> class Rest : public Operation<T>
    {
    public:
        Rest(ops::Operation<T>& a, ops::Operation<T>& b) : Operation<T>(2)
        {
            std::vector<ops::Operation<T>*>::at(0) = &a;
            std::vector<ops::Operation<T>*>::at(1) = &b;
        }

        virtual operator T() const
        {
            return *std::vector<ops::Operation<T>*>::front() - *std::vector<ops::Operation<T>*>::back();
        }
    };

}
#endif
