#ifndef OCTETOS_EC_V1_MATH_HH_INCLUDED
#define OCTETOS_EC_V1_MATH_HH_INCLUDED

#include "ec.hh"
#include <core/3/ast.hh>
#include <core/3/table.hh>
#include <random>

namespace oct::ec::v1
{
    template<typename T,core::index auto C = 0,core::index auto R = 0,core::index I = size_t> using inputs = core::table<T,C,R,I>;

    /**
    *\brief Indica una variable(columna) en la tabla de inputs
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<core::number N,class T = core::ast::typen> struct Variable : public core::ast::node<T>
    {
    public:
        typedef core::ast::node<T> NUMERIC_NODE;

    public:
        Variable() : NUMERIC_NODE(T::variable)
        {
        }
        Variable(const Variable& o) : NUMERIC_NODE(o)
        {
        }
        Variable(const Variable* o) : NUMERIC_NODE(o)
        {
        }
        Variable(T t) : NUMERIC_NODE(t)
        {
        }
        Variable(size_t d) : NUMERIC_NODE(T::variable,d)
        {
        }
        Variable(const char* n) : NUMERIC_NODE(T::variable),name(n)
        {
        }
        Variable(const std::string& n) : NUMERIC_NODE(T::variable),name(n)
        {
        }
        Variable(const std::string& n,size_t d) : NUMERIC_NODE(T::variable,d),name(n)
        {
        }
        virtual ~Variable()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case T::variable:
                out << name;
                break;
            default:
                out << "variable-desconocido";
            }
        }
        template<core::index auto S = 1>
        void print(std::ostream& out,const inputs<N,S>& ins) const
        {
            switch(this->type)
            {
            case T::variable:
                out << name;
                break;
            default:
                out << "variable-desconocido";
            }
        }

        operator size_t()const
        {
            return index;
        }
        Variable& operator = (size_t i)
        {
            index = i;

            return *this;
        }

    public:
        std::string name;
        size_t index;//dato input
    };


    /**
    *\brief Representa un individuo
    *\param N tipo de dato usado para calculos
    */
    template<core::index auto S,core::number N>
    struct Binopr : public Single<N>
    {
    public:
        typedef Single<N> SINGLE_BASE;

    public:
        Binopr() = default;
        Binopr(const Binopr& o) : auto_free(o.auto_free),variables(NULL),node(NULL)
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
        Binopr(Binopr&& o) : auto_free(o.auto_free),variables(o.variables),node(o.node)
        {
            o.node = NULL;
            o.auto_free = false;
            o.variables = NULL;
        }
        Binopr(const inputs<N,S>& ins) : auto_free(true),variables(&ins),node(NULL)
        {
            node = rand_op();
        }
        virtual ~Binopr()
        {
            if(auto_free and node)
            {
                delete node;
                node = NULL;
                variables = NULL;
                auto_free = false;
            }
        }

        Binopr& operator =(const Binopr& o)
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
        Binopr& operator =(Binopr&& o)
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
                n = static_cast<core::ast::Binopr<N>*>(node)->result();
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
            N value = (*variables)[0][0] * (*variables)[0][1];
            //std::cout << "value = " << value << "\n";
            N eval = N(1)/std::abs(value - n);

            return eval;
        }

        static core::ast::node<>* rand_node()
        {
            core::ast::node<>* node;
            switch(randon_node(generator))
            {
            case 1:
                node = rand_op();
                break;
            case 2:
                node = new Variable<N>;
                break;
            case 3:
                node = new core::ast::Numeric<N>(constant(generator));
                break;
            default:
                node = rand_op();
                break;
            }

            return node;
        }


        static core::ast::node<>* rand_op()
        {
            int opr = operation(generator);
            opr = opr + ((int)core::ast::typen::arithmetic);

            core::ast::node<>* a;
            if(nesting(generator))
            {
                a = new Variable<N>;
            }
            else
            {
                a = new core::ast::Numeric<N>(constant(generator));
            }

            core::ast::node<>* b;
            if(nesting(generator))
            {
                b = new Variable<N>;
            }
            else
            {
                b = new core::ast::Numeric<N>(constant(generator));
            }

            return new core::ast::Binopr<N>(core::ast::typen(opr),a,b);
        }

        void from(const Binopr& o,const Binopr& p)
        {
        }


        void partial_copy(const Binopr& o,const Binopr& p)
        {
            if(binary_selection(generator))
            {//coopiar o

            }
            else
            {//copiar p

            }
        }



    public:
        bool auto_free;
        const inputs<N,S>* variables;

    public://genes
        core::ast::node<>* node;
        unsigned width;//ancho del arbol
        unsigned high;//profundidad del arbol


    public:

    public:
        static inline std::random_device rd;
        static inline std::mt19937 generator;
        static inline std::uniform_int_distribution<> operation;
        static inline std::uniform_real_distribution<> constant;
        static inline std::bernoulli_distribution nesting;
        static inline std::uniform_int_distribution<> svariable;
        static inline std::uniform_int_distribution<> randon_node;
        static inline std::bernoulli_distribution mutability;
        static inline std::bernoulli_distribution binary_selection;

        static void init_randsys()
        {
            generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            operation = std::uniform_int_distribution<>(1, 4);
            constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            nesting = std::bernoulli_distribution(0.75);
            svariable = std::uniform_int_distribution<>(0, S - 1);
            randon_node = std::uniform_int_distribution<>(1, 3);//operacion,variable,constante
            mutability = std::bernoulli_distribution(0.02);
            binary_selection = std::bernoulli_distribution(0.5);
        }
    };

    template<core::index auto S,core::number N>
    static core::ast::node<>* create_oper()
    {
        int opr = Binopr<S,N>::operation(Binopr<S,N>::generator);
        bool netsa = Binopr<S,N>::nesting(Binopr<S,N>::generator);
        bool netsb = Binopr<S,N>::nesting(Binopr<S,N>::generator);

        switch(opr)
        {
            case 1:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::addition,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::addition,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::addition,da,db);
                }
                break;
            case 2:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::subtraction,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::subtraction,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::subtraction,da,db);
                }
                break;
            case 3:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::product,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::product,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::product,da,db);
                }
                break;
            case 4:
                if(netsa and netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::quotient,da,db);
                }
                else if(netsa and !netsb)
                {
                    core::ast::Variable<N>* da = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Variable<N>* db = new core::ast::Variable<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::quotient,da,db);
                }
                else if(!netsa and !netsb)
                {
                    core::ast::Numeric<N>* da = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    core::ast::Numeric<N>* db = new core::ast::Numeric<N>(Binopr<S,N>::constant(Binopr<S,N>::generator));
                    return (core::ast::node<>*) new core::ast::Binopr<N>(core::ast::typen::quotient,da,db);
                }
                break;
        }

        return NULL;
    }


    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<class T,core::number N>
    struct BinoprTown : public Town<T>
    {
    public:
        typedef  Town<T> ARTTOWN_BASE;

    public:
        BinoprTown() = default;

        template<core::index auto S>
        void populate(size_t s, const inputs<N,S>& vs)
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
