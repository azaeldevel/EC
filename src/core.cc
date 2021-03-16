
#include <random>
#include <octetos/core/Error.hh>
#include <iostream>
#include <algorithm>

#include "core.hh"


namespace ae
{


bool cmpStrength(const Single* f,const Single* s)
{
	return f->getStrength() > s->getStrength();
}
float randNumber()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(1.0, 100.0);
	
	return distr(gen);
}
float randNumber(float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(1.0, max);
	
	return distr(gen);
}
float randNumber(float min,float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(min, max);
	
	return distr(gen);
}
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







	
Chromosome::Chromosome(const std::string n) : name(n)
{
}
geneF Chromosome::combine(const geneF& P1,const geneF& P2)
{
	if(sizeof(geneF) != sizeof(caret4B_half)) throw octetos::core::Exception("Genes no compatibles para combinar",__FILE__,__LINE__);
	
	geneF child;
	caret4B_half* crChild = reinterpret_cast<caret4B_half*>(&child);
	const caret4B_half* crP1 = reinterpret_cast<const caret4B_half*>(&P1);
	const caret4B_half* crP2 = reinterpret_cast<const caret4B_half*>(&P2);
	crChild->b = crP1->a;
	crChild->a = crP2->b;
	return child;
}

geneUS Chromosome::combineDigits(const geneUS& P1,const geneUS& P2)
{
	if(sizeof(geneUS) != sizeof(caret2B_half_Digits2)) throw octetos::core::Exception("Genes no compatibles para combinar",__FILE__,__LINE__);
	
	geneUS child;
	caret2B_half_Digits2* crChild = reinterpret_cast<caret2B_half_Digits2*>(&child);
	const caret2B_half_Digits2* crP1 = reinterpret_cast<const caret2B_half_Digits2*>(&P1);
	const caret2B_half_Digits2* crP2 = reinterpret_cast<const caret2B_half_Digits2*>(&P2);
	crChild->b = crP1->a;
	crChild->a = crP2->b;
	return child;
}
geneUS Chromosome::mutateDigits(const geneUS& P1)
{
	if(sizeof(geneUS) != sizeof(caret2B_half_Digits3)) throw octetos::core::Exception("Genes no compatibles para combinar",__FILE__,__LINE__);

	geneUS child = 0;
	caret2B_half_Digits3* crChild = reinterpret_cast<caret2B_half_Digits3*>(&child);
	const caret2B_half_Digits3* crP1 = reinterpret_cast<const caret2B_half_Digits3*>(&P1);
	float numrnd1 = randNumber(0.0,1.0);
	if(numrnd1 < 0.25)
	{
		crChild->a = !crP1->a;
	}
	else if(numrnd1 < 0.50)
	{
		crChild->b = !crP1->b;
	}
	else if(numrnd1 < 0.75)
	{
		crChild->c = !crP1->c;
	}
	else
	{
		crChild->d = !crP1->d;
	}
	return child;
}













Junction::Junction(): Chromosome("Junction")
{
	number = randChild();
	algorit = randAlgt();
}
Junction::Junction(geneUS n,geneUS a): Chromosome("Junction")
{
	number = n;
	algorit = a;
}
void Junction::combine(const Chromosome& P1,const Chromosome& P2)
{
	copy(P1,P2);
}
void Junction::copycombine(const Chromosome& P1,const Chromosome& P2)
{
	copy(P1,P2);
}
void Junction::copy(const Chromosome& P1,const Chromosome& P2)
{
	float rdnum = randNumber();
	if(rdnum < 50.0)
	{
		number = ((Junction&)P1).number;
		algorit = ((Junction&)P2).algorit;
	}
	else
	{
		number = ((Junction&)P2).number;
		algorit = ((Junction&)P1).algorit;
	}
}
void Junction::mutate(float p)
{
	float numrd1 = randNumber(0.0,1.0);
	if(numrd1 <= p) number = randNumber(1.0,10.0);
	numrd1 = randNumber(0.0,1.0);
	if(numrd1 <= p) algorit = randAlgt();
}
geneUS Junction::get_number()const
{
	return number;
}
geneUS Junction::get_algorit()const
{
	return algorit;
}
geneUS Junction::randAlgt()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(1.0, 100.0);
	float randNum = distr(gen);
	if(randNum < 10.0)
	{
		return COPY;
	}
	else if(randNum < 30.0)
	{
		return COMBINE;
	}

	return COPYCOMBINE;
}
geneUS Junction::randChild()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(1.0, 5.0);
	return distr(gen);
}
void Junction::randFill()
{
	number = randNumber(1.0,4.0);
	algorit = randAlgt();
}





Single::Single(unsigned int id)
{
	this->id = id;
	age = 0;
	strength = 0;
	pMutationEvent = 0.05;
	pMutableGene = 0.3;
}
Single::Single(unsigned int id,const Junction& j) : junction(j)
{
	this->id = id;
	age = 0;
	strength = 0;
	pMutationEvent = 0.05;
	pMutableGene = 0.3;
}
/*const std::vector<Chromosome*>& Single::getChromosome()const
{
	return chromosomes;
}*/
ID Single::getID()const
{
	return id;
}
unsigned short Single::getAge() const
{
	return age;
}
float Single::getStrength() const
{
	return strength;
}
const Junction& Single::getJunction()const
{
	return junction;
}
float Single::getProbabilityMutationEvent()const
{
	return pMutationEvent;
}
float Single::getProbabilityMutableGene()const
{
	return pMutableGene;
}

/*void Single::add(Chromosome& c)
{
	chromosomes.push_back(&c);
}*/
void Single::deltaAge()
{
	age++;
}
/*void Single::deltaStrength()
{
	strength++;
}*/
/*float Single::efficiency()const
{
	if(age == 0) return 1.0;

	return ((float)strength)/((float)age);
}*/
bool Single::mutate()const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(0.0, 1.0);

	float numrand = distr(gen);
	if(numrand <= pMutationEvent) return true;
	else return false;	
}

}