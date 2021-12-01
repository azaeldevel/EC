

#include "GA-schedule.hh"

namespace ec::sche
{
	


Single::Single(ID id,Enviroment& env) : ec::Single(id,env)
{

}
void Single::eval()
{

}
void Single::save(std::ofstream& fn)
{

}
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*)
{

}
void Single::print(std::ostream&) const
{

}
	
	
	
	
	
	
Enviroment::Enviroment()
{
	init();
}
Enviroment::Enviroment(const std::string& log)
{
	init();
	logDirectory = log;
}

void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = 1000;
	maxProgenitor = 200;
}



void Enviroment::initial()
{
	for(unsigned short i = 0; i < initPopulation; i++)
	{
		Single* single = new Single(nextID(),*this);
		push_back(single);
	}
}
Enviroment::~Enviroment()
{
	for(ec::Single* s : *this)
	{
		delete s;
	}
}



}

