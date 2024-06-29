
#ifndef OCTETOS_EC_V1_FORMULE_HH
#define OCTETOS_EC_V1_FORMULE_HH

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

#include <random>

 #include "nodes.hh"

namespace oct::ec::v1
{
    typedef float TYPEDATA;
    struct vers_check
    {
        node<TYPEDATA>* var;
        bool used;
    };

    class Formule : public Node<TYPEDATA>
    {
    public:
        typedef Node<TYPEDATA> BASE;

    public:
        Formule();

        /**
        *\brief genera una form,ula completamente al azar
        **/
        void generate(size_t variables, size_t deep, std::uniform_real_distribution<TYPEDATA>&,std::mt19937&);
        virtual operator TYPEDATA() const;
        virtual void print(std::ostream& out)const;

    private:
        node<TYPEDATA>* crete_number();
        node<TYPEDATA>* crete_variable();
        operation<TYPEDATA>* create_operation(std::uniform_real_distribution<TYPEDATA>&,std::mt19937&);
        void create_operation(const size_t& deep,size_t current, std::uniform_real_distribution<TYPEDATA>&,std::mt19937&,operation<TYPEDATA>*);
        bool use_term(std::uniform_real_distribution<TYPEDATA>&,std::mt19937&);
        size_t get_random_variable(std::uniform_real_distribution<TYPEDATA>&,std::mt19937&);

    private:
        std::vector<vers_check> vars;
    };
}

#endif
