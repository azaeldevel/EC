
#include "v1.hh"


//void (*single_operator)(core::array<float>&);


Single::Single(size_t size_opers) : opers(size_opers)
{
    init_data();
}
Single::Single(const core::array<float>& ins) : data(ins)
{
    init_data();
}
Single::Single(const core::array<float>& ins, size_t size_opers) : data(ins),opers(size_opers)
{
    init_data();
}

float Single::evaluate() const
{
    return 0;
}
void Single::init_load_operators()
{

}
void Single::init_data()
{
    if(data.size() == 0) data.resize(3);
    for(size_t i = 0; i < data.size(); i++) data[i] = 0;
}


void Single::incs1()
{

}








Math::Math(size_t size_opers) : SINGLE_BASE(size_opers)
{
}
Math::Math(const core::array<float>& ins) : SINGLE_BASE(ins)
{
}
Math::Math(const core::array<float>& ins, size_t size_opers) : SINGLE_BASE(ins,size_opers)
{
}



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
    Math single1;
}
