


#include "GA.hh"


namespace ae::ga
{

Single::Single(const Single& obj) : ae::Single(obj)
{
	
}
Single::Single(unsigned int id,Enviroment& e) : ae::Single(id,e)
{
}
Single::Single(unsigned int id,Enviroment& e,const Junction& junction) : ae::Single(id,e,junction)
{
}




}