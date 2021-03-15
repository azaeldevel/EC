
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <list>
#include <cmath>
#include <math.h>
#include <limits>

#include "GA-ext.hh"


namespace ae::ga
{

bool cmpfloatMax(const MaxMin_By_Value& f,const MaxMin_By_Value& s)
{
	return f.value < s.value;
}
bool cmpfloatMin(const MaxMin_By_Value& f,const MaxMin_By_Value& s)
{
	return fabs(f.value) < fabs(s.value);
}
void remove(std::vector<ae::ga::MaxMin_x2*>& p, ae::ga::MaxMin_x2* s)
{
	std::vector<ae::ga::MaxMin_x2*>::iterator it = std::find(p.begin(),p.end(),s);
	if(it != p.end()) 
	{
		std::cout << "\tSe elimina a " << (*it)->getID() << "\n"; 
		p.erase(it);
	}
}

float randFloat()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(0.0, std::numeric_limits<float>::max());
	std::uniform_real_distribution<> distrsign(0.0, 100.0);
		
	float sing = distrsign(gen);
	//std::cout << "sig " << sing << "\n";
	if(sing < 50.0) return distr(gen);
	return -1.0 * distr(gen);
}
float randFloatDigit()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(1.0, 9.0);
	float f = distr(gen);
	std::cout << "f " << f << "\n";
	return f;
}

ae::geneUC randFloatAlgt()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(ae::Junction::AlgCode::COMBINE, ae::Junction::AlgCode::COPYCOMBINE);
		
	return distr(gen);
}


MaxMin_x2::MaxMin_x2(unsigned int id,geneF x2_mx,geneF x2_min,geneUS number,geneUS algorit) 
		: ae::ga::Single(id)
		,maxmin(x2_mx,x2_min)
		,juntion(number,algorit)
{
	add(maxmin);
	add(juntion);
}

MaxMin_x2::MaxMin_x2(unsigned int id,MaxMin_R mm,Junction j) : Single(id),maxmin(mm),juntion(j)
{
	add(maxmin);
	add(juntion);
}
MaxMin_R& MaxMin_x2::getMaxMin()
{
		return maxmin;
}
	void MaxMin_x2::junction(MaxMin_x2& single,std::vector<MaxMin_x2*>& chils,unsigned short& count)
	{
		//std::cout << "\t" << getID() << "\tpuede tener " << juntion.get_number() << " hijos\n";
		
		for(ae::geneUC i = 0; i < juntion.get_number(); i++,count++)
		{
			ae::MaxMin_R newmm;
			ae::Junction newj;
			switch((short)juntion.get_algorit())
			{
			case ae::Junction::AlgCode::COMBINE:
				newmm.combine(maxmin,single.maxmin);
				newj.combine(juntion,single.juntion);
				break;		
			case ae::Junction::AlgCode::COPY:
				newmm.copy(maxmin,single.maxmin);
				newj.copy(juntion,single.juntion);
				break;
			case ae::Junction::AlgCode::COPYCOMBINE:
				newmm.copycombine(maxmin,single.maxmin);
				newj.copycombine(juntion,single.juntion);
				break;
			}
			float mutate = ae::randNumber(100.0);
			if(mutate <= 5.0)
			{
				newmm.mutate();
				newj.mutate();
				std::cout << "\tSe detecta mutacion para " << count << "\n";
			}
			MaxMin_x2* s = new MaxMin_x2(count,newmm,newj);
			std::cout << "\tSe crea a " << s->getID() << "\n"; 
			chils.push_back(s);
		}
	}
void MaxMin_x2::junction(std::vector<ae::ga::MaxMin_x2*>& p,std::map<ae::ga::MaxMin_x2*,Notas>& e,unsigned short& idCount)
{
	std::list<ae::ga::MaxMin_x2*> better1;
	std::list<ae::ga::MaxMin_x2*> better2;
	
	//std::cout << "\t Maximos \n";
	std::list<MaxMin_By_Value> lsmx;
	for(ae::ga::MaxMin_x2* single : p)
	{
		MaxMin_By_Value v;
		v.maxmin = single;
		v.value = e.find(single)->second.x2_max;
		lsmx.push_back(v);

		if(isnan(single->getMaxMin().get_x2_mx())) remove(p,single);
		if(isnan(single->getMaxMin().get_x2_mn())) remove(p,single);
		if(single->efficiency() < 1.0)
		{
			float randNumRem = ae::randNumber(1.0,100.0);
			if(randNumRem < 60.0) remove(p,single);
		}
	}
	lsmx.sort(cmpfloatMax);	
	for(MaxMin_By_Value& v : lsmx)
	{
		//eliminar los neagtivos
		if(v.value < 0.0) v.maxmin = NULL;
	}
	int count = 0;
	for(MaxMin_By_Value& v : lsmx)
	{
		if(v.maxmin) count++;
		if(count > 25) v.maxmin = NULL; //seleciona los primero 25
	}	
	count = 0;
	for(MaxMin_By_Value& v : lsmx)
	{
		if(v.maxmin) 
		{
			count++;
			//std::cout << "\t"<< count << " - " << v.value << "\n";
			better2.push_back(v.maxmin);
		}
	}

	std::list<MaxMin_By_Value> lsmn;
	for(ae::ga::MaxMin_x2* single : p)
	{
		MaxMin_By_Value v;
		v.maxmin = single;
		v.value = e.find(single)->second.x2_min;
		lsmn.push_back(v);
	}
	lsmn.sort(cmpfloatMin);	
	count = 0;
	for(MaxMin_By_Value& v : lsmn)
	{
		if(v.maxmin) count++;
		if(count > 25) v.maxmin = NULL; //seleciona los primero 25
	}	
	count = 0;
	for(MaxMin_By_Value& v : lsmn)
	{
		if(v.maxmin) 
		{
			count++;
			//std::cout << "\t"<< count << " - " << v.value << "\n";
			auto it = std::find(better2.begin(),better2.end(),v.maxmin);
			if(it != better2.end()) better1.push_back(v.maxmin);
		}
	}
	
	
	for(ae::ga::MaxMin_x2* single : better1)
	{
		single->deltaStrength ();
		single->deltaStrength ();
	}
	for(ae::ga::MaxMin_x2* single : better2)
	{
		single->deltaStrength();
	}
	for(ae::ga::MaxMin_x2* single : p)
	{
		single->deltaAge();
	}

	//
	for(std::list<ae::ga::MaxMin_x2*>::iterator single1 =  better1.begin(); single1 != better1.end();single1++)
	{
		for(std::list<ae::ga::MaxMin_x2*>::iterator single2 = std::next(single1); single2 != better1.end();single2++)
		{
			std::vector<ae::ga::MaxMin_x2*> chils;
			(*single1)->junction(**single2,chils,idCount);
			for(ae::ga::MaxMin_x2* s : chils)//agregar los nuevos hijos a la poblacion
			{
				if(isnan(s->getMaxMin().get_x2_mx()) or isnan(s->getMaxMin().get_x2_mn()))
				{
					delete s;
				}
				else
				{
					p.push_back(s);
				}
			}
		}
	}
	
		
}
void MaxMin_x2::eval_x2(const std::vector<ae::ga::MaxMin_x2*>& population,std::map<ae::ga::MaxMin_x2*,Notas>& evaluation)
{
	const float max = std::numeric_limits<float>::max();
	const float min = 0.0;
	for(ae::ga::MaxMin_x2* single : population)
	{
		float mx = single->getMaxMin().get_x2_mx();
		float mn = single->getMaxMin().get_x2_mn();
		
		Notas nota;
		if(mx < 0.0)
		{
			nota.x2_max = mx;
		}
		else
		{
			nota.x2_max = max - mx;
		}
		nota.x2_min = mn;
		
		evaluation.insert(std::make_pair(single, nota));
	}
}
void MaxMin_x2::saveEvals(const std::string& prefixfn, const std::map<ae::ga::MaxMin_x2*,Notas>& result, unsigned short iteration)
{
	std::string strfn = prefixfn + "-" + std::to_string(iteration) + ".csv";
	std::ofstream fn(strfn);
	if(not fn.is_open()) throw "No se logro abrier el archivo";
	
	for(const std::pair<ae::ga::MaxMin_x2*,Notas>& p : result)
	{
		fn << p.first->getID();
		fn << ",";
		fn << p.second.x2_max;
		fn << ",";
		fn << p.second.x2_min;
		
		fn << "\n";
	}

	fn.flush();
	fn.close();
}
int MaxMin_x2::main(int argc, const char* argv[])
{
	unsigned short itActual,itLimit,idCount;
	
	std::cout << "Iteracion iniciales. : ";
	std::cin >> itLimit;
	itActual = 0;

	//publacion inicial
	std::vector<ae::ga::MaxMin_x2*> population;
	for(idCount = 1; idCount < 100; idCount++)
	{
		population.push_back(new ae::ga::MaxMin_x2(idCount,ae::randNumber(),ae::randNumber(),ae::Junction::randChild(),ae::Junction::randAlgt()));
	}

	repeat:
	while(itActual < itLimit)
	{
		itActual++;
		std::cout << "iteracion " << itActual << "\n";
		
		std::map<ae::ga::MaxMin_x2*,ae::ga::Notas> evaluation;
		ae::ga::MaxMin_x2::eval_x2(population,evaluation);
		ae::ga::MaxMin_x2::saveEvals("MaxMin",evaluation,itActual);
		ae::ga::MaxMin_x2::junction(population,evaluation,idCount);		
	}
	
	std::cout << "Se ha alcanzado la iteracion " << itLimit << ", desea continuar?\n";
	std::string cmd;
	std::cin >> cmd;
	if(cmd.compare("y") == 0 or cmd.compare("Y") == 0)
	{
		itLimit++;
		goto repeat;
	}
	else if(cmd.compare("n") == 0 or cmd.compare("N") == 0)
	{

	}	
	else if(std::stoi(cmd) > 0)
	{
		int add = std::stoi(cmd);
		itLimit += add;
		goto repeat;
	}
	for(ae::ga::MaxMin_x2* single : population)
	{
		delete single;
	}

	return EXIT_SUCCESS;
}


}