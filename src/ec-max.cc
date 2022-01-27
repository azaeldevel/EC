
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







#include <fstream>

#include "max.hh"

void echo(const char* text)
{
	std::cout << text;
}
int main(int argc, const char* argv[])
{
	/*if(argc < 2)
	{
		std::cerr << "Indique el parametro necesarion\n";
		std::cerr << "ec-max --directory-history-logs dir\n";
		return EXIT_SUCCESS;
	}*/

	oct::ec::max::Enviroment* max = new oct::ec::max::Enviroment(argc,argv);
	max->enableEcho(&echo,2);

	bool ret = max->run();
	delete max;//no es necesario delete en mian ya que se llama automaticamente
	return ret? EXIT_SUCCESS : EXIT_FAILURE;
}


