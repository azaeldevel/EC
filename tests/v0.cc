
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
	oct::core::Time times1[10];
	times1[0].read("Tue 05:00","%a %H:%M");
	times1[1].read("Tue 05:00","%a %H:%M");
	times1[2].read("Tue 05:00","%a %H:%M");
	times1[3].read("Tue 05:00","%a %H:%M");
	times1[4].read("Tue 05:00","%a %H:%M");
	times1[5].read("Tue 05:00","%a %H:%M");
	times1[6].read("Tue 05:00","%a %H:%M");
	times1[7].read("Tue 05:00","%a %H:%M");
	times1[8].read("Tue 05:00","%a %H:%M");
	times1[9].read("Tue 05:00","%a %H:%M");

	for(unsigned int i = 1; i < 10; i++)
	{
		if(times1[0] == times1[i])
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	if(times1[0].tm_hour == 5 and times1[0].tm_min == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	for(unsigned int i = 1; i < 10; i++)
	{
		times1[i].add(i*60*60);
	}
	for(unsigned int i = 1; i < 10; i++)
	{
		if(times1[i-1] < times1[i])
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	for(unsigned int i = 1; i < 10; i++)
	{
		if(times1[i-1] <= times1[i])
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	for(unsigned int i = 9; i > 0; i--)
	{
		if(times1[i] > times1[i-1])
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
}

int main(int argc, char *argv[])
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	#if defined(__GNUC__) && defined(__linux__)
	signal(SIGSEGV,oct::core::signal_segmentv);
	signal(SIGABRT,oct::core::signal_abort);
    #elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))

    #else
        #error "Pltaforma desconocida"
    #endif

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
