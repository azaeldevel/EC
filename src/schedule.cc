

#include "schedule.hh"


namespace oct::core
{

}


namespace oct::ec::sche
{
	
	const unsigned int Single::WEEK_HOURS = 168;
	const unsigned int Single::WEEK_HOURS2 = std::pow(Single::WEEK_HOURS,2);

	Single::Single(ID id,Enviroment& env,const Junction& j) : ec::Single(id,env,j)
	{

	}
	Single::Single(ID id,Enviroment& env, const Schedule& s) : ec::Single(id,env), Schedule(s)
	{

	}
	Single::Single(ID id,Enviroment& env) : ec::Single(id,env)
	{

	}
	void Single::save(std::ofstream& fn)
	{
		
	}
	void Single::juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single)
	{
		for(ec::geneUS i = 0; i < getJunction().get_number(); i++)
		{
			Single* newsingle = new Single(env->nextID(),(Enviroment&)*env,getJunction());
			newsingle->resize(size());
			((Schedule*)newsingle)->juncting(*this,((const Single&)*single));					
			chils.push_back(newsingle);
		}
	}
	void Single::print(std::ostream&) const
	{
	}
	void Single::mutate()
	{
		std::uniform_int_distribution<int> distrib(0, size() - 1);
		at(distrib(gen)).mutate();
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
	
	unsigned int gamma_factors = gammaCriterion * data.groups.get_list().size() * Single::WEEK_HOURS2;
	//std::cout << "\tgamma_factors = " << gamma_factors << "\n";
	gamma = 1.0/real(gammaCriterion * data.groups.get_list().size() * Single::WEEK_HOURS2);
	//std::cout << "\tgamma = " << gamma << "\n";
	gammaPortion = 1.0/gammaCriterion;
}
Enviroment::~Enviroment()
{
	init();
}
void Enviroment::init()
{
	initPopulation = 100;
	maxPopulation = initPopulation;
	maxProgenitor = initPopulation;
	gammaCriterion = 2;
}

void Enviroment::initial()
{
	Schedules inits;
	inits.resize(initPopulation);
	
	if(initPopulation < data.groups.get_list().size() * 2) core::Exception("El tamano de la poblacion inicial es muy bajo",__FILE__,__LINE__);
	if((initPopulation % data.groups.get_list().size()) != 0 and (initPopulation / data.groups.get_list().size() ) < 2 ) throw core::Exception("La poblacion inicial deve ser multiplos de la cantida de grupos.",__FILE__,__LINE__);
	
	for(unsigned int i = 0; i < initPopulation; i++)
	{
		Single* sche = new Single(nextID(),*this);
		sche->resize(data.groups.get_list().size());
		Groups::const_iterator itGroup = data.groups.get_list().begin();
		for(Lessons& lessons : *sche)
		{
			lessons.resize((*itGroup).size());
			std::vector<const Subject*>::const_iterator it_subject = (*itGroup).begin();
			unsigned int subject = 0;
			//std::cout << (&*itGroup)->room->get_name() << " : ";
			for(const Subject* subjectGroup : *itGroup)
			{
				lessons[subject].group = &*itGroup;
				lessons[subject].room = (&*itGroup)->room;
				lessons[subject].subject = subjectGroup;
				std::list<const Teachers_Subjects::Row*> rows;
				data.teachers_subjects.searchSubjects(subjectGroup->get_name(),rows);
				//std::cout << lessons[subject].subject->get_name();
				std::list<const Teachers_Subjects::Row*>::const_iterator itr = random(rows);
				const Teachers_Subjects::Row* r = (itr != rows.end()) ? *itr : NULL;
				if(r)
				{
					lessons[subject].teacher = r->teacher;
					//std::cout << "(" << r->teacher->get_name() << "),";
				}
				else 
				{
					std::string msg = "No se encontro maestro asociado para '";
					msg += subjectGroup->get_name() + "'";
					throw core::Exception(msg,__FILE__,__LINE__);
				}
										
				WeekHours week;
				WeekOptions week_opt;
				week.inters(lessons[subject].room->get_week (),lessons[subject].teacher->get_week());
				check_codes code = week.check();
				week.combns(*lessons[subject].subject,week_opt);
				week_opt.random(lessons[subject].week);
				subject++;
				it_subject++;
			}
			//std::cout << "\n";
			itGroup++;
		}
		sche->indexing();
		push_back(sche);
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

/*void Enviroment::juncting()
{
	Single *single1,*single2;
	do
	{
		ec::Single* single1 = getRandomSingle();
		if(single1 == NULL) continue;
		ec::Single* single2 = getRandomSingle();
		if(single2 == NULL) continue;		
		if(single1 == single2) continue;
		
		single1->juncting(newschils,single2);
	}
	while(newschils.size() + size() <= maxPopulation);
}*/

}

