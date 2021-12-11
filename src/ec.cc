
#include <random>
#include <iostream>
#include <algorithm>
#include <ctime>
//#include <libtar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include <fstream>

#include "ec.hh"


namespace oct::ec
{


bool cmpStrength(const Single* f,const Single* s)
{
	return f->getFitness() > s->getFitness();
}
bool cmpStrength1(const Single* f,const Single* s)
{
	return std::abs(f->getFitness() - 1.0) > std::abs(s->getFitness() - 1.0);
}
double randNumber()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distr(0.0, 1.0);

	return distr(gen);
}
double randNumber(double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distr(0.0, max);

	return distr(gen);
}
double randNumber(double min,double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distr(min, max);

	return distr(gen);
}









Chromosome::Chromosome(const std::string n) : name(n)
{
}
Chromosome::~Chromosome()
{

}
const Chromosome& Chromosome::operator = (const Chromosome& obj)
{
	name = obj.name;

	return *this;
}













Junction::Junction(const Junction& obj): Chromosome("Junction")
{
	number = obj.number;
	algorit = obj.algorit;
	type = obj.type;//backward compatible
}
Junction::Junction(): Chromosome("Junction")
{
	number = randNumber(1.0,9.0);
	algorit = randAlgt();
	type = TypeJuntion::BINARY;//backward compatible
}
Junction::Junction(unsigned short max): Chromosome("Junction")
{
	number = max;
	algorit = randAlgt();
	type = TypeJuntion::BINARY;//backward compatible
}
Junction::Junction(geneUS n,geneUS a): Chromosome("Junction")
{
	number = randNumber(1.0,9.0);
	algorit = randAlgt();
	type = TypeJuntion::BINARY;//backward compatible
}
Junction::Junction(TypeJuntion t): Chromosome("Junction")
{
	number = randNumber(1.0,9.0);
	algorit = randAlgt();
	type = t;//backward compatible
}
Junction::~Junction()
{
}
geneUS Junction::get_number()const
{
	return number;
}
geneUS Junction::get_algorit()const
{
	return algorit;
}
geneUS Junction::get_type()const
{
	return type;
}

void Junction::combine(const Chromosome& P1,const Chromosome& P2)
{
	copy(P1);
}

void Junction::copy(const Chromosome& P)
{
	number = ((Junction&)P).number;
	algorit = ((Junction&)P).algorit;
	type = ((Junction&)P).type;
}
void Junction::mutate(float p)
{
	double numrd1 = randNumber(0.0,1.0);
	if(numrd1 <= p) number = randNumber(1.0,10.0);
	numrd1 = randNumber(0.0,1.0);
	if(numrd1 <= p) algorit = randAlgt();
	//if(numrd1 <= p) maxChilds = randNumber(1.0,10.0);
}
geneUS Junction::randAlgt()
{
	double randNum = randNumber();
	if(randNum < 0.01) return COPY;

	return COMBINE;
}
geneUS Junction::randType()
{
	double randNum = randNumber(0.0,1.0)/2.0;
	if(randNum < 0.5) return TypeJuntion::UNARY;

	return TypeJuntion::BINARY;
}
/*geneUS Junction::randChild()
{
	return randNumber(1.0, maxChilds);
}*/
void Junction::randFill(bool favor)
{
	number = randNumber(1.0,9.0);
	algorit = randAlgt();
	if(type == TypeJuntion::NOT_TYPE) type = TypeJuntion::BINARY;//backward compatible
}
void Junction::randFill(TypeJuntion t)
{
	number = randNumber(1.0,9.0);
	algorit = randAlgt();
	type = t;//backward compatible
}













Single::Single(const Single& obj)
{
	env = obj.env;
	id = env->nextID();
	age = 0;
	fitness = obj.fitness;
	junction = obj.junction;
}
Single::Single(ec::ID id,Enviroment& e) : env(&e)
{
	this->id = id;
	init();
}
Single::Single(ec::ID id,Enviroment& e,const Junction& j) : junction(j),env(&e)
{
	this->id = id;
	init();
}
Single::~Single()
{

}

ID Single::getID()const
{
	return id;
}
unsigned short Single::getAge() const
{
	return age;
}
double Single::getFitness() const
{
	return fitness;
}
const Junction& Single::getJunction()const
{
	return junction;
}
Enviroment& Single::getEnviroment()const
{
	return *env;
}
/*Population Single::juncting(std::list<Single*>& chils,unsigned short loglevel,void*)
{
	if(getJunction().get_type() != ec::Junction::TypeJuntion::UNARY) throw octetos::core::Exception("Metodo de reproduccion incorrrecto",__FILE__,__LINE__);

	return 0;
}*/
Population Single::juncting(std::list<Single*>& chils,const Single* single,unsigned short loglevel,void*)
{
	if(getJunction().get_type() != ec::Junction::TypeJuntion::BINARY) throw octetos::core::Exception("Metodo de reproduccion incorrrecto",__FILE__,__LINE__);

	return 0;
}
bool Single::mutation()const
{
	double numrand = randNumber(0.0,1.0);
	if(numrand <= env->getProbabilityMutationEvent()) return true;
	else return false;
}
void Single::deltaAge()
{
	age++;
}
void Single::init()
{
	age = 0;
	fitness = 0;
}








void Enviroment::init()
{
	idCount = 1;
	actualIteration = 0;
	maxIteration = 0;
	echolevel = 0;
	logFile = false;
	//sigmaReduction = 1.0;
	minSolutions = 0;
	pMutationEvent = -1.0;
	pMutableGene = -1.0;
	fout = NULL;
	stopMaxIterations=false;
	stopMinSolutions = false;
	stopMaxSerie = false;
	//percen_at_iteration = 0.4;//%
	comparer = &cmpStrength;
	echoSteps = false;
	maxSerie = 0;
	epsilon = 1.0e-28;
	maxPopulation = 0;
	maxProgenitor = 0;
	initPopulation = 0;
	echolevel = 0;
	logFile = false;
	sigma = 0;
	media = 0;
	actualSerie = 0;
	newIteration = false;
	fout = &std::cout;
}
Enviroment::Enviroment()
{
	init();
}
Enviroment::~Enviroment()
{
	if(size() > 0) free();
}

Enviroment::Enviroment(Iteration m) : maxIteration(m)
{
	init();
}
Enviroment::Enviroment(Iteration m,Iteration ms) : maxIteration(m),maxSerie(ms)
{
	init();
}
Enviroment::Enviroment(const std::string& logDir,bool subtree)
{
	init();
	if(subtree) logDirectory = logDir + "/" + std::to_string(oct::core::getDayID());
	else logDirectory = logDir;
	if(not shell.exists(logDirectory)) shell.mkdir(logDirectory,true);
}
Enviroment::Enviroment(const std::string& logDir,Iteration m) : maxIteration(m)
{
	if(not shell.exists(logDir))
	{
		std::string msg = "El directorio '";
		msg += logDir + "' no existe.";
		throw oct::core::Exception(msg,__FILE__,__LINE__);
	}
	init();
	logDirectory = logDir;
	//if(not shell.exists(logDirectory)) shell.mkdir(logDirectory,true);
}
Enviroment::Enviroment(const std::string& logDir,Iteration mi,Iteration ms) : maxIteration(mi),maxSerie(ms)
{
	if(not shell.exists(logDir))
	{
		std::string msg = "El directorio '";
		msg += logDir + "' no existe.";
		throw oct::core::Exception(msg,__FILE__,__LINE__);
	}
	init();
	logDirectory = logDir + "/serie-" + std::to_string(oct::core::getDayID());//para iteracion
	if(not shell.exists(logDirectory))
	{
		shell.mkdir(logDirectory,true);
	}
	else
	{
		std::string msg = "El directorio '";
		msg += logDir + "' no existe.";
		throw oct::core::Exception(msg,__FILE__,__LINE__);
	}
}
Enviroment::Enviroment(int argc, const char* argv[])
{
	init();
	commands(argc,argv);
}

Population Enviroment::getMaxPopulation()const
{
	return maxPopulation;
}
Population Enviroment::getInitPopulation()const
{
	return initPopulation;
}
Population Enviroment::getMaxProgenitor()const
{
	return maxProgenitor;
}
double Enviroment::getSigma() const
{
	return sigma;
}
double Enviroment::Enviroment::getMedia() const
{
	return media;
}
double Enviroment::getEpsilon() const
{
	return epsilon;
}
double Enviroment::getProbabilityMutableGene()const
{
	return pMutableGene;
}
double Enviroment::getProbabilityMutationEvent()const
{
	return pMutationEvent;
}
/*
unsigned long Enviroment::getSession()const
{
	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

	unsigned long v = (now->tm_year + 1900) * 10000000000;
	v += (now->tm_mon + 1 ) * 100000000;
	v += now->tm_mday * 1000000;
	v += now->tm_hour * 10000;
	v += now->tm_min * 100;
	v += now->tm_sec;

    return v;
}
unsigned long Enviroment::getDayID()
{
	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

	unsigned long v = (now->tm_year + 1900) * 10000;
	v += (now->tm_mon + 1 ) * 100;
	v += now->tm_mday;

    return v;
}
unsigned long Enviroment::getTimeID()
{
	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

	unsigned long v = now->tm_hour * 10000;
	v += now->tm_min * 100;
	v += now->tm_sec;

    return v;
}
*/
ID Enviroment::getCountID()
{
	return idCount;
}
std::ostream* Enviroment::getFout()
{
	return fout;
}
unsigned short Enviroment::getEchoLevel()const
{
	return echolevel;
}
const std::string Enviroment::getLogSubDirectory()const
{
	return logSubDirectory;
}
bool Enviroment::getEchoSteps()const
{
	return echoSteps;
}


ID Enviroment::nextID()
{
	return ++idCount;
}
void Enviroment::enableEcho(std::ostream* f, unsigned short level)
{
	fout = f;
	echolevel = level;
}
/*void Enviroment::enableLogFile(bool log)
{
	logFile = log;
}*/
bool Enviroment::run()
{
	if(stopMinSolutions and minSolutions == 0) throw octetos::core::Exception("La cantida minima de soluciones requeridad deve ser mayor que 0",__FILE__,__LINE__);
	if(initPopulation == 0) throw oct::core::Exception("La poblacion inicial deve ser mayor que 0",__FILE__,__LINE__);
	if(maxProgenitor > maxPopulation) throw oct::core::Exception("La catidad de progenitores deve ser menor que la popblacion",__FILE__,__LINE__);
	if(maxProgenitor == 0) throw oct::core::Exception("La cantiad de progenitore deve er mayor que 0",__FILE__,__LINE__);

	actualIteration = 1;
	//std::cout << "\tStep 1\n";
	initial();
    //std::cout << "\tStep 2\n";
	unsigned short counUndelete = 0;
	std::ofstream history;
	//std::cout << "\tStep 3\n";
	logFile = not logDirectory.empty();
	if(logFile)
	{
		if(not shell.exists(logDirectory))
        {
            std::string msg = "No existe el directorio de logs '";
            msg += logDirectory + "'";
            throw core::Exception(msg,__FILE__,__LINE__);
        }
		std::string strhistory = logDirectory + "/historial.csv";
		history.open(strhistory);
	}

	//std::cout << "\tStep 4\n";

	ID oldleaderID = 0;
	double oldLeaderFitness = 0.0;
	Iteration countOldLeader = 0;
	Iteration countOldLeaderFitness = 0;
	if(echoSteps) std::cout << "\tStep 5\n";
	while(true)
	{
		if(echoSteps) std::cout << "\tStep C1\n";
		if(stopMaxIterations)
		{
			if(actualIteration > maxIteration)
			{
				history.close();
				return false;
			}
		}
		if(echolevel > 0 and fout != NULL)
		{
			if(maxSerie > 0 and stopMaxSerie) (*fout) << ">>> Serie : " << actualSerie << "/" << maxSerie << " - ";
			else ">>> ";
			if(maxIteration > 0) (*fout) << "Iteracion : " << actualIteration << "/" << maxIteration << "\n";
			else (*fout) << "Iteracion : " << actualIteration << "\n";
		}
		if(echoSteps) std::cout << "\tStep C2\n";

		media = 0.0;
		sigma = 0.0;

		if(echoSteps) std::cout << "\tStep C3\n";
		eval();
		if(echoSteps) std::cout << "\tStep C4\n";
		if(not comparer)
		{
			throw oct::core::Exception("No se a asignado el creterio de coparacion.",__FILE__,__LINE__);
		}
		sort(comparer);
		if(echoSteps) std::cout << "\tStep C5\n";

		if(logFile)
		{
			std::string strfn = logSubDirectory +  "/iteracion-" + std::to_string(actualIteration) + ".csv";
			std::ofstream fn(strfn);
			//std::cout << "\t\t" << strfn << "\n";
			if(not fn.is_open()) throw oct::core::Exception("No se logro abrir el archivo",__FILE__,__LINE__);
			for(ec::Single* s : *this)
			{
				s->save(fn);
				fn << "\n";
			}
			fn.flush();
			fn.close();
		}

		ec::ID countBefore = size();
		selection();
		if(echoSteps) std::cout << "\tStep C6\n";
		if(logFile)
		{
			std::string strSelection = logSubDirectory +  "/selection-" + std::to_string(actualIteration) + ".csv";
			//std::cout << "\t\t" << strSelection << "\n";
			std::ofstream fnSelection(strSelection);
			if(not fnSelection.is_open()) throw oct::core::Exception("No se logro abrir el archivo",__FILE__,__LINE__);
			for(Single* s : *this)
			{
				s->save(fnSelection);
				fnSelection << "\n";
			}
			fnSelection.flush();
			fnSelection.close();
		}
		if(echoSteps) std::cout << "\tStep C7\n";
		unsigned short removes = countBefore - size();
		//deletes == 0 ? counUndelete++ : counUndelete = 0;
		if(echolevel > 1 and fout != NULL)
		{
			(*fout) << "\tProgenitores selecionados, total : " << size() << "\n";
			(*fout) << "\tEliminados : " << removes << "\n";
		}
		if(echoSteps) std::cout << "\tStep C8\n";

		for(ec::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getFitness();
			s->deltaAge();
		}
		if(echoSteps) std::cout << "\tStep C9\n";
		media /= size();
		for(ec::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			sigma += pow(s->getFitness() - media,2);
		}
		sigma /= size();
		//std::cout << "\tStep C10\n";
		ec::Single* leader = *begin();
		if(echolevel > 1 and fout != NULL)
		{
			std::cout << "\tLider : " << leader->getFitness() << "\n";
			(*fout) << "\tmedia : " << media << "\n";
			(*fout) << "\tDesviacion estandar : " << sigma << "\n";
			//(*fout) << "\tVariables faltantes : " << getFaltantes() << "\n";
		}
		if(echoSteps) std::cout << "\tStep C11\n";
		/*if(stopNotDiference and actualIteration > 1)
		{
			if(sigma < notDiferenceCota)
			{
				std::cout << "\tFinalizando por no diferencia\n";
				history.close();
				return false;
			}
		}*/
		if(stopMinSolutions)
		{
			solutions.clear();
			for(Single* s : *this)
			{
				if(1.0 - s->getFitness() < epsilon) solutions.push_back(s);

				if(solutions.size() >= minSolutions)
				{
					if(echolevel > 0 and fout != NULL) (*fout) << "\n\tSe completo el conjunto de solucion minimo\n";
					if(logFile) save(solutions,"solution.cvs");
					history.close();
					return true;
				}
			}
		}
		if(echoSteps) std::cout << "\tStep C12\n";

		if(logFile)
		{
			if(history.is_open())
			{
				history  << actualIteration;
				history  << ",";
				history  << size();
				history  << ",";
				history  << media;
				history  << ",";
				history  << sigma;
				history  << ",";
				history  << pMutationEvent;
				history  << ",";
				history  << pMutableGene;
				history  << "\n";
				history .flush();
			}
		}
		if(echoSteps) std::cout << "\tStep C13\n";
		juncting();
		if(echoSteps) std::cout << "\tStep C14\n";
		for(ec::Single* s : newschils)//agregar los nuevos hijos a la poblacion
		{
			push_front(s);
		}
		if(echoSteps) std::cout << "\tStep C15\n";
		if(logFile)
		{
			std::string strChilds = logSubDirectory + "/hijos-" + std::to_string(actualIteration) + ".csv";
			std::ofstream fnChilds(strChilds);
			if(not fnChilds.is_open()) throw oct::core::Exception("No se logro abrir el archivo",__FILE__,__LINE__);
			for(ec::Single* s : newschils)//agregar los nuevos hijos a la poblacion
			{
				s->save(fnChilds);
				fnChilds << "\n";
			}
			fnChilds.flush();
			fnChilds.close();
		}
		if(echolevel > 1 and fout != NULL)
		{
			(*fout) << "\tNuevos Hijos : " << newschils.size() << "\n";
		}
		newschils.clear();

		actualIteration++;
		if(echoSteps) std::cout << "\tStep C16\n";
	}

	return false;
}
bool Enviroment::run(int argc, const char* argv[])
{
	commands(argc,argv);
	return run();
}
bool Enviroment::series()
{
	for(actualSerie = 1 ; actualSerie <= maxSerie ; actualSerie++)
	{
		free();

		if(run()) return true;
	}

	return false;
}
bool Enviroment::series(int argc, const char* argv[])
{
	commands(argc,argv);

	for(actualSerie = 1 ; actualSerie <= maxSerie ; actualSerie++)
	{
		free();

		if(run()) return true;
	}

	return false;
}
void Enviroment::stopperMaxIterations(Iteration max)
{
	maxIteration = max;
	stopMaxIterations = true;
}
/*void Enviroment::stopperNotDiference(double cota)
{
	notDiferenceCota = cota;
	stopNotDiference = true;
}*/
void Enviroment::stopperMinSolutions(Population min)
{
	minSolutions = min;
	stopMinSolutions = true;
}
void Enviroment::stopperMaxSerie(Iteration max)
{
	maxSerie = max;
	stopMaxSerie = true;
}


ec::Single* Enviroment::getProxSolution()
{
	ec::Single* s;
	for(iterator it = begin(); it != end(); it++)
	{
		s = *it;
		if(1.0 - s->getFitness() > epsilon) return s;
	}

	return *begin();
}

Single* Enviroment::getRandomSingleTop() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();

	double rndnum = randNumber(0.0,1.0);
	if(rndnum < 0.30)
	{
		return *begin();
	}
	else if(rndnum < 0.60)
	{
		return *begin()++;
	}

	return NULL;
}
Single* Enviroment::getRandomSingle() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::lognormal_distribution<double> d(0.0,1.0);

	double unit = 1.0/double(size());
	double randN = d(gen);
	unsigned int index = randN/unit;
	//std::cout << "randN : " << randN << "\n";
	//std::cout << "unit : " << unit << "\n";
	//std::cout << "index : " << index << "\n";
	std::advance(it,index);
	if(it != end()) return *it;

	return NULL;
}
void Enviroment::setEchoSteps(bool e)
{
	echoSteps = e;
}
void Enviroment::juncting()
{
	if(echoSteps) std::cout << "Enviroment::juncting Step 1\n";
	Single *single1,*single2;
	Population countNew = 0;
	if(echoSteps)  std::cout << "Enviroment::juncting Step 2\n";
	newschils.clear();
	do
	{
		if(echoSteps) std::cout << "Enviroment::juncting Step 2.1\n";
		ec::Single* single1 = getRandomSingle();
		if(single1 == NULL) continue;
		/*while(single1->getJunction().get_type() == Junction::TypeJuntion::UNARY)
		{
			countNew += single1->juncting(newschils,echolevel,NULL);
			if(newschils.size() + size() > maxPopulation) return;
		}*/
		ec::Single* single2 = getRandomSingle();
		if(single2 == NULL) continue;
		/*while(single2->getJunction().get_type() == Junction::TypeJuntion::UNARY)
		{
			countNew += single2->juncting(newschils,echolevel,NULL);
			if(newschils.size() + size() > maxPopulation) return;
		}*/
		if(single1 == single2) continue;
		if(echoSteps) std::cout << "Enviroment::juncting Step 2.2\n";
		countNew += single1->juncting(newschils,single2,echolevel,NULL);
		if(echoSteps) std::cout << "Enviroment::juncting Step 2.3\n";
		if(echoSteps) std::cout << "Nuevos Individuos " <<  newschils.size() << "\n";
	}
	while(newschils.size() + size() <= maxPopulation);
	if(echoSteps) std::cout << "Enviroment::juncting Step 3\n";
}
void Enviroment::eval()
{
	Single* single;
	for(ec::Single* s : *this)
	{
		single = (Single*) s;
		single->eval();
	}
}
void Enviroment::save()
{
	std::string strfn = logSubDirectory +  "/solutions-" + std::to_string(actualIteration) + ".csv";
	std::ofstream fn(strfn);
	for(ec::Single* s : *this)
	{
		s->save(fn);
		fn << "\n";
	}
	fn.flush();
	fn.close();
}

/**
*\brief Elimina los que no cumple con el criterio de seleccion
*/
void Enviroment::selection()
{//TODO:se puede mejorar al comenzar a eliminar desde el final hasta maxProgenitor
	//eliminar duplicados
	for(iterator i = begin(); i != end(); i++)
	{
		//std::cout << "Step 1\n";
		iterator j = i;
		//std::cout << "Step 2\n";
		advance(j,1);
		//std::cout << "Step 3\n";
		while(i != j and j != end() and size() >= maxProgenitor)
		{
			//std::cout << "Step 3.1\n";
			if((*i)->getID() == (*j)->getID() )
			{
				//std::cout << "Step 3.2\n";
				delete *j;
				//std::cout << "Step 3.3\n";
				j = erase(j);
				//std::cout << "Step 3.4\n";
			}
			else
			{
				j++;
			}
			///std::cout << "Step 3.5\n";
		}
		//std::cout << "Step 4\n";
	}
	iterator i = end();
	while(size() > maxProgenitor)//elimina desde el final hasta alcanzar el conjuto maximo de progenitores
	{
		--i;
		delete *i;
		i = erase(i);
	}
}

void Enviroment::save(const std::list<ec::Single*>& lst, const std::string& file)
{
	std::string strfn = logSubDirectory +  "/" + file;
	std::ofstream fn(strfn);
	for(ec::Single* s : lst)
	{
		s->save(fn);
		fn << "\n";
	}
	fn.flush();
	fn.close();
}

void Enviroment::commands(int argc, const char* argv[])
{
	//std::cout << "Enviroment::commands : Step 1.0\n";
	for(int i = 1; i < argc; i++)
	{
		if(strcmp("--directory-logs",argv[i]) == 0)
		{
			logDirectory = argv[++i];
			if(not shell.exists(logDirectory))
			{
				std::string msg = "El directorio '";
				msg += logDirectory + "' no existe.";
				throw oct::core::Exception(msg,__FILE__,__LINE__);
			}
		}
		if(strcmp("--iterations",argv[i]) == 0)
		{
			stopperMaxIterations(std::stoi(argv[++i]));
		}
		if(strcmp("--serie",argv[i]) == 0)
		{
			if(logDirectory.empty()) throw oct::core::Exception("Asigne primero el directorio de ejecucion",__FILE__,__LINE__);

			//serieName = argv[++i];
			std::string strDay = std::to_string(oct::core::getDayID());
			logDirectory = logDirectory + "/" + strDay;
			if(not shell.exists(logDirectory))
			{
				shell.mkdir(logDirectory);
			}

			stopperMaxSerie(std::stoi(argv[++i]));
			//std::cout << "serie = " << argv[i] << "\n";
		}
		if(strcmp("--max-treat",argv[i]) == 0)
		{
		}
		if(strcmp("--mutation-event",argv[i]) == 0)
		{
			pMutationEvent = std::stod(argv[++i]);
		}
		if(strcmp("--mutation-gene",argv[i]) == 0)
		{
			pMutableGene = std::stod(argv[++i]);
		}
		if(strcmp("--create-session",argv[i]) == 0)
		{
			std::string strDay = std::to_string(oct::core::getDayID());
			std::string strTime = std::to_string(oct::core::getTimeID());
			logDirectory = logDirectory + "/" + strDay + strTime;
			if(not shell.exists(logDirectory))
			{
				shell.mkdir(logDirectory);
			}
		}
	}
}
void Enviroment::free()
{
	for(Single* s : *this)
	{
		delete s;
	}

	clear();
}
}
