
#ifndef AE_HH
#define AE_HH


#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>

#if EXPORTING_OCTETOS_EC_DLL
    #if _MSC_VER
        #define OCTETOS_EC_DECLSPCE_DLL __declspec(dllexport)
    #elif __GNUG__

    #endif
#elif IMPORTING_OCTETOS_EC_DLL
    #if _MSC_VER
    #define OCTETOS_EC_DECLSPCE_DLL __declspec(dllimport)
    #elif __GNUG__

    #endif
#else
    #define OCTETOS_EC_DECLSPCE_DLL
#endif
#if defined(__linux__)
    #include <octetos/core/Error.hh>
    #include <octetos/core/shell.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Error.hh>
    #include <core/src/shell.hh>
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
typedef unsigned long Iteration;
typedef double real;

/*
double randNumber();
double randNumber(double max);
double randNumber(double min, double max);
*/

//static std::random_device rd;
//static std::default_random_engine dre;
//static std::mt19937 gen;


class OCTETOS_EC_DECLSPCE_DLL Exception : public std::exception
{
public:
	enum Code
	{
		UNKNOW,
		BAD_VALUE_maxProgenitor,
		BAD_VALUE_size,
	};

	Exception();
	Exception(Code code,const char* filename, unsigned int line);

	virtual const char* what() const throw();

private:
	Code code;
	const char* filename;
	unsigned int line;
};
/**
*\brief Representa nuestro conjunto de variables
*/
class OCTETOS_EC_DECLSPCE_DLL Chromosome
{
public:
	Chromosome(const std::string name);
	virtual ~Chromosome();

	const Chromosome& operator = (const Chromosome&);

protected:
	static std::random_device rd;
	static std::mt19937 gen;
private:
	std::string name;
};


/*
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
	static std::uniform_int_distribution<int> randChild;
	static std::uniform_int_distribution<int> randAlg;
	static std::uniform_int_distribution<int> randN;
};*/


struct OCTETOS_EC_DECLSPCE_DLL Save
{
	Save();
	Save(std::ofstream&);
	Save(std::ofstream*);
	/*operator std::ofstream&();
	std::ofstream& operator =(std::ofstream&);
	std::ofstream* operator =(std::ofstream*);*/
	bool getNewLeader()const;

	//
    bool new_leader;
	std::ofstream* out;
};

class OCTETOS_EC_DECLSPCE_DLL SaveCollection : public Save
{
public:
	SaveCollection();
	SaveCollection(const std::filesystem::path&);
	~SaveCollection();

	/**
	*\brief abre un archivo cuando se a especificado previamente el directorio
	*/
	void open(const std::filesystem::path& fn);

	/**
	*\brief abre un archivo especificado el nombre y directorio
	*/
	void open(const std::filesystem::path& fn,const std::filesystem::path& dir);
	void close();

protected:
	std::filesystem::path directory;
};

struct OCTETOS_EC_DECLSPCE_DLL SaveCollectionByIteration : public SaveCollection
{
	SaveCollectionByIteration(const std::filesystem::path&,const std::string&);

	void open(Iteration it);

private:
	std::string prefix;
};

struct OCTETOS_EC_DECLSPCE_DLL SaveIteration : public SaveCollectionByIteration
{
	SaveIteration(const std::filesystem::path&);
};
struct OCTETOS_EC_DECLSPCE_DLL SaveChilds : public SaveCollectionByIteration
{
	SaveChilds(const std::filesystem::path&);
};
struct OCTETOS_EC_DECLSPCE_DLL SaveSelections : public SaveCollectionByIteration
{
	SaveSelections(const std::filesystem::path&);
};
struct OCTETOS_EC_DECLSPCE_DLL SaveSolutions : public SaveCollection
{
	SaveSolutions();
	SaveSolutions(const std::filesystem::path&);
};


/**
*\brief Representa una posible solucion a nuestro problema
*/
class OCTETOS_EC_DECLSPCE_DLL Single
{
public:
	/**
	*\brief Constructor de copia
	*/
	Single(const Single&);
	/**
	*\brief Constructor que recive el ID del Individuo y el Ambiente
	*/
	Single(Enviroment&);
	Single(Enviroment&,unsigned int);
	virtual ~Single();

	ID getID()const;
	//const std::vector<Chromosome*>& getChromosome()const;
	unsigned short getAge() const;
	double getFitness() const;
	//const Junction& getJunction()const;
	unsigned int getChilds()const;
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
	virtual void save(Save&) = 0;
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

	static std::random_device rd;
	static std::mt19937 gen;

private:
	ID id;
	//std::vector<Chromosome*> chromosomes;
	unsigned int age;
	unsigned short childs;
};

/**
*\brief Algoritmo de ordenamiento
*/
OCTETOS_EC_DECLSPCE_DLL bool cmpStrength(const Single* f,const Single* s);
/**
*\brief Algoritmo de ordenamiento
*/
OCTETOS_EC_DECLSPCE_DLL bool cmpStrength1(const Single* f,const Single* s);

struct data_reglog
{
	Iteration x;
	real y;
};

typedef std::list<data_reglog> list_reglog;

struct table_reglog
{
	//list_reglog datas;
	real sum_ln_x;
	real sum_ln_x_mean;
	real sum_ln2_x;
	real sum_ln_xy;
	real sum_y2;
	real a;
	real b;
	real y_mean;

	unsigned int getPredictX(real y) const;
	unsigned int getPredictFinally() const;
};



typedef void (*echo)(const char*);
/**
*\brief Pricipales variables de control y proceso
*/
class OCTETOS_EC_DECLSPCE_DLL Enviroment : protected std::list<ec::Single*>
{
public:
	//

	//
	/**
	*\brief Inizializa las variables
	*/
	void init();
	void init2();
	Enviroment();
	Enviroment(const std::filesystem::path& log, bool subtree);
	Enviroment(const std::filesystem::path& log,Iteration maxIteration);
	Enviroment(const std::filesystem::path& log,Iteration maxIteration,Iteration maxSerie);
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
	double getMean() const;
	double getEpsilon() const;
	//double getProbabilityMutableGene()const;
	real getMutableProbability()const;
	//void remove(ae::Single*);
	unsigned long getSession()const;
	//static unsigned long getDayID();
	//static unsigned long getTimeID();
	echo getFout();
	//const std::string getLogSubDirectory()const;
	Iteration getIterationActual()const;
	const std::filesystem::path& getLogDirectory()const;
	const std::filesystem::path& getLogDirectoryHistory()const;
	const std::filesystem::path& getLogDirectorySolutions()const;
	const std::list<ec::Single*> getSolutions()const;
	Population get_population_size()const;
	const ec::Single* get_single(Population index)const;

	/**
	*\brief Devuelve el siguiento ID para un nuevo objeto Single
	*/
	ID nextID();
	ID getCountID();
	//bool getJam()const;
	bool getEchoSteps()const;
	void setEchoSteps(bool);


	void compress(const std::string& in, const std::string& out);
	void enableEcho(echo f, unsigned short level);
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
	virtual void save(const std::list<ec::Single*>& ls, const std::filesystem::path& file);
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

    void create_session();

	/**
	*\brief Detine la funcion run
	*/
	void stop();

	/**
	*\brief Verifica si la funcion run esta en ejecucion
	*/
	bool isRunning();

	/**
	*\brief Coloca en list los mejeros elemento encontrados al momento
	*\return true si logra colocar los elementos solicitados, false si count > tamano de la lista
	*/
	bool getBetters(unsigned int count, std::list<ec::Single*>& list);

	real getProgress()const;

	unsigned int getPredictFinally() const;
public:
	//

private:
	Single* getRandomSingle();
	Single* getRandomSingleAny();
	Single* getRandomSingleFirst();
	Single* getRandomSingleSecond();
	Single* getRandomSingleRandom();

protected:
	std::filesystem::path logDirectory;
	std::filesystem::path logDirectoryHistory;
	std::filesystem::path logDirectorySolutions;
	std::filesystem::path basedir;
	Population initPopulation;
	Population maxPopulation;

	ID idCount;
	Population maxProgenitor;

	unsigned short echolevel;
	unsigned int echoPrecision;
	bool logDirectoryFlag;
	bool logDirectoryHistoryFlag;
	bool logDirectorySolutionsFlag;
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

	echo echoF;

	Save* savingDevice;

    /**
	*\brief Desviacion estandar usada para generar la seleccion en la operacion de apareo
	*/
	real junting_sigma;

    unsigned int maxMutation;

	/**
	*\brief Activa el modulo de prediccion
	*/
	//bool prediction;

	static std::random_device rd;
	static std::mt19937 gen;

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

	bool running;


	table_reglog prediction_table;

	std::uniform_int_distribution<int>* juntion_type;
	std::uniform_int_distribution<int>* juntion_progenitor;
};

}

#endif
