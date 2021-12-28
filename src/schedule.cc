
#include <iomanip>

#include "schedule.hh"


namespace oct::core
{

}


namespace oct::ec::sche
{
	
	

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
		if(size() == 0) throw core::Exception("Hoario vacio",__FILE__,__LINE__);
		
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
	
	//std::cout << "\tgamma_factors = " << gamma_factors << "\n";
	//std::cout << "\tdata.groups.get_list().size() = " << data.groups.get_list().size() << "\n";
	//std::cout << "\tgamma = " << gamma << "\n";
	//if(GAMMA < epsilon) throw oct::core::Exception("gamma < epsilon",__FILE__,__LINE__);
	CRITERION = 3;
	SCHEDULE_ERROR = 0;
	SCHEDULE_OVERLAP_MAX = data.groups.get_list().size() * data.groups.get_max_lessons() * std::pow(Single::WEEK_HOURS/2,2);
	SCHEDULE_COVER_MAX = data.groups.get_list().size() * data.groups.get_max_lessons() * (Single::WEEK_HOURS - 7);
	SCHEDULE_EMPTY_MAX = data.groups.get_list().size() * data.groups.get_max_lessons() * Single::WEEK_HOURS;
	for(unsigned int i = 0; i < CRITERION; i++)
	{
		SCHEDULE_ERROR += 1.0/real(CRITERION);
	}
	SCHEDULE_ERROR = 1.0 - SCHEDULE_ERROR;
	PORTION = 1.0/real(CRITERION);
	SCHEDULE_MAX_HOURS = data.groups.get_list().size() * data.groups.get_max_lessons() * Single::WEEK_HOURS2;
	GAMMA = 1.0/real(SCHEDULE_MAX_HOURS * CRITERION);
	//std::cout << "\tSCHEDULE_ERROR = " <<std::setprecision(echoPrecision) << SCHEDULE_ERROR << "\n";
}
Enviroment::~Enviroment()
{
	init();
}
void Enviroment::init()
{
	initPopulation = 1000;
	maxPopulation = initPopulation;
	maxProgenitor = 100;
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
		for(ClassRoom& lessons : *sche)
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
				lessons[subject].data =&data;
										
				
				WeekHours week;
				WeekOptions week_opt;
				week.inters(lessons[subject].room->get_week (),lessons[subject].teacher->get_week());
				check_codes code = week.check();
				week.combns(*lessons[subject].subject,week_opt);
				week_opt.random(lessons[subject].week);				
				//select_times(lessons[subject],week_opt);
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
const Data& Enviroment::get_data()const
{
	return data;
}

unsigned int Enviroment::get_criterion() const
{
	return CRITERION;
}
unsigned int Enviroment::get_overlap_max() const
{
	return SCHEDULE_OVERLAP_MAX;
}
unsigned int Enviroment::get_cover_max() const
{
	return SCHEDULE_COVER_MAX;
}
unsigned int Enviroment::get_empty_max() const
{
	return SCHEDULE_EMPTY_MAX;
}

double Enviroment::get_gamma() const
{
	return GAMMA;
}
unsigned int Enviroment::get_schedule_max_hours() const
{
	return SCHEDULE_MAX_HOURS;
}
real Enviroment::get_portion() const
{
	return PORTION;
}

void Enviroment::select_times(Lesson& lesson,const WeekOptions& week_opt)
{
	WeekHours week_disp;
	week_disp.inters(lesson.room->get_week(),lesson.teacher->get_week());
	
	unsigned int disp = week_disp.days_disp();
	unsigned int hours_per_day = lesson.subject->get_time() / disp;
	unsigned int hours_hat = lesson.subject->get_time() - (hours_per_day * disp);
	
	for(unsigned int i = 0; i < 7; i++)
	{
		//week_opt.get_day(i,hours_per_day,lesson.week[i]);
	}
}

}

