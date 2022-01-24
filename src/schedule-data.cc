/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 *
 * octetos-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * octetos-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <locale>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>


#include "schedule.hh"



namespace oct::core
{
	Person::Person(const std::string& n,const std::string& ap,const std::string& am)
	{
		name = n + " " + ap + " " + am;
	}
	Person::Person(const std::string& n)
	{
		name = n;
	}
	Person::Person()
	{
	}

	const std::string& Person::operator =(const std::string& n)
	{
		name = n;

		return n;
	}
	const std::string& Person::get_name()const
	{
		return name;
	}





	Time::Time() // : tm({0})
	{
	}
	Time::Time(std::time_t t)
	{
		((tm&)*this) = (*std::localtime(&t));
	}
	Time::Time(const tm& t)
	{
		((tm&)*this) = t;
	}
	Time::Time(const Time& t)
	{
		((tm&)*this) = t;
	}

	const std::time_t* Time::operator =(const std::time_t* t)
	{
		((tm&)*this) = (*std::localtime(t));
		return t;
	}
	std::time_t Time::operator =(std::time_t t)
	{
		((tm&)*this) = (*std::localtime(&t));
		return t;
	}
	const tm& Time::operator =(const tm& t)
	{
		((tm&)*this) = t;

		return *this;
	}
	const Time& Time::operator =(const Time& t)
	{
		((tm&)*this) = t;

		return t;
	}


	//operadores de compracion
	bool Time::operator ==(const Time& o)const
	{
		if(tm_sec != o.tm_sec) return false;
		else if(tm_min != o.tm_min) return false;
		else if(tm_hour != o.tm_hour) return false;
		else if(tm_mday != o.tm_mday) return false;
		else if(tm_mon != o.tm_mon) return false;
		else if(tm_year != o.tm_year) return false;

		return true;
	}
	bool Time::operator ==(const std::tm& o)const
	{
		if(tm_sec != o.tm_sec) return false;
		else if(tm_min != o.tm_min) return false;
		else if(tm_hour != o.tm_hour) return false;
		else if(tm_mday != o.tm_mday) return false;
		else if(tm_mon != o.tm_mon) return false;
		else if(tm_year != o.tm_year) return false;

		return true;
	}
	bool Time::operator ==(std::time_t o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		if(t_this == o) return true;
		return false;
	}

	bool Time::operator !=(const Time& o)const
	{
		if(tm_sec == o.tm_sec) return false;
		else if(tm_min == o.tm_min) return false;
		else if(tm_hour == o.tm_hour) return false;
		else if(tm_mday == o.tm_mday) return false;
		else if(tm_mon == o.tm_mon) return false;
		else if(tm_year == o.tm_year) return false;

		return true;
	}
	bool Time::operator !=(const std::tm& o)const
	{
		if(tm_sec == o.tm_sec) return false;
		else if(tm_min == o.tm_min) return false;
		else if(tm_hour == o.tm_hour) return false;
		else if(tm_mday == o.tm_mday) return false;
		else if(tm_mon == o.tm_mon) return false;
		else if(tm_year == o.tm_year) return false;

		return true;
	}
	bool Time::operator !=(std::time_t o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		if(t_this != o) return true;
		return false;
	}

	bool Time::operator <(const Time& o)const
	{
		if(tm_year < o.tm_year) return true;
		else if(tm_year > o.tm_year) return false;
		else if(tm_mon < o.tm_mon) return true;
		else if(tm_mon > o.tm_mon) return false;
		else if(tm_mday < o.tm_mday) return true;
		else if(tm_mday > o.tm_mday) return false;
		else if(tm_hour < o.tm_hour) return true;
		else if(tm_hour > o.tm_hour) return false;
		else if(tm_min < o.tm_min) return true;
		else if(tm_min > o.tm_min) return false;
		else if(tm_sec < o.tm_sec) return true;
		else if(tm_sec > o.tm_sec) return false;

		return false;
	}
	bool Time::operator <(const tm& o)const
	{
		if(tm_year < o.tm_year) return true;
		else if(tm_year > o.tm_year) return false;
		else if(tm_mon < o.tm_mon) return true;
		else if(tm_mon > o.tm_mon) return false;
		else if(tm_mday < o.tm_mday) return true;
		else if(tm_mday > o.tm_mday) return false;
		else if(tm_hour < o.tm_hour) return true;
		else if(tm_hour > o.tm_hour) return false;
		else if(tm_min < o.tm_min) return true;
		else if(tm_min > o.tm_min) return false;
		else if(tm_sec < o.tm_sec) return true;
		else if(tm_sec > o.tm_sec) return false;

		return false;
	}
	bool Time::operator <(std::time_t t_o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		return t_this < t_o;
	}

	bool Time::operator >(const Time& o)const
	{
		if(tm_year < o.tm_year) return false;
		else if(tm_year > o.tm_year) return true;
		else if(tm_mon < o.tm_mon) return false;
		else if(tm_mon > o.tm_mon) return true;
		else if(tm_mday < o.tm_mday) return false;
		else if(tm_mday > o.tm_mday) return true;
		else if(tm_hour < o.tm_hour) return false;
		else if(tm_hour > o.tm_hour) return true;
		else if(tm_min < o.tm_min) return false;
		else if(tm_min > o.tm_min) return true;
		else if(tm_sec < o.tm_sec) return false;
		else if(tm_sec > o.tm_sec) return true;

		return false;
	}
	bool Time::operator >(const tm& o)const
	{
		if(tm_year < o.tm_year) return false;
		else if(tm_year > o.tm_year) return true;
		else if(tm_mon < o.tm_mon) return false;
		else if(tm_mon > o.tm_mon) return true;
		else if(tm_mday < o.tm_mday) return false;
		else if(tm_mday > o.tm_mday) return true;
		else if(tm_hour < o.tm_hour) return false;
		else if(tm_hour > o.tm_hour) return true;
		else if(tm_min < o.tm_min) return false;
		else if(tm_min > o.tm_min) return true;
		else if(tm_sec < o.tm_sec) return false;
		else if(tm_sec > o.tm_sec) return true;

		return false;
	}
	bool Time::operator >(std::time_t t_o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		return t_this > t_o;
	}

	bool Time::operator <=(const Time& o)const
	{
		if(tm_year < o.tm_year) return true;
		else if(tm_year > o.tm_year) return false;
		else if(tm_mon < o.tm_mon) return true;
		else if(tm_mon > o.tm_mon) return false;
		else if(tm_mday < o.tm_mday) return true;
		else if(tm_mday > o.tm_mday) return false;
		else if(tm_hour < o.tm_hour) return true;
		else if(tm_hour > o.tm_hour) return false;
		else if(tm_min < o.tm_min) return true;
		else if(tm_min > o.tm_min) return false;
		else if(tm_sec < o.tm_sec) return true;
		else if(tm_sec > o.tm_sec) return false;

		return true;
	}
	bool Time::operator <=(const tm& o)const
	{
		if(tm_year < o.tm_year) return true;
		else if(tm_year > o.tm_year) return false;
		else if(tm_mon < o.tm_mon) return true;
		else if(tm_mon > o.tm_mon) return false;
		else if(tm_mday < o.tm_mday) return true;
		else if(tm_mday > o.tm_mday) return false;
		else if(tm_hour < o.tm_hour) return true;
		else if(tm_hour > o.tm_hour) return false;
		else if(tm_min < o.tm_min) return true;
		else if(tm_min > o.tm_min) return false;
		else if(tm_sec < o.tm_sec) return true;
		else if(tm_sec > o.tm_sec) return false;

		return true;
	}
	bool Time::operator <=(std::time_t t_o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		return t_this <= t_o;
	}

	bool Time::operator >=(const Time& o)const
	{
		if(tm_year < o.tm_year) return false;
		else if(tm_year > o.tm_year) return true;
		else if(tm_mon < o.tm_mon) return false;
		else if(tm_mon > o.tm_mon) return true;
		else if(tm_mday < o.tm_mday) return false;
		else if(tm_mday > o.tm_mday) return true;
		else if(tm_hour < o.tm_hour) return false;
		else if(tm_hour > o.tm_hour) return true;
		else if(tm_min < o.tm_min) return false;
		else if(tm_min > o.tm_min) return true;
		else if(tm_sec < o.tm_sec) return false;
		else if(tm_sec > o.tm_sec) return true;

		return true;
	}
	bool Time::operator >=(const tm& o)const
	{
		if(tm_year < o.tm_year) return false;
		else if(tm_year > o.tm_year) return true;
		else if(tm_mon < o.tm_mon) return false;
		else if(tm_mon > o.tm_mon) return true;
		else if(tm_mday < o.tm_mday) return false;
		else if(tm_mday > o.tm_mday) return true;
		else if(tm_hour < o.tm_hour) return false;
		else if(tm_hour > o.tm_hour) return true;
		else if(tm_min < o.tm_min) return false;
		else if(tm_min > o.tm_min) return true;
		else if(tm_sec < o.tm_sec) return false;
		else if(tm_sec > o.tm_sec) return true;

		return true;
	}
	bool Time::operator >=(std::time_t t_o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		return t_this >= t_o;
	}
	Time::operator std::time_t()
	{
		return std::mktime(this);
	}
	Time::operator std::time_t()const
	{
		std::tm tm_this = *this;
		return std::mktime(&tm_this);
	}


	int Time::get_week_day()const
	{
		return tm_wday;
	}
	double Time::diff(const Time& o)const
	{
		std::tm tm_this = *this;
		std::time_t t_this = std::mktime(&tm_this);

		std::tm tm_o = o;
		std::time_t t_o = std::mktime(&tm_o);

		return difftime(t_o, t_this);
	}

	void Time::print(std::ostream& out, const std::string& format) const
	{
		out << std::put_time(this, format.c_str());
	}
	void Time::add(std::time_t s)
	{
		/*print(std::cout,"%c");
        std::cout << ", " << this;
		std::cout << "\n";*/
		std::time_t t_this = std::mktime(this);
		if(t_this == (std::time_t)-1) throw core::Exception("Fallo de mktime",__FILE__,__LINE__);
		//std::cout << "1 t_this = " << t_this << "\n";

		t_this += s;
		//std::cout << "2 t_this = " << t_this << "\n";
		this->operator = (t_this);
	}
	void Time::rest(std::time_t s)
	{
		std::time_t t_this = std::mktime(this);

		t_this -= s;
		this->operator = (t_this);
	}

	void Time::read(const std::string& time, const std::string& format)
	{
	    std::istringstream ss(time);
        ss >> std::get_time(this, format.c_str());
        if(ss.fail())
        {
        	std::string msg = "Fallo la lecrtura de la fecha '";
        	msg += time + "' con el formato '" + format + "'";
        	throw core::Exception(msg,__FILE__,__LINE__);
        }
	}
	void Time::read(const std::string& time, const std::string& format,const std::locale& locale)
	{
	    std::istringstream ss(time);
	    ss.imbue(locale);
        ss >> std::get_time(this, format.c_str());
        if(ss.fail())
        {
        	std::string msg = "Fallo la lecrtura de la fecha '";
        	msg += time + "' con el formato '" + format + "'";
        	throw core::Exception(msg,__FILE__,__LINE__);
        }
	}


#if defined(__GNUC__) && defined(__linux__)
    void print_backtrace(const char* msg,int code)
	{
		void* array[20];
		size_t size;

		size = backtrace(array,20);
		fprintf(stderr,msg,code);
		backtrace_symbols_fd(array,size,STDERR_FILENO);
	}
	void signal_exception(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
	void signal_abort(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
	void signal_segmentv(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))

#else
    #error "Pltaforma desconocida"
#endif

}

namespace oct::ec::sche
{

	const std::time_t Time::FIRST_SUNDAY = 288000;

	Time::Time() //: core::Time(0)
	{
	}
	Time::Time(const std::tm& t) : core::Time(t)
	{
	}
	Time::Time(const Time& t) : core::Time(t)
	{
	}


	const Time& Time::operator =(const Time& t)
	{
		((tm&)*this) = t;

		return *this;
	}
	std::time_t Time::operator =(std::time_t t)
	{
		((tm&)*this) = *std::localtime(&t);

		return t;
	}

	void Time::read(const std::string& d,const std::string& f)
	{
		core::Time::read(d,f);

		//TODO: el parse de resulta incorrecto, este solucion es temporal
		if(tm_wday < 0 or tm_wday > 6) throw core::Exception("Dia de la semana fuera de rango",__FILE__,__LINE__);
		std::time_t newtime = FIRST_SUNDAY;
		newtime += tm_wday * 24 * 60 * 60;
		newtime += tm_hour * 60 * 60;
		newtime += tm_min * 60;
		operator =(newtime);
	}





	bool is_post_hour(const Time& first,const Time& second, const Configuration& config)
	{
		core::Time tm_first = first;
		std::time_t t_first = std::mktime(&tm_first);
		t_first += config.get_seconds_per_hour();
		core::Time tm_next = *std::localtime(&t_first);

		if(tm_next == second) return true;
		return false;
	}
	bool is_prev_hour(const Time& first,const Time& second, const Configuration& config)
	{
		Time tm_second= second;
		std::time_t t_second = std::mktime(&tm_second);
		t_second -= config.get_seconds_per_hour();
		Time tm_prev = *std::localtime(&t_second);

		if(tm_prev == first) return true;
		return false;
	}
	/*void add_hours(core::Time& first,unsigned int hours, const Configuration& config)
	{
		core::Time tm_first = first;
		std::time_t t_first = std::mktime(&tm_first);
		t_first += config.get_seconds_per_hour() * hours;

		first /= t_first;
	}
	void rest_hours(core::Time& first,unsigned int hours, const Configuration& config)
	{
		core::Time tm_first = first;
		std::time_t t_first = std::mktime(&tm_first);
		t_first -= config.get_seconds_per_hour() * hours;

		first = t_first;
	}
	void add_hours(core::Time& first,unsigned int hours,unsigned int second_per_hour)
	{
		core::Time tm_first = first;
		std::time_t t_first = std::mktime(&tm_first);
		t_first += second_per_hour * hours;

		first = t_first;
	}*/





	Day::Day()
	{
		config = NULL;
	}
	Day::Day(const Day& d)
	{
		//std::cout << "Day::Day(const Day& d) - Step 1.0\n";
		if(size() > 24) throw core::Exception("El dia tiene un maximo de 24 horas",__FILE__,__LINE__);

		for(const Time& dt : d)
		{
			push_back(dt);
		}
		//std::cout << "Day::Day(const Day& d) - Step 2.0\n";
		//blocks.clear();
		/*if(config)
		{
			sort(*config);
		}
		else if(d.config)
		{
			sort(*d.config);//ordena y genera bloques
		}
		else
		{
			config = NULL;
		}*/
		config = d.config;
		//std::cout << "Day::Day(const Day& d) - Step 3.0\n";
	}
	Day& Day::operator =(const Day& d)
	{
		//std::cout << "Day::operator = - Step 1.0\n";
		if(size() > 24) throw core::Exception("El dia tiene un maximo de 24 horas",__FILE__,__LINE__);
		if(size() > 0) throw core::Exception("Deve estar vacio al asignar un dia",__FILE__,__LINE__);

		for(const Time& dt : d)
		{
			push_back(dt);
		}
		//std::cout << "Day::operator = - Step 2.0\n";
		//blocks.clear();
		if(config)
		{
			sort(*config);
		}
		else if(d.config)
		{
			sort(*d.config);//ordena y genera bloques
		}
		else
		{
			config = NULL;
		}
		//std::cout << "Day::operator = - Step 3.0\n";
		return *this;
	}
	/*void Day::set(const Configuration& c)
	{
		sort(c);
	}*/


	Day::Blocks& Day::get_blocks()
	{
		return blocks;
	}
	const Day::Blocks& Day::get_blocks() const
	{
		return blocks;
	}
	void Day::inters(const Day& day1, const Day& day2)
	{
		if(day1.size() > 24) throw core::Exception("El dia tiene un maximo de 24 horas",__FILE__,__LINE__);
		if(day2.size() > 24) throw core::Exception("El dia tiene un maximo de 24 horas",__FILE__,__LINE__);
		if(not day1.config) throw core::Exception("No se ha asignado la informacion de configuracion",__FILE__,__LINE__);
		if(not day2.config) throw core::Exception("No se ha asignado la informacion de configuracion",__FILE__,__LINE__);
		if(size() != 0) throw core::Exception("Dia no vacio",__FILE__,__LINE__);

		if(day1.size() == 0 or day2.size() == 0) return;

		//se asumeme que las horas en el dia esta ordenadas, ello resulta de que el el dato config esta asignado
		if(day1.back() < day2.front())
		{//no traslape
			return;//simplemente sale sin agregar horas al dia actual
		}
		else if(day2.back() < day1.front())
		{//no traslape
			return;//simplemente sale sin agregar horas al dia actual
		}

		//Nota grafica : pendiente
		if(day1.front() <= day2.front())
		{
			Day::const_iterator it_day2 = day2.begin();
			Day::const_iterator it_day1 = std::find(day1.begin(),day1.end(),*it_day2);
			for(;it_day1 != day1.end() and it_day2 != day2.end(); it_day1++,it_day2++)
			{
				/*(*it_day1).print(std::cout,"%a %H:%M");
				std::cout << " == ";
				(*it_day2).print(std::cout,"%a %H:%M");
				std::cout << "\n";*/

				//Solo en depuracion
				if((*it_day1).tm_mday < 4 or (*it_day1).tm_mday > 9) throw core::Exception("Dia del mes fuera de rango",__FILE__,__LINE__);
				if((*it_day2).tm_mday < 4 or (*it_day2).tm_mday > 9) throw core::Exception("Dia del mes fuera de rango",__FILE__,__LINE__);
				if((*it_day1).tm_wday>6) throw core::Exception("Dia del semana fuera de rango",__FILE__,__LINE__);
				if((*it_day2).tm_wday>6) throw core::Exception("Dia del semana fuera de rango",__FILE__,__LINE__);

				if((*it_day1) == (*it_day2))
				{
					push_back(*it_day1);
				}
				else
				{
					/*(*it_day1).print(std::cout,"%c");
					std::cout << " != ";
					(*it_day2).print(std::cout,"%c");
					std::cout << "\n";*/
				}
			}
		}
		else if(day2.front() < day1.front())
		{
			Day::const_iterator it_day1 = day1.begin();
			Day::const_iterator it_day2 = std::find(day2.begin(),day2.end(),*it_day1);
			for(;it_day1 != day1.end() and it_day2 != day2.end(); it_day1++,it_day2++)
			{
				/**/

				//Solo en depuracion
				if((*it_day1).tm_mday <=3 or (*it_day1).tm_mday>10) throw core::Exception("Dia del mes fuera de rango",__FILE__,__LINE__);
				if((*it_day2).tm_mday <=3 or (*it_day2).tm_mday>10) throw core::Exception("Dia del mes fuera de rango",__FILE__,__LINE__);
				if((*it_day1).tm_wday>6) throw core::Exception("Dia del semana fuera de rango",__FILE__,__LINE__);
				if((*it_day2).tm_wday>6) throw core::Exception("Dia del semana fuera de rango",__FILE__,__LINE__);

				if((*it_day1) == (*it_day2))
				{

					push_back(*it_day1);
				}
				else
				{
					/*(*it_day1).print(std::cout,"%a %H:%M");
					std::cout << " != ";
					(*it_day2).print(std::cout,"%a %H:%M");
					std::cout << "\n";*/
				}
			}
		}

		sort(*day1.config);
	}
	bool Day::haveDisponible()const
	{
		return std::list<Time>::size() > 0 ? true : false;
	}

	void Day::blocking(const Configuration& config)
	{
		if(size() == 1)
		{
			Block block;
			block.push_back(&front());
			blocks.push_back(block);
			return ;
		}

		iterator itActual = begin();
		iterator itPost = begin();
		itPost++;
		Block block;
		block.push_back(&*itActual);
		Time nextTime;
		for(unsigned int i = 0; i < size(); i++,itPost++,itActual++)
		{
			nextTime = *itActual;
			nextTime.add(config.get_seconds_per_hour());
			if((*itPost) == nextTime)
			{
				block.push_back(&*itPost);
			}
			else
			{
				blocks.push_back(block);
				block.clear();
				block.push_back(&*itPost);
			}
		}
	}
	bool cmpTimes(const Time& firts,const Time& second)
	{
		return firts < second;
	}
	void Day::sort(const Configuration& config)
	{
		this->config = &config;
		//ordenar los elementos core::Time por su valor tm_wday
		std::list<Time>::sort(cmpTimes);
		//std::cout << ">>>sorted\n";
		blocks.clear();
		//contruir bloques de horas continuas
		if(size() == 0) return;//no hay nada que ordenar si hay 1 o 0 elementos

		blocking(config);
	}
	void Day::add(const Block& b)
	{
		if(b.size() == 0) throw core::Exception("El bloque esta vacio",__FILE__,__LINE__);

		int tm_day = b.front()->tm_wday;
		for(const Time* dt : b)
		{
			if(tm_day != dt->tm_wday) throw core::Exception("Toda las horas deven tener el mismo valor tm_wday.",__FILE__,__LINE__);
			push_back(*dt);
		}
	}
	void Day::add(const Day& day)
	{
		for(const Time& time : day)
		{
			push_back(time);
		}
	}
	void Day::combns(DaysOptions& days, unsigned int hours)const
	{
		if(hours < 1) throw core::Exception("No esta permitido bloques de 0",__FILE__,__LINE__);
		if(size() > 24)  throw core::Exception("El dia tiene un maximo de 24 horas",__FILE__,__LINE__);
		if(size() == 0) throw core::Exception("El dia esta vacio",__FILE__,__LINE__);

		int tm_day = front().tm_wday;
		for(const Time& time : *this)
		{
			if(time.tm_wday != tm_day)  throw core::Exception("Los dias de la semana deve ser igaules",__FILE__,__LINE__);
		}

		//std::cout << "Day::combns - Step 1\n";
		unsigned int countHB = 0;
		for(const Block& b : blocks)
		{
			countHB += b.size();
		}
		if(countHB != size())
		{
			std::string msg = "Los bloques contiene un total de '";
			msg += std::to_string(countHB) + ", sin embargo, el dia contiene " + std::to_string(size()) + " horas.";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
		//std::cout << "Day::combns - Step 2.0\n";
		//std::cout << "Day::combns - Step 2.1\n";
		//std::cout << "Day::combns - Step 2.2\n";
		//bloques de combinacion generados
		//std::cout << "Day::combns - Step 3\n";
		Day d;
		Day* day;
		Block block_mult;
		Block::const_iterator it_hour;
		for(const Block& block : blocks)
		{
			if(block.size() == hours)
			{
				days.push_back(d);
				day = &days.back();
				day->add(block);
				continue;//estas horas ya fueron repartidas
			}
			//bloques equivalentes al numero de horas pedidos

			//days.push_back(d);
			//Day& day = days.back();

			//bloques con multiplos de horas pedidos
			const unsigned int mult = block.size() / hours;
			//unsigned int count_blocks = 0;
			if(mult > 0)
			{
				//std::cout << "mult > 0\n";
				block_mult.clear();
				it_hour = block.begin();
				for(unsigned int i = 0; i < mult; i++)
				{
					//std::cout << "\t"<< i <<"\n";
					for(unsigned int j = 0; j < hours; j++)
					{
						//std::cout << "\t\t"<< j <<"\n";
						block_mult.push_back(*it_hour);
						it_hour++;
					}
					//count_blocks++;
					if(block_mult.size() > 0)
					{
						days.push_back(d);
						day = &days.back();
						day->add(block_mult);
						continue;
					}
				}
				/*if(day.get_blocks().size() != count_blocks)
				{
					std::string msg = "Hay '";
					msg += std::to_string(count_blocks) + "' bloques creados, sin embargo, se agregaron " + std::to_string(day.get_blocks().size());
					throw core::Exception(msg,__FILE__,__LINE__);
				}*/
				//si no es exacto, se pueden hacer otras combinaciones
				if(block.size() % hours > 0) combns(days,hours,block);
			}
			else
			{

			}
		}
		//std::cout << "Day::combns - Step 4\n";
	}
	void Day::combns(DaysOptions& days, unsigned int hours, const Block& block)const
	{
		unsigned int free = block.size() - ((block.size() / hours) * hours);
		const unsigned int mult = block.size() / hours;
		Block::const_iterator it_hour = block.begin();

		if(free == 0) return;
		if(block.size() < 3) return;

		Block block_mult;
		Day d;
		Day* day;
		//comenzar enfrente
		for(unsigned int k = 0; k < free; k++)
		{
			std::advance(it_hour,k);
			block_mult.clear();
			for(unsigned int i = 0; i < mult; i++)
			{
				for(unsigned int j = 0; j < hours; j++)
				{
					if(it_hour == block.end()) break;
					block_mult.push_back(*it_hour);
					it_hour++;
				}
				if(block_mult.size() > 0 and block_mult.size() == hours)
				{
					days.push_back(d);
					day = &days.back();
					day->add(block_mult);
					continue;
				}
			}
		}
	}
	void Day::print_day(std::ostream& out) const
	{
		for(const Time& dt : *this)
		{
			dt.print(out,"%a %H:%M");
			out << " ";
		}
	}
	void Day::print_blocks(std::ostream& out) const
	{
		for(const Block& b : blocks)
		{
			out << "\t";
			for(const Time* dt : b)
			{
				dt->print(out,"%a %H:%M");
				out << " ";
			}
			out << "\n";
		}
	}
	void Day::print_intevals_csv(std::ostream& out, const Configuration& config) const
	{
		unsigned int block_i = 0;
		Time timeEnd;
		for(Blocks::const_iterator it = blocks.begin(); it != blocks.end(); it++,block_i++)
		{
			if((*it).size() == 0)
			{

			}
			else if((*it).size() == 1)
			{
				(*it).front()->print(out,"%a %H:%M");
			}
			else
			{
				(*it).front()->print(out,"%a %H:%M");
				out << "-";
				timeEnd = *(*it).back();
				timeEnd.add(config.get_seconds_per_hour());
				timeEnd.print(out,"%a %H:%M");
			}

			if(block_i < blocks.size() - 1) out << ",";
		}
	}
	check_codes Day::check() const
	{
		if(size() == 0 and blocks.size() == 0)  return check_codes::PASS;

		//verificar ordenammiento
		/*const_iterator itPrev = begin();
		const_iterator itActual = begin();
		itActual++;
		while(itActual != end())
		{
			if((*itActual).tm_hour != (*itPrev).tm_hour + 1)
			{
				return false;
			}

			itActual++;
			itPrev++;
		}*/

		for(const Time dt : *this)
		{
			if((*begin()).tm_wday != dt.tm_wday) return check_codes::HOURS_DIFFERENT_DAY;
		}

		unsigned int countHB = 0;
		for(const Block& b : blocks)
		{
			countHB += b.size();
		}
		if(countHB != size()) return check_codes::BLOCK_CONTENT_SIZE_FAIL;//no coinciden las cantidad de horas


		return check_codes::PASS;
	}
	const Day::Block* Day::random_block() const
	{
		if(blocks.size() == 0) return NULL;
		else if(blocks.size() == 1) return &blocks.front();

		std::uniform_int_distribution<> distrib(0, blocks.size());
		Blocks::const_iterator it = blocks.begin();
		std::advance(it,distrib(gen));
		if(it != blocks.end()) &*it;

		return NULL;
	}
	/*void Day::get_hours_around(const Time& hour, unsigned int count,Day::Block& block)const
	{
		if(count == 0) return;
		else if(count == 1)
		{
			get_hours_around(hour,block);
			return;
		}

		const_iterator it = std::find(begin(),end(),hour);
		if(it == end()) return;
		for(unsigned int i = 0; i < count; i++)
		{

		}
	}*/
	void Day::get_hours_around(const Time& hour,Day::Block& block)const
	{
		const_iterator it = std::find(begin(),end(),hour);
		if(it != end())
		{
			block.push_back(&*it);
		}
		else
		{
			return;
		}
	}
	/*bool Day::is_continue(const core::Time& first, const core::Time& second, const Data& data)
	{
		core::Time newdt;
		data.config.add(first,1,newdt);
		if(second == newdt) return true;

		return false;
	}*/

	void Day::clear()
	{
		std::list<Time>::clear();
		blocks.clear();
	}




	void DaysOptions::random(Day& day)const
	{
		if(size() == 0 ) return;

		if(size() == 1)
		{
			day = front();
			return;
		}

		std::uniform_int_distribution<> distrib(0,size() - 1);
		DaysOptions::const_iterator it = begin();
		std::advance(it,distrib(gen));
		day = *it;
	}




	WeekOptions::WeekOptions() : std::vector<DaysOptions>(WeekHours::WEEK_SIZE)
	{

	}

	void WeekOptions::random(WeekHours& week)const
	{
		DaysOptions::const_iterator it;
		std::uniform_int_distribution<> distrib(0,size() - 1);
		for(unsigned int day_actual = 0; day_actual < WeekHours::WEEK_SIZE; day_actual++)
		{
			//std::cout << "day_actual = " << day_actual << "\n";
			if(at(day_actual).empty()) continue;//si no hay elementos a en el dia actual omitir

			it = sche::random(at(day_actual));//no esta vacio
			//std::cout << "day_actual asignado\n";

			week[day_actual] = *it;
		}
	}
	unsigned int WeekOptions::count()const
	{
		unsigned int totals = 0;
		unsigned int actual_combs;
		std::list<WeekHours>::iterator it_last;
		for(unsigned int day_actual = 0; day_actual < WeekHours::WEEK_SIZE; day_actual++)
		{
			if(at(day_actual).size() == 0 ) continue;//si no hay elementosa en elk dia actual omitir

			if(totals > 0) actual_combs = totals * at(day_actual).size();
			else actual_combs = at(day_actual).size();

			totals += actual_combs;
		}

		return totals;
	}
	void WeekOptions::sort(const Configuration& config)
	{
		this->config = &config;
		for(unsigned int day_actual = 0; day_actual < WeekHours::WEEK_SIZE; day_actual++)
		{
			for(Day& day : at(day_actual))
			{
				day.sort(config);
			}
		}
	}

	unsigned int WeekOptions::days_disp() const
	{
		unsigned int count = 0;
		for(const DaysOptions& day : *this)
		{
			if(day.size() > 0) count++;
		}

		return count;
	}


	real distance_by_hour(const Time& day, const Time& base)
	{
		return std::pow(real(day.tm_hour - base.tm_hour),2.0);;
	}
	struct distance_measure
	{
		bool operator()(const real f,const real s) const
		{
			return f < s;
		}
	};
	/*bool WeekHours::get_day(unsigned int day_num,unsigned int hours,const core::Time& base,const Configuration& config,Day& day)const
	{
		if(hours == 0) return false;

		DaysOptions ops;
		unsigned int count_post;
		Day::const_iterator it_prev;
		Day::Block block;
		bool post_flags = false;
		if(day_num > 6) throw core::Exception("El dia solicitado no es valido.",__FILE__,__LINE__);
		const Day& days_ops = at(day_num);
		//buscar si algun dia coinside con la cantidad de horas necesitadas
		for(const Day& day_op : days_ops)
		{
			if(day_op.size() < hours) continue;
			count_post = 0;
			block.clear();
			for(Day::const_iterator it = day_op.begin()++; it != day_op.end(); it++)
			{
				it_prev = it;
				it_prev--;
				post_flags = is_post_hour(*it_prev,*it,config);
				if(not post_flags)
				{//si no se comp-letan la minimia cantidad de horas continuas
					count_post = 0;
					continue;
				}

				if(post_flags) count_post++;
				if(count_post < hours)
				{
					block.push_back(&*it);
				}
				else if(count_post == hours)
				{
					block.push_back(&*it);
					Day new_day;
					new_day.add(block);
					ops.push_back(new_day);
				}
			}
		}
		if(ops.size() < 2)
		{
			return false;//si no hay elecion simplemene no offrece datos
		}

		std::multimap<real,const Day*,distance_measure> day_ops2;
		for(const Day& day : ops)
		{//introduce los datos en una lista ordenada por su distanca a la hora base
			day_ops2.insert({distance_by_hour(day,base),&day});
		}
		day = *day_ops2.begin()->second;//optiene el elemento mas cercano a la hora base
		return true;//si pudo ofrecer datos
	}*/




	const unsigned int WeekHours::WEEK_SIZE = 7;
	WeekHours::WeekHours()
	{
		resize(7);
	}
	WeekHours::WeekHours(const Configuration& c)
	{
		resize(7);
		config = &c;
	}

	/*void WeekHours::set(const Configuration& c)
	{
		config = &c;
		for(Day& day : *this)
		{
			day.sort(c);
		}
	}*/

	const Configuration& WeekHours::get_configuration()const
	{
		return *config;
	}
	bool WeekHours::check_configuration()const
	{
		return config;
	}


	void WeekHours::inters(const WeekHours& comp1, const WeekHours& comp2)
	{
		if(comp2.size() != comp1.size() and size() == comp1.size()) throw core::Exception("La cantidad de dias no coinciden",__FILE__,__LINE__);
		if(size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);
		if(comp1.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);
		if(comp2.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);


		for(unsigned int i = 0; i < size(); i++)
		{
			at(i).inters(comp1[i],comp2[i]);
		}

		return;
	}
	unsigned int WeekHours::days_disp() const
	{
		unsigned int count = 0;
		for(const Day& day : *this)
		{
			if(day.size() > 0) count++;
		}

		return count;
	}

	void WeekHours::combns(const Subject& subject, WeekOptions& week_combs)const
	{
		if(week_combs.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La cantidad de dias en la semana incorrecto",__FILE__,__LINE__);
		if(size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);

		for(unsigned int day = 0; day < WEEK_SIZE ; day++)
		{
			for(unsigned int hours = 1; hours <= subject.get_time(); hours++)
			{
				if(not at(day).empty())  at(day).combns(week_combs[day],hours);
			}
		}

		//TODO:Agregar combinacion para 'Menor cantidad de dias'
		//Dever dar la posibildad de la mayor cantidad de horas posibles al dia

		//TODO:Hay varias combinaciones posibles desde 1 hasta subject->get_time()

	}
	void WeekHours::sort(const Configuration& config)
	{
		this->config = &config;
		for(Day& day : *this)
		{
			day.sort(config);
		}
	}
	void WeekHours::print(std::ostream& out) const
	{
		for(const Day& day : *this)
		{
			if(day.haveDisponible ())
			{
				out << "\n";
				day.print_day(out);
				out << "\n";
				day.print_blocks(out);
			}
		}
	}
	check_codes WeekHours::check() const
	{
		for(const Day& day : *this)
		{
			check_codes code = day.check();
			if(day.check() != check_codes::PASS) return code;
		}

		return check_codes::PASS;
	}
	bool WeekHours::empty()const
	{
		for(const Day& day : *this)
		{
			if(day.size() > 0) return false;
		}

		return true;
	}
	unsigned int WeekHours::count_hours()const
	{
		unsigned int count = 0;
		for(const Day& day : *this)
		{
			count += day.size();
		}

		return count;
	}
	void WeekHours::print_intevals_csv(std::ostream& out, const Configuration& data) const
	{
		for(unsigned int i = 0; i < size(); i++)
		{
			at(i).print_intevals_csv(out,data);
			if(i < size() - 1) out << ",";
		}
	}
	void WeekHours::clear_days()
	{
		for(unsigned int i = 0; i < size(); i++)
		{
			at(i).clear();
		}
	}
	/*void WeekHours::cover(const Subject& subject, WeekHours& week)const
	{
		const Day* day = random_day_disp();
		if(day == NULL) return; //No hay dias disponibles

		const Day::Block* block = day->random_block();
		if(block == NULL) return;//No hay horas disponibles

		const core::DataTime* hour = *random(*block);

		unsigned int disp = days_disp();
		unsigned int hours_per_day = subject.get_time() / disp;
		unsigned int hours_hat = subject.get_time() - (hours_per_day * disp);

		for(unsigned int i = 0; i < disp; i++)
		{
			if(at(i).size() > 0)
			{
				Day::Block block;
				day->get_hours_around(*hour,hours_per_day,block);
				if(block.size() > 0) week[i].add(block);
				block.clear();
			}
		}
	}*/
	const Day* WeekHours::random_day_disp()const
	{
		if(days_disp() == 0) return NULL;

		const Day* day = NULL;
		unsigned int count = 0;
		std::uniform_int_distribution<> distrib(0, 6);
		do
		{
			day = &at(distrib(gen));
			count++;
		}
		while(day->size() > 0 and count < 14);

		return day;
	}
	bool WeekHours::get_day(unsigned int day_num,unsigned int hours,const Time& base,const Configuration& config,Day& day)const
	{
		if(day_num > 6) throw core::Exception("El dia solicitado no es valido.",__FILE__,__LINE__);
		if(hours == 0) return false;
		if(at(day_num).empty()) return false;

		//std::cout << "Step 1\n";

		const Day* day_op;
		//std::cout << "Step 2\n";
		std::multimap<real,const Time*,distance_measure> day_ops2;
		Day newDay;
		//for(unsigned int i = day_num; i < WeekHours::WEEK_SIZE; i++)
		{


			day_ops2.clear();
			day_op = &at(day_num);

			for(const Time& time : *day_op)
			{
				day_ops2.insert({distance_by_hour(time,base),&time});
			}

			//escojer las mas proximas
			newDay.clear();
			unsigned int j = 0;
			//for(auto const& [key,value] : day_ops2)
			for(auto it = day_ops2.begin(); it != day_ops2.end();it++)
			{
				if(j >= day_ops2.size()) break;
				if(j >= hours) break;

				newDay.push_back(*(*it).second);

				j++;
			}
			if(newDay.size() == hours)
			{
				day = newDay;
				return true;
			}
		}

		return false;//si pudo ofrecer datos
	}







	IntervalTime::IntervalTime()
	{}
	IntervalTime::IntervalTime(const std::string& b,const std::string& e)
	{
		set_begin(b);
		set_end(e);
	}
	void IntervalTime::granulate(const Configuration& config, Day& out)
	{
		if(begin.tm_wday != end.tm_wday) throw core::Exception("El intervalo de tiempo deve especificar el mismos dia.",__FILE__,__LINE__);
		if(begin.tm_hour >= end.tm_hour) throw core::Exception("La hora de inicio deve ser meno que lahora final.",__FILE__,__LINE__);

		int hours = config.to_hours(begin.diff(end));
		//std::cout << "hours = " << hours<< "\n";

		if(hours < 1) return;

		//std::cout << "new time\n";
		//begin.print(std::cout,"%c");
		Time newtime = begin;
		//std::cout << "\n";
		out.push_back(newtime);
		for(int i = 1; i < hours; i++)
		{
			newtime.add(config.get_seconds_per_hour());
			//newtime.print(std::cout,"%c");
			//std::cout << "\n";
			if(begin.tm_wday != newtime.tm_wday)
			{
				std::string msg = "Todos los elementos deven tener el mismo dia de semana, '";
				msg = msg + std::to_string(begin.tm_wday) + "' con '" + std::to_string(newtime.tm_wday) + "'";
				//throw core::Exception(msg,__FILE__,__LINE__);
			}
			out.push_back(newtime);
		}
	}
	/*void IntervalTime::granulate(const Configuration* config, WeekHours& out)
	{
		if(begin.tm_wday != end.tm_wday) throw core::Exception("El intervalo de tiempo deve especificar el mismos dia.",__FILE__,__LINE__);
		if(begin.tm_hour >= end.tm_hour) throw core::Exception("La hora de inicio deve ser meno que lahora final.",__FILE__,__LINE__);

		int hours = config->to_hours(begin.diff(end));

		if(hours < 1) return;

		Day& day = out[begin.tm_wday];
		Day::Block b;
		day.get_blocks().push_back(b);
		Day::Block& block = day.get_blocks().back();

		tm tm1 = begin;
		time_t t = mktime(&tm1);
		tm* newt = localtime(&t);
		newt->tm_wday = begin.tm_wday;
		day.push_back(*newt);
		block.push_back(&day.back());
		//std::cout << "t = " << t << "\n";
		for(int i = 1; i < hours; i++)
		{
			t += config->get_seconds_per_hour(); // 60 segundos por 60 minutos = una hora
			//std::cout << "t = " << t << "\n";
			newt = localtime(&t);
			newt->tm_wday = begin.tm_wday;
			day.push_back(*newt);
			block.push_back(&day.back());
		}
	}*/
	/*void IntervalTime::set_begin(const Configuration* config,const std::string& str)
	{
		begin.read(str,Configuration::formats_dt_dayn_hour);
	}
	void IntervalTime::set_end(const Configuration* config,const std::string& str)
	{
		end.read(str,Configuration::formats_dt_dayn_hour);
	}*/
	void IntervalTime::set_begin(const std::string& str)
	{
		begin.read(str,"%a %H:%M");
	}
	void IntervalTime::set_end(const std::string& str)
	{
		end.read(str,"%a %H:%M");
	}




	const std::string Configuration::formats_dt_hour = "%H:%M";
	const std::string Configuration::formats_dt_day_hour = "%a %H:%M";
	const std::string Configuration::formats_dt_dayn_hour = "%w %H:%M";

	void Configuration::init()
	{
		schema_week = SchemaWeek::MF;
		seconds_per_hour = 45 * 60;
		format = FormatDT::DAY_HOUR;
		hours_sigma = 0.085;
		out_dir = "logs/schedule";
	}
	Configuration::Configuration()
	{
		init();
	}
	Configuration::Configuration(const std::string& dir)
	{
		init();
		out_dir = dir;
	}

	/*unsigned int Configuration::get_time_per_hour() const
	{
		return time_per_hour;
	}*/
	std::time_t Configuration::get_seconds_per_hour() const
	{
		return seconds_per_hour;
	}
	Configuration::SchemaWeek Configuration::get_schema_week()const
	{
		return schema_week;
	}
	Configuration::Schema Configuration::get_schema()const
	{
		return schema;
	}
	real Configuration::get_hours_sigma()const
	{
		return hours_sigma;
	}
	/*const std::string& Configuration::get_format_string_datatime()const
	{
		switch(format)
		{
			case FormatDT::HOUR:
				return formats_dt_hour;
			case FormatDT::DAY_HOUR:
				return formats_dt_day_hour;
			case FormatDT::NONE:
				throw core::Exception("Formato de tiempo no asignado",__FILE__,__LINE__);
			default:
				throw core::Exception("Formato de tiempo desconocido",__FILE__,__LINE__);
		}
	}
	const std::string& Configuration::get_format_string_datatime(FormatDT format)
	{
		switch(format)
		{
			case FormatDT::HOUR:
				return formats_dt_hour;
			case FormatDT::DAY_HOUR:
				return formats_dt_day_hour;
			case FormatDT::NONE:
				throw core::Exception("Formato de tiempo no asignado",__FILE__,__LINE__);
			default:
				throw core::Exception("Formato de tiempo desconocido",__FILE__,__LINE__);
		}
	}*/
	void Configuration::set_schema(Schema s)
	{
		schema = s;
	}
	unsigned int Configuration::to_hours(double t)const
	{
		return t/seconds_per_hour;
	}
	int Configuration::get_begin_day() const
	{
		switch(schema_week)
		{
			case SchemaWeek::MF:
			case SchemaWeek::MS:
				return 1;

			default:
				throw core::Exception("Esquema de semana desconocido.",__FILE__,__LINE__);
		}
	}
	Configuration::FormatDT Configuration::get_format_dt()const
	{
		return format;
	}
	/*void Configuration::add(const core::Time& dt, unsigned int hours, core::Time& result)
	{
		tm tm_dt = dt;
		time_t dt_t = mktime(&tm_dt);
		dt_t += hours * get_seconds_per_hour();
		result = *localtime(&dt_t);
	}*/
	/*void Configuration::rest(const core::Time& dt, unsigned int hours, core::Time& result)
	{
		tm tm_dt = dt;
		time_t dt_t = mktime(&tm_dt);
		dt_t -= hours * get_time_per_hour() * 60;
		result = *localtime(&dt_t);
	}*/
	const std::string Configuration::get_out_directory()const
	{
		return out_dir;
	}


	Target::Target() : config(NULL)
	{
		init();
	}
	Target::Target(const Configuration* c) : config(c)
	{
		init();
	}
	void Target::init()
	{
		times.resize(7);
	}
	const Configuration* Target::operator =(const Configuration* c)
	{
		config = c;
		return c;
	}
	const Configuration* Target::set(const Configuration* c)
	{
		config = c;
		return c;
	}
	/*void Target::save(const Day& day)
	{
		for(const core::DataTime& dt : day)
		{
			times[dt.tm_wday].push_back(dt);//el dia de la semana es el indice ene le arreglo
		}
	}*/
	WeekHours& Target::get_week()
	{
		return times;
	}
	const WeekHours& Target::get_week()const
	{
		return times;
	}
	void Target::print(std::ostream& out) const
	{
		for(const Day& day : times)
		{
			for(const Time& dt: day)
			{
				out << std::put_time(&dt, "%a %H:%M");
				out << " ";
			}
			out << ",";
		}
	}
	/*bool Target::cmpHour(const core::DataTime& f,const core::DataTime& s)
	{
		return f.tm_hour < s.tm_hour;
	}*/
	/*void Target::sort()
	{
		for(Day& day : times)
		{
			day.sort();
		}
	}*/




	Teacher::Teacher(const std::string& name,const std::string& ap,const std::string& am) : oct::core::Person(name,ap,am)
	{

	}
	Teacher::Teacher(const std::string& name) : oct::core::Person(name)
	{

	}
	Teacher::Teacher()
	{

	}
	void Teacher::print(std::ostream& out) const
	{
		out << get_name() << ",";
		Target::print(out);
	}





	Room::Room(const std::string& n)
	{
		name = n;
	}
	Room::Room()
	{

	}

	Room& Room::operator =(const std::string& n)
	{
		name = n;

		return *this;
	}
	const std::string& Room::get_name()const
	{
		return name;
	}
	void Room::print(std::ostream& out)const
	{
		out << get_name() << ",";
		Target::print(out);
	}




	Subject::Subject(const std::string& n)
	{
		name = n;
	}
	Subject::Subject()
	{

	}
	const std::string& Subject::get_name()const
	{
		return name;
	}
	void Subject::set(const std::string& n,unsigned int t)
	{
		name = n;
		time = t;
	}
	unsigned int Subject::get_time()const
	{
		return time;
	}
	void Subject::print(std::ostream& out) const
	{
		out << get_name() << ",";
		out << get_time();
	}




	Targets::Targets() : dataObject(NULL)
	{
	}
	Targets::Targets(const Data* d) : dataObject(d)
	{
	}
	const Data* Targets::operator = (const Data* d)
	{
		dataObject = d;
		return d;
	}
	const Data* Targets::set(const Data* d)
	{
		dataObject = d;
		return d;
	}
	void Targets::fetch_times(Target& target,std::stringstream& ssline, unsigned int line,const std::string& fn)
	{
		ec::sche::IntervalTime time;
		std::string data,strH;
		Day day;
		std::stringstream ssTime;
		//int timeDay = dataObject->config.get_begin_day();
		while(std::getline(ssline,data,','))
		{
			/*if(dataObject->config.get_format_dt() == Configuration::FormatDT::HOUR and timeDay > 6)
			{
				std::string msg = "El formtato indicado solo permite 7 datos de entrada en ";
				msg += "'" + fn + "':" + std::to_string(line);
				throw core::Exception(msg, __FILE__,__LINE__);
			}*/
			strH = "";
			//std::cout << data << "\n";
			ssTime.clear();
			ssTime << data;

			std::getline(ssTime,strH,'-');
			//std::cout << "strH : '" << strH << "'\n";
			time.set_begin(strH);
			//time.begin.print(std::cout,"%c");
			//std::cout << "\n";

			std::getline(ssTime,strH,'-');
			//std::cout << "strH : '" << strH << "'\n";
			time.set_end(strH);
			//time.end.print(std::cout,"%c");
			//std::cout << "\n";

			if(time.begin.tm_wday != time.end.tm_wday)
			{
				std::string msg = "El intervalode tiempo se deve referir al mimso dia ";
				msg += "'" + fn + "':" + std::to_string(line);
				throw core::Exception(msg, __FILE__,__LINE__);
			}
			if(time.begin.tm_hour >= time.end.tm_hour)
			{
				std::string msg = "La hora de inicio deve ser menor que la hora final ";
				msg += "'" + fn + "':" + std::to_string(line);
				throw core::Exception(msg, __FILE__,__LINE__);
			}
			day.clear();
			time.granulate(dataObject->config,day);
			//day.sort(dataObject->config);
			//day.print_day(std::cout);
			//std::cout << "\n\n";
			if(not day.empty()) target.get_week()[day.front().tm_wday].add(day);
			//timeDay++;
		}
		target.get_week().sort(dataObject->config);
	}







	Teachers::Teachers(const std::string& fn)
	{
		loadFile(fn);
	}
	Teachers::Teachers()
	{

	}
	const std::list<Teacher>& Teachers::get_list() const
	{
		return teachers;
	}
	void Teachers::loadFile(const std::string& fn)
	{
		if(not dataObject) throw core::Exception("dataObject no asignado.", __FILE__,__LINE__);

		oct::core::Shell shell;
		//std::cout << "cwd 2:" << shell.cwd() << "\n";
		//std::cout << "dir 2:" << fn << "\n";

		std::fstream csv(fn, std::ios::in);
		std::string line,data,strTime,strH;
		if(csv.is_open())
		{
			unsigned int line_number = 1;
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				std::getline(str,data,',');
				Teacher t;
				teachers.push_back(t);
				Teacher& teacher = teachers.back();
				((Target&)teacher) = &dataObject->config;
				//std::cout << data << ",";
				teacher = data;
				fetch_times(teacher,str,line_number,fn);
				line_number++;
				//std::cout << "\n";
			}
			indexing();
		}
		else
		{
			std::string msg = "Fallo la aperturade '";
			msg += fn + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	void Teachers::print(std::ostream& out)
	{
		for(Teacher& row : teachers)
		{
			row.print(out);
			out << "\n";
		}
	}
	void Teachers::indexing()
	{
		if(teacher_by_name.size() > 0) teacher_by_name.clear();
		for(Teacher& t : teachers)
		{
			teacher_by_name.insert({t.get_name().c_str(),&t});
		}
	}
	const Teacher* Teachers::search(const std::string& str) const
	{
		std::map<std::string, Teacher*>::const_iterator it = teacher_by_name.find(str);

		if(it != teacher_by_name.end()) return it->second;
		return NULL;
	}







	Subjects::Subjects(const std::string& fn, const Data* d) : Targets(d)
	{
		loadFile(fn);
	}
	Subjects::Subjects()
	{
	}
	void Subjects::loadFile(const std::string& fn)
	{
		if(not dataObject) throw core::Exception("dataObject no asignado.", __FILE__,__LINE__);

		std::fstream csv(fn, std::ios::in);
		std::string line,data,strH;
		if(csv.is_open())
		{
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				Subject s;
				subjects.push_back(s);
				Subject& subject = subjects.back();
				((Target&)subject) = &dataObject->config;
				//std::cout << line;
				//std::cout << data << ",";

				std::getline(str,data,',');
				//std::cout << data << ",";
				std::string name = data;

				std::getline(str,data,',');
				std::string time = data;
				//std::cout << "\n";
				subject.set(name,std::stoi(time));
				/*if(dataObject->config.get_schema() == Configuration::Schema::WITH_SUBJECTS_TIMES)
				{
					ec::sche::Time time;
					int timeDay = dataObject->config.get_begin_day();
					while(std::getline(str,data,','))
					{
						std::stringstream ssTime(data);
						std::getline(ssTime,strH,'-');
						if(dataObject->config.get_format_dt() == Configuration::FormatDT::HOUR) strH = std::to_string(timeDay) + " " + strH;
						time.set_begin(strH);
						std::getline(ssTime,strH,'-');
						if(dataObject->config.get_format_dt() == Configuration::FormatDT::HOUR) strH = std::to_string(timeDay) + " " + strH;
						time.set_end(strH);
						time.granulate(&dataObject->config,subject.get_times());
						timeDay++;
					}
				}	*/
			}
			indexing();
		}
		else
		{
			std::string msg = "Fallo la aperturade '";
			msg += fn + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	void Subjects::print(std::ostream& out)const
	{
		for(const Subject& s : subjects)
		{
			s.print(out);
			out << "\n";
		}
	}
	void Subjects::indexing()
	{
		if(subject_by_name.size() > 0) subject_by_name.clear();
		for(Subject& s : subjects)
		{
			subject_by_name.insert({s.get_name().c_str(),&s});
		}
	}
	const Subject* Subjects::search(const std::string& str) const
	{
		std::map<std::string, Subject*>::const_iterator it = subject_by_name.find(str);

		if(it != subject_by_name.end()) return it->second;
		return NULL;
	}
	const std::list<Subject>& Subjects::get_list() const
	{
		return subjects;
	}









	Teachers_Subjects::Row::Row()
	{

	}
	void Teachers_Subjects::Row::print(std::ostream& out)const
	{
		out << teacher->get_name() << ",";
		for(const Subject* s : *this)
		{
			out << s->get_name() << ",";
		}
	}
	Teachers_Subjects::Teachers_Subjects(const std::string& fn,const Data* d) : Targets(d)
	{
		loadFile(fn);
	}
	Teachers_Subjects::Teachers_Subjects()
	{

	}
	const std::list<Teachers_Subjects::Row>& Teachers_Subjects::get_list() const
	{
		return teachers_subjects;
	}
	void Teachers_Subjects::loadFile(const std::string& fn)
	{

		if(not dataObject) throw core::Exception("dataObject no asignado.", __FILE__,__LINE__);

		std::fstream csv(fn, std::ios::in);
		std::string line,data;
		if(csv.is_open())
		{
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				//std::cout << line;
				std::getline(str,data,',');
				Teachers_Subjects::Row row;
				const Teacher* rt = dataObject->teachers.search(data);
				if(rt)
				{
					row.teacher = rt;
				}
				else
				{
					std::string msg = "Archivo '";
					msg += fn + "', el maestro '" + data + "', no esta registrada en su correpondiente archivo.";
					throw core::Exception(msg,__FILE__,__LINE__);
				}
				//std::cout << data << ",";
				while(std::getline(str,data,','))
				{
					//std::cout << data << ",";
					const Subject* rs = dataObject->subjects.search(data);
					if(rs)
					{
						row.push_back(rs);
					}
					else
					{
						std::string msg = "Archivo '";
						msg += fn + "', la materia '" + data + "', no esta registrada en su correpondiente archivo.";
						throw core::Exception(msg,__FILE__,__LINE__);
					}
				}

				//std::cout << "\n";
				teachers_subjects.push_back(row);
			}
			indexing();
		}
		else
		{
			std::string msg = "Fallo la aperturade '";
			msg += fn + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	void Teachers_Subjects::print(std::ostream& out)const
	{
		for(const Row& row : teachers_subjects)
		{
			row.print(out);
			out << "\n";
		}
	}
	const Teachers_Subjects::Row* Teachers_Subjects::searchTeachers(const std::string& str)const
	{
	 	auto it = teachers_by_name.find(str);
	 	if(it != teachers_by_name.end()) return it->second;
	 	return NULL;
	}
	void Teachers_Subjects::searchSubjects(const std::string& str, std::list<const Row*>& l)const
	{
		typedef std::multimap<std::string, Row*>::const_iterator iterator;
		std::pair<iterator,iterator> result = subjects_by_name.equal_range(str);
		for(iterator it = result.first; it != result.second; it++)
		{
			l.push_back(it->second);
		}
	}
	void Teachers_Subjects::indexing()
	{
		if(teachers_by_name.size() > 0) teachers_by_name.clear();
		if(subjects_by_name.size() > 0) subjects_by_name.clear();
		for(Row& row : teachers_subjects)
		{
			if(not row.teacher) throw core::Exception("Valor nulo para puntero de Maestro",__FILE__,__LINE__);

			auto itTeacher = teachers_by_name.find(row.teacher->get_name());
			if(itTeacher != teachers_by_name.end())
			{
				std::string msg = "El Maestro '";
				msg += row.teacher->get_name() + "' ya esta registrado previeamente en el artivo Maestros/Materias.";
				throw core::Exception(msg,__FILE__,__LINE__);
			}
			teachers_by_name.insert({row.teacher->get_name(),&row});

			for(const Subject* subject : row)
			{
				if(not subject) throw core::Exception("Valor nulo para puntero de Materia",__FILE__,__LINE__);
				subjects_by_name.insert({subject->get_name(),&row});
			}
		}
	}
	void Teachers_Subjects::hour_by_subjects_csv(std::ofstream& fn)
	{
		std::list<const Row*> rows;
		for(const Subject& subject : dataObject->subjects.get_list())
		{
			searchSubjects(subject.get_name(), rows);
			for(const Row* row : rows)
			{
				//hbs_list.find();
			}

			rows.clear();
		}
	}


	Rooms::Rooms(const std::string& fn)
	{
		loadFile(fn);
	}
	Rooms::Rooms()
	{

	}
	const std::list<Room>& Rooms::get_list() const
	{
		return rooms;
	}

	void Rooms::loadFile(const std::string& fn)
	{
		if(not dataObject) throw core::Exception("dataObject no asignado.", __FILE__,__LINE__);

		std::fstream csv(fn, std::ios::in);
		std::string line,data,strTime,strH;
		if(csv.is_open())
		{
			unsigned int line_number = 1;
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				std::getline(str,data,',');
				Room r;
				rooms.push_back(r);
				Room& room = rooms.back();
				//std::cout << data << ",";
				room = data;
				//std::getline(str,data,',');
				//row.subject = data;
				fetch_times(room,str,line_number,fn);
				line_number++;
				//std::cout << "\n";
			}
			indexing();
		}
		else
		{
			std::string msg = "Fallo la aperturade '";
			msg += fn + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	void Rooms::print(std::ostream& out)const
	{
		for(const Room& r : rooms)
		{
			r.print(out);
			out << "\n";
		}
	}
	const Room* Rooms::search(const std::string& str) const
	{
		std::map<std::string, Room*>::const_iterator it = rooms_by_name.find(str);

		if(it != rooms_by_name.end()) return it->second;
		return NULL;
	}
	void Rooms::indexing()
	{
		if(rooms_by_name.size() > 0) rooms_by_name.clear();
		for(Room& r : rooms)
		{
			rooms_by_name.insert({r.get_name(),&r});
		}
	}



	Group::Group()
	{
	}
	void Group::print(std::ostream& out)const
	{
		out << room->get_name() << ",";
		//out << teacher.get_name() << ",";
	}
	bool Group::is_cover(const Subject& s,const Teachers_Subjects& ts)
	{
		std::list<const Teachers_Subjects::Row*> row;
		ts.searchSubjects(s.get_name(),row);
		if(row.size() == 0)
		{
			std::string msg = "La tabla de Maestros-Materia no contine refereancia para '";
			msg += s.get_name() + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}

		for(const Teachers_Subjects::Row* r : row)
		{
			if(r->teacher->get_week().count_hours() >= s.get_time()) return true;
		}

		return false;
	}
	Groups::Groups(const std::string& fn,const Data* d) : Targets(d)
	{
		loadFile(fn);
	}
	Groups::Groups()
	{

	}
	const std::list<Group>& Groups::get_list() const
	{
		return groups;
	}
	std::list<Group>& Groups::get_list()
	{
		return groups;
	}


	void Groups::loadFile(const std::string& fn)
	{

		if(not dataObject) throw core::Exception("dataObject no asignado.", __FILE__,__LINE__);

		std::fstream csv(fn, std::ios::in);
		std::string line,data,strTime,strH;
		if(csv.is_open())
		{
			while(std::getline(csv,line))
			{
				std::stringstream str(line);

				std::getline(str,data,',');
				Group row;
				//std::cout << "room : " << data << "\n";
				const Room* newr = dataObject->rooms.search(data);
				if(newr)
				{
					row.name = data;
					row.room = newr;
				}
				else
				{
					std::string msg = "Archivo '";
					msg += fn + "', la materia '" + data + "', no esta registrada en su correpondiente archivo.";
					throw core::Exception(msg,__FILE__,__LINE__);
				}

				while(std::getline(str,data,','))
				{
					//std::cout << data << ",";
					const Subject* news = dataObject->subjects.search(data);
					if(news)
					{
						row.push_back(news);
					}
					else
					{
						std::string msg = "Archivo '";
						msg += fn + "', la materia '" + data + "', no esta registrada en su correpondiente archivo.";
						throw core::Exception(msg,__FILE__,__LINE__);
					}
				}
				groups.push_back(row);
			}
			indexing();
			max_lessons = (*groups.begin()).size();
			for(std::list<Group>::iterator it = groups.begin(); it != groups.end(); it++)
			{
				if((*it).size()> max_lessons) max_lessons = (*it).size();
			}
		}
		else
		{
			std::string msg = "Fallo la aperturade '";
			msg += fn + "'";
			throw core::Exception(msg,__FILE__,__LINE__);
		}
	}
	void Groups::print(std::ostream& out)const
	{
		for(const Group& row : groups)
		{
			row.print(out);
			out << "\n";
		}
	}
	const Group* Groups::search_name(const std::string& str) const
	{
		std::map<std::string, Group*>::const_iterator it = groups_by_name.find(str);

		if(it != groups_by_subject.end()) return it->second;
		return NULL;
	}
	const Group* Groups::search_by_subject(const std::string& str) const
	{
		std::map<std::string, Group*>::const_iterator it = groups_by_subject.find(str);

		if(it != groups_by_name.end()) return it->second;
		return NULL;
	}
	void Groups::indexing()
	{
		if(groups_by_name.size() > 0) groups_by_name.clear();
		if(groups_by_subject.size() > 0) groups_by_subject.clear();
		std::map<std::string, Group*>::const_iterator it;
		for(Group& g : groups)
		{
			it = groups_by_name.find(g.room->get_name());

			if(it != groups_by_name.end())
			{
				std::string msg;
				msg = "Se esta repitiendo el gruopo '" + g.room->get_name() + "'";
				throw core::Exception(msg,__FILE__,__LINE__);
			}
			groups_by_name.insert({g.room->get_name(),&g});
			for(const Subject* s : g)
			{
				groups_by_subject.insert({s->get_name(),&g});
			}
		}
	}
	unsigned int Groups::get_max_lessons()const
	{
		return max_lessons;
	}




	Data::Data()
	{
	}
	Data::Data(const std::string& in_dir,const std::string& out_dir) : config(out_dir)
	{
		load(in_dir);
	}
	const std::map<Data::key_hbs, Data::HBRS>& Data::get_list_hbrs() const
	{
		return hbrs_list;
	}
	const std::map<std::string, Data::HBS>& Data::get_hbs()const
	{
		return hbs_by_subject;
	}
	void Data::load(const std::string& dir)
	{
		//TODO:validacion estricta delas entredas
		((Targets&)teachers) = this;
		teachers.loadFile(dir + "/teachers.csv");
		((Targets&)subjects) = this;
		subjects.loadFile(dir + "/subjects.csv");
		((Targets&)rooms) = this;
		rooms.loadFile(dir + "/rooms.csv");
		//
		((Targets&)teachers_subjects) = this;
		teachers_subjects.loadFile(dir + "/teachers-subjects.csv");
		((Targets&)groups) = this;
		groups.loadFile(dir + "/groups.csv");

		build();
	}
	void Data::build()
	{
		for(const Teachers_Subjects::Row& row : teachers_subjects.get_list())
		{
			for(const Subject* subject : row)
			{
				std::map<std::string, HBS>::iterator it = hbs_by_subject.find(subject->get_name());
				if(it == hbs_by_subject.end())
				{
					HBS hbs;
					hbs.subject = subject;
					hbs.row = &row;
					hbs.req_hours = subject->get_time();
					hbs.disp_hours = row.teacher->get_week().count_hours();
					hbs_by_subject.insert({subject->get_name(),hbs});
				}
				else
				{
					HBS& hbs = (*it).second;
					hbs.disp_hours += row.teacher->get_week().count_hours();
				}
			}
		}
		for(Group& g : groups.get_list())
		{
			for(const Subject* subject : g)
			{

				//std::cout << "Subject : " << s->get_name() << "\n";
				key_hbs key;
				key.room = g.room;
				key.subject = subject;
				//std::cout << "find  " << s->get_name() << " - " << g.room->get_name() << ".\n";
				std::map<key_hbs, Data::HBRS>::iterator it = hbrs_list.find(key);
				if(it == hbrs_list.end())
				{
					//std::cout << "prev " << s->get_name() << " - " << g.room->get_name() << ".\n";
					HBRS hbrs;
					hbrs.disp_hours = 0;
					hbrs.subject = subject;
					hbrs.room = g.room;
					hbrs.group = &g;
					WeekHours week;
					std::list<const Teachers_Subjects::Row*> rows;
					teachers_subjects.searchSubjects(subject->get_name(),rows);
					if(rows.empty())
					{
						std::string msg;
						msg = "No se encontro la materia '" + subject->get_name() + "' para el salon '" + g.room->get_name() + "'\n";;
						throw core::Exception(msg,__FILE__,__LINE__);
					}
					for(const Teachers_Subjects::Row* row : rows)
					{
						//std::cout << "comparando horaio " << s->get_name() << " - " << g.room->get_name() << " horaios\n";
						week.inters(g.room->get_week(),row->teacher->get_week());
						hbrs.disp_hours += week.count_hours();
						week.clear_days();
					}
					//std::cout << "inserting  " << s->get_name() << " - " << g.room->get_name() << ".\n";
					hbrs_list.insert({key,hbrs});
				}
				else
				{
					HBRS& hbrs = (*it).second;
					WeekHours week;
					std::list<const Teachers_Subjects::Row*> rows;
					teachers_subjects.searchSubjects(subject->get_name(),rows);
					for(const Teachers_Subjects::Row* row : rows)
					{
						week.inters(g.room->get_week(),row->teacher->get_week());
						hbrs.disp_hours += week.count_hours();
						week.clear_days();
					}
				}

				//
				coverage cover;
				cover.subject = subject;
				cover.is = g.is_cover(*subject,teachers_subjects);
				g.cover.insert({subject->get_name(),cover});
			}
		}
	}
	bool Data::key_hbs::operator < (const key_hbs& o) const
	{
		if(room->get_name() < o.room->get_name()) return true;
		else if(subject->get_name() < o.subject->get_name()) return true;
		return false;
	}

	Lesson::Lesson()
	{
		group = NULL;
		subject = NULL;
		teacher = NULL;
		room = NULL;
		data = NULL;
	}
	void Lesson::mutate()
	{
		std::uniform_int_distribution<int> distrib(1,3);
		switch(distrib(gen))
		{
			case 1:
				mutate_change_teacher();
				break;
			case 2:
				mutate_time();
				break;
			case 3:
				mutate_empty_day();
				break;
		}
	}
	void Lesson::mutate_change_teacher()
	{
			if(not data) throw core::Exception("No se asigno el objeto de datos",__FILE__,__LINE__);
			if(not room->get_week().check_configuration()) throw core::Exception("No se ha asignado datos de configuracion",__FILE__,__LINE__);
			if(not teacher->get_week().check_configuration()) throw core::Exception("No se ha asignado datos de configuracion",__FILE__,__LINE__);

			//std::cout << "\tLessons::mutate Step 2.0.2\n";
			std::list<const Teachers_Subjects::Row*> rows;
			//std::cout << "\tMateria : " << lesson->subject->get_name() <<  " \n";
			data->teachers_subjects.searchSubjects(subject->get_name(),rows);
			if(rows.empty())
			{
				std::string msg = "No hay opciones en la busqueda de '";
				msg += subject->get_name() + "'";
				throw core::Exception(msg,__FILE__,__LINE__);
			}
			//std::cout << "\tLessons::mutate Step 2.0.3\n";
			//std::cout << lessons[subject].subject->get_name();
			std::list<const Teachers_Subjects::Row*>::const_iterator itr = random(rows);
			//std::cout << "\tLessons::mutate Step 2.0.4\n";
			if(itr == rows.end())
			{
				std::string msg = "No se encontro maestro asociado para '";
				msg += subject->get_name() + "'";
				throw core::Exception(msg,__FILE__,__LINE__);
			}
			//std::cout << "\tLessons::mutate Step 2.0.5\n";
			teacher = (*itr)->teacher;

			WeekHours week;
			WeekOptions week_opt;
			week.inters(room->get_week(),teacher->get_week());
			week.combns(*subject,week_opt);

			//escoger un dia al azar para sobre-escribir
			std::uniform_int_distribution<int> distrib(0,WeekHours::WEEK_SIZE - 1);
			unsigned int iday = distrib(gen);
			Day* day = &this->week[iday];
			day->clear();
			//day->sort(data->config);
			week_opt[iday].random(*day);
			if(this->week.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);
	}
	void Lesson::mutate_time()
	{
		WeekHours week;
		WeekOptions week_opt;
		week.inters(room->get_week (),teacher->get_week());
		week.combns(*subject,week_opt);

		std::uniform_int_distribution<int> distrib(0,WeekHours::WEEK_SIZE - 1);
		unsigned int iday = distrib(gen);
		Day* day = &this->week[iday];
		day->clear();
		//day->sort(data->config);
		week_opt[iday].random(*day);
		if(this->week.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);
	}
	void Lesson::mutate_empty_day()
	{
		Day* day = NULL;
		unsigned int count = 0;
		do
		{
		 	day = &*random(week);
		 	count++;
		}
		while(not day->empty() and count < 14);

		day->clear();
		if(this->week.size() != WeekHours::WEEK_SIZE ) throw core::Exception("La semana no puede tener mas de 7 dias",__FILE__,__LINE__);
	}
	void Lesson::clear()
	{
		group = NULL;
		subject = NULL;
		teacher = NULL;
		room = NULL;
		data = NULL;
		week.clear_days();
	}
	
	
	
	
	
	

	ClassRoom::ClassRoom()
	{

	}
	ClassRoom::ClassRoom(unsigned int z) : std::vector<Lesson>(z)
	{

	}
	ClassRoom::ClassRoom(const ClassRoom& g)
	{
		resize(g.size());

		for(unsigned int i = 0; i < g.size(); i++)
		{
			at(i) = g[i];
		}
	}
	ClassRoom& ClassRoom::operator =(const ClassRoom& g)
	{
		resize(g.size());

		for(unsigned int i = 0; i < g.size(); i++)
		{
			at(i) = g[i];
		}

		return *this;
	}
	void ClassRoom::juncting_mesh_lessons(const ClassRoom& g1,const ClassRoom& g2)
	{
		if(g1.size() != g2.size()) throw core::Exception("EL tamano de los registros no coincide.",__FILE__,__LINE__);
		if(g1.size() == 0) throw core::Exception("No hay lecciones",__FILE__,__LINE__);
		if(g2.size() == 0) throw core::Exception("No hay lecciones",__FILE__,__LINE__);

		resize(g1.size());
		std::bernoulli_distribution distrib(0.6);
		for(unsigned int i = 0; i < g1.size(); i++)
		{//selecciona al azar una de las collecciones para elegir agregar dico goal a la collacion actual
			if(distrib(gen))
			{
				at(i) = g1.at(i);
			}
			else
			{
				at(i) = g2.at(i);
			}
		}
	}
	void ClassRoom::juncting_choose_one_lesson(const ClassRoom& g2)
	{
		if(g2.size() == 0) throw core::Exception("No hay lecciones",__FILE__,__LINE__);
		
		std::uniform_int_distribution<> distrib(0,g2.size() - 1); 
		unsigned int i = distrib(gen);
		at(i).clear();
		at(i) = g2[i];
	}
	void ClassRoom::mutate()
	{
		if(size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);

		//std::cout << "\tLessons::mutate Step 1\n";

		std::uniform_int_distribution<int> distrib(0, size() - 1);
		//std::bernoulli_distribution random_mutation(0.5);
		//std::cout << "\tLessons::mutate Step 2.0.0\n";
		at(distrib(gen)).mutate();
	}
	void ClassRoom::save_csv(std::ostream& out,const Configuration& config) const
	{
		for(const Lesson& l : *this)
		{
			out << l.subject->get_name() << ",";
			out << l.teacher->get_name() << ",";
			l.week.print_intevals_csv(out,config);
			out << "\n";
		}
	}






	Schedule::Schedule()
	{

	}
	Schedule::Schedule(unsigned int z) : std::vector<ClassRoom>(z)
	{

	}
	Schedule::Schedule(const Schedule& g)
	{
		resize(g.size());

		for(unsigned int i = 0; i < g.size(); i++)
		{
			at(i) = g[i];
		}
		indexing();
	}
	Schedule& Schedule::operator =(const Schedule& g)
	{
		resize(g.size());

		for(unsigned int i = 0; i < g.size(); i++)
		{
			at(i) = g[i];
		}
		indexing();

		return *this;
	}
	void Schedule::indexing()
	{
		if(lesson_by_teacher.size() > 0) lesson_by_teacher.clear();
		for(const ClassRoom& lessons : *this)
		{
			for(const Lesson& g : lessons)
			{
				lesson_by_teacher.insert({g.teacher->get_name(),&g});
				//std::cout << "Indexing : " << g.teacher->get_name() << "\n";
			}
		}
	}
	void Schedule::search_teachers(const std::string& str, std::vector<const Lesson*>& result)const
	{
		typedef std::multimap<std::string, const Lesson*>::const_iterator iterator;
		std::pair<iterator,iterator> r = lesson_by_teacher.equal_range(str);
		for(iterator it = r.first; it != r.second; it++)
		{
			result.push_back(it->second);
		}
	}
	void Schedule::juncting_mesh_lessons(const Schedule& s1,const Schedule& s2)
	{
		//std::cout << "Size 1 = " << s1.size() << "\n";
		//std::cout << "Size 2 = " << s2.size() << "\n";
		if(s1.size() != s2.size()) throw core::Exception("Los tamanos de horaios no coincide",__FILE__,__LINE__);
		if(s1.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		if(s2.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);

		for(unsigned int i = 0; i < size(); i++)
		{
			at(i).juncting_mesh_lessons(s1[i],s2[i]);
		}
	}
	void Schedule::juncting_mesh_classroom(const Schedule& s1,const Schedule& s2)
	{
		//std::cout << "Size 1 = " << s1.size() << "\n";
		//std::cout << "Size 2 = " << s2.size() << "\n";
		if(s1.size() != s2.size()) throw core::Exception("Los tamanos de horaios no coincide",__FILE__,__LINE__);
		if(s1.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		if(s2.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);

		std::bernoulli_distribution distrib(0.6);
		for(unsigned int i = 0; i < s1.size(); i++)
		{
			if(distrib(gen))
			{
				at(i) = s1.at(i);
			}
			else
			{
				at(i) = s2.at(i);
			}
		}
	}
	void Schedule::juncting_half(const Schedule& s1,const Schedule& s2)
	{
		//std::cout << "Size 1 = " << s1.size() << "\n";
		//std::cout << "Size 2 = " << s2.size() << "\n";
		if(s1.size() != s2.size()) throw core::Exception("Los tamanos de horaios no coincide",__FILE__,__LINE__);
		if(s1.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		if(s2.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		
		unsigned int step = s1.size()/2;
		unsigned int i;
		for(i = 0; i < step; i++)
		{
			at(i) = s1.at(i);
		}
		for(; i < s1.size(); i++)
		{
			at(i) = s2.at(i);
		}
	}	
	void Schedule::juncting_choose_one_lesson(const Schedule& s1,const Schedule& s2)
	{
		//std::cout << "Size 1 = " << s1.size() << "\n";
		//std::cout << "Size 2 = " << s2.size() << "\n";
		if(s1.size() != s2.size()) throw core::Exception("Los tamanos de horaios no coincide",__FILE__,__LINE__);
		if(s1.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		if(s2.size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);

		std::bernoulli_distribution distrib(0.6);
		for(unsigned int i = 0; i < s1.size(); i++)
		{
			at(i) = s1.at(i);
		}
		
		std::uniform_int_distribution<> distribChoose(0,s2.size() - 1); 
		unsigned int i = distribChoose(gen);
		at(i).juncting_choose_one_lesson(s2[i]);
	}
	void Schedule::mutate()
	{
		if(size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		std::uniform_int_distribution<int> distrib(0, size() - 1);
		at(distrib(gen)).mutate();
	}

	void Schedule::save_csv(const Configuration& config,const std::string& dir) const
	{
		std::ofstream out_csv;
		std::string fn;
		for(const ClassRoom& cr : *this)
		{
			fn = dir + "/" + cr[0].group->name + ".csv";
			//std::cout << "Open Schedule : " << fn << "\n";
			out_csv.open(fn);
			if(out_csv.is_open())
			{
				cr.save_csv(out_csv,config);
				out_csv.flush();
				out_csv.close();
			}
			else
			{
				std::string msg = "Fallo la apertura de '";
				msg += fn + "'";
				throw core::Exception(msg,__FILE__,__LINE__);
			}
		}
	}
}

