
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

	oct::ec::sche::Time times1[10];
	for(unsigned int i = 0; i < 10; i++)
	{
	    times1[i].read("Tue 05:00","%a %H:%M");
		/*times1[i].print(std::cout,"%c");
		std::cout << ", " << (std::time_t)times1[i];
		std::cout << ", " << &times1[i];
		std::cout << "\n";*/
	}
	//std::cout << "\n";
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
		if(times1[i].tm_wday == 2)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times1[i].tm_mday == 6)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times1[i].tm_year == 70)
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
		if(times1[0] != times1[i])
		{
			CU_ASSERT(false);
		}
		else
		{
			CU_ASSERT(true);
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
		times1[i].add(i * 45 * 60);
	}
	/*for(unsigned int i = 0; i < 10; i++)
	{
		times1[i].print(std::cout,"%c");
		std::cout << ", " << (std::time_t)times1[i];
		std::cout << "\n";
	}
	std::cout << "\n";*/
	for(unsigned int i = 1; i < 10; i++)
	{
		if(times1[i-1] < times1[i])
		{
			CU_ASSERT(true);
		}
		else
		{
			times1[i-1].print(std::cout,"%a %H:%M");
			std::cout << "<";
			times1[i].print(std::cout,"%a %H:%M");
			CU_ASSERT(false);
		}
		if(times1[i].tm_wday == 2)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times1[i].tm_mday == 6)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times1[i].tm_year == 70)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	for(unsigned int i = 0; i < 9; i++)
	{
		if(times1[i+1] > times1[i])
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


	oct::ec::sche::Time times2[10];
	for(unsigned int i = 0; i < 10; i++)
	{
	    times2[i].read("Wed 05:00","%a %H:%M");
		/*times2[i].print(std::cout,"%c");
		std::cout << ", " << (std::time_t)times2[i];
		std::cout << "\n";*/
	}
	for(unsigned int i = 1; i < 10; i++)
	{
		if(times2[0] == times2[i])
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times2[i].tm_wday == 3)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times2[i].tm_mday == 7)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times2[i].tm_year == 70)
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
		times2[i].add(i*45*60);
	}
	for(unsigned int i = 1; i < 10; i++)
	{
		if(times2[i].tm_wday == 3)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times2[i].tm_mday == 7)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		if(times2[i].tm_year == 70)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	/*std::cout << "\n";
	for(unsigned int i = 0; i < 10; i++)
	{
		times2[i].print(std::cout,"%c");
		std::cout << ", " << (std::time_t)times2[i];
		std::cout << "\n";
	}*/
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
