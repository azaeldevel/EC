
#include <list>
#include <math.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#if defined(__linux__)
	#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include <io.h>
#else
#error "Plataforma desconocida"
#endif
#include <string.h>
#include <stdio.h>

#include "sudoku.hh"


namespace oct::ec::sudoku
{




Chromosome::Chromosome(const Chromosome& obj) : oct::ec::Chromosome("sudoku::Chromosome")
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
	//std::random_device rd;
	//std::mt19937 gen(rd());
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			std::bernoulli_distribution distrib(0.5);
			if(distrib(gen))
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
/*void Chromosome::mutate(double p)
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			double numrd = randNumber();
			if(numrd <= p) numbers[i][j] = randNumber(1.0,9.1);
		}
	}
}*/
void Chromosome::randFill()
{
	//std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1,9);
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			if(numbers[i][j] == 0) numbers[i][j] = distrib(gen);
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





Single::Single(const Single& obj) : oct::ec::Single(obj)
{

}
Single::Single(Enviroment& e,Chromosome init[][3]) : oct::ec::Single(e)
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
	//genMD5();
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
Single::Single(Enviroment& e,Chromosome** newData,Chromosome init[][3],unsigned int c) : ec::Single(e,c)
{
	tabla = newData;
	intiVals = init;
	//genMD5();
}

/*
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
*/
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

void Single::randFill()
{
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			tabla[i][j].randFill();
			tabla[i][j].resetCollision();
		}
	}
}
void Single::juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single)
{
	//std::cout << "\t" << idCount << " puede tener " << getJunction().get_number() << " hijos\n";
	ID idCount;
	for(ec::geneUS i = 0; i < getChilds(); i++)
	{
		idCount = getEnviroment().nextID();

		Chromosome** newtabla = new Chromosome*[3];
		for(unsigned short i = 0; i < 3; i++)
		{
			newtabla[i] = new Chromosome[3];
		}
		
		for(unsigned short i = 0; i < 3; i++)
		{
			for(unsigned short j = 0; j < 3; j++)
			{
				newtabla[i][j].combine(tabla[i][j],((Single*)single)->tabla[i][j]);
			}
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

		Single* s = new Single((Enviroment&)*env,newtabla,intiVals,getChilds());
		chils.push_back(s);
		if(env->getEchoLevel() > 2 and getEnviroment().getFout() != NULL) 
		{
			std::string log = "\tSe crea a ";
			log += std::to_string(s->getID()) + "\n";
			getEnviroment().getFout()(log.c_str());
		}
	}
}
void Single::save(Save& s)
{
	(*s.out) << getID();
	(*s.out) << ",";
	(*s.out) << getFitness();
	(*s.out) << ",";
	(*s.out) << getErros();
	//fn << ",";
	//fn << getMD5();
	(*s.out) << ",";
	(*s.out) << getAge();
	for(unsigned short i = 0; i < 3; i++)
	{
		for(unsigned short j = 0; j < 3; j++)
		{
			for(unsigned short k = 0; k < 3; k++)
			{
				for(unsigned short l = 0; l < 3; l++)
				{
					(*s.out) << ",";
					(*s.out) << tabla[i][k].getNumber(j,l);
				}
			}
		}
	}
}
/*
const oct::core::StringMD5& Single::getMD5()const
{
	return md5;
}
*/
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
void Single::mutate()
{
	//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distribIndex(0, 2);
    std::uniform_int_distribution<int> distribNumber(1, 9);
    unsigned short i,j,k,l,N;
    //std::cout << distribIndex(gen) << "," << distribIndex(gen) << "," << distribIndex(gen) << "," << distribIndex(gen) << "\n";
    i = distribIndex(gen);
    j = distribIndex(gen);
    k = distribIndex(gen);
    l = distribIndex(gen);
    N = distribNumber(gen);
    //std::cout << i << "," << j << "," << k << "," << l << "," << N << "\n";
    tabla[i][j].setNumber(k,l,N);
}












Enviroment::Enviroment()
{
}
/*Enviroment::Enviroment(const std::string& initB)
{
	init(initB);
}
Enviroment::Enviroment(const std::string& initB,Iteration maxite)
{
	init(initB);
	stopperMaxIterations(maxite);
}*/
Enviroment::Enviroment(const std::string& initB,Iteration maxite,const std::string& logDir)  : ec::Enviroment (logDir,maxite)
{
	init();
	stopperMaxIterations(maxite);
	//logDirectory = logDir + "/" + std::to_string(ec::sudoku::Enviroment::getDayID());
	//shell.mkdir(logDirectory);
	//logFile = not logDirectory.empty();
	//addTerminator(Terminations::MAXITERATION);
	//addTerminator(Terminations::MINSOLUTIONS);
}
Enviroment::Enviroment(const std::string& initB,Iteration maxite,const std::string& logDir,Iteration maxS) : ec::Enviroment (logDir,maxite,maxS)
{
	init();
	stopperMaxIterations(maxite);
	//logFile = not logDirectory.empty();
	stopperMaxSerie(maxS);
}
Enviroment::Enviroment(int argc, const char* argv[]) : ec::Enviroment(argc,argv)
{
	//std::cout << "Step 1.0\n";
	init();
	//std::cout << "Step 3.0\n";
	for(int i = 1; i < argc; i++)
	{
		if(strcmp("--board",argv[i]) == 0)
		{
			//std::cout << "--board = " << argv[++i] << "\n";
			fnBoard = argv[++i];
		}
	}
	//std::cout << "Step 3.0\n";
}
Enviroment::~Enviroment()
{
}
void Enviroment::init()
{
	maxPopulation = 9 * 6 * 81;//81*a
	initPopulation = 9 * 6 * 81;
	maxProgenitor = 9 * 3 * 81;//9*a
	idCount = 1;

	echolevel = 0;
	sigma = 0.0;
	media = 0.0;

	//actualIteration = 1;
	//maxIteration = 1000;
	newIteration = true;
	stopperMinSolutions(1);
	//pMutationEvent = 0.002;
	//if(pMutableGene < 0.0) pMutableGene = 0.80;
	gamma = 1.0/(81.0 * 4.0);
	epsilon = gamma;
	//fnBoard = initB;
	//iterJam = 1500;
	//addTerminator(ae::Terminations::JAM);
	//sliceJam = iterJam /10;
	comparer = &cmpStrength;
	maxMutation = 5;
}
void Enviroment::initBoard(const std::string& initTable)
{
	//std::cout << "Enviroment::initBoard : Step 1\n";		
	std::ifstream file(initTable);
	if(not file.is_open()) 
	{
		std::string msg = "No se logro abrir el archivo '";
		msg += initTable + "'";
		throw oct::core::Exception(msg,__FILE__,__LINE__);
	}
	std::string strline;
	std::vector<unsigned short> inits;
	//std::cout << "Enviroment::initBoard : Step 2\n";
	while (std::getline(file, strline))
	{
		//std::cout << strline << "\n";
	  	char *tok = strtok((char*)strline.c_str()," ");
		while (tok!=NULL)
		{
		    //printf("%s\n",tok);
			inits.push_back(std::stoi(tok));
		    tok=strtok(NULL," ");
		}
	}
	//std::cout << "Enviroment::initBoard : Step 3\n";
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
	//std::cout << "Enviroment::initBoard : Step 4\n";
}
unsigned short Enviroment::getFaltantes() const
{
	return (1.0 - media) * (1.0/gamma);
}
double Enviroment::getGamma() const
{
	return gamma;
}





void Enviroment::initial()
{
	//std::cout << "Enviroment::initial : Step 1\n";
	//std::cout << "fnBoard = " << fnBoard << "\n";
	initBoard(fnBoard);
	//std::cout << "Enviroment::initial : Step 2\n";
	//poblacion inicial
	//std::cout << "sudokuInit = " << sudokuInit << "\n";
	for(Population i = 0; i < initPopulation; i++,idCount++)
	{
		Single* s = new Single(*this,sudokuInit);
		s->randFill();
		push_back(s);
	}
	//std::cout << "Enviroment::initial : Step 3\n";
}



}
