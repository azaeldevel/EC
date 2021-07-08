
#ifndef AE_HH
#define AE_HH

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

#include <list>
#include <string>
#include <vector>

namespace ec
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
	virtual void randFill(bool favor = false) = 0;
	
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
	virtual void randFill(bool favor = false);
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
	virtual void randFill(bool favor = false) = 0;
	virtual Population juncting(std::list<Single*>& chils,const Single* single,unsigned short loglevel,void*) const = 0;
	virtual void save(std::ofstream& fn) = 0;
	virtual void print(std::ostream&) const = 0;

protected:
	/**
	*\brief numero entre 0 y 1 que determina la cercania al valor esperado(tiende a 1)
	*/
	double fitness;

	Enviroment* env;
private:
	ID id;
	//std::vector<Chromosome*> chromosomes;
	unsigned short age;
	Junction junction;
};

bool cmpStrength(const Single* f,const Single* s);
enum MethodeSelection
{
	INCREMENTING_MEDIA,
	LEADER_STRONG,
};
enum Terminations
{
	MAXITERATION,
	MINSOLUTIONS,
	FORLEADER_NEW,
	FORLEADER_INCREMENTFITNESS,
	JAM
};

class Enviroment : public std::list<ec::Single*>
{
public:
	//

	//
	void init();
	Enviroment();
	//Enviroment(const std::string& log,Iteration maxIteration);
	Enviroment(Iteration maxIteration);
	~Enviroment();

	//getters
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
	static unsigned long getDayID();
	static unsigned long getTimeID();
	std::ostream* getFout();
	const std::string getLogSubDirectory()const;
	ID nextID();
	ID getCountID();
	bool getJam()const;

	
	void compress(const std::string& in, const std::string& out);
	void enableEcho(std::ostream* f, unsigned short level);
	void enableLogFile(bool log);
	unsigned short getEchoLevel()const;
	void write_archive(const char *outname, const char **filename);
	//void addTerminator(Terminations);
	void stopperMaxIterations(Iteration max);
	void stopperNotDiference(double cota);
	
	virtual bool run();
	virtual void selection() = 0;
	virtual void initial()=0;
	virtual void eval()=0;
	virtual void juncting()=0;
	virtual void save()=0;
	//virtual void series(const std::string& logDir,Iteration maxIteBySerie);
	
protected:
	std::string logDirectory;
	std::string logSubDirectory;
	Population initPopulation;
	Population maxPopulation;

	ID idCount = 1;
	Population maxProgenitor;
	
	unsigned short echolevel;
	bool logFile;
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

	unsigned long session;

	/**
	*\brief Para almacenar temporamente los nuevos individuos creados
	*/
	std::list<ec::Single*> newschils;


	/**
	*\brief Inidicatores de terminacion, es un numero entre 0 y 1.
	*/
	float percen_at_iteration;

	/**
	*\brief Contador de atasco
	*/
	//Iteration iterJam;

	/**
	*\brief Determina si el terminador JAM es activado
	*/
	//bool enableJam;

	/**
	*\brief Determina si el terminador JAM es activado
	*/
	//Iteration sliceJam;


private:
	/**
	*\brief Siguiente individiuo que aun no es una solucion
	*/
	ec::Single* getProxSolution();
	
	//std::vector<Terminations> terminations;

	//bool inJam;	

	/**
	*\brief Se usa cuando se activa el terminador NOT_NEW_LEADER_AT_PERCEN_ITERATION, para determinar el porcentaje de evaluacion
	*/
	bool stopMaxIterations,stopNotDiference,enableMinSolutions;
	//bool enableNotNewLeaderAtPercen,enableNotIncrementFitnessLeaderAtPercen;
	
	double notDiferenceCota;

	Iteration maxIteration;
};

}

#endif