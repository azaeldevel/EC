
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
	void Single::save(Save&)
	{
		const Configuration& config = ((Enviroment*)env)->get_data().config;
		
		std::string dir = config.get_out_directory() + "/" + std::to_string(env->getIterationActual()) + "/" + std::to_string(getID());
		
		env->shell.mkdir(dir);
		save_csv(config,dir);		
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
		
	
	
	
	


Enviroment::Enviroment(const std::string& log,const std::string& in_dir,const std::string& out_dir) : data(in_dir,out_dir)
{
	if(echolevel > 0 and fout != NULL) (*fout) << "Creando Ambiente..\n";
	logDirectory = log;
	init(in_dir);		
}
Enviroment::~Enviroment()
{
}
void Enviroment::init(const std::string& in_dir)
{
	if(echolevel > 0 and fout != NULL) (*fout) << "Inicializacion..\n";
	mutableProb = 0.05;
		
	if(not in_dir.empty())
	{
		input_directory = in_dir;
		initPopulation = data.groups.get_list().size() * data.groups.get_max_lessons();
		maxProgenitor = initPopulation;
		maxPopulation = std::pow(initPopulation,2);
	}
	else
	{
		throw oct::core::Exception("Deve asignar el archivo de proyecto.",__FILE__,__LINE__);
	}
	
	CRITERION = 4;
	//SCHEDULE_ERROR = 0;
	schedule_overlap_max = data.groups.get_list().size() * data.groups.get_max_lessons() * Single::WEEK_HOURS/2;
	schedule_overlap_max2 = std::pow(schedule_overlap_max,2);
	schedule_cover_max = data.groups.get_list().size() * data.groups.get_max_lessons() * (Single::WEEK_HOURS - 7);
	schedule_cover_max2 = std::pow(schedule_cover_max,2);
	SCHEDULE_EMPTY_MAX = data.groups.get_list().size() * data.groups.get_max_lessons() * Single::WEEK_HOURS;
	schedule_sigma_hours_limit = data.config.get_hours_sigma();
	//Se asumen 4 horas en 0 y 3 en 24
	real mean = real(24 * 3) / real(7);
	real sigma = ((3.0 * std::pow(24.0 - mean,2.0)) + (4.0 * std::pow(mean,2.0)));
	sigma /= 7.0;
	schedule_sigma_hours_max = sigma;
	schedule_sigma_hours_max2 = std::pow(schedule_sigma_hours_max,2.0);
	
	/*for(unsigned int i = 0; i < CRITERION; i++)
	{
		SCHEDULE_ERROR += 1.0/real(CRITERION);
	}*/
	//SCHEDULE_ERROR = 1.0 - SCHEDULE_ERROR;
	//PORTION = 1.0/real(CRITERION);
	//schedule_max_hours = std::min((unsigned int)data.groups.get_list().size() * data.groups.get_max_lessons() * (Single::WEEK_HOURS/2), Single::WEEK_HOURS2) ;
	//GAMMA = 1.0/real(SCHEDULE_MAX_HOURS * CRITERION);
}

void Enviroment::initial()
{
	if(echolevel > 0 and fout != NULL) (*fout) << "Poblando ambiente..";
	Schedules inits;
	inits.resize(initPopulation);
	
	if(initPopulation < data.groups.get_list().size() * 2) throw core::Exception("El tamano de la poblacion inicial es muy bajo",__FILE__,__LINE__);
	if((initPopulation % data.groups.get_list().size()) != 0 and (initPopulation / data.groups.get_list().size() ) < 2 ) throw core::Exception("La poblacion inicial deve ser multiplos de la cantida de grupos.",__FILE__,__LINE__);
	
	if(echolevel > 0 and fout != NULL) 
	{
		(*fout) << ".";
		fout->flush();
	}
	for(unsigned int i = 0; i < initPopulation; i++)
	{
		if(echolevel > 0 and fout != NULL)
		{
			(*fout) << ".";
			fout->flush();
		}
		Single* sche = new Single(nextID(),*this);
		sche->resize(data.groups.get_list().size());
		Groups::const_iterator itGroup = data.groups.get_list().begin();
		for(ClassRoom& lessons : *sche)
		{
			if(echolevel > 0 and fout != NULL)
			{
				(*fout) << ".";
				fout->flush();
			}
			lessons.resize((*itGroup).size());
			std::vector<const Subject*>::const_iterator it_subject = (*itGroup).begin();
			unsigned int subject = 0;
			//std::cout << (&*itGroup)->room->get_name() << " : ";
			for(const Subject* subjectGroup : *itGroup)
			{
				if(echolevel > 0 and fout != NULL)
				{
					(*fout) << ".";
					fout->flush();
				}
				//std::cout << "Enviroment::initial step : 1 \n";
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
				
				//std::cout << "Enviroment::initial step : 2\n";
				//es un algoritmo que creara los horarios lo mas correctos posibles
				select_times(lessons[subject],week);
				//std::cout << "Enviroment::initial step : 3\n";
				//random_complete_times(lessons[subject],week_opt);
				//std::cout << "Enviroment::initial step : 4\n";
				subject++;
				it_subject++;
				//std::cout << "Enviroment::initial step : 5 \n";
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
	return schedule_overlap_max;
}
unsigned long Enviroment::get_overlap_max2() const
{
	return schedule_overlap_max2;
}
unsigned int Enviroment::get_cover_max() const
{
	return schedule_cover_max;
}
unsigned long Enviroment::get_cover_max2() const
{
	return schedule_cover_max2;
}
unsigned int Enviroment::get_empty_max() const
{
	return SCHEDULE_EMPTY_MAX;
}
unsigned int Enviroment::get_sigma_hours_max() const
{
	return schedule_sigma_hours_max;
}
unsigned int Enviroment::get_sigma_hours_max2() const
{
	return schedule_sigma_hours_max2;
}
unsigned int Enviroment::get_sigma_hours_limit() const
{
	return schedule_sigma_hours_limit;
}
/*unsigned int Enviroment::get_schedule_max_hours() const
{
	return schedule_max_hours;
}*/
/*double Enviroment::get_gamma() const
{
	return GAMMA;
}*/
/*real Enviroment::get_portion() const
{
	return PORTION;
}*/

void Enviroment::select_times(Lesson& lesson,const WeekHours& week)
{
	if(lesson.subject->get_time() == 0) throw core::Exception("No puede habe hora 0 en el la materia.",__FILE__,__LINE__);
	unsigned int disp = week.days_disp();
	if(disp == 0) return;
	unsigned int hours_per_day = lesson.subject->get_time() / disp;
	if(hours_per_day == 0) hours_per_day = 1;
	//unsigned int hours_hat = lesson.subject->get_time() - (hours_per_day * disp);
	
	const core::Time* time;
	for(unsigned int i = 0; i < WeekHours::WEEK_SIZE; i++)
	{
		time = &*random(week[i]);
		week.get_day(i,hours_per_day,*time,data.config,lesson.week[i]);
		if(lesson.week[i].size() > lesson.subject->get_time()) break;
	}
	/*
	unsigned int count_H = lesson.week.count_hours();
	if(count_H < lesson.subject->get_time())
	{
		for(unsigned int i = 0; i < WeekHours::WEEK_SIZE; i++)
		{
			if(lesson.week[i].empty())
			{
				week.get_day(i,lesson.subject->get_time() - count_H,*time,data.config,lesson.week[i]);
			}
		}
	}
	*/
	/*
	Day* day;
	count_H = lesson.week.count_hours();
	do
	{		
		day = &*random(lesson.week);
		week.get_day(i,(lesson.subject->get_time() - count_H) + day->size(),*time,data.config,*day)
	}
	while();
	*/
}

void Enviroment::random_complete_times(Lesson& lesson,const WeekOptions& week_opt)
{
	for(unsigned int i = 0; i < WeekHours::WEEK_SIZE; i++)
	{
		//std::cout << lesson.subject->get_name() << " requiere " << lesson.subject->get_time() << " de las cuales hay " << lesson.week.count_hours() << "\n";
		if(lesson.subject->get_time() <= lesson.week.count_hours()) return;
		if(lesson.week[i].size() > 0) continue;
		
		//TODO:realizar esta asignacion en un orden aleatorio
		week_opt[i].random(lesson.week[i]);
	}
}
}

