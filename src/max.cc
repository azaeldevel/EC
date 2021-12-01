
#include <iostream>
#include <limits.h>

#include "max.hh"

namespace ec::max
{



struct caret_2B_half
{
	unsigned short a:8,b:8;
};
struct caret_2B_16b
{
	unsigned short a:1,b:1,c:1,d:1,e:1,f:1,g:1,h:1,i:1,j:1,k:1,l:1,m:1,n:1,o:1;
};

Chromosome::Chromosome() : ec::Chromosome("max")
{
	gennumber = randGenNumber();
	combine = randCombine();
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

geneUS Chromosome::randGenNumber()
{
	geneUS g;
	caret_2B_16b* gene = reinterpret_cast<caret_2B_16b*>((geneUS*)&g);
	double randNum = randNumber(0.0,1.0);
		
	if(randNum < 1.0/16.0)
	{
		gene->a = 1;
	}
	else if(randNum < 2.0/16.0)
	{
		gene->b = 1;
	}
	else if(randNum < 3.0/16.0)
	{
		gene->c = 1;
	}
	else if(randNum < 4.0/16.0)
	{
		gene->d = 1;
	}
	else if(randNum < 5.0/16.0)
	{
		gene->e = 1;
	}
	else if(randNum < 6.0/16.0)
	{
		gene->f = 1;
	}
	else if(randNum < 7.0/16.0)
	{
		gene->g = 1;
	}
	else if(randNum < 8.0/16.0)
	{
		gene->h = 1;
	}
	else if(randNum < 9.0/16.0)
	{
		gene->i = 1;
	}
	else if(randNum < 10.0/16.0)
	{
		gene->j = 1;
	}
	else if(randNum < 11.0/16.0)
	{
		gene->k = 1;
	}
	else if(randNum < 12.0/16.0)
	{
		gene->l = 1;
	}
	else if(randNum < 13.0/16.0)
	{
		gene->m = 1;
	}
	else if(randNum < 14.0/16.0)
	{
		gene->n = 1;
	}
	else if(randNum < 15.0/16.0)
	{
		gene->o = 1;
	}
	else
	{
		gene->o = 1;
	}	
		
	return g;
}
Chromosome::pfnCombine Chromosome::randCombine()
{
	double randN = randNumber(0.0,4.0);
	unsigned short randUS = randN + 1;
	switch(randUS)
	{
		case 1:
			return &Chromosome::combine1;		
			break;
		case 2:
			return &Chromosome::combine2;		
			break;
		case 3:
			return &Chromosome::combine3;		
			break;
		case 4:
			return &Chromosome::combine4;		
			break;
	}
	
	return &Chromosome::combine4;
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
	if(sizeof(caret_2B_16b) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_16b* g1 = reinterpret_cast<const caret_2B_16b*>((const geneUS*)&gennumber);
	const caret_2B_16b* g2 = reinterpret_cast<const caret_2B_16b*>((const geneUS*)&gene);
	caret_2B_16b g3;
	g3.a = g1->a;
	g3.b = g2->b;
	g3.c = g1->c;
	g3.d = g2->d;
	g3.e = g1->e;
	g3.f = g2->f;
	g3.g = g1->g;
	g3.h = g2->h;
	g3.i = g1->i;
	g3.j = g2->j;
	g3.k = g1->k;
	g3.l = g2->l;
	g3.m = g1->m;
	g3.n = g2->n;
	g3.o = g1->o;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::combine4(const geneUS& gene)
{
	if(sizeof(caret_2B_16b) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	const caret_2B_16b* g1 = reinterpret_cast<const caret_2B_16b*>((const geneUS*)&gennumber);
	const caret_2B_16b* g2 = reinterpret_cast<const caret_2B_16b*>((const geneUS*)&gene);
	caret_2B_16b g3;
	g3.a = g2->a;
	g3.b = g1->b;
	g3.c = g2->c;
	g3.d = g1->d;
	g3.e = g2->e;
	g3.f = g1->f;
	g3.g = g2->g;
	g3.h = g1->h;
	g3.i = g2->i;
	g3.j = g1->j;
	g3.k = g2->k;
	g3.l = g1->l;
	g3.m = g2->m;
	g3.n = g1->n;
	g3.o = g2->o;
	
	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::mutate(const geneUS& g)
{
	if(sizeof(caret_2B_16b) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);
	
	caret_2B_16b gene = *reinterpret_cast<const caret_2B_16b*>((const geneUS*)&g);
	double randNum = randNumber(0.0,1.0);
	
	if(randNum < 1.0/16.0)
	{
		gene.a = not gene.a;
	}
	else if(randNum < 2.0/16.0)
	{
		gene.b = not gene.b;
	}
	else if(randNum < 3.0/16.0)
	{
		gene.c = not gene.c;
	}
	else if(randNum < 4.0/16.0)
	{
		gene.d = not gene.d;
	}
	else if(randNum < 5.0/16.0)
	{
		gene.e = not gene.e;
	}
	else if(randNum < 6.0/16.0)
	{
		gene.f = not gene.f;
	}
	else if(randNum < 7.0/16.0)
	{
		gene.g = not gene.g;
	}
	else if(randNum < 8.0/16.0)
	{
		gene.h = not gene.h;
	}
	else if(randNum < 9.0/16.0)
	{
		gene.i = not gene.i;
	}
	else if(randNum < 10.0/16.0)
	{
		gene.j = not gene.j;
	}
	else if(randNum < 11.0/16.0)
	{
		gene.k = not gene.k;
	}
	else if(randNum < 12.0/16.0)
	{
		gene.l = not gene.l;
	}
	else if(randNum < 13.0/16.0)
	{
		gene.m = not gene.m;
	}
	else if(randNum < 14.0/16.0)
	{
		gene.n = not gene.n;
	}
	else if(randNum < 15.0/16.0)
	{
		gene.o = not gene.o;
	}
	else if(randNum < 16.0/16.0)
	{
		gene.o = not gene.o;
	}
	else
	{
		gene.o = not gene.o;
	}	
	
	geneUS newGen = *reinterpret_cast<geneUS*>(&gene);
	
	return newGen;
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
			genN = Chromosome::mutate(genN);
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
Enviroment::Enviroment(const std::string& log) : ec::Enviroment()
{
	init();
	logDirectory = log;
}
Enviroment::Enviroment(int argc, const char* argv[]) : ec::Enviroment(argc,argv)
{
	init();
}

void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = 1000;
	maxProgenitor = 200;
	//echoSteps = false;
	stopperMinSolutions(2);
	stopperMaxIterations(100);
	epsilon = 1.0/double(USHRT_MAX);
	//std::cout << "epsilon = " << epsilon << "\n";
	comparer = &ec::cmpStrength;
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
	
}





}

