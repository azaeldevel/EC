
#include "../../core/3/numbers.hh"
#include "v1.hh"
#include "1/nodes.hh"

namespace core = oct::core::v3;
namespace ec = oct::ec::v1;

int v1_init(void)
{
	return 0;
}

int v1_clean(void)
{
	return 0;
}

void v1_developing()
{
}
void v1_nodes()
{
    ec::Number<float> num1(5.0f);
    ec::Number<float> num2(1.9f);
    ec::Number<float> num3(3.9f);
    ec::Addition<float> op1(num1,num2);
    ec::Addition<float> op2(op1,num3);
    ec::Subtration<float> op3(op2,num2);
    ec::Divition<float> op4(op1,num2);


    CU_ASSERT(core::equal((float)num1, 5.0f))
    CU_ASSERT(core::equal((float)num2, 1.9f))
    CU_ASSERT(core::equal((float)num3, 3.9f))
    CU_ASSERT(core::equal((float)op1, 6.9f))
    CU_ASSERT(core::equal((float)op2, 10.8f))
    //op3.print(std::cout);
    //std::cout << (float) op3 << "\n";
    CU_ASSERT(core::equal((float)op3, 8.9f,1.0e-6f))
    CU_ASSERT(core::equal((float)op4, 3.6315f,1.0e-4f))
}

