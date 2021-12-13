

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
	data.load(directory);
	
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
	init();
}
void Enviroment::init()
{
	initPopulation = 5;
	maxPopulation = initPopulation;
	maxProgenitor = initPopulation;
}



void Enviroment::initial()
{
	Schedules inits;
	inits.resize(initPopulation);
	
	//
	for(Schedule& sche : inits)
	{
		Goal goal;
		for(Groups::const_iterator itGroup = data.groups.get_list().begin(); itGroup != data.groups.get_list().end(); itGroup++)
		{
			goal.group = &*itGroup;
			goal.room = (&*itGroup)->room;		
			for(const Subject* subjectGroup : *itGroup)
			{
				List<const Teachers_Subjects::Row*> rows;
				data.teachers_subjects.searchSubjects(subjectGroup->get_name(),rows);
				goal.subject = subjectGroup;
				const Teachers_Subjects::Row* r = rows.rand();
				if(r) goal.teacher = r->teacher;
				else throw core::Exception("No se encontro maestro asociado",__FILE__,__LINE__);
				
				sche.goals.push_back(goal);
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


/*
unsigned int Enviroment::counter()const
{
	unsigned int count = 0;
	for(Groups::const_iterator itGroup = data.groups.get_list().begin(); itGroup != data.groups.get_list().end(); itGroup++)
	{
		//goal.group = &*itGroup;
		//goal.room = (&*itGroup)->room;
		for(unsigned int j = 0; j < data.groups.get_list().size(); j++)
		{
			for(const Subject* subject : *itGroup)
			{
				std::list<const Teachers_Subjects::Row*> rows;
				data.teachers_subjects.searchSubjects(subject->get_name(),rows);
				for(const Teachers_Subjects::Row* ts : rows)//cada mestro
				{
					//goal.teacher = ts->teacher;
					for(const Subject* subject : *ts)
					{
						//goal.subject = subject;
												
						//const WeekHours& dispTeacher = ts->teacher->get_times();//disponibilidad de mestros
						//const WeekHours& dispRoom = (*itGroup).room->get_times();//disponibilidad de salon
						//const WeekHours& dispSubject = (*itGroup).room->get_times();//disponibilidad de salon
						//if(dispTeacher.size() != dispRoom.size()) throw core::Exception("La cantidad de dias no coinciden",__FILE__,__LINE__);
						count++; 
					}
				}
			}
		}
	}
}
*/
unsigned int Enviroment::counter()const
{
	unsigned int count = 0;
	for(Groups::const_iterator itGroup = data.groups.get_list().begin(); itGroup != data.groups.get_list().end(); itGroup++)
	{
			for(const Subject* subjectGroup : *itGroup)
			{
				List<const Teachers_Subjects::Row*> rows;
				data.teachers_subjects.searchSubjects(subjectGroup->get_name(),rows);
				for(const Teachers_Subjects::Row* ts : rows)
				{
					for(const Subject* subject : *ts)
					{
						count++; 
					}
				}
			}
	}
	
	return count;
}

}

