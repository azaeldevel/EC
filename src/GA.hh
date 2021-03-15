

#ifndef AE_GA_HH
#define AE_GA_HH

#include <iostream>
#include <map>

#include "core.hh"


namespace ae::ga
{

class Single : public ae::Single
{
public:
	Single(unsigned int id,const Junction& junction);
	Single(unsigned int id);
};



}

#endif