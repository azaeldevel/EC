
#include "v1.hh"







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
    core::ast::Variable<float> variables[3];
    variables[0].name = "x";
    variables[1].name = "y";
    variables[2].name = "z";

    ec::Arithmetic<3,float>::init_randsys();

    ec::Arithmetic<3,float> single1;
    single1.rand_op(variables);
    std::cout << "\n";
    single1.node->print(std::cout);
    std::cout << "\n";
    ec::Town<ec::Arithmetic<3,float>,float> town;
}
