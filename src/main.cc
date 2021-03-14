/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * AE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <map>
#include <limits>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <list>
#include <algorithm>

#include "GA.hh"

//determinar los maximos y minimos de la funcion indicada

struct Notas
{
	float x2_max;//la tendecia hacia 0 es mejor
	float x2_min;//la tendecia hacia 0 es mejor

	float strength;
};


class MaxMin : public ae::ga::Single
{
public:
	MaxMin(unsigned int id,ae::geneF x2_mx,ae::geneF x2_min,ae::geneUS number,ae::geneUS algorit) 
		: ae::ga::Single(id)
		,maxmin(x2_mx,x2_min)
		,juntion(number,algorit)
	{
		add(maxmin);
		add(juntion);
		//std::cout << " MaxMin number : " << juntion.get_number() << "\n";
	}
	MaxMin(unsigned int id,ae::MaxMin_R mm,ae::Junction j) : ae::ga::Single(id),maxmin(mm),juntion(j)
	{
		add(maxmin);
		add(juntion);
	}
public:
	ae::MaxMin_R& getMaxMin()
	{
		return maxmin;
	};
	virtual void junction(MaxMin& single,std::vector<MaxMin*>& chils,unsigned short& count)
	{
		std::cout << "\t" << getID() << "\tpuede tener " << juntion.get_number() << " hijos\n";
		for(ae::geneUC i = 0; i < juntion.get_number(); i++)
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
			if(mutate >= 15.0 and mutate <= 20.0)
			{
				newmm.mutate();
				newj.mutate();
			}
			count++;
			MaxMin* s = new MaxMin(count,newmm,newj);
			std::cout << "\tSe crea a " << s->getID() << "\n"; 
			chils.push_back(s);
		}
	};
private:
	ae::MaxMin_R maxmin;
	ae::Junction juntion;
};



void eval_x2(const std::vector<MaxMin*>& population,std::map<MaxMin*,Notas>& evaluation)
{
	const float max = std::numeric_limits<float>::max();
	const float min = 0.0;
	for(MaxMin* single : population)
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
void saveEvals(const std::string& prefixfn, const std::map<MaxMin*,Notas>& result, unsigned short iteration)
{
	std::string strfn = prefixfn + "-" + std::to_string(iteration) + ".csv";
	std::ofstream fn(strfn);
	if(not fn.is_open()) throw "No se logro abrier el archivo";
	
	for(const std::pair<MaxMin*,Notas>& p : result)
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

struct MaxMin_By_Value
{
	MaxMin* maxmin;
	float value;
};
bool cmpfloatMax(const MaxMin_By_Value& f,const MaxMin_By_Value& s)
{
	return f.value < s.value;
}
bool cmpfloatMin(const MaxMin_By_Value& f,const MaxMin_By_Value& s)
{
	return fabs(f.value) > fabs(s.value);
}
void remove(std::vector<MaxMin*>& p, MaxMin* s)
{
	std::vector<MaxMin*>::iterator it = std::find(p.begin(),p.end(),s);
	if(it != p.end()) 
	{
		std::cout << "\tSe elimina a " << (*it)->getID() << "\n"; 
		p.erase(it);
	}
}
void junction(std::vector<MaxMin*>& p,std::map<MaxMin*,Notas>& e,unsigned short& idCount)
{
	std::list<MaxMin*> better1;
	std::list<MaxMin*> better2;
	
	//std::cout << "\t Maximos \n";
	std::list<MaxMin_By_Value> lsmx;
	for(MaxMin* single : p)
	{
		MaxMin_By_Value v;
		v.maxmin = single;
		v.value = e.find(single)->second.x2_max;
		lsmx.push_back(v);

		if(single->efficiency() < 1.0)
		{
			float randNumRem = ae::randNumber(100.0);
			if(randNumRem < 15.0) remove(p,single);
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

	//std::cout << "\t Minimos \n";
	std::list<MaxMin_By_Value> lsmn;
	for(MaxMin* single : p)
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
	
	//std::cout << "better1 " << better1.size() << "\n";
	//std::cout << "better2 " << better2.size() << "\n";
	for(MaxMin* single : better1)
	{
		single->deltaStrength ();
		single->deltaStrength ();
	}
	for(MaxMin* single : better2)
	{
		single->deltaStrength();
	}
	for(MaxMin* single : p)
	{
		single->deltaAge();
	}

	//
	for(std::list<MaxMin*>::iterator single1 =  better1.begin(); single1 != better1.end();single1++)
	{
		for(std::list<MaxMin*>::iterator single2 = std::next(single1); single2 != better1.end();single2++)
		{
			std::vector<MaxMin*> chils;
			(*single1)->junction(**single2,chils,idCount);
			for(MaxMin* s : chils)//agregar los nuevos hijos a la poblacion
			{
				p.push_back(s);
			}
		}
	}
	for(std::list<MaxMin*>::iterator single1 =  better2.begin(); single1 != better2.end();single1++)
	{
		for(std::list<MaxMin*>::iterator single2 = std::next(single1); single2 != better2.end();single2++)
		{
			std::vector<MaxMin*> chils;
			(*single1)->junction(**single2,chils,idCount);
			for(MaxMin* s : chils)//agregar los nuevos hijos a la poblacion
			{
				p.push_back(s);
			}
		}
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
int main()
{
	unsigned short itActual,itLimit,idCount;
	
	itActual = 0;
	itLimit = 3;
	std::vector<MaxMin*> population;
	for(idCount = 1; idCount < 100; idCount++)
	{
		unsigned short numchlids = randFloatDigit();
		//std::cout << "numchlids " << numchlids << "\n";
		population.push_back(new MaxMin(idCount,randFloat(),randFloat(),numchlids,randFloatAlgt()));
	}

	repeat:
	while(itActual < itLimit)
	{
		itActual++;
		std::cout << "iteracion " << itActual << "\n";
		
		std::map<MaxMin*,Notas> evaluation;
		eval_x2(population,evaluation);
		saveEvals("MaxMin",evaluation,itActual);
		junction(population,evaluation,idCount);		
	}
	
	std::cout << "Se ha alcanzado la interacion " << itLimit << ", desea continuar?\n";
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
	for(MaxMin* single : population)
	{
		delete single;
	}
	return 0;
}


