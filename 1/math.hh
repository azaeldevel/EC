#ifndef OCTETOS_EC_V1_MATH_HH_INCLUDED
#define OCTETOS_EC_V1_MATH_HH_INCLUDED

#include "ec.hh"
#include <core/3/ast.hh>
#include <random>

namespace oct::ec::v1
{
    /**
    *\brief Representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::index auto S,core::number N>
    struct Arithmetic : public Single<N>
    {
    public:
        typedef Single<N> SINGLE_BASE;

    public:
        Arithmetic() = default;
        Arithmetic(const Arithmetic& o) : auto_free(o.auto_free),node(NULL),variables(NULL)
        {
            if(o.auto_free)
            {
                node = NULL;
                auto_free = false;
                throw core::exception("Se esta copiando on objeto com memoria en heap, no es posible continuar la operacion");
            }
            node = o.node;
            auto_free = o.auto_free;
            variables = o.variables;
        }
        Arithmetic(Arithmetic&& o) : auto_free(o.auto_free),node(o.node),variables(o.variables)
        {
            o.node = NULL;
            o.auto_free = false;
            o.variables = NULL;
        }
        Arithmetic(core::ast::Variable<N> (&vs)[S]) : auto_free(true),node(NULL),variables(&vs)
        {
            this->rand_op();
        }
        virtual ~Arithmetic()
        {
            if(auto_free and node)
            {
                delete node;
                node = NULL;
                variables = NULL;
                auto_free = false;
            }
        }

        Arithmetic& operator =(const Arithmetic& o)
        {
            if(o.auto_free)
            {
                node = NULL;
                auto_free = false;
                throw core::exception("Se esta copiando on objeto com memoria en heap, no es posible continuar la operacion");
            }
            node = o.node;
            auto_free = o.auto_free;
            variables = o.variables;

            return *this;
        }
        Arithmetic& operator =(Arithmetic&& o)
        {
            //
            node = o.node;
            auto_free = o.auto_free;
            variables = o.variables;
            //
            o.node = NULL;
            o.auto_free = false;
            o.variables = NULL;
            //std::cout << "Asignacion de movimiento realizada...\n";

            return *this;
        }

    public:
        virtual N evaluate() const
        {
            N n;

            switch(node->type)
            {
            case core::ast::typen::addition:
            case core::ast::typen::subtraction:
            case core::ast::typen::product:
            case core::ast::typen::quotient:
                n = static_cast<core::ast::Arithmetic<N>*>(node)->result();
                break;
            case core::ast::typen::number:
                n = static_cast<core::ast::Numeric<N>*>(node)->result();
                break;
            case core::ast::typen::variable:
                n = static_cast<core::ast::Variable<N>*>(node)->result();
                break;
            default:
                break;
            }
            N value = (*variables)[0].data * (*variables)[1].data;
            //std::cout << "value = " << value << "\n";
            N eval = N(1)/std::abs(value - n);

            return eval;
        }

        void rand_node()
        {
            switch(randon_node(generator))
            {
            case 1:
                node = rand_op();
                break;
            case 2:
                node = (*variables)[svariable(generator)];
                break;
            case 3:
                node = new core::ast::Numeric<N>(constant(generator));
                break;
            default:
                node = rand_op();
                break;
            }
        }
        void rand_op()
        {
            int opr = operation(generator);
            opr = opr + ((int)core::ast::typen::arithmetic);

            core::ast::Numeric<N>* a;
            if(nesting(generator))
            {
                a = &(*variables)[svariable(generator)];
            }
            else
            {
                a = new core::ast::Numeric<N>(constant(generator));
            }

            core::ast::Numeric<N>* b;
            if(nesting(generator))
            {
                b = &(*variables)[svariable(generator)];
            }
            else
            {
                b = new core::ast::Numeric<N>(constant(generator));
            }

            node = new core::ast::Arithmetic<N>(core::ast::typen(opr),a,b);
        }

        Arithmetic& pair(const Arithmetic& o)
        {

        }

    public:
        bool auto_free;
        core::ast::Variable<N> (*variables)[S];

    public://genes
        core::ast::node<>* node;
        unsigned width;//ancho del arbol
        unsigned high;//profundidad del arbol
        N mutability;

    public:

    public:
        static inline std::random_device rd;
        static inline std::mt19937 generator;
        static inline std::uniform_int_distribution<> operation;
        static inline std::uniform_real_distribution<> constant;
        static inline std::bernoulli_distribution nesting;
        static inline std::uniform_int_distribution<> svariable;
        static inline std::uniform_int_distribution<> randon_node;

        static void init_randsys()
        {
            generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            operation = std::uniform_int_distribution<>(1, 4);
            constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            nesting = std::bernoulli_distribution(0.75);
            svariable = std::uniform_int_distribution<>(0, S - 1);
            randon_node = std::uniform_int_distribution<>(1, 3);//operacion,variable,constante
        }
    };

    template<core::index auto S,core::number N>
    static core::ast::node<>* create_oper()
    {
        int opr = Arithmetic<S,N>::operation(Arithmetic<S,N>::generator);
        bool netsa = Arithmetic<S,N>::nesting(Arithmetic<S,N>::generator);
        bool netsb = Arithmetic<S,N>::nesting(Arithmetic<S,N>::generator);

        switch(opr)
        {
            case 1:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::addition,da,db);
                }
                break;
            case 2:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::subtraction,da,db);
                }
                break;
            case 3:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::product,da,db);
                }
                break;
            case 4:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Arithmetic<S,N>::constant(Arithmetic<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Arithmetic<N>(core::ast::typen::quotient,da,db);
                }
                break;
        }

        return NULL;
    }


    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<class T,core::number N>
    struct ArithmeticTown : public Town<T>
    {
    public:
        typedef  Town<T> ARTTOWN_BASE;

    public:
        ArithmeticTown() = default;

        template<core::index auto S>
        void populate(size_t s, core::ast::Variable<N> (&vs)[S])
        {
            auto_free = true;
            this->resize(s);
            for(size_t i = 0; i < s; i++)
            {
                this->operator[](i) =  T(vs);
            }
        }

    public:
        bool auto_free;
    };

}

#endif // EC_HH_INCLUDED
