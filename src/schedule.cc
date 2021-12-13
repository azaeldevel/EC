

#include "schedule.hh"


namespace oct::core
{

}


namespace oct::ec::sche
{
	
	


	Single::Single(ID id,Enviroment& env, const Schedule&) : ec::Single(id,env)
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
	std::vector<Schedule> inits;
	inits.resize(initPopulation);
	
	//
	for(Groups::const_iterator itGroup = data.groups.get_list().begin(); itGroup != data.groups.get_list().end(); itGroup++)
	{
		for(unsigned int j = 0; j < data.groups.get_list().size(); j++)
		{
			for(const Subject* subject : *itGroup)
			{
				std::list<const Teachers_Subjects::Row*> rows;
				data.teachers_subjects.searchSubjects(subject->get_name(),rows);
				for(const Teachers_Subjects::Row* ts : rows)
				{
				
					
					const WeekHours& dispTeacher = ts->teacher->get_times();//disponibilidad de mestros
					const WeekHours& dispRoom = (*itGroup).room->get_times();//disponibilidad de salon
					
					if(dispTeacher.size() != dispRoom.size()) throw core::Exception("La cantidad de dias no coinciden",__FILE__,__LINE__);
					
					Goal goal;
					goal.group = &*itGroup;
					//goal.teacher = 
				}
			}
		}
	}
	
	//creando individuuos
	for(const Schedule& s : inits)
	{
		Single* single = new Single(nextID(),*this,s);
		push_back(single);
	}
}



}

