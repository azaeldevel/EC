
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
class Enviroment;


typedef float geneF;
typedef double geneD;
typedef unsigned short geneUS;
typedef unsigned geneS;
typedef unsigned int genUI;
typedef int genI;
typedef void* genFC;

typedef unsigned long ID;
typedef ID Population;
typedef unsigned int Iteration;

double randNumber();
double randNumber(double max);
double randNumber(double min, double max);


class Chromosome
{
public:
	Chromosome(const std::string name);
	virtual ~Chromosome();
	virtual void combine(const Chromosome& P1,const Chromosome& P2) = 0;
	virtual void copy(const Chromosome& P1) = 0;
	/**
	*\brief p numero entre 0 y 1 que determina la probabilidad de cada gen de ser mutado.
	*/
	virtual void mutate(float p) = 0;

	const Chromosome& operator = (const Chromosome&);

	//
	static geneF mixture(const geneF& P1,const geneF& P2);

	static geneUS mixture(const geneUS& P1,const geneUS& P2);
	static geneUS mixtureDigits(const geneUS& P1,const geneUS& P2);
	static geneUS mutate(const geneUS& P1);
	static geneUS mutateDigits(const geneUS& P1);	
	virtual void randFill() = 0;
	
protected:
	unsigned int mutated;
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
	virtual ~Junction();
	Junction(geneUS number,geneUS algorit);
	geneUS get_number()const;
	geneUS get_algorit()const;
	static geneUS randAlgt();
	static geneUS randChild();
	
	
	virtual void combine(const Chromosome& P1,const Chromosome& P2);
	virtual void copy(const Chromosome& P);
	virtual void mutate(float p);
	virtual void randFill();
private:
	geneUS number;
	geneUS algorit;	
};


class Single
{
public:
	Single(const Single&);
	Single(ID id,Enviroment&);	
	Single(ID id,Enviroment&,const Junction& junction);
	virtual ~Single();
	
	ID getID()const;
	//const std::vector<Chromosome*>& getChromosome()const;
	unsigned short getAge() const;
	double getFitness() const;
	const Junction& getJunction()const;
	Enviroment& getEnviroment()const;

	void add(Chromosome&);
	void deltaAge();
	//void deltaStrength();
	float efficiency()const;
	bool mudable()const;
	void init();
	

	virtual void eval() = 0;
	virtual void randFill() = 0;
	virtual void juncting(ID& idCount,std::list<Single*>& chils,Single* single,unsigned short loglevel) = 0;
	virtual void save(std::ofstream& fn) = 0;

protected:
	/**
	*\brief numero entre 0 y 1 que determina la cercania al valor esperado(tiende a 1)
	*/
	double fitness;
private:
	ID id;
	//std::vector<Chromosome*> chromosomes;
	unsigned short age;
	Junction junction;
	Enviroment* env;
};

bool cmpStrength(const Single* f,const Single* s);
enum MethodeSelection
{
	INCREMENTING_MEDIA,
	LEADER_STRONG,
};

class Enviroment : public std::list<ae::Single*>
{
public:
	//

	//
	Enviroment();
	Enviroment(const std::string& log,Iteration limitIteration);
	~Enviroment();
	Population getMaxPopulation()const;
	Population getInitPopulation()const;
	Population getMaxProgenitor()const;
	
	double getSigma() const;
	//double getSigmaReduction() const;
	double getMedia() const;
	double getEpsilon() const;
	double getProbabilityMutableGene()const;
	double getProbabilityMutationEvent()const;
	//void remove(ae::Single*);
	unsigned long getSession()const;
	std::ostream* getFout();
	ID next();
	ID getCountID();
	void compress(const std::string& in, const std::string& out);
	void enableEcho(std::ostream* f, unsigned short level);
	
	virtual bool run() = 0;
	virtual void selection() = 0;
	
protected:
	std::string logDirectory;
	Iteration maxIteration;
	Population maxPopulation;
	Population initPopulation;

	ID idCount = 1;
	Population maxProgenitor;
	
	unsigned short loglevel;
	double sigma;
	double media;
	
	Iteration actualIteration;
	/*
	*\brief si el programa encuentra al menos las soluciones indcadas podra terminar
	*
	*/
	Population minSolutions;

	bool newIteration;
	
	double epsilon;
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada gen de ser mutado.
	*/
	double pMutableGene;
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada el evento de mutacion ocurrar.
	*/
	double pMutationEvent;

	std::ostream* fout;
};

}

#endif