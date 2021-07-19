

#include <limits.h>

#include "GA-max.hh"

namespace ec::max
{



struct caret_2B_half
{
	unsigned short a:8,b:8;
};

Chromosome::Chromosome() : ec::Chromosome("max")
{

}
geneUS Chromosome::getNumber()const
{
	return gennumber;
}

geneUS Chromosome::combine1(const geneUS& gene)
{
	if(sizeof(caret_2B_half) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_half* g1 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gennumber);
	const caret_2B_half* g2 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gene);
	caret_2B_half g3;
	g3.a = g1->a;
	g3.b = g2->b;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::combine2(const geneUS& gene)
{
	if(sizeof(caret_2B_half) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_half* g1 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gennumber);
	const caret_2B_half* g2 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gene);
	caret_2B_half g3;
	g3.a = g1->b;
	g3.b = g2->a;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::combine3(const geneUS& gene)
{
	if(sizeof(caret_2B_half) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_half* g1 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gennumber);
	const caret_2B_half* g2 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gene);
	caret_2B_half g3;
	g3.a = g1->a;
	g3.b = g2->a;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::combine4(const geneUS& gene)
{
	if(sizeof(caret_2B_half) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_half* g1 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gennumber);
	const caret_2B_half* g2 = reinterpret_cast<const caret_2B_half*>((const geneUS*)&gene);
	caret_2B_half g3;
	g3.a = g1->b;
	g3.b = g2->b;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
void Chromosome::mutate()
{

}









Single::Single(ID id,Enviroment& env) : ec::Single(id,env)
{

}
void Single::eval()
{
	fitness = double(chromo.getNumber()) / double(USHRT_MAX);	
}
void Single::save(std::ofstream& fn)
{
	fn << getID();
	fn << ",";
	fn << getFitness();
	fn << ",";
	fn << chromo.getNumber();
}
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*)
{
}
void Single::print(std::ostream& fn) const
{
	fn << getID();
	fn << ",";
	fn << getFitness();
	fn << ",";
	fn << chromo.getNumber();
}
	
	
	
	
	
bool Enviroment::run()
{
	initial();
	
	std::cout << "Lista de numeros : " << "\n";
	for(ec::Single* s: *this)
	{
		((Single*)s)->eval();
	}
	sort(comparer);
	for(ec::Single* s: *this)
	{
		((Single*)s)->print(std::cout);
		std::cout << "\n";
	}
	return true;
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

