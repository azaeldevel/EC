
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
#include "GA-sudoku.hh"


int main(int argc, const char* argv[])
{
	if(argc < 4) 
	{
		std::cerr << "Indique lo cuatro parametros necesarion\n";
		std::cerr << "sudoku  (dirlog|-) InitialBoard iterations series\n";
		return EXIT_SUCCESS;
	}
			
	std::string logDir = argv[1];
	std::string initBoard = argv[2];
	if(logDir.compare("-") == 0) logDir = "";//desactivacion de logs	
	unsigned int iterations = std::stoi(argv[3]);
	unsigned int series = std::stoi(argv[4]);	
	//bool logFile = not logDir.empty();//enableLogFile ();
	std::string logDirectorySerie = logDir + "/" + std::to_string(ec::sudoku::Enviroment::getDayID());;
		
	ec::sudoku::Enviroment* sudoku = new ec::sudoku::Enviroment(initBoard,iterations,logDirectorySerie,series);		
	sudoku->enableEcho(&std::cout,2);
	
	return sudoku->series()? EXIT_SUCCESS : EXIT_FAILURE;
}


