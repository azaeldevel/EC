
#include <list>
#include <math.h>
#include <octetos/core/Error.hh>
#include <fstream>
#include <iterator>
#include <octetos/coreutils/shell.hh>
#include <algorithm>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#include "GA-ext.hh"


namespace ae::ga
{




SudokuChromosome::SudokuChromosome(const SudokuChromosome& obj) : Chromosome("SudokuChromosome")
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = obj.numbers[i][j];	
		}
	}
}
SudokuChromosome::SudokuChromosome() : Chromosome("SudokuChromosome")
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = 0 ;	
		}
	}
}

const SudokuChromosome& SudokuChromosome::operator = (const SudokuChromosome& obj)
{
	Chromosome::operator =(obj);
	
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			//std::cout << "numbers[" << i << "][" << j << "]" << "\n";
			numbers[i][j] = obj.numbers[i][j];	
		}
	}

	return *this;
}
geneUS SudokuChromosome::getNumber(unsigned short i,unsigned short j)const
{
	return numbers[i][j];	
}
void SudokuChromosome::setNumber(unsigned short i,unsigned short j,geneUS g)
{
	numbers[i][j] = g;
}



void SudokuChromosome::combine(const ae::Chromosome& P1,const ae::Chromosome& P2)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			double numrd = randNumber(0.0,1.0);
			if(numrd < 0.5)
			{
				numbers[i][j] = ((const SudokuChromosome&)P1).numbers[i][j];
			}
			else
			{
				numbers[i][j] = ((const SudokuChromosome&)P2).numbers[i][j];
			}			
		}
	}
}
void SudokuChromosome::copy(const ae::Chromosome& P)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = ((const SudokuChromosome&)P).numbers[i][j];
		}
	}
}
void SudokuChromosome::mutate(float p)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			double numrd = randNumber();
			if(numrd <= p) numbers[i][j] = randNumber(1.0,9.1);
		}
	}
}
void SudokuChromosome::randFill()
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			if(numbers[i][j] == 0) numbers[i][j] = randNumber(1.0,9.1);
		}
	}
}
SudokuChromosome::~SudokuChromosome()
{

}







SudokuSingle::SudokuSingle(const SudokuSingle& obj) : Single(obj)
{

}
SudokuSingle::SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome t[3][3]) : Single(id,e)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
	intiVals = t;
	genMD5();
}
SudokuSingle::~SudokuSingle()
{

}
SudokuSingle::SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome t[3][3],const SudokuChromosome initv[3][3],const Junction& junction) : Single(id,e,junction)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
	intiVals = initv;
	genMD5();
}

void SudokuSingle::genMD5()
{
	std::string strmd5;
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{					
					 strmd5 += std::to_string(tabla[i][j].getNumber(k,l));
				}
			}
		}
	}
	md5.set(strmd5);
}
void SudokuSingle::eval()
{
	double fails = 0.0;
		
	//conteo por cuadro
	//std::cout << "Por cuadro\n";
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			unsigned short countD[] = {0,0,0,0,0,0,0,0,0};
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{				
					if(tabla[i][j].getNumber(k,l) > 9)
					{
						fails++;
						//std::cout << "tabla[" << i << "]" << "[" << j << "]" << ".number(" << k << "," << l << ") is " << tabla[i][j].number(k,l) << " > 9\n";
					}
					else
					{
						if(tabla[i][j].getNumber(k,l) > 0) countD[tabla[i][j].getNumber(k,l) - 1]++;//cuentas la cantidad de digitos repetidos
					}
					//std::cout << "tabla[" << i << "]" << "[" << j << "]" << ".number(" << k << "," << l << ") is " << tabla[i][j].number(k,l) << "\n";
				}
			}
			for(unsigned short c : countD)
			{
				if(c > 1) fails = fails + (float)(c - 1);//despues de uno es repeticion
			}
		}
	}

	
	//por linea
	//std::cout << "Por linea\n";
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			unsigned short countD[] = {0,0,0,0,0,0,0,0,0};
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{					
					if(tabla[i][k].getNumber(j,l) > 9)
					{
						fails++;
						//std::cout << "tabla[" << i << "]" << "[" << k << "]" << ".number(" << j << "," << l << ") is " << tabla[i][k].number(j,l) << " > 9\n";
					}
					else
					{
						if(tabla[i][k].getNumber(j,l) > 0) countD[tabla[i][k].getNumber(j,l) - 1]++;//cuentas la cantidad de digitos repetidos
					}						
					//std::cout << "tabla[" << i << "]" << "[" << k << "]" << ".set(" << j << "," << l << ") is " << tabla[i][k].set(j,l) << "\n"; 
				}
			}
			for(unsigned short c : countD)
			{
				if(c > 1) fails = fails + (float)(c - 1);//despues de uno es repeticion
			}
		}
	}

	//por columna
	//std::cout << "Por columna\n";
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			unsigned short countD[] = {0,0,0,0,0,0,0,0,0};
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{				
					if(tabla[k][i].getNumber(l,j) > 9)
					{
						fails++;
						//std::cout << "tabla[" << k << "]" << "[" << i << "]" << ".number(" << l << "," << j << ") is " << tabla[k][i].number(l,j) << " > 9\n";
					}
					else
					{
						if(tabla[k][i].getNumber(l,j) > 0)  countD[tabla[k][i].getNumber(l,j) - 1]++;//cuentas la cantidad de digitos repetidos
					}						
					//std::cout << "tabla[" << k << "]" << "[" << i << "]" << ".set(" << l << "," << j << ") is " << tabla[k][i].set(l,j) << "\n"; 
				}	
			}
			for(unsigned short c : countD)
			{
				if(c > 1) fails = fails + (float)(c - 1);//despues de uno es repeticion
			}
		}
	}

	//no deve haber 0, execto en el caso de incio;
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			unsigned short countD[] = {0,0,0,0,0,0,0,0,0};
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{				
					if(tabla[i][j].getNumber(k,l) == 0)
					{
						fails++;						
					}
				}
			}
		}
	}
	
	fitness = 1.0 - (fails * (((const SudokuEnviroment&)getEnviroment()).getGamma()));
}
	
	

const SudokuChromosome& SudokuSingle::getTalba(unsigned short i,unsigned short j)const
{
	return tabla[i][j];
}

void SudokuSingle::randFill()
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j].randFill();
		}
	}
}
void SudokuSingle::juncting(ID& idCount,std::list<ae::Single*>& chils,ae::Single* single,unsigned short loglevel)
{
	//std::cout << "\t" << idCount << " puede tener " << getJunction().get_number() << " hijos\n";
	for(ae::geneUS i = 0; i < getJunction().get_number(); i++,idCount++)
	{
		SudokuChromosome newtabla[3][3];
		ae::Junction newj;
		switch(getJunction().get_algorit())
		{
		case ae::Junction::AlgCode::COMBINE:
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					double rnnum = randNumber();
					if(rnnum < 0.5) newtabla[i][j].combine(tabla[i][j],((SudokuSingle*)single)->tabla[i][j]);
					else newtabla[i][j].combine(((SudokuSingle*)single)->tabla[i][j],tabla[i][j]);
				}
			}
			newj.combine(getJunction(),single->getJunction());
			break;		
		case ae::Junction::AlgCode::COPY:
			{
				double numrd = randNumber();
				for(unsigned short i = 0; i < 3; i++)
				{
					for(unsigned short j = 0; j < 3; j++)
					{
						if(numrd < 0.5)
						{
							newtabla[i][j].copy(tabla[i][j]);
						}
						else
						{
							newtabla[i][j].copy(((SudokuSingle*)single)->tabla[i][j]);
						}					
					}
				}
				if(numrd < 0.5)
				{
					newj.copy(getJunction());
				}
				else
				{
					newj.copy(single->getJunction());
				}
				break;
			}
		default:
			throw octetos::core::Exception("Algoritmo desconocido",__FILE__,__LINE__);
		}
			
		if(mudable())
		{
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].mutate(getEnviroment().getProbabilityMutableGene());
				}
			}
			newj.mutate(getEnviroment().getProbabilityMutableGene());
			if(loglevel > 2 and getEnviroment().getFout() != NULL) (*(getEnviroment().getFout())) << "\tSe detecta mutacion para " << idCount << "\n";
		}

		//los datos iniciales no se deven cambiar.
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				for(unsigned short k = 0; k < 3; k++)
				{
					for(unsigned short l = 0; l < 3; l++)
					{
						if(intiVals[i][j].getNumber(k,l) != 0) 
						{
							newtabla[i][j].setNumber(k,l,intiVals[i][j].getNumber(k,l));
						}
					}
				}
			}
		}
	
		SudokuSingle* s = new SudokuSingle(idCount,getEnviroment(),newtabla,intiVals,newj);
		if(loglevel > 2 and getEnviroment().getFout() != NULL) (*(getEnviroment().getFout())) << "\tSe crea a " << s->getID() << "\n"; 
		chils.push_back(s);
	}
}
void SudokuSingle::save(std::ofstream& fn)
{	
	fn << getID();
	fn << ",";
	fn << getFitness();	
	fn << ",";
	fn << getErros();
	fn << ",";
	fn << getMD5();
	fn << ",";
	fn << getAge();
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{
					fn << ",";
					fn << tabla[i][k].getNumber(j,l);
				}
			}
		}
	}
	fn << "\n";
}
const octetos::core::MD5sum& SudokuSingle::getMD5()const
{
	return md5;
}
unsigned int SudokuSingle::getErros()const
{
	return (1.0 - fitness) * (1.0 / (((SudokuEnviroment&)getEnviroment()).getGamma()));
}


void SudokuSingle::print(std::ostream& out) const
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{					
					out << " " << tabla[i][k].getNumber(j,l) ;
				}
			}
			out << "\n";
		}
	}
}
void SudokuSingle::printInit(std::ostream& out) const
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{					
					out << " " << intiVals[i][k].getNumber(j,l) ;
				}
			}
			out << "\n";
		}
	}
}


ae::Single* SudokuEnviroment::getRandomSingleTop() const
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
ae::Single* SudokuEnviroment::getRandomSingle() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();
	
	double rndnum = randNumber(0.0,maxp);
	std::advance(it,rndnum);
	if(it != end()) return *it;
	
	return NULL;
}
SudokuEnviroment::SudokuEnviroment()
{
}
SudokuEnviroment::SudokuEnviroment(const std::string& log,const std::string& initB) : ae::Enviroment(log)
{
	init(initB);
}
SudokuEnviroment::~SudokuEnviroment()
{
	for(ae::Single* s : *this)
	{
		delete s;
	}
}
void SudokuEnviroment::init(const std::string& initB)
{
	maxPopulation = 1458;//81*a
	initPopulation = maxPopulation;
	maxProgenitor = 162;//9*a
	idCount = 1;

	echolevel = 0;
	sigma = 0.0;
	media = 0.0;
	
	//actualIteration = 0;
	maxIteration = 2000;
	newIteration = true;
	minSolutions = 3;
	pMutationEvent = 1.0;
	pMutableGene = 1.0/81.0;
	gamma = 1.0/(81.0 * 4.0);
	epsilon = gamma;
	
	initBoard(initB);
	
	//poblacion inicial
	for(Population i = 0; i < initPopulation; i++,idCount++)
	{
		SudokuSingle* s = new SudokuSingle(idCount,*this,sudokuInit);
		s->randFill();
		push_back(s);		
	}
}
void SudokuEnviroment::initBoard(const std::string& initTable)
{
	std::ifstream file(initTable);
	if(not file.is_open()) throw octetos::core::Exception("No se logro abrier el archivo",__FILE__,__LINE__);
	std::string strline; 
	std::vector<unsigned short> inits;
	while (std::getline(file, strline)) 
	{
	  	char *tok = strtok((char*)strline.c_str()," "); 
		while (tok!=NULL) 
		{
		    //printf("%s\n",tok); 
			inits.push_back(std::stoi(tok));
		    tok=strtok(NULL," ");
		}
	}
	unsigned short index = 0;
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{					
					sudokuInit[i][k].setNumber(j,l,inits[index]);
					index++;
				}
			}
		}
	}
}
unsigned short SudokuEnviroment::getFaltantes() const
{
	return (1.0 - media) * (1.0/gamma);
}
double SudokuEnviroment::getGamma() const
{
	return gamma;
}
bool SudokuEnviroment::run()
{
	unsigned long session = getSession();
	logSubDirectory = logDirectory +"/" + std::to_string(session);
	coreutils::Shell shell;
	if(logLevel > 0)
	{
		shell.mkdir(logSubDirectory);
	}
	//bool retVal = false;

	std::string strhistory = logSubDirectory + "/Sudoku-history.csv";
	std::ofstream history;
	if(logLevel > 0)
	{
		history.open(strhistory);
	}
	for(actualIteration = 1; actualIteration <= maxIteration; actualIteration++)
	{
		if(echolevel > 0 and fout != NULL) 
		{
			(*fout) << ">>> Iteracion : " << actualIteration << "/" << maxIteration << "\n";
		}
		media = 0.0;
		sigma = 0.0;
		//std::cout <<  "Step 1\n";
		if(echolevel > 1 and fout != NULL) 
		{
			(*fout) << "\tTamano de la poblacion : " << size() << "\n";			
			//std::cout << "\tgamman : " << gamma << "\n";
		}
		//std::cout <<  "Step 2\n";
		Population countSols = 0;
		std::string cmdSol;
		for(ae::Single* s : *this)
		{
			s->eval();	
			s->deltaAge ();
		}
		
		sort(cmpStrength);
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getFitness();			
		}
		media /= size();
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			sigma += pow(s->getFitness() - media,2);
		}
		sigma /= size();
		
		/*
		SudokuSingle& s = ((SudokuSingle&)**begin());
		s.printInit(std::cout);
		std::cout << "\n";	
		s.print(std::cout);
		std::cout << "Fortaleza : " << s.getFitness () << "\n\n";
		*/
		//std::cout <<  "Step 3\n";
		if(logLevel > 2)
		{
			std::string strfn = logSubDirectory +  "/Sudoku-" + std::to_string(actualIteration) + ".csv";
			std::ofstream fn(strfn);
			if(not fn.is_open()) throw octetos::core::Exception("No se logro abrier el archivo",__FILE__,__LINE__);
			for(ae::Single* s : *this)
			{
				s->save(fn);
			}
			fn.flush();
			fn.close();
		}
		if(echolevel > 1 and fout != NULL) 
		{
			(*fout) << "\tmedia : " << media << "\n";
			(*fout) << "\tDesviacion estandar : " << sigma << "\n";
			(*fout) << "\tVariables faltantes : " << getFaltantes() << "\n";
		}
		//std::cout <<  "Step 4\n";
		for(ae::Single* s : *this)
		{
			if(1.0 - s->getFitness () < Enviroment::epsilon)
			{
				countSols++;
				if(countSols >= minSolutions)
				{
					if(echolevel > 0 and fout != NULL) (*fout) << "\n\tSe completo el conjunto de solucion minimo\n";
					((SudokuSingle*)s)->print((*fout));
					saveSolutions(logSubDirectory);
					//compress(logDir,logDir+".tar");
					return true;
				}
			}
		}
		//std::cout <<  "Step 5\n";
		if(logLevel > 0)
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
				history  << ",";
				history  << getFaltantes();
				history  << "\n";
				history .flush();
			}
			else
			{
				throw "No se logro abrier el archivo";
			}
		}
		//std::cout <<  "Step 6\n";
		ae::ID countBefore = size();
		
		selection();
		if(logLevel > 2)
		{
			std::string strSelection = logSubDirectory +  "/Sudoku-" + std::to_string(actualIteration) + "-selection.csv";
			std::ofstream fnSelection(strSelection);
			if(not fnSelection.is_open()) throw "No se logro abrier el archivo";
			for(ae::Single* s : *this)
			{
				s->save(fnSelection);
			}
			fnSelection.flush();
			fnSelection.close();
		}
		if(echolevel > 1 and fout != NULL) 
		{
			(*fout) << "\tProgenitores selecionados, total : " << size() << "\n";
			(*fout) << "\tEliminados : " << countBefore - size() << "\n";	
		}
				
		
		std::list<ae::Single*> newschils;
		do
		{
			ae::Single* single1 = getRandomSingle();
			if(single1 == NULL) continue;
			ae::Single* single2 = getRandomSingle();
			if(single2 == NULL) continue;
			if(single1 == single2) continue;
			single1->juncting(idCount,newschils,single2,echolevel);
			if(echolevel > 1 and fout != NULL) (*fout) << "\tSe ha unido " << single1->getID() << " con " << single2->getID() << "\n";

		}
		while(newschils.size() + size() <= maxPopulation);
		if(logLevel > 2)
		{
			std::string strChilds = logSubDirectory + "/Sudoku-" + std::to_string(actualIteration) + "-childs.csv";
			std::ofstream fnChilds(strChilds);
			if(not fnChilds.is_open()) throw "No se logro abrier el archivo";				
			for(ae::Single* s : newschils)//agregar los nuevos hijos a la poblacion
			{
				push_front(s);
				s->save(fnChilds);
			}
			fnChilds.flush();
			fnChilds.close();
		}
		if(echolevel > 1 and fout != NULL) 
		{
			(*fout) << "\tNuevos Hijos : " << newschils.size() << "\n";
		}
	}
	 
	if(echolevel > 1 and fout != NULL) (*fout) << "Comprimiendo...";	
	//sleep(1);
	//compress(logDir,logDir+".tar");
	//shell.rm(logSubDirectory);
	if(echolevel > 1 and fout != NULL) (*fout) << " hecho\n";
	history.close();
	
	return false;
}


void SudokuEnviroment::selection()
{
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
			if(((SudokuSingle*)*i)->getMD5().compare(((SudokuSingle*)*j)->getMD5()) == 0 )
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
void SudokuEnviroment::saveSolutions(const std::string& dir)const
{
	std::string strfn = dir +  "/Sudoku-" + std::to_string(actualIteration) + "-solutions.csv";
	std::ofstream fn(strfn);
	for(ae::Single* s : *this)
	{
		if(1.0 - s->getFitness () < Enviroment::epsilon)
		{
			s->save(fn);
		}
	}
	fn.flush();
	fn.close();
}


}