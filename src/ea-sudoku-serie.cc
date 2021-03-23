/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
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
#include "GA-ext.hh"


int main(int argc, const char* argv[])
{
	ae::ga::SudokuEnviroment *sudoku;
	std::string dir = "logs/firtsStatics";
	coreutils::Shell shell;
	shell.mkdir(dir,true);
	for(int i = 1; i < 10; i++)
	{	
		sudoku = new ae::ga::SudokuEnviroment();
		std::cout << "Test " << i << "\n";
		sudoku->logDirectory = dir;		
		if(sudoku->run())
		{
			ae::Single* single = *(sudoku->begin());
			std::ofstream fnSolution(dir + "/solutions.csv");
			single->saveCSV(fnSolution);
			fnSolution.flush();
			fnSolution.close();
		}
		delete sudoku;
	}
	
	return EXIT_SUCCESS;
}


