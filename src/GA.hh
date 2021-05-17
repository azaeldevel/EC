

#ifndef AE_GA_HH
#define AE_GA_HH

#include <iostream>
#include <map>

#include "core.hh"


namespace ec::ga
{

class Single : public ec::Single
{
public:
	Single(const Single&);
	Single(ID id,Enviroment&,const Junction& junction);
	Single(ID id,Enviroment&);
};



}

#endif