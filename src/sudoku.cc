
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



SudokuSingle::SudokuSingle(unsigned int id,SudokuChromosome t[3][3] ) : Single(id)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
	intiVals = (SudokuChromosome**)t;
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
	intiVals = (SudokuChromosome**)&t[0][0];
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
	
	selection = MethodeSelection::INCREMENTING_MEDIA;

	fixedPopupation = true;
	requiereCertainty = true;
	actualIteration = 0;
	limitIteration = 100;
	newIteration = true;
	
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
		population.sort(cmpStrength);
		for(ae::Single* s : population)
		{
			//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
			media += s->getStrength();
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

		//la poblacion progenitora se eleige de acuaerdo al valor de la desviacion estandar

		//selecionar n-sigmnas por debajo de la media
		double electStrength = 0.0;
		switch(selection)
		{
		case MethodeSelection::INCREMENTING_MEDIA:
			electStrength = media;
			break;
		case MethodeSelection::LEADER_STRONG:
			electStrength = (*population.begin())->getStrength() + (sigmaReduccion * sigma);
			break;
		default:
			throw octetos::core::Exception("Metodo de seleccion desconocido.",__FILE__,__LINE__);
		}
		if(loglevel > 0) std::cout << "\tSelecion por strength : " << electStrength << "\n";
		
		unsigned short countActual = population.size();
		unsigned short countProgenitor = 0;
		std::list<ae::Single*>::iterator toDelete = population.end();
		for(std::list<ae::Single*>::iterator it = population.begin(); it != population.end(); it++)
		{
			countProgenitor++;
			if(toDelete != population.end()) 
			{
				population.remove(*toDelete);
				toDelete = population.end();
			}
			if((*it)->getStrength() < electStrength and countProgenitor <= population.size() )
			{
				toDelete = it;
			}
		}
		if(toDelete != population.end()) 
		{
			population.remove(*toDelete);
			toDelete = population.end();
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
				
		/*if(mediaStop < media)
		{
			std::string strfn = "Sudoku-" + std::to_string(actualIteration) + "-end.csv";
			std::ofstream fn(strfn);
			if(not fn.is_open()) throw "No se logro abrier el archivo";
			unsigned short countSolutions = 0;
			for(ae::Single* s : population)
			{				
				if(1.0 - s->getStrength() < 0.00001) 
				{
					s->saveEval(fn);
					countSolutions++;
				}
			}
			if(countSolutions >= minSolutions)
			{
				fn.flush();
				fn.close();
				return;
			}
		}*/
		if(loglevel > 0) std::cout << "\tGenerando decendencia..\n";
		std::list<ae::Single*> newschils;
		//std::list<ae::Single*>::iterator single2 = population.begin();
		//std::advance (single2 , population.size() / 2);//divide la pobacion en 2 para realizar los cruces
		for(
		    std::list<ae::Single*>::iterator single1 =  population.begin(); 
		    single1 != population.end();
		    single1++
		    )
		{
			if(newschils.size() + population.size() >= maxPopulation)
			{
				break;
			}
			for(
				std::list<ae::Single*>::reverse_iterator single2 = population.rbegin();
			    single2 != population.rend();
			    ++single2
			    )
			{
				if(newschils.size() + population.size() >= maxPopulation)
				{
					break;
				}
				(*single1)->juncting(idCount,newschils,*single2,loglevel);
				if(loglevel > 1) std::cout << "\tSe ha unido " << (*single1)->getID() << " con " << (*single2)->getID() << "\n"; 
			}
		}
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
}

}