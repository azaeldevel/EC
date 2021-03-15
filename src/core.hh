
#ifndef AE_HH
#define AE_HH

#include <vector>

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#error "Plataforma no soportada"
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#error "Plataforma no soportada"
#endif
#endif

#include <string>


namespace ae
{

typedef int geneI;
typedef float geneF;
typedef long geneL;
typedef unsigned short geneUS;
typedef double geneD;
typedef unsigned char geneUC;

float randNumber();
float randNumber(float max);
float randNumber(float min, float max);

class Chromosome
{
public:
	Chromosome(const std::string name);
	virtual void combine(const Chromosome& P1,const Chromosome& P2) = 0;
	virtual void copycombine(const Chromosome& P1,const Chromosome& P2) = 0;
	virtual void copy(const Chromosome& P1,const Chromosome& P2) = 0;
	virtual void mutate() = 0;

private:
	std::string name;
};



class Junction : public Chromosome
{
public:
	enum AlgCode
	{
		COMBINE,
		COPY,
		COPYCOMBINE,
	};
public:
	Junction();
	Junction(geneUS number,geneUS algorit);
	geneUS get_number()const;
	geneUS get_algorit()const;
	static geneUS randAlgt();
	static geneUS randChild();
	
	virtual void combine(const Chromosome& P1,const Chromosome& P2);
	virtual void copycombine(const Chromosome& P1,const Chromosome& P2);
	virtual void copy(const Chromosome& P1,const Chromosome& P2);
	virtual void mutate();
private:
	geneUS number;
	geneUS algorit;	
};



class Single
{
public:
	Single(unsigned int id);	
	Single(unsigned int id,const Junction& junction);
	
	unsigned short getID();
	const std::vector<Chromosome*>& getChromosome()const;
	unsigned short getAge() const;
	unsigned short getStrength() const;
	const Junction& getJunction()const;

	void add(Chromosome&);
	void deltaAge();
	void deltaStrength();
	float efficiency()const;
	
protected:
	
private:
	unsigned short id;
	std::vector<Chromosome*> chromosomes;
	unsigned short age;
	unsigned short strength;
	Junction junction;

};



}

#endif