
#include <CUnit/Basic.h>

#include <max.hh>

using namespace oct::ec::max;
void max_devel()
{
	Enviroment enviroment(std::filesystem::path("../../tests/max"));
	
	bool ret = enviroment.run();
	
	if(ret)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
}