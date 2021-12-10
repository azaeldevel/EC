

#include "schedule.hh"


namespace oct::core
{

}


namespace oct::ec::sche
{
	
	
	void Studen::init_rand(const sche::Groups::Group*)
	{
		
	}
	


	Single::Single(ID id,Enviroment& env, const std::vector<Studen>&) : ec::Single(id,env)
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
	initPopulation = 100;
	maxPopulation = 100;
	maxProgenitor = 20;
	
	data.load("tests");
}



void Enviroment::initial()
{
	
	int count = data.groups.get_list().size();
	std::vector<std::vector<Studen>> inits;
	inits.resize(initPopulation);
	
	//
	for(unsigned int i = 0; i < inits.size(); i++)
	{
		inits[i].resize(data.groups.get_list().size());
		Groups::const_iterator it = data.groups.get_list().begin();
		for(unsigned int j = 0; j < data.groups.get_list().size(); j++,it++)
		{
			inits[i][j].init_rand(&*it);
		}
	}
	
	//creando individuuos
	for(const std::vector<Studen>& s : inits)
	{
		Single* single = new Single(nextID(),*this,s);
		push_back(single);
	}
}



}

