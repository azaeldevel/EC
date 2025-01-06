#ifndef OCTETOS_EC_V1_MATH_HH_INCLUDED
#define OCTETOS_EC_V1_MATH_HH_INCLUDED

#include "ec.hh"
#include <core/3/ast-math.hh>
#include <core/3/table.hh>
#include <random>

namespace oct::ec::v1
{
    template<typename T,core::index auto C = 0,core::index auto R = 0,core::index I = size_t> using inputs = core::table<T,C,R,I>;

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
            node = rand_node();
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
                n = static_cast<core::ast::Number<N>*>(node)->result();
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
                node = new core::ast::Variable<N>(svariable(generator));
                break;
            case 3:
                node = new core::ast::Number<N>(constant(generator));
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
                a = new core::ast::Variable<N>(svariable(generator));
            }
            else
            {
                a = new core::ast::Number<N>(constant(generator));
            }

            core::ast::node<>* b;
            if(nesting(generator))
            {
                b = new core::ast::Variable<N>(svariable(generator));
            }
            else
            {
                b = new core::ast::Number<N>(constant(generator));
            }

            return new core::ast::Binopr<N>(core::ast::typen(opr),a,b);
        }

        void inheritance_number_simple_constant_operatio(core::ast::Number<N>* n)
        {
            int opr = operation(generator);
            opr = opr + ((int)core::ast::typen::arithmetic);
            core::ast::typen type = core::ast::typen(opr);
            switch(node->type)
            {
                case core::ast::typen::addition:
                    n->data += constant(generator);
                    break;
                case core::ast::typen::subtraction:
                    n->data -= constant(generator);
                    break;
                case core::ast::typen::product:
                    n->data *= constant(generator);
                    break;
                case core::ast::typen::quotient:
                    n->data /= constant(generator);
                    break;
                default:
                    break;
            }
        }
        void inheritance_number_media(core::ast::Number<N>* n, core::ast::Number<N>* o,core::ast::Number<N>* p)
        {
            int opr = operation_puls_1(generator);
            opr = opr + ((int)core::ast::typen::arithmetic);
            core::ast::typen type = core::ast::typen(opr);
            switch(node->type)
            {
                case core::ast::typen::addition:
                    n->data += (o->data+p->data)/N(2);
                    break;
                case core::ast::typen::subtraction:
                    n->data -= (o->data+p->data)/N(2);
                    break;
                case core::ast::typen::product:
                    n->data *= (o->data+p->data)/N(2);
                    break;
                case core::ast::typen::quotient:
                    n->data /= (o->data+p->data)/N(2);
                    break;
                default:
                    n->data = (o->data+p->data)/N(2);
                    break;
            }
        }

        void from(const Binopr& o,const Binopr& p)
        {
            //Aseguira que puede encontrar una constante
            if(o.node->is_number() and p.node->is_number())
            {
                if(binary_selection(generator))
                {
                    node = copy<N>(o.node);
                }
                else
                {
                    node = copy<N>(p.node);
                }
                auto number = static_cast<core::ast::Number<N>*>(node);
                if(binary_selection(generator))
                {
                    inheritance_number_simple_constant_operatio(number);
                }
                else
                {
                    inheritance_number_media(number,static_cast<core::ast::Number<N>*>(o->node),static_cast<core::ast::Number<N>*>(p->node));
                }
                return;
            }
            else
            {
                if(o.node->is_number())
                {
                    node = copy<N>(o.node);
                    auto number = static_cast<core::ast::Number<N>*>(node);
                    if(binary_selection(generator))
                    {
                        inheritance_number_simple_constant_operatio(number);
                    }
                    else
                    {
                        inheritance_number_media(number,static_cast<core::ast::Number<N>*>(o->node),static_cast<core::ast::Number<N>*>(p->node));
                    }
                    return;
                }
                if(p.node->is_number())
                {
                    node = copy<N>(p.node);
                    auto number = static_cast<core::ast::Number<N>*>(node);
                    inheritance_number_simple_constant_operatio(number);
                    if(binary_selection(generator))
                    {
                        inheritance_number_simple_constant_operatio(number);
                    }
                    else
                    {
                        inheritance_number_media(number,static_cast<core::ast::Number<N>*>(o->node),static_cast<core::ast::Number<N>*>(p->node));
                    }
                return;
                }
            }

            //
            if(binary_selection(generator))
            {
                node = copy<N>(o.node);
            }
            else
            {
                node = copy<N>(p.node);
            }

            //Asegurar que puede contrar una funcion lineal

            //Aegurar otras formas
        }


        void copy_constant(const Binopr& o)
        {

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
        static inline std::uniform_int_distribution<> operation_puls_1;

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
            operation_puls_1 = std::uniform_int_distribution<>(1, 5);
        }
    };


    /**
    *\brief Una purblo es el conjunto minimo de poblacion posible
    */
    template<core::index auto S,core::number N,class T>
    struct BinoprTown : public Town<N,T>
    {
    public:
        typedef  Town<N,T> ARTTOWN_BASE;

    public:
        BinoprTown() = default;
        ~BinoprTown()
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

        void populate(size_t s, const inputs<N,S>& vs)
        {
            this->auto_free = true;
            this->resize(s);
            for(size_t i = 0; i < s; i++)
            {
                this->operator[](i) = new T(vs);
            }
        }

    public:
    };

}

#endif // EC_HH_INCLUDED
