
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


#include "GA-sudoku.hh"


namespace ec::sudoku
{




Chromosome::Chromosome(const Chromosome& obj) : ec::Chromosome("sudoku::Chromosome")
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = obj.numbers[i][j];	
		}
	}
}
Chromosome::Chromosome() : ec::Chromosome("sudoku::Chromosome")
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = 0 ;	
		}
	}
}

const Chromosome& Chromosome::operator = (const Chromosome& obj)
{
	ec::Chromosome::operator =(obj);
	
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
geneUS Chromosome::getNumber(unsigned short i,unsigned short j)const
{
	return numbers[i][j];	
}
void Chromosome::setNumber(unsigned short i,unsigned short j,geneUS g)
{
	numbers[i][j] = g;
}



void Chromosome::combine(const ec::Chromosome& P1,const ec::Chromosome& P2)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			double numrd = randNumber(0.0,1.0);
			if(numrd < 0.5)
			{
				numbers[i][j] = ((const Chromosome&)P1).numbers[i][j];
			}
			else
			{
				numbers[i][j] = ((const Chromosome&)P2).numbers[i][j];
			}			
		}
	}
}
void Chromosome::copy(const ec::Chromosome& P)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			numbers[i][j] = ((const Chromosome&)P).numbers[i][j];
		}
	}
}
void Chromosome::mutate(float p)
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
void Chromosome::randFill(bool favor)
{
	if(favor)
	{
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				if(numbers[i][j] == 0) numbers[i][j] = freeNumber();
			}
		}
	}
	else
	{
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				if(numbers[i][j] == 0) numbers[i][j] = randNumber(1.0,9.1);
			}
		}
	}
}
Chromosome::~Chromosome()
{

}
geneUS Chromosome::freeNumber()const
{
	bool used[] = {false,false,false,false,false,false,false,false,false};
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			if(numbers[i][j] > 0) used[numbers[i][j]] = true;
		}
	}
	for(unsigned short i = 1; i <= 9; i++)
	{
		if(not used[i]) return i;
	}
	
	return 0;
}
void Chromosome::resetCollision()
{
	geneUS colli1 = 0,colli2 = 0;
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{
					if(numbers[i][j] == numbers[k][l]) 
					{
						numbers[i][j] = 0;
						numbers[k][l] = 0;
					}
				}
			}
		}
	}
}





Single::Single(const Single& obj) : ec::Single(obj)
{

}
Single::Single(unsigned int id,Enviroment& e,Chromosome init[][3]) : ec::Single(id,e)
{
	//std::cout << "Step 1.2.1\n";
	//std::cout << "init = " << init << "\n";
	tabla = new Chromosome*[3];
	for(unsigned short i = 0; i < 3; i++)
	{
		tabla[i] = new Chromosome[3];
	}
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = init[i][j];
		}
	}
	//std::cout << "Step 1.2.2\n";
	intiVals = init;
	//std::cout << "Step 1.2.3\n";
	genMD5();
	//std::cout << "Step 1.2.4\n";
}
Single::~Single()
{
	for(unsigned short i = 0; i < 3; i++)
	{
		delete [] tabla[i];
	}
	delete[] tabla;
}
Single::Single(unsigned int id,Enviroment& e,Chromosome** newData,Chromosome init[][3],const Junction& junction) : ec::Single(id,e,junction)
{
	tabla = newData;	
	intiVals = init;
	genMD5();
}

void Single::genMD5()
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
void Single::eval()
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
	
	fitness = 1.0 - (fails * (((const sudoku::Enviroment&)getEnviroment()).getGamma()));
}
	
	

const Chromosome& Single::getTalba(unsigned short i,unsigned short j)const
{
	return tabla[i][j];
}

void Single::randFill(bool favor)
{
	if(favor)
	{
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				tabla[i][j].resetCollision();
				tabla[i][j].randFill(favor);			
			}
		}
	}
	else
	{
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				tabla[i][j].randFill();
			}
		}
	}
}
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*) const
{
	//std::cout << "\t" << idCount << " puede tener " << getJunction().get_number() << " hijos\n";
	ID idCount;
	Population countNew = 0;
	for(ec::geneUS i = 0; i < getJunction().get_number(); i++,countNew++)
	{
		idCount = getEnviroment().nextID();
		
		Chromosome** newtabla = new Chromosome*[3];
		for(unsigned short i = 0; i < 3; i++)
		{
			newtabla[i] = new Chromosome[3];
		}
		ec::Junction newj;
		switch(getJunction().get_algorit())
		{
		case ec::Junction::AlgCode::COMBINE:
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					double rnnum = randNumber();
					if(rnnum < 0.5) newtabla[i][j].combine(tabla[i][j],((Single*)single)->tabla[i][j]);
					else newtabla[i][j].combine(((Single*)single)->tabla[i][j],tabla[i][j]);
				}
			}
			newj.combine(getJunction(),single->getJunction());
			break;		
		case ec::Junction::AlgCode::COPY:
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
							newtabla[i][j].copy(((Single*)single)->tabla[i][j]);
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
	
		//tratar de desatascar
		/*if(getEnviroment().getJam())
		{
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].resetCollision();
				}
			}
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].randFill(true);
				}
			}
		}*/
		Single* s = new Single(idCount,(Enviroment&)*env,newtabla,intiVals,newj);
		if(loglevel > 2 and getEnviroment().getFout() != NULL) (*(getEnviroment().getFout())) << "\tSe crea a " << s->getID() << "\n"; 
		chils.push_back(s);
	}
	return countNew;
}
void Single::save(std::ofstream& fn)
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
const octetos::core::MD5sum& Single::getMD5()const
{
	return md5;
}
unsigned int Single::getErros()const
{
	return (1.0 - fitness) * (1.0 / (((sudoku::Enviroment&)getEnviroment()).getGamma()));
}


void Single::print(std::ostream& out) const
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
void Single::printInit(std::ostream& out) const
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












ec::Single* Enviroment::getRandomSingleTop() const
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
ec::Single* Enviroment::getRandomSingle() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();
	
	double rndnum = randNumber(0.0,maxp);
	std::advance(it,rndnum);
	if(it != end()) return *it;
	
	return NULL;
}
Enviroment::Enviroment()
{
}
Enviroment::Enviroment(const std::string& initB)
{
	init(initB);
}
Enviroment::Enviroment(const std::string& initB,Iteration maxite)
{
	init(initB);
	maxIteration = maxite;
}
Enviroment::Enviroment(const std::string& initB,Iteration maxite,const std::string& logDir)
{
	init(initB);
	maxIteration = maxite;
	logDirectory = logDir;
	logFile = not logDirectory.empty();	
	addTerminator(Terminations::MAXITERATION);
	addTerminator(Terminations::MINSOLUTIONS);
}
Enviroment::~Enviroment()
{
	for(ec::Single* s : *this)
	{
		delete s;
	}
}
void Enviroment::init(const std::string& initB)
{
	maxPopulation = 810;//81*a
	initPopulation = maxPopulation;
	maxProgenitor = 162;//9*a
	idCount = 1;

	echolevel = 0;
	sigma = 0.0;
	media = 0.0;
	
	//actualIteration = 1;
	//maxIteration = 1000;
	newIteration = true;
	minSolutions = 1;
	pMutationEvent = 0.02;
	pMutableGene = 1.0/81.0;
	gamma = 1.0/(81.0 * 4.0);
	epsilon = gamma;
	fnBoard = initB;
	//iterJam = 1500;
	//addTerminator(ae::Terminations::JAM);
	//sliceJam = iterJam /10;
}
void Enviroment::initBoard(const std::string& initTable)
{
	//std::cout << "Step 1.1.1\n";
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
	//std::cout << "Step 1.1.2\n";
	unsigned short index = 0;	
	//std::cout << "sudokuInit = " << sudokuInit << "\n";
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
	//std::cout << "Step 1.1.3\n";
}
unsigned short Enviroment::getFaltantes() const
{
	return (1.0 - media) * (1.0/gamma);
}
double Enviroment::getGamma() const
{
	return gamma;
}



void Enviroment::selection()
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
			if(((Single*)*i)->getMD5().compare(((Single*)*j)->getMD5()) == 0 )
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
void Enviroment::save()
{
	std::string strfn = logSubDirectory +  "/solutions-" + std::to_string(actualIteration) + ".csv";
	std::ofstream fn(strfn);
	for(ec::Single* s : *this)
	{
		s->save(fn);
	}
	fn.flush();
	fn.close();
}

void Enviroment::initial()
{
	//std::cout << "Step 1.1\n";
	initBoard(fnBoard);
	//std::cout << "Step 1.2\n";
	//poblacion inicial
	//std::cout << "sudokuInit = " << sudokuInit << "\n";
	for(Population i = 0; i < initPopulation; i++,idCount++)
	{
		Single* s = new Single(nextID(),*this,sudokuInit);
		s->randFill();
		push_back(s);		
	}
	//std::cout << "Step 1.3\n";
}
void Enviroment::eval()
{
	for(ec::Single* s : *this)
	{
		s->eval();	
		s->deltaAge();
	}
}
void Enviroment::juncting()
{
	do
	{
		ec::Single* single1 = getRandomSingle();
		if(single1 == NULL) continue;
		ec::Single* single2 = getRandomSingle();
		if(single2 == NULL) continue;
		if(single1 == single2) continue;
		single1->juncting(newschils,single2,echolevel,NULL);
		if(echolevel > 2 and fout != NULL) (*fout) << "\tSe ha unido " << single1->getID() << " con " << single2->getID() << "\n";
	}
	while(newschils.size() + size() <= maxPopulation);
}

}