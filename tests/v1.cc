
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
    variables[0].data = 5.0987;
    variables[1].name = "y";
    variables[1].data = 11.984;
    variables[2].name = "z";
    variables[2].data = 34.65417;
    core::table<core::ast::Variable<float>,3> vars;

    ec::Arithmetic<3,float>::init_randsys();

    /*ec::Arithmetic<3,float> single1;
    single1.rand_op();
    std::cout << "\n";
    single1.node->print(std::cout);
    std::cout << "\n";*/
    ec::ArithmeticTown<ec::Arithmetic<3,float>,float> town;
    town.populate(10,variables);
    town.evaluate();
}
