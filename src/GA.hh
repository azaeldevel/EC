

#ifndef AE_GA_HH
#define AE_GA_HH


#include <map>

#include "ec.hh"


namespace oct::ec::ga
{

class Single : public ec::Single
{
public:
	Single(const Single&);
	Single(ID id,Enviroment&,unsigned int);
	Single(ID id,Enviroment&);
};



}

#endif