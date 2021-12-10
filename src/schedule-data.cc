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

#include "schedule.hh"

#if defined(_WIN32) || defined(_WIN64)

extern "C" char* strptime(const char* s,const char* f,struct tm* tm) 
{
	std::istringstream input(s);
	input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
	input >> std::get_time(tm, f);
	if (input.fail()) {
		return nullptr;
	}
	return (char*)(s + input.tellg());
}

#endif

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

	DataTime::DataTime()
	{
		(tm&)*this = {0};
	}
	DataTime::DataTime(const tm& t)
	{
		(tm&)*this = t;
	}
	const time_t* DataTime::operator =(const time_t* t)
	{
		tm* thistm = localtime(t);
		(tm&)*this = *thistm;
		return t;
	}
	const tm& DataTime::operator =(const tm& t)
	{
		(tm&)*this = t;
		return t;
	}
	int DataTime::get_week_day()const
	{
		return tm_wday;
	}

	double DataTime::diff(const DataTime& dt)const
	{
		time_t tm1,tm2;
		tm t1 = *this;
		tm t2 = dt;
		tm1 = mktime(&t1);
		tm2 = mktime(&t2);
		return difftime(tm2, tm1);		
	}
}

namespace oct::ec::sche
{


	void Day::inters(const Day& comp, Day& rest)const
	{		
		for(const core::DataTime& tdt : *this)
		{
			for(const core::DataTime& cdt : comp)
			{
				if(tdt.tm_wday != cdt.tm_wday) throw core::Exception("Los objetos indicado, tiene dias distinto",__FILE__,__LINE__);
				
				if(tdt.tm_hour == cdt.tm_hour) rest.push_back(cdt);
			}
		}		
	}





	WeekHours::WeekHours()
	{
		resize(7);
	}
	void WeekHours::inters(const WeekHours& comp, WeekHours& rest)const
	{		
		if(size() != comp.size()) throw core::Exception("La cantidad de dias no coinciden",__FILE__,__LINE__);
		
		for(unsigned int i = 0; i < size(); i++)
		{
			at(i).inters(comp[i],rest[i]);
		}		
	}


	void Time::granulate(const Configuration* config, Day& out)
	{
		if(begin.tm_wday != end.tm_wday) throw core::Exception("El intervalo de tiempo deve especifficar el mismos dia.",__FILE__,__LINE__);
		
		int hours = config->to_hours(begin.diff(end));	
		
		if(hours < 1) return;
		
		tm tm1 = begin;
		time_t t = mktime(&tm1);
		tm* newt = localtime(&t);
		newt->tm_wday = begin.tm_wday;
		out.push_back(*newt);
		//std::cout << "t = " << t << "\n";
		for(int i = 1; i < hours; i++)
		{
			t += config->get_time_per_hour() * 60; // 60 segundos por 60 minutos = una hora
			//std::cout << "t = " << t << "\n";
			newt = localtime(&t);
			newt->tm_wday = begin.tm_wday;
			out.push_back(*newt);
		}
	}
	void Time::set_begin(const Configuration* config,const std::string& str)
	{
		strptime(str.c_str(), config->get_format_string_datatime().c_str(),&begin);
	}
	void Time::set_end(const Configuration* config,const std::string& str)
	{
		strptime(str.c_str(), config->get_format_string_datatime().c_str(),&end);
	}
	void Time::set_begin(const std::string& str)
	{
		strptime(str.c_str(), "%w %H:%M",&begin);
	}
	void Time::set_end(const std::string& str)
	{
		strptime(str.c_str(), "%w %H:%M",&end);
	}




	std::string Configuration::formats_dt_hour = "%H:%M";	
	std::string Configuration::formats_dt_day_hour = "%a %H:%M";
	
	Configuration::Configuration()
	{
		schema_week = SchemaWeek::MS;
		time_per_hour = 60;
		format = FormatDT::HOUR;
	}
	
	unsigned int Configuration::get_time_per_hour() const
	{
		return time_per_hour;
	}
	Configuration::SchemaWeek Configuration::get_schema_week()const
	{
		return schema_week;
	}
	Configuration::Schema Configuration::get_schema()const
	{
		return schema;
	}
	const std::string& Configuration::get_format_string_datatime()const
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
	void Configuration::set_schema(Schema s)
	{
		schema = s;
	}
	long Configuration::to_hours(double t)const
	{
		long mins = t/60.0;
		long hours = mins/time_per_hour;
		return hours;
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
	void Target::save(const Day& day)
	{
		for(const core::DataTime& dt : day)
		{
			times[dt.tm_wday].push_back(dt);//el dia de la semana es el indice ene le arreglo
		}
	}
	WeekHours& Target::get_times()
	{
		return times;
	}
	const WeekHours& Target::get_times()const
	{
		return times;
	}
	void Target::print(std::ostream& out) const
	{
		for(const Day& day : times)
		{
			for(const core::DataTime& dt: day)
			{
				out << std::put_time(&dt, "%a %H:%M");
				out << " ";
			}
			out << ",";
		}
	}
	bool Target::cmpHour(const core::DataTime& f,const core::DataTime& s)
	{
		return f.tm_hour < s.tm_hour;
	}
	void Target::sort()
	{
		for(Day& day : times)
		{
			day.sort(cmpHour);
		}
	}
	
	
	

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
		
		std::fstream csv(fn, std::ios::in);
		std::string line,data,strTime,strH;
		if(csv.is_open())
		{
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				std::getline(str,data,',');
				Teacher teacher;
				((Target&)teacher) = &dataObject->config;
				//std::cout << data << ",";
				teacher = data;
				ec::sche::Time time;
				Day day;
				//Se inicia en lunes
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
					time.granulate(&dataObject->config,day);
					teacher.save(day);
					timeDay++;
				}
				teachers.push_back(teacher);	
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
				Subject subject;
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
				Day day;			
				if(dataObject->config.get_schema() == Configuration::Schema::WITH_SUBJECTS_TIMES)
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
						time.granulate(&dataObject->config,day);
						subject.save(day);
						timeDay++;
					}
				}				
				subjects.push_back(subject);
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
		out << subject->get_name();
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

				std::getline(str,data,',');
				//std::cout << data << ",";				
				const Subject* rs = dataObject->subjects.search(data);
				if(rs)
				{
					row.subject = rs;
				}
				else 	
				{
					std::string msg = "Archivo '";
					msg += fn + "', la materia '" + data + "', no esta registrada en su correpondiente archivo.";
					throw core::Exception(msg,__FILE__,__LINE__);
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
	void Teachers_Subjects::searchTeachers(const std::string& str, std::list<const Row*>& l)const
	{
		typedef std::multimap<std::string, Row*>::const_iterator iterator;
		std::pair<iterator,iterator> result = teachers_by_name.equal_range(str);
		for(iterator it = result.first; it != result.second; it++)
		{
			l.push_back(it->second);
		}
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
			teachers_by_name.insert({row.teacher->get_name(),&row});
			if(not row.subject) throw core::Exception("Valor nulo para puntero de Materia",__FILE__,__LINE__);
			subjects_by_name.insert({row.subject->get_name(),&row});
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
			while(std::getline(csv,line))
			{
				std::stringstream str(line);
				std::getline(str,data,',');
				Room room;
				//std::cout << data << ",";
				room = data;
				//std::getline(str,data,',');
				//row.subject = data;
				ec::sche::Time time;
				Day day;
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
					time.granulate(&dataObject->config,day);
					room.save(day);
					timeDay++;
				}
				rooms.push_back(room);	
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



	Groups::Group::Group()
	{
	}		
	void Groups::Group::print(std::ostream& out)const
	{
		out << room->get_name() << ",";
		//out << teacher.get_name() << ",";
	}
	
	Groups::Groups(const std::string& fn,const Data* d) : Targets(d)
	{
		loadFile(fn);
	}
	Groups::Groups()
	{
		
	}	
	const std::list<Groups::Group>& Groups::get_list() const
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
				//std::cout << "room : " << data << " : ";
				const Room* newr = dataObject->rooms.search(data);
				if(newr) 
				{
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
	const Groups::Group* Groups::search_name(const std::string& str) const
	{
		std::map<std::string, Group*>::const_iterator it = groups_by_name.find(str);

		if(it != groups_by_subject.end()) return it->second;
		return NULL;		
	}	
	const Groups::Group* Groups::search_by_subject(const std::string& str) const
	{
		std::map<std::string, Group*>::const_iterator it = groups_by_subject.find(str);

		if(it != groups_by_name.end()) return it->second;
		return NULL;		
	}
	void Groups::indexing()
	{
		if(groups_by_name.size() > 0) groups_by_name.clear();
		if(groups_by_subject.size() > 0) groups_by_subject.clear();
		for(Group& g : groups)
		{
			groups_by_name.insert({g.room->get_name(),&g});
			for(const Subject* s : g)
			{
				groups_by_subject.insert({s->get_name(),&g});
			}
		}
	}
	
	
	
	
	void Data::load(const std::string& dir)
	{
		((Targets&)subjects) = this;
		subjects.loadFile(dir + "/subjects.csv");
		((Targets&)teachers) = this;
		teachers.loadFile(dir + "/teachers.csv");
		((Targets&)rooms) = this;
		rooms.loadFile(dir + "/rooms.csv");
		//
		((Targets&)teachers_subjects) = this;
		teachers_subjects.loadFile(dir + "/teachers-subjects.csv");
		((Targets&)groups) = this;
		groups.loadFile(dir + "/groups.csv");
	}
}

