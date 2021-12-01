
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
#include <fstream>
//#include <octetos/coreutils/shell.hh>
#include "sudoku.hh"


int main(int argc, const char* argv[])
{
	if(argc < 4) 
	{
		std::cerr << "Indique lo cuatro parametros necesarion\n";
		std::cerr << "ec-sudoku  --directory-logs '..' --board '..' --iterations '..' --serie 'nombre cantidad'\n";
		return EXIT_SUCCESS;
	}
			
	std::cout << "Step 0.0\n";	
	oct::ec::sudoku::Enviroment* sudoku = new oct::ec::sudoku::Enviroment(argc,argv);
	sudoku->enableEcho(&std::cout,2);
	bool check = sudoku->run();
	
	delete sudoku; 
	
	return check? EXIT_SUCCESS : EXIT_FAILURE;
}


