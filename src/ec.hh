
#ifndef AE_HH
#define AE_HH


#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>

#if defined(__GNUC__) && defined(__linux__)
    #include <octetos/core/Error.hh>
    #include <octetos/core/shell.hh>
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    #include <Error.hh>
    #include <shell.hh>
#else
    #error "Pltaforma desconocida"
#endif


namespace oct::ec
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
typedef double real;

double randNumber();
double randNumber(double max);
double randNumber(double min, double max);


static std::random_device rd;
static std::default_random_engine dre;
static std::mt19937 gen;

/**
*\brief Representa nuestro conjunto de variables
*/
class Chromosome
{
public:
	Chromosome(const std::string name);
	virtual ~Chromosome();

	const Chromosome& operator = (const Chromosome&);

protected:
	//static std::random_device rd;
	//static std::mt19937 gen;
private:
	std::string name;
};



class Junction : public Chromosome
{
public:
	enum TypeJuntion
	{
		NOT_TYPE,
		UNARY,
		BINARY,
	};
	enum AlgCode
	{
		COPY,
		COMBINE,
	};
public:
	Junction();
	Junction(unsigned short maxChilds);
	virtual ~Junction();
	Junction(const Junction& );
	Junction(geneUS number,geneUS algorit);
	Junction(TypeJuntion type);
	geneUS get_number()const;
	geneUS get_algorit()const;
	geneUS get_type()const;
	static geneUS randAlgt();
	//static geneUS randChild();
	static geneUS randType();


	virtual void combine(const Chromosome& P1,const Chromosome& P2);
	virtual void copy(const Chromosome& P);
	virtual void mutate(float p);
	virtual void randFill(bool favor = false);
	virtual void randFill(TypeJuntion);
private:
	geneUS number;
	geneUS algorit;
	TypeJuntion type;
};

/**
*\brief Representa una posible solucion a nuestro problema
*/
class Single
{
public:
	/**
	*\brief Constructor de copia
	*/
	Single(const Single&);
	/**
	*\brief Constructor que recive el ID del Individuo y el Ambiente
	*/
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
	//bool mutation()const;
	void init();

	/**
	*\brief Evalua al individuo y asigna su valor de adaptabilidad(fitness)
	*/
	virtual void eval() = 0;/**
	*\brief Realiza el apareo entre dos individuos
	*/
	//virtual Population juncting(std::list<Single*>& chils,unsigned short loglevel,void*);
	/**
	*\brief Realiza el apareo entre dos individuos
	*/
	virtual void juncting(std::list<Single*>& chils,const Single* single) = 0;
	/**
	*\brief Crea un arcivo CSV con los datos relevantes del individuo
	*/
	virtual void save(std::ofstream& fn) = 0;
	/**
	*\brief Imprime los datos relevantes del individuo
	*/
	virtual void print(std::ostream&) const = 0;

	/**
	*\brief Crea una mutacion
	*/
	virtual void mutate() = 0;
protected:
	/**
	*\brief numero entre 0 y 1 que determina la cercania al valor esperado(tiende a 1)
	*/
	double fitness;

	Enviroment* env;

	//static std::random_device rd;
	//static std::mt19937 gen;
private:
	ID id;
	//std::vector<Chromosome*> chromosomes;
	unsigned short age;
	Junction junction;
};

/**
*\brief Algoritmo de ordenamiento
*/
bool cmpStrength(const Single* f,const Single* s);
/**
*\brief Algoritmo de ordenamiento
*/
bool cmpStrength1(const Single* f,const Single* s);

/**
*\brief Pricipales variables de control y proceso
*/
class Enviroment : public std::list<ec::Single*>
{
public:
	//

	//
	/**
	*\brief Inizializa las variables
	*/
	void init();
	Enviroment();
	Enviroment(const std::string& log, bool subtree);
	Enviroment(const std::string& log,Iteration maxIteration);
	Enviroment(const std::string& log,Iteration maxIteration,Iteration maxSerie);
	Enviroment(Iteration maxIteration);
	Enviroment(Iteration maxIteration,Iteration maxSerie);
	Enviroment(int argc, const char* argv[]);
	virtual ~Enviroment();

	//getters
	Population getMaxPopulation()const;
	Population getInitPopulation()const;
	Population getMaxProgenitor()const;
	double getSigma() const;
	//double getSigmaReduction() const;
	double getMedia() const;
	double getEpsilon() const;
	//double getProbabilityMutableGene()const;
	//double getMutableProbability()const;
	//void remove(ae::Single*);
	unsigned long getSession()const;
	//static unsigned long getDayID();
	//static unsigned long getTimeID();
	std::ostream* getFout();
	//const std::string getLogSubDirectory()const;
	
	/**
	*\brief Devuelve el siguiento ID para un nuevo objeto Single
	*/
	ID nextID();
	ID getCountID();
	//bool getJam()const;
	bool getEchoSteps()const;
	void setEchoSteps(bool);


	void compress(const std::string& in, const std::string& out);
	void enableEcho(std::ostream* f, unsigned short level);
	//void enableLogFile(bool log);
	unsigned short getEchoLevel()const;
	void write_archive(const char *outname, const char **filename);
	//void addTerminator(Terminations);
	void stopperMaxIterations(Iteration max);
	//void stopperNotDiference(double cota);
	void stopperMinSolutions(Population);
	void stopperMaxSerie(Iteration max);
	virtual void commands(int argc, const char* argv[]);

	/**
	*\brief Inicia la ejecution del algoritmo(funcion de entrada)
	*/
	virtual bool run();
	/**
	*\brief Inicia la ejecution del algoritmo con los parametro de linea de comando(funcion de entrada)
	*/
	virtual bool run(int argc, const char* argv[]);
	/**
	*\brief Inicia el proceso de veluacion
	*/
	//virtual void eval();
	/**
	*\brief Inicia el proceso de apareo
	*/
	virtual void juncting();

	/**
	*\brief Inicia el proceso de guardar
	*/
	virtual void save();
	/**
	*\brief Inicia el proceso de gualdar la lista indicada, llamando a la funcion Single.save() de cada obejto en la lista
	*\param ls lista de objetos para guardar
	*\param file nombre de archivo que se genera
	*/
	virtual void save(const std::list<ec::Single*>& ls, const std::string& file);
	/**
	*\brief Inicia el proceso de seleccion de individuos
	*/
	virtual void selection();
	/**
	*\brief Crea la poblacion inicial
	*/
	virtual void initial() = 0;

	/**
	*\brief Inicia el proceso de serie(funcion de entrada)
	*/
	virtual bool series();
	/**
	*\brief Inicia el proceso de serie con argumentos de linea de comandos(funcion de entrada)
	*/
	virtual bool series(int argc, const char* argv[]);
	/**
	*\brief Libera la memoria ocupada por la actual poblacion y vacia la lista
	*/
	virtual void free();
private:
	
	Single* getRandomSingle();
	Single* getRandomSingleTop();
	Single* getRandomSingleAny();

protected:
	std::string logDirectory;
	std::string logDirectoryHistory;
	std::string basedir;
	Population initPopulation;
	Population maxPopulation;

	ID idCount;
	Population maxProgenitor;

	unsigned short echolevel;
	unsigned int echoPrecision;
	bool logDirectoryFlag;
	bool logDirectoryHistoryFlag;
	double sigma;
	double media;

	Iteration actualIteration;

	Iteration actualSerie;

	bool newIteration;

	double epsilon;
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada gen de ser mutado.
	*/
	//double pMutableGene;
	/**
	*\brief numero entre 0 y 1 que determina la probabilidad de cada el evento de mutacion ocurrar.
	*/
	double mutableProb;

	std::ostream* fout;

	//unsigned long session;

	/**
	*\brief Para almacenar temporamente los nuevos individuos creados
	*/
	std::list<ec::Single*> newschils;

	std::list<ec::Single*> solutions;

	/**
	*\brief Inidicatores de terminacion, es un numero entre 0 y 1.
	*/
	//float percen_at_iteration;

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

	bool (*comparer)(const Single* f,const Single* s);

	bool echoSteps;

	//
	oct::core::Shell shell;

private:
	/**
	*\brief Siguiente individiuo que aun no es una solucion
	*/
	ec::Single* getProxSolution();

	//std::vector<Terminations> terminations;

	//bool inJam;


	Iteration maxIteration;

	/**
	*\brief Se usa cuando se activa el terminador NOT_NEW_LEADER_AT_PERCEN_ITERATION, para determinar el porcentaje de evaluacion
	*/
	bool stopMaxIterations;

	//bool stopNotDiference;

	//double notDiferenceCota;


	/*
	*\brief si el programa encuentra al menos las soluciones indcadas podra terminar
	*
	*/
	Population minSolutions;

	bool stopMinSolutions;

	Iteration maxSerie;

	bool stopMaxSerie;

	//std::string serieName;

	unsigned short maxChilds;
};

}

#endif
