

#include "schedule.hh"


namespace oct::core
{

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
	
	
	
	
	
	


Enviroment::Enviroment(const std::string& log,const std::string& dir)
{
	init();
	logDirectory = log;
	directory = dir;
	data.subjects.loadFile(dir+"/subjects.csv");
	data.teachers.loadFile(dir+"/teachers.csv");
	data.rooms.loadFile(dir+"/rooms.csv");
	data.teachers_subjects.loadFile(dir+"/teachers-subjects.csv");
	
	if(not shell.exists(logDirectory)) 
	{
		shell.mkdir(logDirectory);
		if(not shell.exists(logDirectory))
		{
			std::string msg = "El directorio '";
			msg += logDirectory + "' no existe.";
			throw oct::core::Exception(msg,__FILE__,__LINE__);
		}
	}
}

Enviroment::~Enviroment()
{
	
}
void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = 1000;
	maxProgenitor = 200;
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
	int hours = data.config.to_hours(t1.diff(t2));
	
	std::cout << "pulverizando " << hours << "\n";
	if(hours < 1) return;

	out.resize(hours);
	time_t t = mktime(&t1);
	out[0] = &t;
	std::cout << "t = " << t << "\n";
	for(int i = 1; i < hours; i++)
	{
		t += 3600; // 60 segundos por 60 minutos = una hora
		std::cout << "t = " << t << "\n";
		out[i] = &t;
	}
}



}

