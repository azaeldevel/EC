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
        typedef N (*evaluator)(const inputs<N,S>*);

    public:
        Binopr() = default;
        Binopr(const Binopr& o) : auto_free(o.auto_free),variables(NULL),node(NULL),evalr_actual(NULL)
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
            evalr_actual = o.evalr_actual;
        }
        Binopr(Binopr&& o) : auto_free(o.auto_free),variables(o.variables),node(o.node),evalr_actual(o.evalr_actual)
        {
            o.node = NULL;
            o.auto_free = false;
            o.variables = NULL;
        }
        Binopr(const inputs<N,S>& ins,evaluator evalr) : auto_free(true),variables(&ins),node(NULL),evalr_actual(evalr)
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

        static N eval_constant(const inputs<N,S>* vars)
        {
            return (*vars)[1][1];
        }

    public:
        virtual N evaluate() const
        {
            N rest;

            switch(node->type)
            {
            case core::ast::typen::addition:
            case core::ast::typen::subtraction:
            case core::ast::typen::product:
            case core::ast::typen::quotient:
                rest = static_cast<core::ast::Binopr<N>*>(node)->result();
                break;
            case core::ast::typen::number:
                rest = static_cast<core::ast::Number<N>*>(node)->result();
                break;
            case core::ast::typen::variable:
                rest = static_cast<core::ast::Variable<N>*>(node)->result();
                break;
            default:
                break;
            }


            N value = evalr_actual(variables);
            //std::cout << "value = " << value << "\n";
            N eval;
            if(std::isnan(rest))
            {
                eval = 0;
            }
            else if(std::isinf(rest))
            {
                eval = 0;
            }
            else if(core::equal(rest,value))
            {
                eval = N(1);
            }
            else if(core::equal(value,N(0.0)))
            {
                eval = rest/std::numeric_limits<N>::max();
            }
            else if(core::equal(rest,N(0.0)))
            {
                eval = value/std::numeric_limits<N>::max();//ya se
            }
            else
            {
                eval = (value - rest)/std::numeric_limits<N>::max();
            }

            if(core::diff(eval,N(0.0)))
            {
                eval = N(1)/eval;
            }

            return std::abs(eval);
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

        virtual void print(std::ostream& out) const
        {
            switch(node->type)
            {
            case core::ast::typen::addition:
            case core::ast::typen::subtraction:
            case core::ast::typen::product:
            case core::ast::typen::quotient:
                static_cast<const core::ast::Binopr<N>*>(node)->print(out);
                break;
            case core::ast::typen::nest:
                static_cast<const core::ast::Nest<N>*>(node)->print(out);
                break;
            case core::ast::typen::number:
                static_cast<const core::ast::Number<N>*>(node)->print(out);
                break;
            case core::ast::typen::variable:
                static_cast<const core::ast::Variable<>*>(node)->print(out);
                break;
            default:
                break;
            }
        }



    public:
        bool auto_free;
        const inputs<N,S>* variables;
        evaluator evalr_actual;

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
        static inline std::fisher_f_distribution<N> selection_firts_pair;
        static inline std::uniform_int_distribution<> selection_second_pair;
        static inline unsigned population_size;

        static void init_randsys(unsigned size)
        {
            population_size = size;
            int barrera = population_size/10;
            std::setprecision(10);
            generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            operation = std::uniform_int_distribution<>(1, 4);
            constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            nesting = std::bernoulli_distribution(0.75);
            svariable = std::uniform_int_distribution<>(0, S - 1);
            randon_node = std::uniform_int_distribution<>(1, 3);//operacion,variable,constante
            mutability = std::bernoulli_distribution(0.02);
            binary_selection = std::bernoulli_distribution(0.5);
            operation_puls_1 = std::uniform_int_distribution<>(1, 5);
            selection_firts_pair = std::fisher_f_distribution<N>(1,barrera);
            selection_second_pair = std::uniform_int_distribution<>(1,population_size);
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
        virtual ~BinoprTown()
        {
        }

        void populate_random(const inputs<N,S>& vs)
        {
            this->auto_free = true;
            this->resize(T::population_size/10);
            for(size_t i = 0; i < this->size(); i++)
            {
                this->operator[](i) = new T(vs,T::eval_constant);
            }
        }
        virtual void evaluate()
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                this->operator[](i)->ranking = this->operator[](i)->evaluate();
            }
            auto cmpfun = [](T* a,T* b)
            {
                return  a->ranking > b->ranking;
            };
            std::sort(this->begin(),this->end(),cmpfun);
        }

        virtual void print(std::ostream& out) const
        {
            std::cout << "objetivo : ";
            std::cout << this->operator[](0)->evalr_actual(this->operator[](0)->variables);
            std::cout << "\n";
            for(size_t i = 0; i < this->size(); i++)
            {
                std::cout << i << "\t";
                std::cout << "evaluacion : ";
                std::cout << this->operator[](i)->ranking;
                std::cout << "\texpresion : ";
                this->operator[](i)->print(std::cout);
                std::cout << "\n";
            }
        }

        virtual core::array<size_t,2> select_pair_with_comunal()const
        {
            core::array<size_t,2> rest;
            rest[0] = (size_t)T::selection_firts_pair(T::generator);
            rest[1] = T::selection_second_pair(T::generator);
            if(rest[0] == rest[1])//asegurar que no son iguales
            {
                rest[1] = T::selection_second_pair(T::generator);
            }
            if(rest[0] == rest[1])//asegurar que no son iguales
            {
                rest[1] = T::selection_second_pair(T::generator);
            }
            if(rest[0] == rest[1])//asegurar que no son iguales
            {
                rest[0] = (size_t)T::selection_firts_pair(T::generator);
                rest[1] = T::selection_second_pair(T::generator);
            }

            return rest;
        }
        virtual void pair()
        {
            core::array<size_t,2> selectd = select_pair_with_comunal();
            std::cout << "Aparear : " << selectd[0] << " --> " << selectd[1] << "\n";
        }

    public:
    };

}

#endif // EC_HH_INCLUDED
