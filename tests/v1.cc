
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
    std::uniform_int_distribution<> tree_width(1, 10);
    std::uniform_int_distribution<> tree_deep(1, 20);
    std::bernoulli_distribution nesteing(0.7);

    ec::Arithmetic<> single1 = ec::Arithmetic<>::populate_generic(generator,operation,tree_width,tree_deep,nesteing);

}
