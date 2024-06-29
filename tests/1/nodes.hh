
#ifndef OCTETOS_CORE_V3_NODES_HH
#define OCTETOS_CORE_V3_NODES_HH

/**
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

#include <vector>

#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3
{

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class node
    {
    private:
    public:
        node() = default;
        virtual ~node() = default;

        virtual operator T() const = 0;
    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Node : public std::vector<node<T>*>,public node<T>
    {
    private:
        typedef std::vector<node<T>*> BASE;
    private:

    public:
        Node() = default;
        Node(size_t s) : BASE(s)
        {
        }
        virtual ~Node() = default;

    };


    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Number : public node<T>
    {
    private:
        T number;
    public:
        Number() = default;
        Number(const T& n) : number(n)
        {
        }
        virtual ~Number() = default;

        virtual operator T() const
        {
            return number;
        }
        Number& operator =(const T& n)
        {
            number = n;
            return *this;
        }
    };


    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class operation : public Node<T>
    {
    private:
        typedef Node<T> BASE;

    public:
        operation() = default;
        operation(node<T>& a,node<T>& b) : BASE(2)
        {
            BASE::at(0) = &a;
            BASE::at(1) = &b;
        }
        virtual ~operation() = default;
        void set(node<T>& a,node<T>& b)
        {
            if(BASE::size() != 2) BASE::resize(2);
            BASE::at(0) = &a;
            BASE::at(1) = &b;
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Addition : public operation<T>
    {
    private:
        typedef operation<T> BASE;

    public:
        Addition() = default;
        Addition(node<T>& a,node<T>& b) : BASE(a,b)
        {
        }
        virtual ~Addition() = default;

        virtual operator T() const
        {
            return T(*BASE::at(0)) + T(*BASE::at(1));
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Subtration : public operation<T>
    {
    private:
        typedef operation<T> BASE;

    public:
        Subtration() = default;
        Subtration(node<T>& a,node<T>& b) : BASE(a,b)
        {
        }
        virtual ~Subtration() = default;

        virtual operator T() const
        {
            return T(*BASE::at(0)) - T(*BASE::at(1));
        }
    };


}

#endif
