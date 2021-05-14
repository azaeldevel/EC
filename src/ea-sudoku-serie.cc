
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
	if(argc < 4) 
	{
		std::cerr << "Indique lo cuatro parametros necesarion\n";
		std::cerr << "sudoku InitialBoard dirlog|- iterations series\n";
		return EXIT_SUCCESS;
	}
	
	std::string initBoard = argv[1];
	
	std::string dirLog = argv[2];
	if(dirLog.compare("-") == 0) dirLog = "";//desactivacion de logs
	
	unsigned int itBySerie = std::stoi(argv[3]);
	
	unsigned int Serie = std::stoi(argv[4]);
	
	ae::ga::SudokuEnviroment sudoku(initBoard,itBySerie);
	sudoku.series(dirLog,Serie);
	
	return EXIT_SUCCESS;
}


