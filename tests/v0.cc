
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


static oct::ec::sche::Data data;

int init(void)
{
	oct::core::Shell shell;
	//std::cout << "cwd :" << shell.cwd() << "\n";
	
	data.config.set_schema(oct::ec::sche::Configuration::Schema::WITH_SUBJECTS_TIMES);
	data.load("tests");

	return 0;
}
int clean(void)
{
	return 0;
}

void testDeveloping()
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
	
	oct::ec::sche::Enviroment* sche = new oct::ec::sche::Enviroment("logs","tests");
	//std::cout << "Combinaciones : " << sche->counter() << "\n";
	sche->initial();
	
	
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
	std::list<oct::ec::sche::WeekHours> weeks_combs;
	if(week2.check()) //verificar que este ordenado
	{
		CU_ASSERT(false);
	}
	else 
	{
		CU_ASSERT(true);
	}
	//std::cout << "----\n";
	//week2.print(std::cout);
	week2.combns(subject1,weeks_combs);
	
}
int main(int argc, char *argv[])
{

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Testing Evolution Computing", init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Developing", testDeveloping)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}
