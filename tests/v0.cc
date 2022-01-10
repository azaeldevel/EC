
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
#include <chrono>
#include <csignal>


void schedule_devel();
int schedule_init(void);
int schedule_clean(void);

void time_devel()
{
		
}

int main(int argc, char *argv[])
{	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	signal(SIGSEGV,oct::core::signal_segmentv);
	signal(SIGABRT,oct::core::signal_abort);

	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Testing Evolution Computing..", schedule_init, schedule_clean);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Developing Time class", time_devel)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Developing Schedule", schedule_devel)))
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
