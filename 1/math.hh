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
        Binopr(const Binopr& o) : auto_free(o.auto_free),variables(NULL),evalr_actual(NULL),node(NULL)
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
        Binopr(Binopr&& o) : auto_free(o.auto_free),variables(o.variables),evalr_actual(o.evalr_actual),node(o.node)
        {
            o.node = NULL;
            o.auto_free = false;
            o.variables = NULL;
        }
        /**
        *\brief Conbtructor principal
        *\param ins datos de entreda
        *\param evalr funcion de evaluacion
        *\param rand true si se asigna los genes al azar, false si se deja con basura los genes
        **/
        Binopr(const inputs<N,S>& ins,evaluator evalr,bool rand = true) : auto_free(true),variables(&ins),evalr_actual(evalr),node(NULL)
        {
            if(rand) rand_single();
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
        static N eval_constant(const inputs<N,S>* vars)
        {
            //return (*vars)[2][0];
            return std::numbers::pi;
        }
        virtual N evaluate() const
        {
            N result;
            if(!node) throw core::exception("No se ha asignado el nodo pra la expresion");

            switch(node->type)
            {
            case core::ast::typen::addition:
            case core::ast::typen::subtraction:
            case core::ast::typen::product:
            case core::ast::typen::quotient:
                result = static_cast<core::ast::Binopr<N>*>(node)->result();
                break;
            case core::ast::typen::number:
                result = static_cast<core::ast::Number<N>*>(node)->result();
                break;
            case core::ast::typen::variable:
                result = static_cast<core::ast::Variable<N>*>(node)->result();
                break;
            case core::ast::typen::nest:
                result = static_cast<core::ast::Nest<N>*>(node)->result();
                break;
            default:
                break;
            }


            N value = evalr_actual(variables);
            //std::cout << "value = " << value << "\n";
            N eval;

            if(std::isnan(result))
            {
                eval = 0;
            }
            else if(std::isinf(result))
            {
                eval = 0;
            }
            else if(core::equal(result,value))
            {
                eval = N(1);
            }
            else if(core::equal(value,N(0)) and core::equal(result,N(0)))
            {//caso inecesesario ressult es igaula value
                eval = N(1);
            }
            else if(core::equal(value,N(0)) and core::diff(result,N(0)))
            {
                if(std::abs(result) > N(1))
                {
                    eval = N(1)/result;
                }
                else
                {
                    eval = result;
                }
            }
            else if(core::diff(value,N(0)) and core::equal(result,N(0)))
            {
                if(std::abs(value) > N(1))
                {
                    eval = N(1)/value;
                }
                else
                {
                    eval = value;
                }
            }
            else if(core::diff(value,N(0)) and core::diff(result,N(0)))
            {
                N domeval = value - result;
                if(std::abs(domeval) > N(1))
                {
                    eval = N(1)/domeval;
                }
                else if(std::abs(domeval) < N(1))
                {
                    if(value > result)
                    {
                        eval = N(1) - domeval;
                    }
                    else
                    {
                        eval = N(1) + domeval;
                    }
                }
                else
                {//la diferencia es 1 o -1
                    if(value > N(0) and result > N(0))
                    {
                        eval = N(1) - (value - result);
                    }
                    else if(value > N(0) and result < N(0))
                    {
                        eval = (N(2) - (value - result))/N(2);
                    }
                    else if(value < N(0) and result > N(0))
                    {
                        eval = (N(2) - (result - value))/N(2);
                    }
                    else if(value < N(0) and result < N(0))
                    {
                        eval = N(1) + (value + result);
                    }
                    else
                    {
                        throw core::exception("Erro de logica, algun valor quedo fuera de los rango co nsiderados.");
                    }
                }
            }
            else
            {
                throw core::exception("Erro de logica, algun valor quedo fuera de los rango co nsiderados.");
            }

            if(std::abs(eval) > N(1))
            {
                std::cout << "eval -> value::result \t" << eval << " -> "  << value << " - " << result << "\n";
            }


            return eval;
        }

    public://funciones de apareo
        void rand_single()
        {
            node = rand_node();
            if(binary_selection(generator))
            {
                preference = &almost_everytime;
            }
            else
            {
                preference = &almost_never;
            }
            changeable_deep = (*preference)(generator);
            changeable_constant = (*preference)(generator);
            changeable_operations = (*preference)(generator);
            changeable_variables = (*preference)(generator);
            /*if(binary_selection(generator))
            {
                changeable_deep_increment = &almost_everytime;
            }
            else
            {
                changeable_deep_increment = &almost_never;
            }*/
            N tempval;
            for(size_t i = 0; i < 5; i++)
            {//asgura un numero (0,1)
                for(size_t j = 0; j < 3; j++)
                {
                    tempval = constant(generator);
                    if(core::diff(tempval,N(0))) break;
                }
                pivots[i] = N(1)/tempval;
            }
            for(size_t i = 4; i < 10; i++)
            {//asgura un numero mayor que 1
                for(size_t j = 0; j < 6; j++)
                {
                    tempval = constant(generator);
                    if( std::abs(tempval) > N(1)) break;
                }
                pivots[i] = tempval;
            }
            pivot_one = pivots[select_pivot(generator)];
            pivot_big = pivots[5 + select_pivot(generator)];
        }
        void rand_single_constants()
        {
            node = new core::ast::Number<N>(constant(generator));
            if(binary_selection(generator))
            {
                preference = &almost_everytime;
            }
            else
            {
                preference = &almost_never;
            }
            changeable_deep = (*preference)(generator);
            changeable_constant = (*preference)(generator);
            changeable_operations = (*preference)(generator);
            changeable_variables = (*preference)(generator);
            /*if(binary_selection(generator))
            {
                changeable_deep_increment = &almost_everytime;
            }
            else
            {
                changeable_deep_increment = &almost_never;
            }*/
            N tempval;
            for(size_t i = 0; i < 5; i++)
            {//asgura un numero (0,1)
                for(size_t j = 0; j < 3; j++)
                {
                    tempval = constant(generator);
                    if(core::diff(tempval,N(0))) break;
                }
                pivots[i] = N(1)/tempval;
            }
            for(size_t i = 4; i < 10; i++)
            {//asgura un numero mayor que 1
                for(size_t j = 0; j < 6; j++)
                {
                    tempval = constant(generator);
                    if( std::abs(tempval) > N(1)) break;
                }
                pivots[i] = tempval;
            }
            pivot_one = pivots[select_pivot(generator)];
            pivot_big = pivots[5 + select_pivot(generator)];
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
        std::bernoulli_distribution* preference;//randopn binary selector
        bool changeable_deep;//si se pude cambiar la profundidad del arboal al aparearse
        bool changeable_constant;//si se pude cambiar los valores de las constantes
        bool changeable_operations;//si se pude cambiar las operaciones
        bool changeable_variables;//si se pude cambiar las variables
        //std::bernoulli_distribution* changeable_deep_increment;//la preferencia en el cambio de la profundida
        static const size_t pivots_size = 10;
        core::array<N,pivots_size> pivots;
        size_t pivot_one;
        size_t pivot_big;

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
        static inline std::bernoulli_distribution almost_everytime;
        static inline std::bernoulli_distribution almost_never;
        static inline std::uniform_int_distribution<> select_pivot;
        static inline std::uniform_int_distribution<> select_gen_constant;
        static inline unsigned population_size;

        static void init_randsys(unsigned size)
        {
            population_size = size;
            int barrera = population_size/10;
            std::setprecision(10);
            generator = std::mt19937(rd()); // mersenne_twister_engine seeded with rd()
            operation = std::uniform_int_distribution<>(1, 4);//+,-,*,/
            constant = std::uniform_real_distribution<>(-1.0e6, 1.0e6);
            nesting = std::bernoulli_distribution(0.75);
            svariable = std::uniform_int_distribution<>(0, S - 1);
            randon_node = std::uniform_int_distribution<>(1, 3);//operacion,variable,constante
            mutability = std::bernoulli_distribution(0.02);
            binary_selection = std::bernoulli_distribution(0.5);
            operation_puls_1 = std::uniform_int_distribution<>(1, 5);//+,-,*,/,?
            selection_firts_pair = std::fisher_f_distribution<N>(1,barrera);
            selection_second_pair = std::uniform_int_distribution<>(1,population_size - 1);
            almost_everytime = std::bernoulli_distribution(0.8);
            almost_never = std::bernoulli_distribution(0.2);
            select_pivot = std::uniform_int_distribution<>(0,(pivots_size/2) - 1);//+,-,*,/
            select_gen_constant = std::uniform_int_distribution<>(1,9);
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
        BinoprTown(const inputs<N,S>& vs) : variables(&vs)
        {
        }

        void populate_random()
        {
            this->auto_free = true;
            this->resize(T::population_size);
            for(size_t i = 0; i < this->size(); i++)
            {
                this->operator[](i) = new T(*variables,T::eval_constant,false);
                this->operator[](i)->rand_single_constants();
            }
        }

        /**
        *
        */
        virtual void evaluate()
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                this->operator[](i)->evaluation = this->operator[](i)->evaluate();
            }
            auto cmpfun = [](T* a,T* b)
            {
                return  a->evaluation > b->evaluation;
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
                std::cout << this->operator[](i)->evaluation;
                std::cout << ",\t" << this->operator[](0)->evalr_actual(this->operator[](0)->variables);
                std::cout << ",\texpresion : ";
                this->operator[](i)->print(std::cout);
                std::cout << "\n";
            }
        }

        /**
        *
        */
        void resumen(std::ostream& out) const
        {
            std::cout << "Poblacion : " << this->size() << "\n";
            std::cout << "objetivo : ";
            std::cout << this->operator[](0)->evalr_actual(this->operator[](0)->variables);
            std::cout << "\n";
            unsigned count_constants = 0;
            for(size_t i = 0; i < this->size(); i++)
            {
                if(this->operator[](i)->node->type == core::ast::typen::number) count_constants++;
            }
            N media = 0;
            for(size_t i = 0; i < this->size(); i++)
            {
                media += this->operator[](i)->evaluation;
            }
            media /= N(this->size());
            std::cout << "Constantes : " << count_constants << "\n";
            std::cout << "Media : " << media << "\n";
        }

        /**
        *
        */
        void listing(std::ostream& out) const
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                std::cout << i << "\t";
                std::cout << "evaluacion : ";
                std::cout << this->operator[](i)->evaluation;
                std::cout << ",\t" << this->operator[](i)->evalr_actual(this->operator[](i)->variables);
                std::cout << "\texpresion : ";
                this->operator[](i)->print(std::cout);
                std::cout << "\n";
            }
        }

        /**
        *\brief Realiza el apareo
        *
        */
        virtual void pair()
        {
            core::array<size_t,2> selectd;

            size_t pairs = T::population_size/5;
            core::array<T*> borned(pairs),deads(pairs);
            for(size_t i = 0; i < pairs; i++)
            {
                if(T::mutability(T::generator)) active_mutation = true;
                selectd = select_pair_with_comunal();
                //std::cout << "Aparear : " << selectd[0] << " --> " << selectd[1] << "\n";
                borned[i] = new T(*variables,T::eval_constant,false);
                if(active_mutation and T::almost_never(T::generator))
                {
                    borned[i]->rand_single_constants();
                }
                else
                {
                    mesh_gens(*borned[i],*this->operator[](selectd[0]),*this->operator[](selectd[1]));
                }
                if(active_mutation and T::almost_everytime(T::generator))
                {
                    if(T::binary_selection(T::generator))
                    {
                        mutation_pivots(*this->operator[](selectd[0]));
                    }
                    else
                    {
                        mutation_pivots(*this->operator[](selectd[1]));
                    }
                }
                active_mutation = false;
            }
            for(size_t i = 0, j = this->size() - 1; i < pairs; i++,j--)
            {
                deads[i] =  this->operator[](j);
                //std::cout << " j : " << j << "\n";
                //std::cout << " j -> : " << (void*)this->operator[](j) << "\n";
                this->operator[](j) = borned[i];
                if(not borned[i]->node) throw core::exception("No se asigno el nodo correspondiente.");
            }
            for(size_t i = 0; i < pairs; i++)
            {
                delete deads[i];
            }
        }

        void mutation(T& born)
        {
            if((T::binary_selection)(T::generator))
            {
                mutation_pivots(born);
            }
            else
            {
                mutation_node(born);
            }
        }
        void mutation_node(T& born)
        {
            born.rand_single_constants();
        }
        void mutation_pivots(T& born)
        {
            N tempval;
            if((T::binary_selection)(T::generator))
            {
                    if((T::binary_selection)(T::generator))
                    {
                        for(size_t i = 0; i < 5; i++)
                        {//asgura un numero (0,1)
                            for(size_t j = 0; j < 3; j++)
                            {
                                tempval = T::constant(T::generator);
                                if(core::diff(tempval,N(0))) break;
                            }
                            born.pivots[T::select_pivot(T::generator)] = N(1)/tempval;
                        }
                    }
                    else
                    {
                        for(size_t i = 4; i < 10; i++)
                        {//asgura un numero mayor que 1
                            for(size_t j = 0; j < 6; j++)
                            {
                                tempval = T::constant(T::generator);
                                if( std::abs(tempval) > N(1)) break;
                            }
                            born.pivots[T::select_pivot(T::generator)] = tempval;
                        }
                    }
            }
            else
            {
                    if((T::binary_selection)(T::generator))
                    {
                        born.pivot_one = born.pivots[T::select_pivot(T::generator)];
                    }
                    else
                    {
                        born.pivot_big = born.pivots[5 + T::select_pivot(T::generator)];
                    }
            }
        }

        virtual core::array<size_t,2> select_pair_with_comunal()const
        {
            core::array<size_t,2> rest;
            rest[0] = (size_t)T::selection_firts_pair(T::generator);

            if(rest[0] >= this->size())//asegurar que no son iguales
            {
                rest[0] = (size_t)T::selection_firts_pair(T::generator);
            }
            if(rest[0] >= this->size())//asegurar que no son iguales
            {
                rest[0] = (size_t)T::selection_firts_pair(T::generator);
            }
            if(rest[0] >= this->size())//asegurar que no son iguales
            {
                rest[0] = (size_t)T::selection_firts_pair(T::generator);
            }

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
        void mesh_gens_binopr(T& born, const T& parenta, const T& parentb)
        {
        }
        void mesh_gens_variable(T& born, const T& parenta, const T& parentb)
        {
        }
        void mesh_gens_random_node(T& born, const T& parenta, const T& parentb)
        {
        }

        core::ast::node<>* mesh_gens_constant_parents(T& born, const T& parenta, const T& parentb)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parenta.node);
            const auto nodeb = static_cast<const core::ast::Number<N>*>(parenta.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            N contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);

            switch(core::ast::typen(T::operation(T::generator)))
            {
            case core::ast::typen::addition:
                node->data = nodea->data + nodeb->data;
                break;
            case core::ast::typen::subtraction:
                node->data = nodea->data - nodeb->data;
                break;
            case core::ast::typen::product:
                if(core::equal(nodeb->data,N(0)))
                {
                    if((*parenta.preference)(T::generator))
                    {
                        node->data = nodea->data * parentb.pivot_one;
                    }
                    else
                    {
                        node->data = nodea->data * parentb.pivot_big;
                    }
                }
                else
                {
                    node->data = nodea->data * nodeb->data;
                }
                break;
            case core::ast::typen::quotient:
                if(core::equal(nodeb->data,N(0)))
                {
                    if((*parenta.preference)(T::generator))
                    {
                        node->data = nodea->data / parentb.pivot_one;
                    }
                    else
                    {
                        node->data = nodea->data / parentb.pivot_big;
                    }
                }
                else
                {
                    if((*parenta.preference)(T::generator))
                    {
                        node->data = nodea->data / parentb.pivot_one;
                    }
                    else
                    {
                        node->data = nodea->data / nodeb->data;
                    }

                }
                break;
            default:
                break;
            }

            return node;
        }

        core::ast::node<>* mesh_gens_constant_parents_pivot_one(T& born, const T& parenta, const T& parentb)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parenta.node);
            //const auto nodeb = static_cast<const core::ast::Number<N>*>(parenta.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            switch(core::ast::typen(T::operation(T::generator)))
            {
            case core::ast::typen::addition:
                node->data = nodea->data + parentb.pivot_one;
                break;
            case core::ast::typen::subtraction:
                node->data = nodea->data - parentb.pivot_one;
                break;
            case core::ast::typen::product:
                node->data = nodea->data * parentb.pivot_one;
                break;
            case core::ast::typen::quotient:
                node->data = nodea->data / parentb.pivot_one;
                break;
            default:
                break;
            }

            return node;
        }

        core::ast::node<>* mesh_gens_constant_parents_pivot_big(T& born, const T& parenta, const T& parentb)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parenta.node);
            //const auto nodeb = static_cast<const core::ast::Number<N>*>(parenta.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            switch(core::ast::typen(T::operation(T::generator)))
            {
            case core::ast::typen::addition:
                node->data = nodea->data + parentb.pivot_big;
                break;
            case core::ast::typen::subtraction:
                node->data = nodea->data - parentb.pivot_big;
                break;
            case core::ast::typen::product:
                node->data = nodea->data * parentb.pivot_big;
                break;
            case core::ast::typen::quotient:
                node->data = nodea->data / parentb.pivot_big;
                break;
            default:
                break;
            }

            return node;
        }
        core::ast::node<>* mesh_gens_constant_parents_pivot_random(T& born, const T& parenta, const T& parentb)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parenta.node);
            //const auto nodeb = static_cast<const core::ast::Number<N>*>(parenta.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            size_t index;
            if((*born.preference)(T::generator))
            {
                index = T::select_pivot(T::generator);
            }
            else
            {
                index = 4 + T::select_pivot(T::generator);
            }
            switch(core::ast::typen(T::operation(T::generator)))
            {
            case core::ast::typen::addition:
                node->data = nodea->data + parentb.pivots[index];
                break;
            case core::ast::typen::subtraction:
                node->data = nodea->data - parentb.pivots[index];
                break;
            case core::ast::typen::product:
                node->data = nodea->data * parentb.pivots[index];
                break;
            case core::ast::typen::quotient:
                node->data = nodea->data / parentb.pivots[index];
                break;
            default:
                break;
            }

            return node;
        }

        core::ast::node<>* mesh_gens_constant_single(T& born, const T& parent)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parent.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            N contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);
            if(core::equal(contant,N(0))) contant = T::constant(T::generator);
            switch(core::ast::typen(T::operation(T::generator)))
            {
            case core::ast::typen::addition:
                node->data = nodea->data + contant;
                break;
            case core::ast::typen::subtraction:
                node->data = nodea->data - contant;
                break;
            case core::ast::typen::product:
                node->data = nodea->data * contant;
                break;
            case core::ast::typen::quotient:
                node->data = nodea->data / contant;
                break;
            default:
                break;
            }

            return node;
        }
        core::ast::node<>* mesh_gens_constant_pivoted(T& born, const T& parent)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parent.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            if((*born.preference)(T::generator))
            {
                if((*born.preference)(T::generator))
                {
                    node->data = nodea->data * parent.pivot_one;
                }
                else
                {
                    node->data = nodea->data * parent.pivot_big;
                }
            }
            else
            {
                if((*born.preference)(T::generator))
                {
                    node->data = nodea->data * (parent.pivots[T::select_pivot(T::generator)]/parent.pivot_one);
                }
                else
                {
                    node->data = nodea->data * ((parent.pivots[T::select_pivot(T::generator)] - parent.pivots[T::select_pivot(T::generator)])/parent.pivot_one);
                }
            }

            return node;
        }

        core::ast::node<>* mesh_gens_constant_pivoted_operation(T& born, const T& parent)
        {
            const auto nodea = static_cast<const core::ast::Number<N>*>(parent.node);

            core::ast::Number<N>* node = new core::ast::Number<N>;
            if((*born.preference)(T::generator))
            {
                if((*born.preference)(T::generator))
                {
                    node->data = nodea->data + parent.pivot_one;
                }
                else
                {
                    node->data = nodea->data - parent.pivot_one;
                }
            }
            else
            {
                if((*born.preference)(T::generator))
                {
                    node->data = (nodea->data - parent.pivot_big)/parent.pivot_big;
                }
                else
                {
                    node->data =  (nodea->data - parent.pivot_one)/parent.pivot_big;
                }
            }

            return node;
        }
        core::ast::node<>* mesh_gens_constant(T& born, const T& parenta, const T& parentb)
        {
            switch(T::select_gen_constant(T::generator))
            {
            case 1:
                return mesh_gens_constant_pivoted_operation(born,parenta);
            case 2:
                return mesh_gens_constant_pivoted(born,parenta);
            case 3:
                return mesh_gens_constant_single(born,parenta);
            case 4:
                return mesh_gens_constant_parents(born,parenta,parentb);
            case 5:
                return mesh_gens_constant_parents_pivot_one(born,parenta,parentb);
            case 6:
                return mesh_gens_constant_parents_pivot_big(born,parenta,parentb);
            case 7:
                return mesh_gens_constant_parents_pivot_random(born,parenta,parentb);
            default:
                return mesh_gens_constant_pivoted(born,parenta);
                break;
            }
            if((*born.preference)(T::generator))
            {
                if((*born.preference)(T::generator))
                {
                }
                else if((*born.preference)(T::generator))
                {
                }
                else
                {
                }
            }
            else
            {
                if((*born.preference)(T::generator))
                {
                }
                else if((*born.preference)(T::generator))
                {
                }
                else if((*born.preference)(T::generator))
                {
                }
                else
                {
                }
            }
        }
        /**
        *\brief Asigna los genes de un individuo a partir de los padres
        *\param born individuo cuyos genes seran asignados
        *\param parenta un padre del nuevo individuo
        *\param parentb un padre del nuevo individuo
        */
        void mesh_gens(T& born, const T& parenta, const T& parentb)
        {
            if(born.node) throw core::exception("El nodo no esta vacio, deve esta vacio para continuar");
            active_mutation = false;


            if(T::binary_selection(T::generator))
            {
                born.preference = parenta.preference;
                born.changeable_deep = parentb.changeable_deep;
                born.changeable_constant = parenta.changeable_constant;
                born.changeable_operations = parentb.changeable_operations;
                born.changeable_variables = parenta.changeable_variables;
                //born.changeable_deep_increment = parentb.changeable_deep_increment;
                born.pivots = parentb.pivots;
                born.pivot_one = parenta.pivot_one;
                born.pivot_big = parentb.pivot_big;
                if(active_mutation and T::almost_everytime(T::generator))
                {
                    mutation_pivots(born);
                }

                if(parenta.node->is_number())
                {
                    if(active_mutation and T::almost_everytime(T::generator))
                    {
                        //mutation_counter++;
                        mutation_node(born);
                    }
                    else
                    {
                        born.node = mesh_gens_constant(born,parenta,parentb);
                    }

                    born.auto_free = true;
                }
                else
                {
                    born.rand_single_constants();
                }
            }
            else
            {
                born.preference = parentb.preference;
                born.changeable_deep = parenta.changeable_deep;
                born.changeable_constant = parentb.changeable_constant;
                born.changeable_operations = parenta.changeable_operations;
                born.changeable_variables = parentb.changeable_variables;
                //born.changeable_deep_increment = parenta.changeable_deep_increment;
                born.pivots = parenta.pivots;
                born.pivot_one = parentb.pivot_one;
                born.pivot_big = parenta.pivot_big;
                if(parentb.node->is_number())
                {
                    born.node = mesh_gens_constant(born,parentb,parenta);
                    born.auto_free = true;
                }
                else
                {
                    born.rand_single_constants();
                }
            }



        }

    public:
        const inputs<N,S>* variables;

    public:
        bool active_mutation;
    };

}

#endif // EC_HH_INCLUDED
