
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
    ec::Binopr<3,float>::init_randsys();

    ec::inputs<float,3> vars;
    vars.resize(2);//cantidad de resgistro
    vars[0][0] = 1.2;
    vars[0][1] = 65.964;
    vars[0][2] = 198.1254832;
    vars[1][0] = 9653.264;
    vars[1][1] = 2.3154;
    vars[1][2] = 198.1254832;

    ec::BinoprTown<3,float,ec::Binopr<3,float>> town;
    town.populate(10,vars);
    town.evaluate();

}
