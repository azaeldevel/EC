
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

#if CODEBLOCKS_IDE
    #define DATA_DIR "tests/en"
#else
    #define DATA_DIR "../../tests/en"
#endif

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
	//std::cout << "Step 1\n";
	if(data.teachers.get_list().size() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "data.teachers.get_list().size() : " << data.teachers.get_list().size() << "\n";
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
	if(data.rooms.get_list().size() == 8)
	{
		
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "count : " << data.rooms.get_list().size() << "\n";
		CU_ASSERT(false);
	}
	if(data.teachers_subjects.get_list().size() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "data.teachers_subjects.get_list().size() : " << data.teachers_subjects.get_list().size() << "\n";
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
		std::cout << "rowTS.size() = " << rowTS.size() << "\n";;
		CU_ASSERT(false);
	}

	//std::cout << "Step 2\n";
	std::list<const Teachers_Subjects::Row*> rowTS2;
	data.teachers_subjects.searchSubjects("Geografia I",rowTS2);
	if(rowTS2.size() == 1)
	{
		//oct::ec::sche::List<const oct::ec::sche::Teachers_Subjects::Row*>::iterator it = rowTS2.begin();
		//std::cout << "rowTS2->teacher " << (*it)->teacher->get_name()<< "\n";
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "rowTS2.size() = " << rowTS2.size() << "\n";
		CU_ASSERT(false);
	}


	std::list<const oct::ec::sche::Teachers_Subjects::Row*> rowTS3;
	data.teachers_subjects.searchSubjects("Estadistica I",rowTS3);
	if(rowTS3.size() == 2)
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
	data.teachers_subjects.searchSubjects("Fisca I",rowTS3);
	std::list<const Teachers_Subjects::Row*>::const_iterator it_rowTS3_Row = oct::ec::sche::random(rowTS3);
	if(rowTS3.size() >= 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "rowTS3_Row.size() = " << rowTS3.size() << "\n";
		CU_ASSERT(false);
	}
	const Teachers_Subjects::Row* rowTS3_Row = *it_rowTS3_Row;
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


	IntervalTime time1;
	time1.set_begin("Mon 08:00");
	if(time1.begin.tm_hour == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "time1.begin.tm_hour = " << time1.begin.tm_hour << "\n";
		CU_ASSERT(false);
	}
	time1.set_end("Mon 20:00");
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
	day.sort(data.config);
	if(day.size() == 16)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "day.size() = " << day.size() << "\n";
		CU_ASSERT(false);
	}
	//typedef oct::ec::sche::Day::iterator iterator_day;

	/*int i = 0;
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
	}*/

	IntervalTime time2;
	time2.set_begin("Tue 08:00");
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
	time2.set_end("Tue 20:00");
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
	day2.sort(data.config);
	if(day2.size() == 16)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "day2.size() = " << day2.size() << "\n";
		CU_ASSERT(false);
	}
	for(const oct::core::Time& dt : day2)
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

	//std::cout << "Step 3\n";
	
	//teacher1->print(std::cout);
	//subject1->print(std::cout);
	//room1->print(std::cout);

	IntervalTime time3;
	time3.set_begin("Tue 08:00");
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
	time3.set_end("Tue 20:00");
	if(time3.end.tm_hour == 20)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "time3.end.tm_hour = " << time3.end.tm_hour << "\n";
		CU_ASSERT(false);
	}
	/*oct::ec::sche::WeekHours week1;
	time3.granulate(&data.config,week1);
	if(week1[2].size() == 16)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "week1[2].size() = " << week1[2].size() << "\n";
		CU_ASSERT(false);
	}
	for(const oct::core::Time& dt : week1[2])
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
	}*/

	IntervalTime time4;
	time4.set_begin("Mon 05:00");
	if(time4.begin.tm_hour == 5)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "time4.begin.tm_hour = " << time4.begin.tm_hour << "\n";
		CU_ASSERT(false);
	}
	time4.set_end("Mon 16:00");
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
	day4.sort(data.config);
	if(day4.size() == 14)
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
	/*std::cout << "day:\n";
	for(const oct::core::Time& time : day)
	{
		time.print(std::cout,"%a %H:%M");
		std::cout << "\n";
	}
	std::cout << "day4:\n";
	for(const oct::core::Time& time : day4)
	{
		time.print(std::cout,"%a %H:%M");
		std::cout << "\n";
	}*/
	//std::cout << "day5>>>\n";
	day5.inters(day,day4);
	//std::cout << "day5<<<\n";
	if(day5.size() == 10)
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
		for(const oct::core::Time& time : day5)
		{
			time.print(std::cout,"%a %H:%M");
			std::cout << "\n";
		}
		std::cout << "day5.size() = " << day5.size() << "\n";
		CU_ASSERT(false);
	}

	IntervalTime time6("Mon 08:00", "Mon 11:00");
	IntervalTime time7("Mon 13:00", "Mon 16:00");
	IntervalTime time8("Mon 17:00", "Mon 23:00");
	oct::ec::sche::Day day6;
	time8.granulate(&data.config,day6);
	time6.granulate(&data.config,day6);
	time7.granulate(&data.config,day6);
	day6.sort(data.config);
	/*for(const oct::core::Time& dt : day6)
	{
		dt.print(std::cout,"%a %H:%M");
		std::cout << "\n";
	}*/
	//std::cout << ">>>>>>>>>>>>>>Day6.\n";
	/*for(const Day::Block& block : day6.get_blocks())
	{
		std::cout << "New block.\n";
		for(const oct::core::Time* dt : block)
		{
			dt->print(std::cout,"%a %H:%M");
			std::cout << "\n";
		}
	}*/
	
	if(day6.get_blocks().size() == 3) //12 horas de clase, 9 hora de tiempo
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
		if(iBlock == 0)
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
			if((*itBlock).size() == 8)
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
	if(day6.front().tm_hour == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "day6.front().tm_hour = " << day6.front().tm_hour << "\n";
		CU_ASSERT(false);
	}
	if(day6.back().tm_hour == 22)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "day6.back().tm_hour = " << day6.back().tm_hour << "\n";
		CU_ASSERT(false);
	}
	if(day6.size() == 16)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "day6.size() = " << day6.size() << "\n";
		CU_ASSERT(false);
	}
	unsigned int day6_count = 0;
	for(const Day::Block& block : day6.get_blocks())
	{
		for(const oct::core::Time* dt : block)
		{
			day6_count++;
		}
	}
	if(day6_count == 16)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "Contenido de bloques es " << day6_count << ", pero el dia contine : " << day6.size() << "\n";
		CU_ASSERT(false);
	}
	
	//std::cout << ">>>>>>>>>>>>>>Day6.\n";
	std::list<Day> combsList;
	day6.combns(combsList,2);
	if(combsList.size() == 11)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "combsList.size() = " << combsList.size() << "\n";
		CU_ASSERT(false);
	}
	//std::cout << "<<<<<<<<<<<<<<Day6.\n";
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
	//std::cout << "Step 1\n";
	day6.combns(combsList,3);
	if(combsList.size() == 18)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "combsList.size() = " << combsList.size() << "\n";
		CU_ASSERT(false);
	}
	//std::cout << "Step 2\n";
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
	
	//std::cout << "Step 3\n";
	week2.sort(data.config);
	week2.combns(*subject1,week_opt);	
	//std::cout << "Step 4\n";
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
	if(week_opt.count() == 4919376)
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
	//std::cout << "Step 5\n";
	week3.sort(data.config);
	week3.combns(*subject2,week_opt2);
	//std::cout << "Step 6\n";
	/*std::cout << "Week Room \n";
	room1->get_week ().print(std::cout);
	std::cout << "\n";
	std::cout << "Week Teacher \n";
	teacher2->get_week ().print(std::cout);
	std::cout << "\n";
	//std::cout << "Interseccion \n";*/
	//week3.print(std::cout);
	if(week_opt2.count() == 708750)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "week_opt2.count() = " << week_opt2.count() << "\n";
		CU_ASSERT(false);
	}
	//std::cout << "week_opt2.random(week4>>>>>>>>>>>>>>>>>>>>>>>\n";
	//WeekHours week4;
	//week_opt2.random(week4);
	//std::cout << "week_opt2.random(week4<<<<<<<<<<<<<<<<<<<<<<<\n";
	//std::cout << "Horario \n";
	//week4.print(std::cout);
	/*if(week4.empty())
	{
		std::cout << "week4.empty() is empty\n";
		CU_ASSERT(false);
	}
	else
	{
		CU_ASSERT(true);
	}*/
	//WeekHours week3;
	//week_opt.random(week3);
	//week3.print(std::cout);
	
	Day day_base;
	oct::core::Time time_base;
	for(const Day& day_op : week3)
	{
		if(not day_op.empty())
		{
			/*
			std::cout << "\tdays_ops.size(): " << days_ops.size() << "\n";
			for(const Day& day : days_ops)
			{
				day.print_day(std::cout);
				std::cout << "\n";
				day.print_blocks(std::cout);
				std::cout << "\n";
			}
			*/
			day_base = day_op;
			break;
		}
	}
	if(day_base.empty())
	{
		CU_ASSERT(false);
	}
	else
	{
		CU_ASSERT(true);
	}
	//std::cout << "\tHours count :" << day_base.size() << " \n";
	time_base = *random(day_base);
	//std::cout << "\tDia base : ";
	//day_base.print_day(std::cout);
	/*std::cout << "\n";
	std::cout << "\tHora base : " << time_base.tm_hour << "\n";*/
	Day day_selected;
	week3.get_day(time_base.tm_wday,2,time_base,data.config,day_selected);
	//day_selected.print_day(std::cout);
	//std::cout << "\n";




	/*Enviroment sche ("logs/schedule",DATA_DIR,"logs/schedule");
	try
	{
		sche.initial();
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what() << "\n";
		CU_ASSERT(false);
	}
	if(sche.getInitPopulation() == sche.size())
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "sche.getInitPopulation() = " << sche.getInitPopulation() << "\n";
		CU_ASSERT(false);
	}
	Enviroment::iterator it_sche = sche.begin();
	const Single& single_shce = (const Single&)**it_sche;
	if(single_shce.size() == data.groups.get_list().size())
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "single_shce.size() = " << single_shce.size() << "\n";
		CU_ASSERT(false);
	}
	std::vector<const Lesson*> sche_teachers;
	single_shce.search_teachers("Monica Perez Ortencia",sche_teachers);
	if(sche_teachers.size() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "sche_teachers.size() = " << sche_teachers.size()<< "\n";
		CU_ASSERT(false);
	}*/

	oct::core::Time dt1[10];
	dt1[0].read("Tue 05:00","%a %H:%M");
	dt1[1].read("Tue 06:00","%a %H:%M");
	dt1[2].read("Tue 07:00","%a %H:%M");
	dt1[3].read("Tue 08:00","%a %H:%M");
	dt1[4].read("Tue 09:00","%a %H:%M");
	dt1[5].read("Tue 10:00","%a %H:%M");
	dt1[6].read("Tue 11:00","%a %H:%M");
	dt1[7].read("Tue 12:00","%a %H:%M");
	dt1[8].read("Tue 13:00","%a %H:%M");
	dt1[9].read("Tue 14:00","%a %H:%M");

	for(unsigned int i = 0; i < 10; i++)
	{
		if(dt1[i].tm_hour == i + 5)
		{
			CU_ASSERT(true);
		}
		else
		{
			std::cout << "dt1[i].tm_hour = " << dt1[i].tm_hour << "\n";
			CU_ASSERT(false);
		}
	}

	oct::core::Time dt2[10];	
	dt2[0].read("Tue 06:35","%a %H:%M");
	dt2[1].read("Tue 06:35","%a %H:%M");
	dt2[2].read("Tue 06:35","%a %H:%M");
	dt2[3].read("Tue 06:35","%a %H:%M");
	dt2[4].read("Tue 06:35","%a %H:%M");
	dt2[5].read("Tue 06:35","%a %H:%M");
	dt2[6].read("Tue 06:35","%a %H:%M");
	dt2[7].read("Tue 06:35","%a %H:%M");
	dt2[8].read("Tue 06:35","%a %H:%M");
	dt2[9].read("Tue 06:35","%a %H:%M");
	/*for(unsigned int i = 0; i < 10; i++)
	{
		std::cout << "Hora : ";
		dt2[i].print(std::cout,"%a %H:%M");
		std::cout << "\n ";
	}*/
	for(unsigned int i = 0; i < 10; i++)
	{
		dt2[i].add(i*data.config.get_seconds_per_hour());
	}
	if(dt2[0].tm_hour == 6 and dt2[0].tm_min == 35)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "dt2[i].tm_hour = " << dt2[0].tm_hour << ", dt2[i].tm_min ="  << dt2[0].tm_min << "\n";
		CU_ASSERT(false);
	}
	if(dt2[1].tm_hour == 7 and dt2[1].tm_min == 20)
	{
		CU_ASSERT(true);
	}
	else
	{
		std::cout << "dt2[i].tm_hour = " << dt2[1].tm_hour << ", dt2[i].tm_min ="  << dt2[1].tm_min << "\n";
		CU_ASSERT(false);
	}
	
	
	
	bool ret_dt2;
	for(unsigned int i = 1; i < 10; i++)
	{
		ret_dt2 = is_post_hour(dt2[i-1],dt2[i],data.config);
		if(ret_dt2)
		{
			CU_ASSERT(true);
		}
		else
		{
			std::cout << "is_post_hour(dt2[i-1],dt2[i],data.config) is " << ret_dt2 << "\n";
			CU_ASSERT(false);
		}
	}
	for(unsigned int i = 9; i > 0; i--)
	{
		ret_dt2 = is_prev_hour(dt2[i-1],dt2[i],data.config);
		if(ret_dt2)
		{
			CU_ASSERT(true);
		}
		else
		{
			std::cout << "is_prev_hour(dt2[i-1],dt2[i],data.config) is " << ret_dt2 << "\n";
			CU_ASSERT(false);
		}
	}

	/*for(auto const& [key,value] : data.get_list_hbrs())
	{
		std::cout << "(" << key.room->get_name() << "," << key.subject->get_name() << "-->" << value.disp_hours << "\n";
	}*/

	/*std::uniform_int_distribution<int> distrib(0, 9);
	for(unsigned int i = 0; i < 100; i++)
	{
		std::cout << i << ":" << distrib(oct::ec::dre) << "\n";
	}*/
}

