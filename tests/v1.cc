
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
    ec::Binopr<3,float>::init_randsys(100);

    ec::inputs<float,3> vars;
    vars.resize(2);//cantidad de resgistro
    vars[0][0] = 1.2;
    vars[0][1] = 65.964;
    vars[0][2] = 198.1254832;
    vars[1][0] = 9653.264;
    vars[1][1] = 1.f/2365.f;
    vars[1][2] = 198.1254832;

    ec::BinoprTown<3,float,ec::Binopr<3,float>> town(vars);
    town.populate_random();
    /*town.evaluate();
    town.print(std::cout);
    std::cout << "\n\n";
    town.pair();*/
    for(size_t i = 0; i < 50; i++)
    {
        town.evaluate();
        //town.print(std::cout);
        town.resumen(std::cout);
        std::cout << "\n\n";
        town.pair();
    }
    town.listing(std::cout);
}
