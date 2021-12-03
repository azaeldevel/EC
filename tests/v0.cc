
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>
#include <schedule.hh>


static oct::ec::sche::Data data;

int init(void)
{
	data.subjects.loadFile("tests/subjects.csv");
	data.teachers.loadFile("tests/teachers.csv");
	data.rooms.loadFile("tests/rooms.csv");
	data.teachers_subjects.loadFile("tests/teachers-subjects.csv");

	return 0;
}
int clean(void)
{
	return 0;
}

void testDeveloping()
{
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
	std::cout << "\n";
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
