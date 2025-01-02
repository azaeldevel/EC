
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
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 generator(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> operation(1, 4);
    std::uniform_real_distribution<> constant(-1.0e6, 1.0e6);
    std::bernoulli_distribution nesteing(0.7);

    ec::Arithmetic<float>* single1 = new ec::Arithmetic<float>(ec::Arithmetic<float>::create_node(generator,operation,nesteing,constant),true);

}
