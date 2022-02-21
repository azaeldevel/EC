
#include <iostream>
#include <limits.h>

#include "max.hh"

namespace oct::ec::max
{



struct caret_2B_half
{
	unsigned short a:8,b:8;
};
struct caret_2B_16b
{
	unsigned short a:1,b:1,c:1,d:1,e:1,f:1,g:1,h:1,i:1,j:1,k:1,l:1,m:1,n:1,o:1,p:1;
};

Chromosome::Chromosome() : oct::ec::Chromosome("max")
{
	gennumber = randGenNumber();
	combine = randCombine();
}
Chromosome::Chromosome(geneUS numb,pfnCombine fn): oct::ec::Chromosome("max")
{
	gennumber = numb;
	combine = fn;
}

Chromosome::Chromosome(const Chromosome& chromo): oct::ec::Chromosome("max")
{
	gennumber = chromo.gennumber;
	combine = chromo.combine;
}
const Chromosome& Chromosome::operator =(const Chromosome& chromo)
{
	gennumber = chromo.gennumber;
	combine = chromo.combine;

	return chromo;
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
	std::uniform_int_distribution<> distribution(1,USHRT_MAX/2);
	return distribution(gen);
}
/*
geneUS Chromosome::randGenNumber()
{
	geneUS g;
	caret_2B_16b* gene = reinterpret_cast<caret_2B_16b*>((geneUS*)&g);
	std::uniform_int_distribution<> distribution(1,16);

	switch(distribution(gen))
	{
		case 1:
			gene->a = 1;
			break;
		case 2:
			gene->b = 1;
			break;
		case 3:
			gene->c = 1;
			break;
		case 4:
			gene->d = 1;
			break;
		case 5:
			gene->e = 1;
			break;
		case 6:
			gene->f = 1;
			break;
		case 7:
			gene->g = 1;
			break;
		case 8:
			gene->h = 1;
			break;
		case 9:
			gene->i = 1;
			break;
		case 10:
			gene->j = 1;
			break;
		case 11:
			gene->k = 1;
			break;
		case 12:
			gene->l = 1;
			break;
		case 13:
			gene->m = 1;
			break;
		case 14:
			gene->n = 1;
			break;
		case 15:
			gene->o = 1;
			break;
		case 16:
			gene->p = 1;
			break;
	}

	return g;
}*/
Chromosome::pfnCombine Chromosome::randCombine()
{
	std::uniform_int_distribution<> distribution(1,4);
	return distribution(gen);
}
geneUS Chromosome::combination(geneUS g)
{
	switch(combine)
	{
		case 1:
			return combine1(g);
		case 2:
			return combine2(g);
		case 3:
			return combine3(g);
		case 4:
			return combine4(g);
	}

	return 0;
}
geneUS Chromosome::combine1(geneUS gene)
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
geneUS Chromosome::combine2(geneUS gene)
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
geneUS Chromosome::combine3(geneUS gene)
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
	g3.p = g2->p;

	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
geneUS Chromosome::combine4(geneUS gene)
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
	g3.p = g1->p;

	geneUS newgen = reinterpret_cast<const geneUS&>(g3);
	return newgen;
}
void Chromosome::mutate()
{
	if(sizeof(caret_2B_16b) != sizeof(geneUS)) throw octetos::core::Exception("No coincide los tipos de datos",__LINE__,__FILE__);

	caret_2B_16b& gene = *reinterpret_cast<caret_2B_16b*>(&gennumber);
	std::uniform_int_distribution<> distribution(1,16);

	switch(distribution(gen))
	{
		case 1:
			gene.a = !gene.a;
			break;
		case 2:
			gene.b = !gene.b;
			break;
		case 3:
			gene.c = !gene.c;
			break;
		case 4:
			gene.d = !gene.d;
			break;
		case 5:
			gene.e = !gene.e;
			break;
		case 6:
			gene.f = !gene.f;
			break;
		case 7:
			gene.g = !gene.g;
			break;
		case 8:
			gene.h = !gene.h;
			break;
		case 9:
			gene.i = !gene.i;
			break;
		case 10:
			gene.j = !gene.j;
			break;
		case 11:
			gene.k = !gene.k;
			break;
		case 12:
			gene.l = !gene.l;
			break;
		case 13:
			gene.m = !gene.m;
			break;
		case 14:
			gene.n = !gene.n;
			break;
		case 15:
			gene.o = !gene.o;
			break;
		case 16:
			gene.p = !gene.p;
			break;
	}
}







Single::Single(Enviroment& e) : oct::ec::Single(e)
{
}
Single::Single(Enviroment& e,geneUS g,Chromosome::pfnCombine f) : oct::ec::Single(e),chromo(g,f)
{
}


void Single::set(const Chromosome& c)
{
	chromo = c;
}

void Single::eval()
{
	//if(true) std::cout << "Single::eval " << USHRT_MAX << " \n";
	fitness = real(chromo.getNumber()) / real(USHRT_MAX);
}
void Single::save(Save& fn)
{
	//std::cout << "\tSingle::save 1\n";
	(*fn.out) << getID();
	(*fn.out) << ",";
	(*fn.out) << getFitness();
	(*fn.out) << ",";
	(*fn.out) << chromo.getNumber();
	//std::cout << "\tSingle::save 2\n";
	(*fn.out).flush();
}
void Single::juncting(std::list<oct::ec::Single*>& childs,const oct::ec::Single* single)
{
	for(ec::geneUS i = 0; i < getChilds(); i++)
	{
		childs.push_back(new Single((Enviroment&)*env));
		Single* newSingle = (Single*)childs.back();

		geneUS newGen = chromo.combination(((Single*)single)->chromo.getNumber());
		Chromosome newChromo(newGen,chromo.getCombine());
		newSingle->set(newChromo);

	}
}
void Single::print(std::ostream& fn) const
{
	fn << getID();
	fn << ",";
	fn << getFitness();
	fn << ",";
	fn << chromo.getNumber();
}
void Single::mutate()
{
	chromo.mutate();
}





Enviroment::Enviroment()
{
	init();
}
Enviroment::Enviroment(const std::string& log) : oct::ec::Enviroment()
{
	logDirectory = log;
	init();
}
Enviroment::Enviroment(int argc, const char* argv[]) : oct::ec::Enviroment(argc,argv)
{
	init();
}
Enviroment::Enviroment(const std::filesystem::path& dir)
{
	logDirectoryHistory = dir;
	logDirectorySolutions = dir;
	init();
}

void Enviroment::init()
{
	initPopulation = 100;
	maxPopulation = 100;
	maxProgenitor = 10;
	//echoSteps = false;
	stopperMinSolutions(1);
	stopperMaxIterations(100);
	//epsilon = 1.0/double(USHRT_MAX);
	//std::cout << "epsilon = " << epsilon << "\n";
	comparer = &oct::ec::cmpStrength;
	mutableProb = 0.2;
	maxMutation = 1;
	create_session();
}



void Enviroment::initial()
{
	for(unsigned short i = 0; i < initPopulation; i++)
	{
		Single* single = new Single(*this);
		push_back(single);
	}
}
Enviroment::~Enviroment()
{

}





}

