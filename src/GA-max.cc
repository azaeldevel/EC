
#include <iostream>
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
	randCombine();
}
Chromosome::Chromosome(geneUS numb,pfnCombine fn): ec::Chromosome("max")
{
	gennumber = numb;
	combine = fn;
}
geneUS Chromosome::getNumber()const
{
	return gennumber;
}
Chromosome::pfnCombine Chromosome::getCombine()const
{
	return combine;
}


void Chromosome::randCombine()
{
	double randN = randNumber(1.0,5.0);
	unsigned short randAlgCombi(randN);
	//std::cout << "randAlgCombi = " << randAlgCombi << "\n";
	switch(randAlgCombi)
	{
	case 1:
		combine = &Chromosome::combine1;
		break;	
	case 2:
		combine = &Chromosome::combine2;	
		break;	
	case 3:
		combine = &Chromosome::combine3;
		break;		
	case 4:
		combine = &Chromosome::combine4;
		break;	
	default:
		combine = &Chromosome::combine4;
	}
}
geneUS Chromosome::combination(const geneUS& gene)
{
	return (this->*combine)(gene);
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









Single::Single(ID id,Enviroment& e,geneUS g,Chromosome::pfnCombine f) : ec::Single(id,e),chromo(g,f)
{
}
Single::Single(ID id,Enviroment& env) : ec::Single(id,env)
{

}
void Single::eval()
{
	//if(true) std::cout << "Single::eval " << USHRT_MAX << " \n";
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
	if(env->getEchoSteps()) std::cout << "Single::juncting Step 1\n";
	Population countNews = 0;
	if(env->getEchoSteps()) std::cout << "Single::juncting Step 2\n";
	for(ec::geneUS i = 0; i < getJunction().get_number(); i++)
	{
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.1\n";
		Chromosome::pfnCombine algCombine;
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.2\n";
		geneUS genN = chromo.combination(((Single*)single)->chromo.getNumber());
		double randMutate = randNumber(0.0,1.0);
		if(env->getProbabilityMutationEvent() < randMutate)
		{
			
		}
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.3\n";
		double randAlgSingle = randNumber(0.0,1.0);
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.4\n";
		if(randAlgSingle < 0.5)	
		{
			algCombine = chromo.getCombine();
		}
		else
		{
			algCombine = ((Single*)single)->chromo.getCombine();
		}
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.5\n";
		Single* newSingle = new Single(env->nextID(),(Enviroment&)*env,genN,algCombine);
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.6\n";
		chils.push_back(newSingle);
		if(env->getEchoSteps()) std::cout << "Single::juncting Step C.2.7\n";
		countNews++;		
	}
	
	return countNews;
}
void Single::print(std::ostream& fn) const
{
	fn << getID();
	fn << ",";
	fn << getFitness();
	fn << ",";
	fn << chromo.getNumber();
}
geneUS Single::mutate(geneUS)
{

}	
	
	
	
	
/*bool Enviroment::run()
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
}*/
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
	echoSteps = false;
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

