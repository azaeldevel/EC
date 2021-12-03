
#include <iomanip>


#include "schedule.hh"

namespace oct::ec::sche
{
	

	void Enviroment::testing()
	{
		
		data.subjects.loadFile(directory + "/subjects.csv");
		data.teachers.loadFile(directory + "/teachers.csv");
		data.rooms.loadFile(directory + "/rooms.csv");
		data.teachers_subjects.loadFile(directory + "/teachers-subjects.csv");
		
		pile.resize(4);

		pile.at(0).teachers.resize(data.teachers.get_list().size());//dos maestros
		if(data.config.get_schema_week() == Configuration::SchemaWeek::MS)
		{
			for(TeacherDust& dust : pile.at(0).teachers)
			{
				dust.times.resize(6);//6 dias de trabajo lara el mestro
			}
		}
		else
		{
			throw core::Exception("Esquema de semana desconocido",__FILE__,__LINE__);
		}
		pile.at(0).room.resize(1);//un salon
		pile.at(0).room.at(0).resize(1);//turno matutino
		//horarion de maestro 1	
		int i = 0;
		for(const Teachers::Row& row : data.teachers.get_list())
		{
			for(int j = 0; j < row.size(); j++)
			{
				pile.at(0).teachers.at(i).teacher = &row.teacher;
				pulverize_hours(row[j].begin,row[j].end,pile.at(0).teachers.at(i).times.at(j));
			}
			i++;
		}
		/*
		for(const TeacherDust& dust : pile.at(0).teachers)
		{
			std::string name;
			((core::Person*)dust.teacher)->get_name(name);
			std::cout << "\t" << name << "\n";
			for(const DaysTimes& time : dust.times)
			{
				std::cout << "\t\tDia\n";
				for(const core::DataTime& dt : time)
				{
					std::cout << "\t\t" << std::put_time(&dt, "%H:%M") << "\n";
				}
			}
		}
		*/
		//data.teachers.print(std::cout);
		const Teachers::Row* row = data.teachers.search("Leticia Mojica");
		if(row) row->print(std::cout);
		else std::cout << "No se encontro el maestro indicado\n";
		//clase
		pile.at(0).subject = 5;
		//
		//horarion de salon
		//strptime("8:00", "%H:%M",&begin);
		//strptime("13:00", "%H:%M",&end);
	}


}

