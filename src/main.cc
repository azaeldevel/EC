
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 *
 * AE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include <iostream>

#include "Program-tree.hh"


using namespace oct::ec::prog;
int main(int argc, const char* argv[])
{

    Plus plus1(10,25);
    Rest rest1(11,9);

    std::cout << "Suma : " << plus1 << std::endl;
    std::cout << "Rest : " << rest1 << std::endl;

	return EXIT_SUCCESS ;
}


