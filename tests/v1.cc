
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
    ec::Binopr<3,double>::init_randsys(100);

    ec::inputs<double,3> vars;
    vars.resize(3);//cantidad de resgistro
    vars[0][0] = 1.2;
    vars[0][1] = 65.964;
    vars[0][2] = 198.1254832;
    vars[1][0] = 9653.264;
    vars[1][1] = 1.f/2365.f;
    vars[1][2] = 198.1254832;
    vars[2][0] = 0.5;
    vars[2][1] = 0.7;
    vars[2][2] = 0.83;

    //ec::BinoprTown<3,float,ec::Binopr<3,float>> town(vars);
    //town.populate_random();
    /*
    town.evaluate();
    town.print(std::cout);
    std::cout << "\n\n";
    */
    //town.pair();

    /*for(size_t i = 0; i < 1000000; i++)
    {
        town.evaluate();
        //town.print(std::cout);
        town.resumen(std::cout);
        std::cout << "\n\n";
        town.pair();
    }
    town.listing(std::cout);*/

    std::cout << "\n";

    /*
    std::cout << "std::log(0.001) = " << std::log(0.001) << "\n";
    std::cout << "std::log(0.01) = " << std::log(0.01) << "\n";
    std::cout << "std::log(0.1) = " << std::log(0.1) << "\n";
    std::cout << "std::log(1) = " << std::log(1) << "\n";
    std::cout << "std::log(10) = " << std::log(10) << "\n";
    std::cout << "std::log(100) = " << std::log(100) << "\n";
    */

    std::cout << "\n";

    /*
    std::cout << "std::exp(0.001) = " << std::exp(0.001) << "\n";
    std::cout << "std::exp(0.01) = " << std::exp(0.01) << "\n";
    std::cout << "std::exp(0.1) = " << std::exp(0.1) << "\n";
    std::cout << "std::exp(1) = " << std::exp(1) << "\n";
    std::cout << "std::exp(10) = " << std::exp(10) << "\n";
    std::cout << "std::exp(100) = " << std::exp(100) << "\n";
    */
    //std::cout << "std::exp(1000) = " << std::exp(1000) << "\n";
    //std::cout << "std::exp(10000) = " << std::exp(10000) << "\n";

    ec::BinoprCity<3,double,ec::Binopr<3,double>> city(vars);
    city.populate_random(10);
    //
    /*
    city.evaluate();
    city.resumen(std::cout);
    city.listing(std::cout);
    */

    for(size_t i = 0; i < 100000; i++)
    {
        city.evaluate();
        city.resumen(std::cout);
        city.listing(std::cout);
        city.pair();
    }
    //static_cast<BinoprTown<3,float,ec::Binopr<3,float>>*>(city[0])->listing(out);


}
