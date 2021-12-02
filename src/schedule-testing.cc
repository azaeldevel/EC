
#include <iomanip>


#include "schedule.hh"

namespace oct::ec::sche
{
	

	void Enviroment::testing()
	{
		pile.resize(4);

		pile.at(0).teacher.resize(2);//dos maestros
		pile.at(0).teacher.at(0).resize(6);//6 dias de trabajo lara el mestro
		pile.at(0).teacher.at(1).resize(6);//6 dias de trabajo lara el mestro
		pile.at(0).room.resize(1);//un salon
		pile.at(0).room.at(0).resize(1);//turno matutino
		//horarion de maestro 1
		core::DataTime begin;
		core::DataTime end;		
		strptime("8:00", "%H:%M",&begin);
		strptime("13:00", "%H:%M",&end);
		pulverize_hours(begin,end,pile.at(0).teacher.at(0));
		//std::cout << std::put_time(&begin, "%H:%M") << "\n";
		//std::cout << std::put_time(&end, "%H:%M") << "\n";
		for(core::DataTime& dt : pile.at(0).teacher.at(0))
		{
			std::cout << std::put_time(&dt, "%H:%M") << "\n";
		}
		pulverize_hours(begin,end,pile.at(0).teacher.at(1));
		/*pulverize_hours(begin,end,pile.at(0).teacher.at(2));
		pulverize_hours(begin,end,pile.at(0).teacher.at(3));
		pulverize_hours(begin,end,pile.at(0).teacher.at(4));
		pulverize_hours(begin,end,pile.at(0).teacher.at(5));*/
		//horarion de maestro 2		
		/*pulverize_hours(begin,end,pile.at(0).teacher.at(0));
		pulverize_hours(begin,end,pile.at(1).teacher.at(1));
		pulverize_hours(begin,end,pile.at(2).teacher.at(2));
		pulverize_hours(begin,end,pile.at(3).teacher.at(3));
		pulverize_hours(begin,end,pile.at(4).teacher.at(4));
		pulverize_hours(begin,end,pile.at(5).teacher.at(5));*/
		//clase
		//pile.at(0).subject = 5;
		//
		//horarion de salon
		/*strptime("8:00", "%H:%M",&begin);
		strptime("13:00", "%H:%M",&end);*/
		
		
	}


}

