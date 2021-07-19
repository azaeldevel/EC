

#include "GA-max.hh"

namespace ec::max
{


struct caret4B_half
{
	short a:16,b:16;
};
struct caret2B_half
{
	unsigned short a:8,b:8,c:4;
};

struct caret2B_half_Digits1
{
	unsigned short a:4,e:12;
};
struct caret2B_half_Digits2
{
	unsigned short a:2,b:2,e:12;
};
struct caret2B_half_Digits3
{
	unsigned short a:1,b:1,c:1,d:1,e:12;
};



geneUS Chromosome::combine(const geneUS& P1,const geneUS& P2)
{
	if(sizeof(caret2B_half) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	
}
geneUS Chromosome::mutate(const geneUS& P1)
{

}










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
/**
*\brief Inicializa los datos meimbros
*/
void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = 1000;
	maxProgenitor = 200;
}

/**
*\brief Elimina los que no cumple con el criterio de seleccion
*/
void Enviroment::selection()
{
	if(size() < maxProgenitor) return;
	
	std::list<ec::Single*> todelete;
	
	std::list<ec::Single*>::iterator it = begin();
	std::advance(it,size() - maxProgenitor);
	for( ; it != end(); it++)
	{
		todelete.push_back(*it);
	}
	
	for(ec::Single* s : todelete)
	{
		delete s;
	}
}
/**
*\brief Crea la poblacion inicial
*/
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

