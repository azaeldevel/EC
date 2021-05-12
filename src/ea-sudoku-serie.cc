
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
#include <octetos/coreutils/shell.hh>
#include "GA-sudoku.hh"


int main(int argc, const char* argv[])
{
	if(argc < 1) 
	{
		std::cerr << "Indique el archivo de inicialización\n";
		return EXIT_SUCCESS;
	}
	
	ae::ga::SudokuEnviroment sudoku(argv[1],1000);
	sudoku.series("logs",100);
	
	return EXIT_SUCCESS;
}


