
#include <list>
#include <math.h>
#include <octetos/core/Error.hh>
#include <fstream>
#include <iterator>


#include "GA-ext.hh"


namespace ae::ga
{





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
SudokuSingle::SudokuSingle(unsigned int id,SudokuChromosome t[3][3] ) : Single(id)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
	//intiVals = (SudokuChromosome**)t;
	genMD5();
}
SudokuSingle::SudokuSingle(unsigned int id,SudokuChromosome t[3][3],const Junction& junction) : Single(id,junction)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
	//intiVals = (SudokuChromosome**)&t[0][0];
	genMD5();
}

void SudokuSingle::eval()
{
	float fails = 0.0;
		
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
	
	strength = fails / (81.0 * 4.0);
	strength = 1.0 - strength;
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
					newtabla[i][j].mutate(getProbabilityMutationEvent());
				}
			}
			newj.mutate(getProbabilityMutationEvent());
			if(loglevel > 1) std::cout << "\tSe detecta mutacion para " << idCount << "\n";
		}
		//
		/*for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				for(unsigned short k = 0; k < 3; k++)
				{
					for(unsigned short l = 0; l < 3; l++)
					{				
						if(intiVals[i][j].number(k,l) != 0)
						{
							newtabla[i][j].number(k,l) = intiVals[i][j].number(k,l);
						}						
					}
				}
			}
		}*/
	
		SudokuSingle* s = new SudokuSingle(idCount,newtabla,newj);
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


ae::Single* getrandomElement(std::list<ae::Single*>& ls)
{
	float maxp = std::distance(ls.begin(),ls.end());
	std::list<ae::Single*>::iterator it = ls.begin();
	
	float rndnum = randNumber(0.0,1.0);
	if(rndnum < 0.50)
	{
		rndnum = randNumber(0.0,maxp/100);
		std::advance(it,rndnum);
		if(it != ls.end()) return *it;
	}
	else
	{
		rndnum = randNumber(0.0,maxp);
		std::advance(it,rndnum);
		if(it != ls.end()) return *it;
	}
	
	return NULL;
}

SudokuEnviroment::SudokuEnviroment()
{
	maxPopulation = 1000;
	initPopulation = maxPopulation;
	maxProgenitor = maxPopulation / 10;
	idCount = 1;

	loglevel = 1;
	sigma = 0.0;
	media = 0.0;
	sigmaReduccion = 2.0;
	
	fixedPopupation = true;
	requiereCertainty = true;
	actualIteration = 0;
	limitIteration = 100;
	newIteration = true;
	epsilon = 1/(81.0*4.0*2);
	minSolutions = 1;
}
void SudokuEnviroment::run()
{
	SudokuChromosome tabla[3][3];
	tabla[0][0].number(0,1) = 3;
	tabla[0][0].number(0,2) = 1;
	tabla[0][1].number(0,0) = 9;
	tabla[0][2].number(0,0) = 7;
	tabla[0][2].number(0,2) = 4;
	tabla[0][0].number(1,0) = 7;
	tabla[0][0].number(1,2) = 8;
	tabla[0][2].number(1,0) = 6;
	tabla[0][2].number(1,2) = 9;
	tabla[0][2].number(2,1) = 2;
	tabla[0][1].number(2,1) = 1;
	tabla[1][0].number(0,0) = 8;
	tabla[1][1].number(0,1) = 6;
	tabla[1][2].number(0,2) = 7;
	tabla[1][1].number(1,2) = 2;
	tabla[1][2].number(1,1) = 3;
	tabla[1][0].number(2,0) = 3;
	tabla[1][1].number(2,1) = 4;
	tabla[1][2].number(2,2) = 2;
	tabla[2][1].number(0,1) = 5;
	tabla[2][0].number(1,0) = 2;
	tabla[2][0].number(1,2) = 9;
	tabla[2][2].number(0,1) = 8;
	tabla[2][2].number(1,0) = 3;
	tabla[2][2].number(1,2) = 1;
	tabla[2][0].number(2,1) = 8;
	tabla[2][0].number(2,2) = 6;
	tabla[2][1].number(2,0) = 7;
	tabla[2][2].number(2,0) = 2;
	tabla[2][2].number(2,2) = 5;
	
		
	//poblacion inicial
	std::list<ae::Single*> population;
	for(unsigned short i = 0; i < initPopulation; i++,idCount++)
	{
		SudokuSingle* s = new SudokuSingle(idCount,tabla);
		s->randFill();
		population.push_back(s);
	}

	std::string strfn4 = "log/Sudoku-" + std::to_string(actualIteration) + "-history.csv";
	std::ofstream fn4(strfn4);
	do
	{
		actualIteration++;
		media = 0.0;
		sigma = 0.0;
		std::cout << ">>> Iteracion : " << actualIteration << "\n";
		if(loglevel > 0) std::cout << "\tTamano de la poblacion : " << population.size() << "\n";

		
		//(*population.begin())->eval();
		//std::cout << "\t" << (*population.begin())->getID() << " Fortaleza : " << (*population.begin())->getStrength() << "\n";
		for(ae::Single* s : population)
		{
			s->eval();	
		}
		ae::ID countSolution = 0;
		population.sort(cmpStrength);
		for(ae::Single* s : population)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getStrength();
			if(1.0 - s->getStrength() < SudokuEnviroment::epsilon)
			{
				countSolution++;
				std::string strfn3 = "log/Sudoku-" + std::to_string(actualIteration) + "-solutions.csv";
				std::ofstream fn3(strfn3);
				if(not fn3.is_open()) throw "No se logro abrier el archivo";
				for(ae::Single* s : population)
				{
					s->saveEval(fn3);
				}
				fn3.flush();
				fn3.close();
				if(countSolution > countSolution)
				{
					std::cout << "\tSe alcanzo el conjuto minimo de soluciones\n";
					return;
				}
			}
		}
		media /= population.size();
		if(loglevel > 0) std::cout << "\tmedia : " << media << "\n";
		for(ae::Single* s : population)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			sigma += pow(s->getStrength() - media,2);
		}
		sigma /= population.size();
		if(loglevel > 0) std::cout << "\tDesviacion estandar : " << sigma << "\n";

		if(fn4.is_open()) 
		{
			fn4 << actualIteration;
			fn4 << ",";
			fn4 << media;
			fn4 << ",";
			fn4 << sigma;			
			fn4.flush();
		}
		else
		{
			throw "No se logro abrier el archivo";
		}
		
		ae::ID countActual = population.size();
		ae::ID countDeletes = 0;
		std::list<ae::Single*>::reverse_iterator toDelete = population.rend();
		for(std::list<ae::Single*>::reverse_iterator it = population.rbegin(); it != population.rend(); it++)
		{
			if(countDeletes < countActual/2)
			{
				toDelete = it;
				countDeletes++;
			}
			if(toDelete != population.rend()) 
			{
				population.remove(*toDelete);
				toDelete = population.rend();
			}
		}
		if(toDelete != population.rend()) 
		{
			population.remove(*toDelete);
			toDelete = population.rend();
		}
		unsigned short countEliminened = countActual - population.size();
		if(loglevel > 0) 
		{
			std::cout << "\tProgenitores selecionados, total : " << population.size() << "\n";
			std::cout << "\tEliminados : " << countEliminened << "\n";			
		}

		
		std::string strfn = "log/Sudoku-" + std::to_string(actualIteration) + ".csv";
		std::ofstream fn(strfn);
		if(not fn.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : population)
		{
			s->saveEval(fn);
		}
		fn.flush();
		fn.close();
				
		//if(loglevel > 0) std::cout << "\tGenerando decendencia..\n";
		std::list<ae::Single*> newschils;
		do
		{
			//std::cout << "Step 1\n";
			ae::Single* single1 = getrandomElement(population);
			//std::cout << "Step 2\n";
			if(single1 == NULL) continue;
			//std::cout << "Step 3\n";
			ae::Single* single2 = getrandomElement(population);
			//std::cout << "Step 4\n";
			if(single2 == NULL) continue;
			//std::cout << "Step 5\n";
			if(single1 == single2) continue;
			//std::cout << "Step 6\n";
			single1->juncting(idCount,newschils,single2,loglevel);
			if(loglevel > 1) std::cout << "\tSe ha unido " << single1->getID() << " con " << single2->getID() << "\n";
		}
		while(newschils.size() + population.size() <= maxPopulation);
		
		std::string strfn2 = "log/Sudoku-" + std::to_string(actualIteration) + "-childs.csv";
		std::ofstream fn2(strfn2);
		if(not fn2.is_open()) throw "No se logro abrier el archivo";
		for(ae::Single* s : population)
		{
			s->saveEval(fn2);
		}
		fn2.flush();
		fn2.close();
		for(ae::Single* s : newschils)//agregar los nuevos hijos a la poblacion
		{
			float rdnum = randNumber(0.0,1.0);
			if(rdnum < 0.5) population.push_front(s);
			else population.push_back(s);						
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