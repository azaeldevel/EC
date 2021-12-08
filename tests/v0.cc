
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>
#include <schedule.hh>


static oct::ec::sche::Data data;

int init(void)
{
	
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
	if(data.teachers_subjects.get_list().size() == 12)
	{
		CU_ASSERT(true);
	}
	else 
	{
		CU_ASSERT(false);
	}



	
	const oct::ec::sche::Teachers::Row* row = data.teachers.search("Leticia Mojica");
	if(row) 
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
	const oct::ec::sche::Subjects::Row* rowSuject = data.subjects.search("Fisica");
	if(rowSuject) 
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
	std::list<oct::ec::sche::Teachers_Subjects::Row*> rowTS;
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
	const oct::ec::sche::Rooms::Row* rowR1 = data.rooms.search("1A");
	if(rowR1) 
	{
		//row->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}
	
	std::cout << "\n";
	const oct::ec::sche::Groups::Row* rowG1 = data.groups.search("1A");
	if(rowG1) 
	{
		//rowG1->print(std::cout);
		CU_ASSERT(true);
	}
	else 
	{
		//std::cout << "No se encontro el maestro indicado\n";
		CU_ASSERT(false);		
	}
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
