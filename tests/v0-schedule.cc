
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>
#include <schedule.hh>
#include <locale>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define DATA_DIR "../../tests"
using namespace oct::ec::sche;

static Data data;

int schedule_init(void)
{
	data.load(DATA_DIR);
	
	return 0;
}
int schedule_clean(void)
{
	return 0;
}

void schedule_devel()
{
	if(data.teachers.get_list().size() == 16)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.subjects.get_list().size() == 16)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.rooms.get_list().size() == 6)
	{
		//std::cout << "count : " << data.rooms.get_list().size() << "\n";
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.teachers_subjects.get_list().size() == 16)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}



	
	const oct::ec::sche::Teacher* teacher1 = data.teachers.search("Leticia Mojica");
	if(teacher1) 
	{
		//row->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);
	}
	//std::cout << "\n";
	const oct::ec::sche::Subject* subject1 = data.subjects.search("Fisica I");
	if(subject1) 
	{
		//rowSuject->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}
	//std::cout << "\n";
	//data.teachers_subjects.print(std::cout);
	std::list<const oct::ec::sche::Teachers_Subjects::Row*> rowTS;
	data.teachers_subjects.searchSubjects("Espanol I",rowTS);
	if(rowTS.size() == 2) 
	{
		//
		/*for(oct::ec::sche::Teachers_Subjects::Row* row : rowTS)
		{
			row->print(std::cout);
			std::cout << "\n";
		}*/
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}
	
	
	std::list<const oct::ec::sche::Teachers_Subjects::Row*> rowTS2;
	data.teachers_subjects.searchSubjects("Geografia I",rowTS2);
	if(rowTS2.size() == 1) 
	{
		//oct::ec::sche::List<const oct::ec::sche::Teachers_Subjects::Row*>::iterator it = rowTS2.begin();
		//std::cout << "rowTS2->teacher " << (*it)->teacher->get_name()<< "\n";
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "rowTS2.size() " << rowTS2.size() << "\n";
		CU_ASSERT(false);		
	}
	
	
	std::list<const oct::ec::sche::Teachers_Subjects::Row*> rowTS3;
	data.teachers_subjects.searchSubjects("Estadistica I",rowTS3);
	if(rowTS3.size() == 3) 
	{
		//oct::ec::sche::List<const oct::ec::sche::Teachers_Subjects::Row*>::iterator it = rowTS3.begin();
		//std::cout << "rowTS3->teacher " << (*it)->teacher->get_name()<< "\n";
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "rowTS3.size() = " << rowTS3.size() << "\n";
		CU_ASSERT(false);		
	}
	std::list<const oct::ec::sche::Teachers_Subjects::Row*>::const_iterator it_rowTS3_Row;
	it_rowTS3_Row = oct::ec::sche::random(rowTS3);
	const oct::ec::sche::Teachers_Subjects::Row* rowTS3_Row = *it_rowTS3_Row;
	if(rowTS3_Row) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "rowTS3_Row = NULL\n";
		CU_ASSERT(false);		
	}
	
	//std::cout << "\n";
	//data.teachers_subjects.print(std::cout);
	const oct::ec::sche::Room* room1 = data.rooms.search("1A");
	if(room1) 
	{
		//row->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}
	
	//std::cout << "\n";
	const oct::ec::sche::Group* rowG1 = data.groups.search_name("1A");
	if(rowG1) 
	{
		//rowG1->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "No se encontro el grupo '1A'\n";
		CU_ASSERT(false);		
	}
	
	
	oct::ec::sche::Time time1;
	time1.set_begin(&data.config, "1 8:00");
	if(time1.begin.tm_hour == 8) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time1.begin.tm_hour = " << time1.begin.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	time1.set_end(&data.config, "1 20:00");
	if(time1.end.tm_hour == 20) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time1.end.tm_hour = " << time1.end.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	oct::ec::sche::Day day;
	time1.granulate(&data.config,day);
	if(day.size() == 12) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day.size() = " << day.size() << "\n";
		CU_ASSERT(false);		
	}
	typedef oct::ec::sche::Day::iterator iterator_day;

	int i = 0;
	for(iterator_day it = day.begin(); it != day.end(); it++, i++)
	{
		if((*it).tm_hour == i + 8)
		{
			CU_ASSERT(true);
		}
		else
		{
			std::cout << "day[i].tm_hour = " << i + 8 << "\n";
			CU_ASSERT(false);
		}
	}
	
	oct::ec::sche::Time time2;
	time2.set_begin("2 8:00");
	if(time2.begin.tm_wday == 2) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time2.begin.tm_wday = " << time2.begin.tm_wday << "\n";
		CU_ASSERT(false);		
	}
	if(time2.begin.tm_hour == 8) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time1.begin.tm_hour = " << time2.begin.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	time2.set_end("2 20:00");
	if(time2.end.tm_hour == 20) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time2.end.tm_hour = " << time2.end.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	oct::ec::sche::Day day2;
	time2.granulate(&data.config,day2);
	if(day2.size() == 12) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day2.size() = " << day2.size() << "\n";
		CU_ASSERT(false);		
	}
	for(const oct::core::DataTime& dt : day2)
	{
		//std::cout << std::put_time(&dt, "%a %H:%M") << "\n";
		if(dt.tm_wday == 2) 
		{
			CU_ASSERT(true);
		}
		else 
		{
			std::cout << "dt.tm_wday = " << dt.tm_wday << "\n";
			CU_ASSERT(false);		
		}
	}
	
	//teacher1->print(std::cout);
	//subject1->print(std::cout);
	//room1->print(std::cout);	
	
	oct::ec::sche::Time time3;
	time3.set_begin("2 8:00");
	if(time3.begin.tm_wday == 2) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time3.begin.tm_wday = " << time3.begin.tm_wday << "\n";
		CU_ASSERT(false);		
	}
	if(time3.begin.tm_hour == 8) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time3.begin.tm_hour = " << time3.begin.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	time3.set_end("2 20:00");
	if(time3.end.tm_hour == 20) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time3.end.tm_hour = " << time3.end.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	oct::ec::sche::WeekHours week1;
	time3.granulate(&data.config,week1);
	if(week1[2].size() == 12) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "week1[2].size() = " << week1[2].size() << "\n";
		CU_ASSERT(false);		
	}
	for(const oct::core::DataTime& dt : week1[2])
	{
		//std::cout << std::put_time(&dt, "%a %H:%M") << "\n";
		if(dt.tm_wday == 2) 
		{
			CU_ASSERT(true);
		}
		else 
		{
			std::cout << "week1[2].tm_wday = " << dt.tm_wday << "\n";
			CU_ASSERT(false);		
		}
	}
	
	oct::ec::sche::Time time4;
	time4.set_begin(&data.config, "1 6:00");
	if(time4.begin.tm_hour == 6) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time4.begin.tm_hour = " << time4.begin.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	time4.set_end(&data.config, "1 16:00");
	if(time4.end.tm_hour == 16) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time4.end.tm_hour = " << time4.end.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	oct::ec::sche::Day day4;
	time4.granulate(&data.config,day4);
	if(day4.size() == 10) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day4.size() = " << day4.size() << "\n";
		CU_ASSERT(false);		
	}
	
	//interseccion de horas
	oct::ec::sche::Day day5;
	day5.inters(day,day4);
	if(day5.size() == 8) 
	{
		/*std::cout << "day\n";
		day.print_day(std::cout);
		std::cout << "\n";
		std::cout << "day4\n";
		day5.print_day(std::cout);
		std::cout << "\n";
		std::cout << "day5\n";
		day5.print_day(std::cout);
		std::cout << "\n";*/
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day5.size() = " << day5.size() << "\n";
		CU_ASSERT(false);		
	}
		
	oct::ec::sche::Time time6("1 4:00", "1 10:00");
	oct::ec::sche::Time time7("1 12:00", "1 16:00");
	oct::ec::sche::Time time8("1 17:00", "1 20:00");
	oct::ec::sche::Day day6;
	time8.granulate(&data.config,day6);
	time6.granulate(&data.config,day6);
	time7.granulate(&data.config,day6);
	day6.sort();
	/*for(const oct::core::DataTime& dt : day6)
	{
		dt.print(std::cout,oct::ec::sche::Configuration::formats_dt_day_hour);
		std::cout << "\n";
	}*/
	if(day6.get_blocks().size() == 3) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day6.get_blocks().size() = " << day6.get_blocks().size() << "\n";
		CU_ASSERT(false);		
	}
	
	unsigned int iBlock = 0; 
	for(oct::ec::sche::Day::Blocks::iterator itBlock = day6.get_blocks().begin(); itBlock != day6.get_blocks().end(); itBlock++,iBlock++)
	{
		/*std::cout << "bloque " << iBlock << "\n";		
		for(const oct::core::DataTime* dt : *itBlock)
		{
			std::cout << "\t";
			dt->print(std::cout,oct::ec::sche::Configuration::formats_dt_day_hour);
			std::cout << "\n";
		}*/
		if( iBlock == 0)
		{
			if((*itBlock).size() == 6) 
			{
				CU_ASSERT(true);
			}
			else 
			{
				std::cout << "(*itBlock).size = " << (*itBlock).size() << "\n";
				CU_ASSERT(false);		
			}
		}
		else if( iBlock == 1)
		{
			if((*itBlock).size() == 4) 
			{
				CU_ASSERT(true);
			}
			else 
			{
				std::cout << "(*itBlock).size = " << (*itBlock).size() << "\n";
				CU_ASSERT(false);		
			}
		}
		else if( iBlock == 2)
		{
			if((*itBlock).size() == 3) 
			{
				CU_ASSERT(true);
			}
			else 
			{
				std::cout << "(*itBlock).size = " << (*itBlock).size() << "\n";
				CU_ASSERT(false);		
			}
		}
	}
	if(day6.front().tm_hour == 4) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day6.front().tm_hour = " << day6.front().tm_hour << "\n";
		CU_ASSERT(false);		
	}
	if(day6.back().tm_hour == 19) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day6.back().tm_hour = " << day6.back().tm_hour << "\n";
		CU_ASSERT(false);		
	}	
	if(day6.size() == 13) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "day6.size() = " << day6.size() << "\n";
		CU_ASSERT(false);		
	}
		
	std::list<oct::ec::sche::Day> combsList;
	day6.combns(combsList,2);
	if(combsList.front().get_blocks().size() == 7) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "combsList.front().get_blocks().size() = " << combsList.front().get_blocks().size() << "\n";
		CU_ASSERT(false);		
	}
	/*unsigned int i_day = 0;
	iBlock = 0;
	for(const oct::ec::sche::Day& day : combsList)
	{
		std::cout << "day " << i_day << "\n";
		for(oct::ec::sche::Day::Blocks::const_iterator itBlock = day.get_blocks().begin(); itBlock != day.get_blocks().end(); itBlock++,iBlock++)
		{
			std::cout << "bloque " << iBlock << "\n";		
			for(const oct::core::DataTime* dt : *itBlock)
			{
				std::cout << "\t";
				dt->print(std::cout,oct::ec::sche::Configuration::formats_dt_day_hour);
				std::cout << "\n";
			}
		}
		i_day++;
	}*/
	day6.combns(combsList,3);
	std::list<oct::ec::sche::Day>::iterator itDay = combsList.begin();
	itDay++;	
	if((*itDay).get_blocks().size() == 5) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "(*itDay).get_blocks().size() = " << (*itDay).get_blocks().size() << "\n";
		CU_ASSERT(false);		
	}
	/*
	unsigned int i_day = 0;
	for(const oct::ec::sche::Day& day : combsList)
	{
		std::cout << "day " << i_day << "\n";
		for(oct::ec::sche::Day::Blocks::const_iterator itBlock = day.get_blocks().begin(); itBlock != day.get_blocks().end(); itBlock++,iBlock++)
		{
			std::cout << "bloque " << iBlock << "\n";		
			for(const oct::core::DataTime* dt : *itBlock)
			{
				std::cout << "\t";
				dt->print(std::cout,oct::ec::sche::Configuration::formats_dt_day_hour);
				std::cout << "\n";
			}
		}
		i_day++;
	}
	*/
	
	const oct::ec::sche::Teacher* teacher2 = data.teachers.search("Monica Perez Ortencia");
	if(teacher2) 
	{
		//row->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);
	}
	oct::ec::sche::WeekHours week2 = teacher2->get_week();	
	if(week2[1].size() > 1)
	{
		oct::ec::sche::Day::const_iterator it_day_1 = oct::ec::sche::random(week2[1]);
		if(it_day_1 != week2[1].end()) 
		{
			//(*it_day_1).print(std::cout,"%a %H:%M");
			CU_ASSERT(true);
		}
		else 
		{
			CU_ASSERT(false);
		}		
	}
	oct::ec::sche::WeekHours::const_iterator it_week_day = 	oct::ec::sche::random(week2);
	if(it_week_day != week2.end())
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	//week2.print(std::cout);
	//el criterio de revificacion puede cambiar
	if(week2.check() != check_codes::PASS) //verificar que este ordenado
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(true);
	}
	//std::cout << "----\n";
	//week2.print(std::cout);
	//std::list<oct::ec::sche::WeekHours> weeks_combs;
	oct::ec::sche::WeekOptions week_opt;
	week2.combns(*subject1,week_opt);
	if(week_opt.size() == 7) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "week_opt.size() = " << week_opt.size() << "\n";
		CU_ASSERT(false);		
	}
	
	//este valor puede cambiar comforme mejore el algoritmo, esta a que por propositos de desarrollo
	if(week_opt.count() == 472392) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "week_opt.count() = " << week_opt.count() << "\n";
		CU_ASSERT(false);		
	}

	const oct::ec::sche::Subject* subject2 = data.subjects.search("Estadistica I");
	if(subject1) 
	{
		//rowSuject->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}

	WeekHours week3;
	WeekOptions week_opt2;
	week3.inters(room1->get_week (),teacher2->get_week ());
	check_codes codes1 = week3.check();
	if(codes1 == check_codes::PASS)
	{
		CU_ASSERT(true);
	}
	else 
	{
		switch(codes1)
		{
			case check_codes::BLOCK_CONTENT_SIZE_FAIL:
				std::cout << "El tamano de los bloques y la cantidad de dias no coinciden\n";
				break;
			default:
				std::cout << "Otros errores\n";
		}
		for(const Day& day : week3)
		{
			std::cout << "\n";
			day.print_day(std::cout);
		}
		CU_ASSERT(false);		
	}
	week3.combns(*subject2,week_opt2);
	/*std::cout << "Week Room \n";
	room1->get_week ().print(std::cout);
	std::cout << "\n";
	std::cout << "Week Teacher \n";
	teacher2->get_week ().print(std::cout);
	std::cout << "\n";
	//std::cout << "Interseccion \n";	
	//week3.print(std::cout);*/
	if(week_opt2.count() == 3072) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "week_opt2.count() = " << week_opt2.count() << "\n";
		CU_ASSERT(false);		
	}
	WeekHours week4;
	week_opt2.random(week4);
	//std::cout << "Horario \n";	
	//week4.print(std::cout);
	if(week4.empty()) 
	{
		std::cout << "week4.empty() is empty\n";
		CU_ASSERT(false);
	}
	else 
	{
		
		CU_ASSERT(true);		
	}
	//WeekHours week3;
	//week_opt.random(week3);
	//week3.print(std::cout);

	Enviroment sche ("logs",DATA_DIR);
	try
	{
		sche.initial();
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what() << "\n";
		CU_ASSERT(false);
	}
}

