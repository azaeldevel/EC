
/*
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * CC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




#include "formule.hh"

namespace oct::ec::v1
{
    Formule::Formule() : BASE(1)
    {
    }

    void Formule::generate(size_t variables, size_t deep, std::uniform_real_distribution<TYPEDATA>& numgen,std::mt19937& rng)
    {
        std::cout << "Formule::generate 1.0\n";
        vars.resize(variables);
        for(size_t i = 0; i < variables; i++)
        {
            vars[i].var = crete_variable();
            vars[i].used = false;
        }
        std::cout << "Formule::generate 1.2\n";

        BASE::at(0) = create_operation(numgen,rng);
        std::cout << "Formule::generate 1.3\n";
        create_operation(deep,(size_t)1,numgen,rng,(operation<TYPEDATA>*)BASE::at(0));
        std::cout << "Formule::generate 1.4\n";
    }
    void Formule::create_operation(const size_t& deep,size_t current, std::uniform_real_distribution<TYPEDATA>& numgen,std::mt19937& rng,operation<TYPEDATA>* op)
    {
        std::cout << "Formule::create_operation1.0\n";
        if(deep < current) return;
        std::cout << "Formule::create_operation1.1\n";
        std::cout << "current = " << current << "\n";


        std::cout << "Formule::create_operation1.2\n";
        node<TYPEDATA> *a,*b;
        TYPEDATA rngval = numgen(rng);
        std::bernoulli_distribution boolgen1(rngval);
        //primer termino
        bool data = boolgen1(rng);
        std::cout << "Formule::create_operation1.3\n";
        if(data)
        {
            a = create_operation(numgen,rng);
            create_operation(deep,current + 1,numgen,rng,(operation<TYPEDATA>*)a);

            if(use_term(numgen,rng))
            {
                b = vars[get_random_variable(numgen,rng)].var;
            }
            else
            {
                b = crete_number();
            }
        }
        else
        {
            if(use_term(numgen,rng))
            {
                a = vars[get_random_variable(numgen,rng)].var;
            }
            else
            {
                a = crete_number();
            }

            b = create_operation(numgen,rng);
            create_operation(deep,current + 1,numgen,rng,(operation<TYPEDATA>*)b);
        }
        std::cout << "Formule::create_operation1.4\n";

        op->set(*a,*b);

        std::cout << "Formule::create_operation1.5\n";
    }
    size_t Formule::get_random_variable(std::uniform_real_distribution<TYPEDATA>& numgen,std::mt19937& rng)
    {

        return false;
    }
    bool Formule::use_term(std::uniform_real_distribution<TYPEDATA>& numgen,std::mt19937& rng)
    {
        TYPEDATA rngval = numgen(rng);
        std::bernoulli_distribution boolgen(rngval);
        return boolgen(rng);
    }

    Formule::operator TYPEDATA() const
    {
        return 0.0f;
    }

    void Formule::print(std::ostream& out)const
    {
        BASE::at(0)->print(out);
    }

    node<TYPEDATA>* Formule::crete_number()
    {
        return new Number<TYPEDATA>;
    }
    node<TYPEDATA>* Formule::crete_variable()
    {
        return new Variable<TYPEDATA>;
    }
    operation<TYPEDATA>* Formule::create_operation(std::uniform_real_distribution<TYPEDATA>& numgen,std::mt19937& rng)
    {
        TYPEDATA rngval = numgen(rng);

        if(rngval < 0.3f)
        {
            return new Addition<TYPEDATA>;
        }
        else if(rngval < 0.6f)
        {
            return new Subtration<TYPEDATA>;
        }
        else if(rngval < 0.75f)
        {
            return new Product<TYPEDATA>;
        }
        else if(rngval < 0.9f)
        {
            return new Divition<TYPEDATA>;
        }
        else //if(rnd <= 1.0f)
        {
            return new Pow<TYPEDATA>;
        }

        return NULL;
    }

}
