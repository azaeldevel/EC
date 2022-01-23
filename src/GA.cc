


#include "GA.hh"


namespace oct::ec::ga
{

Single::Single(const Single& obj) : ec::Single(obj)
{
	
}
Single::Single(ID id,Enviroment& e) : ec::Single(id,e)
{
}
Single::Single(ID id,Enviroment& e,unsigned int c) : ec::Single(id,e,c)
{
}




}