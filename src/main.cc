
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
	std::time_t offtime = 0;
	std::time_t timefull = 0;
	oct::core::Time time1(0);
	//time1.read("Tue 23:15","%a %H:%M");
	time1.print(std::cout,"%c");	
	std::cout << "\n";
	
	oct::core::Time time2(oct::ec::sche::Time::FIRST_SUNDAY);
	time2.print(std::cout,"%c");	
	std::cout << "\n";

	offtime = 1 * 24 * 60 * 60;
	oct::core::Time time3(oct::ec::sche::Time::FIRST_SUNDAY + offtime);
	time3.print(std::cout,"%c");	
	std::cout << "\n";
	timefull = mktime(&time3);
	if(timefull != oct::ec::sche::Time::FIRST_SUNDAY + offtime) std::cout << "La marca de tiempo no coincide\n";
	
	offtime = 2 * 24 * 60 * 60;
	oct::core::Time time4(oct::ec::sche::Time::FIRST_SUNDAY + offtime);
	time4.print(std::cout,"%c");	
	std::cout << "\n";
	timefull = mktime(&time4);
	if(timefull != oct::ec::sche::Time::FIRST_SUNDAY + offtime) std::cout << "La marca de tiempo no coincide\n";
	
	offtime = 3 * 24 * 60 * 60;
	oct::core::Time time5(oct::ec::sche::Time::FIRST_SUNDAY + offtime);
	time5.print(std::cout,"%c");	
	std::cout << "\n";
	timefull = mktime(&time5);
	if(timefull != oct::ec::sche::Time::FIRST_SUNDAY + offtime) std::cout << "La marca de tiempo no coincide\n";


	return EXIT_SUCCESS ;
}


