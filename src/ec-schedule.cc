
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
#include <string>
#include <csignal>


#if defined(__GNUC__) && defined(__linux__)
    #include <octetos/core/shell.hh>
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    #include <shell.hh>
#else
    #error "Pltaforma desconocida"
#endif

#include "schedule.hh"

int main(int argc, const char* argv[])
{
	signal(SIGSEGV,oct::core::signal_segmentv);
	signal(SIGABRT,oct::core::signal_abort);
	
	std::string strDay = std::to_string(oct::core::getDayID());
	std::string strTime = std::to_string(oct::core::getTimeID());
	std::string strid = strDay + "-" + strTime;
	std::string log_dir = "logs/schedule/";
	log_dir += strid;
	oct::ec::sche::Enviroment* sche = new oct::ec::sche::Enviroment(log_dir,"tests",log_dir);
	sche->enableEcho(&std::cout,2);

	bool ret;
	ret = sche->run();

	delete sche;

	return ret? EXIT_SUCCESS : EXIT_FAILURE;
}


