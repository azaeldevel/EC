
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
	
	ae::ga::SudokuEnviroment *sudoku;
	std::string dir = "logs/fewSolutions";
	std::string dirSolutions = dir + "/solutions.cvs";
	coreutils::Shell shell;
	shell.mkdir(dir,true);
	std::ofstream fSolutions(dirSolutions);
	int i = 1;
	bool done;
	do
	{
		std::cout << "Test " << i << "\n";
		sudoku = new ae::ga::SudokuEnviroment(dir,argv[1]);
		sudoku->enableEcho (&std::cout,2);
		sudoku->enableLogFile (true);
		done = sudoku->run();
		if(done)
		{
			if(fSolutions.is_open())
			{
				sudoku->save();
				fSolutions << sudoku->getLogSubDirectory ();
				fSolutions << "\n";
				fSolutions.flush();
			}
		}
		delete sudoku;
		i++;
	}
	while(not done);
	fSolutions.close();
	
	return EXIT_SUCCESS;
}


