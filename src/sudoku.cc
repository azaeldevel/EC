
#include <list>
#include <math.h>
#include <octetos/core/Error.hh>
#include <fstream>

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
			numbers[i][j] = ae::Chromosome::combineDigits(((const SudokuChromosome&)P1).numbers[i][j],((const SudokuChromosome&)P2).numbers[i][j]);
		}
	}
}
void SudokuChromosome::copycombine(const ae::Chromosome& P1,const ae::Chromosome& P2)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			float numrd1 = randNumber(0.0,1.0);
			if(numrd1 < 0.5)
			{
				float numrd2 = randNumber(0.0,1.0);
				if(numrd2 < 0.5)
				{
					numbers[i][j] = ((const SudokuChromosome&)P1).numbers[i][j];
				}
				else
				{
					numbers[i][j] = ae::Chromosome::combineDigits(((const SudokuChromosome&)P1).numbers[i][j],((const SudokuChromosome&)P2).numbers[i][j]);
				}				
			}
			else
			{
				float numrd2 = randNumber(0.0,1.0);
				if(numrd2 < 0.5)
				{
					numbers[i][j] = ((const SudokuChromosome&)P2).numbers[i][j];
				}
				else
				{
					numbers[i][j] = ae::Chromosome::combineDigits(((const SudokuChromosome&)P1).numbers[i][j],((const SudokuChromosome&)P2).numbers[i][j]);
				}
			}
		}
	}
}
void SudokuChromosome::copy(const ae::Chromosome& P1,const ae::Chromosome& P2)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			float numrd1 = randNumber(0.0,1.0);
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



SudokuSingle::SudokuSingle(unsigned int id,const SudokuChromosome t[3][3] ) : Single(id)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
}
SudokuSingle::SudokuSingle(unsigned int id,const SudokuChromosome t[3][3],const Junction& junction) : Single(id,junction)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j] = t[i][j];
		}
	}
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
	
	strength = fails / (81.0 * 3.0 );
	strength = 1.0 - strength;
}
	
	

const SudokuChromosome& SudokuSingle::getTalba(unsigned short i,unsigned short j)const
{
	return tabla[i][j];
}
int SudokuSingle::main(int argc, const char* argv[])
{
	ae::ID maxPopulation = 100;
	ae::ID initP = maxPopulation;
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
	
	ae::ID idCount = 1;

	bool genlog = true;
	float sigma = 0.0;
	float media = 0.0;

	unsigned short elect = 0;// los que se elegiran desde el pricipio de la lista

	bool fixedPopupation = true;
	bool requiereCertainty = true;
	unsigned short actualIteration = 0;

	bool newIteration = true;
	
	//poblacion inicial
	std::list<ae::Single*> population;
	for(unsigned short i = 0; i < initP; i++,idCount++)
	{
		SudokuSingle* s = new SudokuSingle(idCount,tabla);
		s->randFill();
		population.push_back(s);
	}

	do
	{
	actualIteration++;
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
	std::cout << "\tmedia : " << media << "\n";
	for(ae::Single* s : population)
	{
		//std::cout << "\t" << s->getID() << " Fortaleza : " << s->getStrength() << "\n";
		sigma += pow(s->getStrength() - media,2);
	}
	sigma /= population.size();
	std::cout << "\tdesviacion estandar : " << sigma << "\n";

	//la poblacion progenitora se eleige de acuaerdo al valor de la desviacion estandar
	elect = population.size() / 10;
	/*if(sigma < 0.00001)
	{
		elect = population.size() / 7;
	}
	else if(sigma < 0.001)
	{
		elect = (2 * population.size()) / 3;
	}	
	else if(sigma < 0.01)
	{
		elect = (3 * population.size()) / 4;
	}	
	else if(sigma < 0.1)
	{
		elect = (2 * population.size()) / 5;
	}		
	else
	{
		elect = (1 * population.size()) / 6;
	}*/
	std::cout << "\tPoblacion progenitora : " << elect << "\n";

	unsigned short countElect = 1;
	std::list<ae::Single*>::iterator toDelete = population.end();
	for(std::list<ae::Single*>::iterator it = population.begin(); it != population.end(); it++,countElect++)
	{
		if(toDelete != population.end()) 
		{
			population.remove(*toDelete);
			toDelete = population.end();
		}
		if(countElect >= elect) 
		{
			toDelete = it;
		}
	}
	std::cout << "\tTamano de la poblacion : " << population.size() << "\n";

	for(ae::Single* s : population)
	{
		s->saveEval("Sudoku",population,actualIteration);
	}
	if(requiereCertainty)
	{
		if(1.0 - media < 0.00001 and sigma < 0.00001)
		{
			//termina el programa
			newIteration = false;
		}
		else
		{
			newIteration = true;
		}
	}
		
	for(std::list<ae::Single*>::iterator single1 =  population.begin(); single1 != population.end();single1++)
	{
		if(fixedPopupation)
		{
			if(population.size() >= maxPopulation) break;
		}
		for(std::list<ae::Single*>::iterator single2 = std::next(single1); single2 != population.end();single2++)
		{
			if(fixedPopupation)
			{
				if(population.size() >= maxPopulation) break;
			}
			std::list<ae::Single*> chils;
			(*single1)->juncting(idCount,chils,*single2);
			for(ae::Single* s : chils)//agregar los nuevos hijos a la poblacion
			{
				population.push_back(s);			
			}
		}
	}
	}
	while(newIteration);
	
	return EXIT_SUCCESS;
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
void SudokuSingle::juncting(ID& idCount,std::list<ae::Single*>& chils,ae::Single* single)
{
	std::cout << "\t" << idCount << " puede tener " << getJunction().get_number() << " hijos\n";
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
		case ae::Junction::AlgCode::COPYCOMBINE:
			for(unsigned short i = 0; i < 3; i++)
			{
				for(unsigned short j = 0; j < 3; j++)
				{
					newtabla[i][j].copycombine(tabla[i][j],((SudokuSingle*)single)->tabla[i][j]);
				}
			}
			newj.copycombine(getJunction(),single->getJunction());
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
			std::cout << "\tSe detecta mutacion para " << idCount << "\n";
		}
		SudokuSingle* s = new SudokuSingle(idCount,newtabla,newj);
		std::cout << "\tSe crea a " << s->getID() << "\n"; 
		chils.push_back(s);
	}
}
void SudokuSingle::saveEval(const std::string& prefixfn, const std::list<ae::Single*>& result, unsigned short iteration)
{
	std::string strfn = prefixfn + "-" + std::to_string(iteration) + ".csv";
	std::ofstream fn(strfn);
	if(not fn.is_open()) throw "No se logro abrier el archivo";
	
	for(const ae::Single* p : result)
	{
		fn << p->getID();
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

	fn.flush();
	fn.close();
}

}