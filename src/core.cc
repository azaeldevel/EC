
#include <random>


#include "core.hh"


namespace ae
{



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


	
Chromosome::Chromosome(const std::string n) : name(n)
{
}

		

struct caretFloat
{
	short a:16,b:16;
};
struct caretFloatBits
{
	short a:1,b:1,c:1,d:1,e:1,f:1,g:1,h:1,i:1,j:1,k:1,l:1,m:1,n:1,o:1,p:4,q:1,r:1,s:2,t:1,u:1,v:1,w:1,x:1,y:1,z:1;
};

MaxMin_R::MaxMin_R() : Chromosome("MaxMin_R")
{}
MaxMin_R::MaxMin_R(geneF x2_mx,geneF x2_mn) : Chromosome("MaxMin_R")
{
	this->x2_mx = x2_mx;
	this->x2_mn = x2_mn;
}
void MaxMin_R::combine(const Chromosome& with,const Chromosome& P2)
{
	caretFloat* cfLocal = reinterpret_cast<caretFloat*>(&x2_mn);
	caretFloat* cfPar = reinterpret_cast<caretFloat*>(&((MaxMin_R&)with).x2_mn);
	float rdnum2 = randNumber();
	if(rdnum2 < 50.0)
	{
		float child;
		caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
		crChild->a = cfPar->b;
		crChild->b = cfLocal->a;
		x2_mn = child;
	}
	else
	{
		float child;
		caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
		crChild->b = cfPar->a;
		crChild->a = cfLocal->b;
		x2_mn = child;
	}
	
	cfLocal = reinterpret_cast<caretFloat*>(&x2_mx);
	cfPar = reinterpret_cast<caretFloat*>(&((MaxMin_R&)with).x2_mx);
	rdnum2 = randNumber();
	if(rdnum2 < 50.0)
	{
			float child;
			caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
			crChild->a = cfPar->b;
			crChild->b = cfLocal->a;
			x2_mx = child;
	}
	else
	{
		float child;
		caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
		crChild->b = cfPar->a;
		crChild->a = cfLocal->b;
		x2_mx = child;
	}
}
void MaxMin_R::copycombine(const Chromosome& with,const Chromosome& P2)
{
float rdnum = randNumber();
	if(rdnum < 50.0)
	{
		x2_mx = ((MaxMin_R&)with).x2_mx;//copy
		//x2_mn = with.x2_mn;//combine
		caretFloat* cfLocal = reinterpret_cast<caretFloat*>(&x2_mn);
		caretFloat* cfPar = reinterpret_cast<caretFloat*>(&((MaxMin_R&)with).x2_mn);
		float rdnum2 = randNumber();
		if(rdnum2 < 50.0)
		{
			float child;
			caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
			crChild->a = cfPar->b;
			crChild->b = cfLocal->a;
			x2_mn = child;
		}
		else
		{
			float child;
			caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
			crChild->b = cfPar->a;
			crChild->a = cfLocal->b;
			x2_mn = child;
		}
	}
	else
	{
		//x2_mx = with.x2_mx;//combine
		caretFloat* cfLocal = reinterpret_cast<caretFloat*>(&x2_mx);
		caretFloat* cfPar = reinterpret_cast<caretFloat*>(&((MaxMin_R&)with).x2_mx);
		float rdnum2 = randNumber();
		if(rdnum2 < 50.0)
		{
			float child;
			caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
			crChild->a = cfPar->b;
			crChild->b = cfLocal->a;
			x2_mx = child;
		}
		else
		{
			float child;
			caretFloat* crChild = reinterpret_cast<caretFloat*>(&child);
			crChild->b = cfPar->a;
			crChild->a = cfLocal->b;
			x2_mx = child;
		}
		
		x2_mn = ((MaxMin_R&)with).x2_mn;//copy
	}
}
void MaxMin_R::copy(const Chromosome& with,const Chromosome& P2)
{
	x2_mx = ((MaxMin_R&)with).x2_mx;
	x2_mn = ((MaxMin_R&)with).x2_mn;
}
void MaxMin_R::mutate()
{
	caretFloatBits* bits = reinterpret_cast<caretFloatBits*>(&x2_mx);
	short rdnum2 = (short)randNumber(26.0);
	switch(rdnum2)
	{
	case 1:
		bits->a = 1;
		break;
	case 2:
		bits->b = 1;
		break;
	case 3:
		bits->c = 1;
		break;
	case 4:
		bits->d = 1;
		break;
	case 5:
		bits->e = 1;
		break;
	case 6:
		bits->f = 1;
		break;
	case 7:
		bits->g = 1;
		break;
	case 8:
		bits->h = 1;
		break;
	case 9:
		bits->i = 1;
		break;
	case 10:
		bits->j = 1;
		break;
	case 11:
		bits->k = 1;
		break;
	case 12:
		bits->l = 1;
		break;
	case 13:
		bits->m = 1;
		break;
	case 14:
		bits->n = 1;
		break;
	case 15:
		bits->o = 1;
		break;
	case 16:
		bits->p = 1;
		break;
	case 17:
		bits->q = 1;
		break;
	case 18:
		bits->r = 1;
		break;
	case 19:
		bits->s = 1;
		break;
	case 20:
		bits->t = 1;
		break;
	case 21:
		bits->u = 1;
		break;
	case 22:
		bits->v = 1;
		break;
	case 23:
		bits->w = 1;
		break;
	case 24:
		bits->x = 1;
		break;
	case 25:
		bits->y = 1;
		break;
	case 26:
		bits->z = 1;
		break;
	}
}
geneF MaxMin_R::get_x2_mx()const
{
	return x2_mx;
}
geneF MaxMin_R::get_x2_mn()const
{
	return x2_mn;
}

Junction::Junction(): Chromosome("Junction")
{}
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
void Junction::mutate()
{
	number = randNumber(1.0,3.0);
	algorit = randAlgt();
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
		return COPYCOMBINE;
	}

	return COMBINE;
}
geneUS Junction::randChild()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(1.0, 3.0);
	return distr(gen);
}


Single::Single(unsigned int id)
{
	this->id = id;
	age = 0;
	strength = 0;
}
const std::vector<Chromosome*>& Single::getChromosome()const
{
	return chromosomes;
}
unsigned short Single::getID()
{
	return id;
}
unsigned short Single::getAge() const
{
	return age;
}
unsigned short Single::getStrength() const
{
	return strength;
}
void Single::add(Chromosome& c)
{
	chromosomes.push_back(&c);
}
void Single::deltaAge()
{
	age++;
}
void Single::deltaStrength()
{
	strength++;
}
float Single::efficiency()const
{
	if(age == 0) return 1.0;

	return ((float)strength)/((float)age);
}

}