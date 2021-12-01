

#include "schedule.hh"


namespace oct::core
{
	DataTime::DataTime()
	{
		(tm&)*this = {0};
	}
	const time_t* DataTime::operator =(const time_t* t)
	{
		tm* thistm = gmtime(t);
		
		return t;
	}
	int DataTime::get_week_day()const
	{
		return tm_wday;
	}

	int DataTime::diffHours(DataTime& dt)
	{
		time_t tm1,tm2;
		tm1 = mktime(this);
		tm2 = mktime(&dt);
		double diff = difftime(tm2, tm1);
		return diff/60.0;
	}
}


namespace oct::ec::sche
{
	


Single::Single(ID id,Enviroment& env) : ec::Single(id,env)
{

}
void Single::eval()
{

}
void Single::save(std::ofstream& fn)
{

}
Population Single::juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single,unsigned short loglevel,void*)
{
	
}
void Single::print(std::ostream&) const
{

}
	
	
	
	
	
	
Enviroment::Enviroment()
{
	init();
}

Enviroment::Enviroment(const std::string& log)
{
	init();
	logDirectory = log;
}
Enviroment::Enviroment(const std::string& log, Pile& p) : pile(&p)
{
	init();
	logDirectory = log;
	if(not shell.exists(logDirectory)) 
	{
		std::string msg = "El directorio '";
		msg += logDirectory + "' no existe.";
		throw oct::core::Exception(msg,__FILE__,__LINE__);
	}
}

Enviroment::~Enviroment()
{
	delete pile;
}
void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = 1000;
	maxProgenitor = 200;
	pile = NULL;	
}



void Enviroment::initial()
{
	for(unsigned short i = 0; i < initPopulation; i++)
	{
		Single* single = new Single(nextID(),*this);
		push_back(single);
	}
}
void Enviroment::pulverize_hours(core::DataTime& t1,core::DataTime& t2,std::vector<core::DataTime>& out)
{
	int hours = t2.diffHours(t1);

	if(hours < 1) return;

	out.resize(hours);
	time_t t = mktime(&t1);
	out[0] = &t;
	for(int i = 1; i < hours; i++)
	{
		t += 3600; // 60 segundos por 60 minutos = una hora
		out[i] = &t;
	}
}



}

