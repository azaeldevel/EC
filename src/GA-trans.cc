

#include <fstream>
#include <algorithm>
#include <iostream>

#include "GA-trans.hh"

namespace ec::trans
{


Enviroment::Enviroment()
{
	init();
}
Enviroment::Enviroment(const std::string& log) : ec::Enviroment(log,true)
{
	init();
}
void Enviroment::init()
{
	countID = 0;//contador de nodos
	initPopulation = 10000;
	maxPopulation = 1000;
	maxProgenitor = 500;
	stopperMaxIterations(2000);
	//stopperNotDiference(1.0e-20);
	//comparer = &cmpStrength1;
	fractionDen = 5.0; //target 2, longitud 1, direccion 1, orden 1
	fractionQuality = 1.0/fractionDen;
	genLengthMin = 5;
	threads = 40;
	//echoSteps = true;
	
	//
	direction = true;
}
Enviroment::~Enviroment()
{
	
}

double Enviroment::getGammaLengthFront() const
{
	return gammaLengthFront;
}
double Enviroment::getGammaLengthBack() const
{
	return gammaLengthBack;
}
double Enviroment::getGammaTarget() const
{
	return gammaTarget;
}

unsigned short Enviroment::getGenLengthMin() const
{
	return genLengthMin;
}

void Enviroment::initial()
{

}



}