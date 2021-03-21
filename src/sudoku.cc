
#include <list>
#include <math.h>
#include <octetos/core/Error.hh>
#include <fstream>
#include <iterator>
#include <octetos/coreutils/shell.hh>
#include <algorithm>


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
			float numrd = randNumber(0.0,1.0);
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
void SudokuChromosome::copy(const ae::Chromosome& P1,const ae::Chromosome& P2)
{
	float numrd1 = randNumber(0.0,1.0);
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			if(numrd1 < 0.7)
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
void SudokuChromosome::mutate(float p)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			float numrd = randNumber(0.0,1.0);
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
			if(numbers[i][j] == 0)
			{
				numbers[i][j] = randNumber(1.0,9.1);
			}
		}
	}
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
SudokuSingle::SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome (*t)[3]) : Single(id,e)
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
SudokuSingle::SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome (*t)[3],const Junction& junction) : Single(id,e,junction)
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
						//std::cout << "tabla[" << i << "]" << "[" << j << "]" << ".number(" << k << "," << l << ") is " << tabla[i][j].number(k,l) << " > 9\n";
					}
					//std::cout << "tabla[" << i << "]" << "[" << j << "]" << ".number(" << k << "," << l << ") is " << tabla[i][j].number(k,l) << "\n";
				}
			}
		}
	}
	
	strength = 1.0 - (fails * (((const SudokuEnviroment&)getEnviroment()).getGamma()));
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
					float rnnum = randNumber();
					if(rnnum < 0.5) newtabla[i][j].combine(tabla[i][j],((SudokuSingle*)single)->tabla[i][j]);
					else newtabla[i][j].combine(((SudokuSingle*)single)->tabla[i][j],tabla[i][j]);
				}
			}
			newj.combine(getJunction(),single->getJunction());
			break;		
		case ae::Junction::AlgCode::COPY:
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].copy(tabla[i][j],((SudokuSingle*)single)->tabla[i][j]);
				}
			}
			newj.copy(getJunction(),single->getJunction());
			break;
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
			//getEnviroment().mutated++;
			if(loglevel > 1) std::cout << "\tSe detecta mutacion para " << idCount << "\n";
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
							unsigned short n = intiVals[i][j].getNumber(k,l);
							newtabla[i][j].setNumber(k,l,n);
						}
					}
				}
			}
		}
	
		SudokuSingle* s = new SudokuSingle(idCount,getEnviroment(),newtabla,newj);
		if(loglevel > 1) std::cout << "\tSe crea a " << s->getID() << "\n"; 
		chils.push_back(s);
	}
}
void SudokuSingle::saveEval(std::ofstream& fn)
{	
	fn << getID();
	fn << ",";
	fn << getStrength();	
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
	return (1.0 - strength) * (1.0 / (((SudokuEnviroment&)getEnviroment()).getGamma()));
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
		out << "\n";
	}
}



ae::Single* SudokuEnviroment::getRandomSingleTop() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();
	
	float rndnum = randNumber(0.0,1.0);
	if(rndnum < 0.50)
	{
		rndnum = randNumber(0.0,maxp/100);
		std::advance(it,rndnum);
		if(it != end()) return *it;
	}
	else
	{
		rndnum = randNumber(0.0,maxp);
		std::advance(it,rndnum);
		if(it != end()) return *it;
	}
	
	return NULL;
}
ae::Single* SudokuEnviroment::getRandomSingle() const
{
	float maxp = std::distance(begin(),end());
	const_iterator it = begin();
	
	float rndnum = randNumber(0.0,maxp);
	std::advance(it,rndnum);
	if(it != end()) return *it;
	
	return NULL;
}
SudokuEnviroment::SudokuEnviroment()
{
	maxPopulation = 500;
	initPopulation = maxPopulation;
	maxProgenitor = 18;
	idCount = 1;

	loglevel = 1;
	sigma = 0.0;
	media = 0.0;
	//sigmaReduction = 2.0;
	
	//fixedPopupation = true;
	//requiereCertainty = true;
	actualIteration = 0;
	limitIteration = 1000;
	newIteration = true;
	minSolutions = 1;
	pMutationEvent = 0.9;
	pMutableGene = 1.0/51.0;
	gamma = 1.0/(81.0 * 4.0);
	epsilon = gamma;
	
}
unsigned short SudokuEnviroment::getFaltantes() const
{
	return (1.0 - media) * (1.0/gamma);
}
double SudokuEnviroment::getGamma() const
{
	return gamma;
}
void SudokuEnviroment::run()
{
	SudokuChromosome sudokuInit[3][3];
	sudokuInit[0][0].setNumber(0,1,3);
	sudokuInit[0][0].setNumber(0,2,1);
	sudokuInit[0][1].setNumber(0,0,9);
	sudokuInit[0][2].setNumber(0,0,7);
	sudokuInit[0][2].setNumber(0,2,4);
	sudokuInit[0][0].setNumber(1,0,7);
	sudokuInit[0][0].setNumber(1,2,8);
	sudokuInit[0][2].setNumber(1,0,6);
	sudokuInit[0][2].setNumber(1,2,9);
	sudokuInit[0][2].setNumber(2,1,2);
	sudokuInit[0][1].setNumber(2,1,1);
	sudokuInit[1][0].setNumber(0,0,8);
	sudokuInit[1][1].setNumber(0,1,6);
	sudokuInit[1][2].setNumber(0,2,7);
	sudokuInit[1][1].setNumber(1,2,2);
	sudokuInit[1][2].setNumber(1,1,3);
	sudokuInit[1][0].setNumber(2,0,3);
	sudokuInit[1][1].setNumber(2,1,4);
	sudokuInit[1][2].setNumber(2,2,2);
	sudokuInit[2][1].setNumber(0,1,5);
	sudokuInit[2][0].setNumber(1,0,2);
	sudokuInit[2][0].setNumber(1,2,9);
	sudokuInit[2][2].setNumber(0,1,8);
	sudokuInit[2][2].setNumber(1,0,3);
	sudokuInit[2][2].setNumber(1,2,1);
	sudokuInit[2][0].setNumber(2,1,8);
	sudokuInit[2][0].setNumber(2,2,6);
	sudokuInit[2][1].setNumber(2,0,7);
	sudokuInit[2][2].setNumber(2,0,2);
	sudokuInit[2][2].setNumber(2,2,5);

	
	//poblacion inicial
	//std::list<ae::Single*> population;
	
	const SudokuChromosome (*p)[3] = sudokuInit;	
	for(Population i = 0; i < initPopulation; i++,idCount++)
	{
		SudokuSingle* s = new SudokuSingle(idCount,*this,sudokuInit);
		s->randFill();
		push_back(s);		
	}
	
	
	//((SudokuSingle*)*begin())->print(std::cout);

	unsigned long session = getSession();
	std::string logDir = "log-" + std::to_string(session);
	coreutils::Shell shell;
	shell.mkdir(logDir);

	std::string strhistory = logDir + "/Sudoku-history.csv";
	std::ofstream history (strhistory);
	do
	{
		actualIteration++;
		std::cout << ">>> Iteracion : " << actualIteration << "\n";
		media = 0.0;
		sigma = 0.0;
		if(loglevel > 0) 
		{
			std::cout << "\tTamano de la poblacion : " << size() << "\n";			
			//std::cout << "\tgamman : " << gamma << "\n";
		}
				
		Population countSols = 0;
		std::string cmdSol;
		for(ae::Single* s : *this)
		{
			s->eval();	
			s->deltaAge ();
		}
		//ae::ID countSolution = 0;
		sort(cmpStrength);
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getStrength();			
		}
		media /= size();
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			sigma += pow(s->getStrength() - media,2);
		}
		sigma /= size();

		std::string strfn = logDir +  "/Sudoku-" + std::to_string(actualIteration) + ".csv";
		std::ofstream fn(strfn);
		if(not fn.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : *this)
		{
			s->saveEval(fn);
		}
		fn.flush();
		fn.close();
		
		if(loglevel > 0) 
		{
			std::cout << "\tmedia : " << media << "\n";
			std::cout << "\tDesviacion estandar : " << sigma << "\n";
			std::cout << "\tVariables faltantes : " << getFaltantes() << "\n";
		}

		for(ae::Single* s : *this)
		{
			if(1.0 - s->getStrength () < Enviroment::epsilon)
			{
				countSols++;
				if(countSols >= minSolutions)
				{
					((SudokuSingle*)s)->print(std::cout);
					std::cout << "\n\tSe completo el conjunto de solucion mini, desea cotinua?\n";
					std::cin >> cmdSol;
					if(cmdSol.compare("S") == 0 or cmdSol.compare("s") == 0)
					{
						continue;
					}
					else if(cmdSol.compare("N") == 0 or cmdSol.compare("n") == 0)
					{
						return;
					}	
					else if(std::stoi(cmdSol) > 0)
					{
						int add = std::stoi(cmdSol);
						minSolutions += add;
					}
				}
			}
		}
		
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
		
		ae::ID countBefore = size();
		
		selection();
		
		std::string strfn5 = logDir +  "/Sudoku-" + std::to_string(actualIteration) + "-selection.csv";
		std::ofstream fn5(strfn5);
		if(not fn5.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : *this)
		{
			s->saveEval(fn5);
		}
		fn5.flush();
		fn5.close();
		
		if(loglevel > 0) 
		{
			std::cout << "\tProgenitores selecionados, total : " << size() << "\n";
			std::cout << "\tEliminados : " << countBefore - size() << "\n";	
		}
				
		
		std::list<ae::Single*> newschils;
		do
		{
			ae::Single* single1 = getRandomSingle();
			//std::cout << "Step 2\n";
			if(single1 == NULL) continue;
			//std::cout << "Step 3\n";
			ae::Single* single2 = getRandomSingle();
			//std::cout << "Step 4\n";
			if(single2 == NULL) continue;
			//std::cout << "Step 5\n";
			if(single1 == single2) continue;
			//std::cout << "Step 6\n";
			single1->juncting(idCount,newschils,single2,loglevel);
			if(loglevel > 1) std::cout << "\tSe ha unido " << single1->getID() << " con " << single2->getID() << "\n";
		}
		while(newschils.size() + size() <= maxPopulation);
		
		std::string strfn2 = logDir + "/Sudoku-" + std::to_string(actualIteration) + "-childs.csv";
		std::ofstream fn2(strfn2);
		if(not fn2.is_open()) throw "No se logro abrier el archivo";				
		for(ae::Single* s : newschils)//agregar los nuevos hijos a la poblacion
		{
			push_front(s);
			s->saveEval(fn2);
		}
		fn2.flush();
		fn2.close();
		if(loglevel > 0) 
		{
			std::cout << "\tNuevos Hijos : " << newschils.size() << "\n";
		}
		
		if(actualIteration < limitIteration)
		{
			newIteration = true;
		}
		else
		{
			std::cout << "Sesion :  " << session << "\n";
			std::cout << "Se ha alcanzado la iteracion " << limitIteration << ", desea continuar?\n";
			std::string cmd;
			std::cin >> cmd;
			if(cmd.compare("y") == 0 or cmd.compare("Y") == 0)
			{
				newIteration = true;
			}
			else if(cmd.compare("n") == 0 or cmd.compare("N") == 0)
			{
				newIteration = false;
			}	
			else if(std::stoi(cmd) > 0)
			{
				int add = std::stoi(cmd);
				limitIteration += add;
			}
		}
	}
	while(newIteration);

	history .close();
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
		i = erase(i);
	}
}
bool SudokuEnviroment::compress(const std::string& tarf,const std::string& dir)
{
	//zipFile zf = zipOpen64(tarf.c_str(),0);
	//zipOpenNewFileInZip(zf,dir.c_str(),&zi,NULL,0,NULL,0,NULL,0,-1);
	

    return true;
}

}