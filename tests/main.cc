
#include <iostream>
#include <CUnit/Basic.h>


#ifdef OCTETOS_EC_V0_TDD

#endif
#ifdef OCTETOS_EC_V1_TDD
	#include "v1.hh"
#endif

int main(int argc, char *argv[])
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

#ifdef OCTETOS_EC_V0_TDD
#endif
#ifdef OCTETOS_EC_V1_TDD
	CU_pSuite pSuite_v1 = CU_add_suite("Octetos Evolution Computing v1", v1_init, v1_clean);
	if (NULL == pSuite_v1)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite_v1, "Developing..", v1_developing)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite_v1, "Nodes..", v1_nodes)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
#endif

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
