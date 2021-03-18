
#ifndef AE_HH
#define AE_HH


#include <list>

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


typedef float geneF;
typedef unsigned short geneUS;


float randNumber();
float randNumber(float max);
float randNumber(float min, float max);


class Chromosome
{
public:
	Chromosome(const std::string name);
	virtual void combine(const Chromosome& P1,const Chromosome& P2) = 0;
	virtual void copy(const Chromosome& P1,const Chromosome& P2) = 0;
	/**
	*\brief p numero entre 0 y 1 que determina la probabilidad de cada gen de ser mutado.
	*/
	virtual void mutate(float p) = 0;

	//
	static geneF mixture(const geneF& P1,const geneF& P2);

	static geneUS mixture(const geneUS& P1,const geneUS& P2);
	static geneUS mixtureDigits(const geneUS& P1,const geneUS& P2);
	static geneUS mutate(const geneUS& P1);
	static geneUS mutateDigits(const geneUS& P1);	
	virtual void randFill() = 0;
	
private:
	std::string name;
};



class Junction : public Chromosome
{
public:
	enum AlgCode
	{
		COPY,
		COMBINE,
	};
public:
	Junction();
	Junction(geneUS number,geneUS algorit);
	geneUS get_number()const;
	geneUS get_algorit()const;
	static geneUS randAlgt();
	static geneUS randChild();
	
	
	virtual void combine(const Chromosome& P1,const Chromosome& P2);
	virtual void copy(const Chromosome& P1,const Chromosome& P2);
	virtual void mutate(float p);
	virtual void randFill();
private:
	geneUS number;
	geneUS algorit;	
};


typedef unsigned int ID;
class Single
{
public:
	Single(ID id);	
	Single(ID id,const Junction& junction);
	
	ID getID()const;
	//const std::vector<Chromosome*>& getChromosome()const;
	unsigned short getAge() const;
	float getStrength() const;
	const Junction& getJunction()const;
	float getProbabilityMutationEvent()const;
	float getProbabilityMutableGene()const;

	void add(Chromosome&);
	void deltaAge();
	//void deltaStrength();
	float efficiency()const;
	bool mutate()const;

	virtual void eval() = 0;
	virtual void randFill() = 0;
	virtual void juncting(ID& idCount,std::list<Single*>& chils,Single* single,unsigned short loglevel) = 0;
	virtual void saveEval(std::ofstream& fn) = 0;

protected:
	/**
	*\brief numero entre 0 y 1 que determina la cercania al valor esperado(tiende a 1)
	*/
	float strength;
	
private:
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada gen de ser mutado.
	*/
	float pMutableGene;
	ID id;
	//std::vector<Chromosome*> chromosomes;
	unsigned short age;
	Junction junction;
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada el evento de mutacion ocurrar.
	*/
	float pMutationEvent;

};
bool cmpStrength(const Single* f,const Single* s);

enum MethodeSelection
{
	INCREMENTING_MEDIA,
	LEADER_STRONG,
};
class Enviroment
{
public:
	Enviroment();
	
	virtual void run() = 0;
	
protected:
	ae::ID maxPopulation;
	ae::ID initPopulation;

	ae::ID idCount = 1;

	bool loglevel;
	float sigma;
	float media;
	float sigmaReduccion;

	float mediaStop;

	//unsigned short elect;// los que se elegiran desde el pricipio de la lista

	bool fixedPopupation;
	bool requiereCertainty;
	unsigned int actualIteration;
	unsigned int limitIteration;
	/*
	*\brief si el programa encuentra al menos las soluciones indcadas podra terminar
	*
	*/
	unsigned short minSolutions;

	bool newIteration;

	MethodeSelection selection;
};

}

#endif