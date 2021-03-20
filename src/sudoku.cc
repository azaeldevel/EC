
#include <list>
#include <math.h>
#include <octetos/core/Error.hh>
#include <fstream>
#include <iterator>


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
geneUS& SudokuChromosome::number(unsigned short i,unsigned short j)
{
	return numbers[i][j];
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
			if(numrd1 < 0.5)
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
			if(numrd < p) numbers[i][j] = ae::Chromosome::mutateDigits(numbers[i][j]);
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
				numbers[i][j] = randNumber(1.0,9.9);
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
					 strmd5 += std::to_string(tabla[i][j].number(k,l));
				}
			}
		}
	}
	md5.set(strmd5);
}
SudokuSingle::SudokuSingle(unsigned int id,const Enviroment& e,const SudokuChromosome (*t)[3]) : Single(id,e)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			//std::cout << "&t[" << i << "][" << j << "]" << &t[i][j] << "\n";
			//std::cout << "t[" << i << "][" << j << "]" << "\n";
			tabla[i][j] = t[i][j];
		}
	}
	intiVals = t;
	genMD5();
}
SudokuSingle::SudokuSingle(unsigned int id,const Enviroment& e,const SudokuChromosome (*t)[3],const Junction& junction) : Single(id,e,junction)
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
					if(tabla[i][j].number(k,l) > 9)
					{
						fails++;
						//std::cout << "tabla[" << i << "]" << "[" << j << "]" << ".number(" << k << "," << l << ") is " << tabla[i][j].number(k,l) << " > 9\n";
					}
					else
					{
						if(tabla[i][j].number(k,l) > 0) countD[tabla[i][j].number(k,l) - 1]++;//cuentas la cantidad de digitos repetidos
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
					if(tabla[i][k].number(j,l) > 9)
					{
						fails++;
						//std::cout << "tabla[" << i << "]" << "[" << k << "]" << ".number(" << j << "," << l << ") is " << tabla[i][k].number(j,l) << " > 9\n";
					}
					else
					{
						if(tabla[i][k].number(j,l) > 0) countD[tabla[i][k].number(j,l) - 1]++;//cuentas la cantidad de digitos repetidos
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
					if(tabla[k][i].number(l,j) > 9)
					{
						fails++;
						//std::cout << "tabla[" << k << "]" << "[" << i << "]" << ".number(" << l << "," << j << ") is " << tabla[k][i].number(l,j) << " > 9\n";
					}
					else
					{
						if(tabla[k][i].number(l,j) > 0)  countD[tabla[k][i].number(l,j) - 1]++;//cuentas la cantidad de digitos repetidos
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
					if(tabla[i][j].number(k,l) == 0)
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
					newtabla[i][j].combine(tabla[i][j],((SudokuSingle*)single)->tabla[i][j]);
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
			
		if(mutate())
		{
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].mutate(getEnviroment().getProbabilityMutableGene());
				}
			}
			newj.mutate(getEnviroment().getProbabilityMutableGene());
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
						if(intiVals[i][j].getNumber(k,l) != 0) newtabla[i][j].number(k,l) = intiVals[i][j].getNumber(k,l);						
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
	fn << getMD5();
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{
					fn << ",";
					fn << tabla[i][k].number(j,l);
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
	maxPopulation = 4000;
	initPopulation = maxPopulation;
	maxEliminination = maxPopulation / 20;
	idCount = 1;

	loglevel = 1;
	sigma = 0.0;
	media = 0.0;
	//sigmaReduction = 2.0;
	
	//fixedPopupation = true;
	//requiereCertainty = true;
	actualIteration = 0;
	limitIteration = 3000;
	newIteration = true;
	minSolutions = 1;
	pMutationEvent = 0.02;
	pMutableGene = pMutationEvent/81.0;
	gamma = 1.0/(81.0 * 4.0);
	epsilon = gamma;
	
}
unsigned short SudokuEnviroment::getFaltantes() const
{
	return (1.0 - media) * 4.0 * 81.0;
}
double SudokuEnviroment::getGamma() const
{
	return gamma;
}
void SudokuEnviroment::run()
{
	SudokuChromosome sudokuInit[3][3];
	sudokuInit[0][0].number(0,1) = 3;
	sudokuInit[0][0].number(0,2) = 1;
	sudokuInit[0][1].number(0,0) = 9;
	sudokuInit[0][2].number(0,0) = 7;
	sudokuInit[0][2].number(0,2) = 4;
	sudokuInit[0][0].number(1,0) = 7;
	sudokuInit[0][0].number(1,2) = 8;
	sudokuInit[0][2].number(1,0) = 6;
	sudokuInit[0][2].number(1,2) = 9;
	sudokuInit[0][2].number(2,1) = 2;
	sudokuInit[0][1].number(2,1) = 1;
	sudokuInit[1][0].number(0,0) = 8;
	sudokuInit[1][1].number(0,1) = 6;
	sudokuInit[1][2].number(0,2) = 7;
	sudokuInit[1][1].number(1,2) = 2;
	sudokuInit[1][2].number(1,1) = 3;
	sudokuInit[1][0].number(2,0) = 3;
	sudokuInit[1][1].number(2,1) = 4;
	sudokuInit[1][2].number(2,2) = 2;
	sudokuInit[2][1].number(0,1) = 5;
	sudokuInit[2][0].number(1,0) = 2;
	sudokuInit[2][0].number(1,2) = 9;
	sudokuInit[2][2].number(0,1) = 8;
	sudokuInit[2][2].number(1,0) = 3;
	sudokuInit[2][2].number(1,2) = 1;
	sudokuInit[2][0].number(2,1) = 8;
	sudokuInit[2][0].number(2,2) = 6;
	sudokuInit[2][1].number(2,0) = 7;
	sudokuInit[2][2].number(2,0) = 2;
	sudokuInit[2][2].number(2,2) = 5;

	
	//poblacion inicial
	//std::list<ae::Single*> population;
	
	const SudokuChromosome (*p)[3] = sudokuInit;	
	for(unsigned short i = 0; i < initPopulation; i++,idCount++)
	{
		SudokuSingle* s = new SudokuSingle(idCount,*this,sudokuInit);
		s->randFill();
		push_back(s);
	}

	std::string strfn4 = "log/Sudoku-" + std::to_string(actualIteration) + "-history.csv";
	std::ofstream fn4(strfn4);
	do
	{
		actualIteration++;
		media = 0.0;
		sigma = 0.0;
		std::cout << ">>> Iteracion : " << actualIteration << "\n";
		std::cout << "\tgamman : " << gamma << "\n";
		if(loglevel > 0) std::cout << "\tTamano de la poblacion : " << size() << "\n";

		
		//(*population.begin())->eval();
		//std::cout << "\t" << (*population.begin())->getID() << " Fortaleza : " << (*population.begin())->getStrength() << "\n";
		for(ae::Single* s : *this)
		{
			s->eval();	
		}
		ae::ID countSolution = 0;
		sort(cmpStrength);
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getStrength();			
		}
		for(ae::Single* s : *this)
		{
			//Verifiacion d soluciones			
			if(1.0 - s->getStrength() < SudokuEnviroment::epsilon)
			{
				countSolution++;
				std::string strfn3 = "log/Sudoku-" + std::to_string(actualIteration) + "-solutions.csv";
				std::ofstream fn3(strfn3);
				if(not fn3.is_open()) throw octetos::core::Exception("No se logro abrier el archivo",__FILE__,__LINE__);
				s->saveEval(fn3);
				if(countSolution > 0)
				{
					std::cout << "\tSe encontro una solucion.\n";
				}
				fn3.flush();
				fn3.close();
				if(countSolution <= minSolutions)
				{
					std::cout << "\tSe alcanzo el conjuto minimo de soluciones\n";
					return;
				}
			}
		}
		media /= size();
		if(loglevel > 0) std::cout << "\tmedia : " << media << "\n";
		if(loglevel > 0) std::cout << "\tVariables faltantes : " << getFaltantes() << "\n";
		for(ae::Single* s : *this)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			sigma += pow(s->getStrength() - media,2);
		}
		sigma /= size();
		if(loglevel > 0) std::cout << "\tDesviacion estandar : " << sigma << "\n";

		if(fn4.is_open()) 
		{
			fn4 << actualIteration;
			fn4 << ",";
			fn4 << size();
			fn4 << ",";
			fn4 << media;
			fn4 << ",";
			fn4 << getFaltantes();
			fn4 << ",";
			fn4 << sigma;			
			fn4.flush();
		}
		else
		{
			throw "No se logro abrier el archivo";
		}
		
		ae::ID countActual = size();
		ae::ID countDeletes = 0;
		reverse_iterator toDelete = rend();
		for(reverse_iterator it = rbegin(); it != rend(); it++)
		{
			if(countDeletes < maxEliminination)
			{
				if(1.0 - (*it)->getStrength() < SudokuEnviroment::epsilon)
				{//no eliminar si h alcanzado el valor maximo
					continue;
				}	
				else
				{
					toDelete = it;
					countDeletes++;
				}
			}
			if(toDelete != rend()) 
			{
				//delete *toDelete;
				remove(*toDelete);
				toDelete = rend();
			}
		}
		if(toDelete != rend()) 
		{
			remove(*toDelete);
			toDelete = rend();
		}
		unsigned short countEliminened = countActual - size();
		if(loglevel > 0) 
		{
			std::cout << "\tProgenitores selecionados, total : " << size() << "\n";
			std::cout << "\tEliminados : " << countEliminened << "\n";			
		}

		
		std::string strfn = "log/Sudoku-" + std::to_string(actualIteration) + ".csv";
		std::ofstream fn(strfn);
		if(not fn.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : *this)
		{
			s->saveEval(fn);
		}
		fn.flush();
		fn.close();
				
		//if(loglevel > 0) std::cout << "\tGenerando decendencia..\n";
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
		
		std::string strfn2 = "log/Sudoku-" + std::to_string(actualIteration) + "-childs.csv";
		std::ofstream fn2(strfn2);
		if(not fn2.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : *this)
		{
			s->saveEval(fn2);
		}
		fn2.flush();
		fn2.close();
		for(ae::Single* s : newschils)//agregar los nuevos hijos a la poblacion
		{
			float rdnum = randNumber(0.0,1.0);
			if(rdnum < 0.5) push_front(s);
			else push_back(s);						
		}
		if(loglevel > 0) std::cout << "\tNuevos Hijos : " << newschils.size() << "\n";
		
		if(actualIteration < limitIteration)
		{
			newIteration = true;
		}
		else
		{
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

	fn4.close();
}

}