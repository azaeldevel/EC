

#ifndef EC_PROGRAM_HH
#define EC_PROGRAM_HH

#include <list>
#include <vector>

#include "ec.hh"


namespace oct::ec::prog
{
    template<typename T> class Tree;


    enum OP
    {
        PLUS,
        REST,
        MULT,
        DIV,
    };
    template<typename T> class Node
    {
    private:
        enum Type
        {
            NONE,
            DATA,
            NODE,
            OPER,
        };

    public:
        Node(const T& d)
        {
            element.data = d;
            type = DATA;
        }
        Node(OP op)
        {
            element.op = op;
            type = OPER;
        }
        Node(const Tree<T>& n)
        {
            element.tree = &n;
            type = NODE;
        }

        Type get_type() const
        {
            return type;
        }

        Node<T>& operator =(const T& d)
        {
            element.data = d;
            type = DATA;
            return *this;
        }
        Node<T>& operator =(OP op)
        {
            element.op = op;
            type = OPER;
            return *this;
        }
        Node<T>& operator =(const Tree<T>& t)
        {
            element.tree = &t;
            type = NODE;
            return *this;
        }

    private:
        union Element
        {
            T data;
            OP op;
            const Tree<T>* tree;
        };

        Element element;
        Type type;
    };

    template<typename T> class Tree : std::list<Node<T>>
	{
    public:
        void push_back(const T& d);
        void push_back(const Tree<T>& t)
        {
            std::list<Node<T>>::push_back(&t);
        }
        void push_back (OP op)
        {
            std::list<Node<T>>::push_back(op);
        }

    };


    template<typename T> class Plus : protected std::vector<T>
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
    template<typename T> class Rest : protected std::vector<T>
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



	template<typename T> class Expresion : public Tree<T>
	{
    public:
        operator T()const
        {
            T value = T(0);
            for(const Node<T>& node: *this)
            {
                /*switch()
                {
                case NONE:

                    break;
                case DATA:

                    break;
                case NODE:

                    break;
                case OPER:

                    break;
                }*/
            }
        }
    private:
    };

}

#endif
