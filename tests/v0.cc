
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
	data.config.set_schema(oct::ec::sche::Configuration::Schema::WITH_SUBJECTS_TIMES);
	data.load("../../tests");

	return 0;
}
int clean(void)
{
	return 0;
}

void testDeveloping()
{
	if(data.teachers.get_list().size() == 8)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.subjects.get_list().size() == 8)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.rooms.get_list().size() == 3)
	{
		//std::cout << "count : " << data.rooms.get_list().size() << "\n";
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}
	if(data.teachers_subjects.get_list().size() == 8)
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
	const oct::ec::sche::Subject* subject1 = data.subjects.search("Fisica");
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
	data.teachers_subjects.searchSubjects("Espanol",rowTS);
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
	time1.set_begin(&data.config, "8:00");
	if(time1.begin.tm_hour == 8) 
	{
		CU_ASSERT(true);
	}
	else 
	{
		std::cout << "time1.begin.tm_hour = " << time1.begin.tm_hour << "\n";
		CU_ASSERT(false);		
	}
	time1.set_end(&data.config, "20:00");
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
