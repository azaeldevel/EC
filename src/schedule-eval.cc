

#include "schedule.hh"

//#include <octetos/core/MD5sum.hh>

namespace oct::ec::sche
{
	
	/**
	** Criterios:
	** 		El mismo maestro no puede tener materias diferentes a la misma hora :
	** 		El mismo maestro no puede tener la misma materia diferentes a la misma hora : 
	** 		Diferentes materias no pueden tener el mismo salon a la misma hora : No traslape de clase
	** 		La misma materias no pueden tener el mismo salon a la misma hora :
	** 		La misma materias no pueden tener el diferentes salones a la misma hora : No traslape de clase
	** 		Cada materia tiene solo un maestro por ggrupo: Maestro unico por materia
	** 		Los criterio de disponibilidad para cada objetivo dever ser compidos : disponibilidad
	** 		Hay criterios adicionales expresados en la configuracion que deve ser cumplidos
	** Definicion:
	**		Clase : relacion salon,materia
	**/
	void Single::eval()
	{
		fitness = 0;
		
		//std::cout << "\tSingle::eval : Step 1\n";
		//std::cout << "\tgamma = " << env->getGamma() << "\n";
		
		overlap_by_teacher();

		cover();
		
		not_empty();//un horarion con 0 horas no es util.
		//std::cout << "\tfiteness = " << fitness << "\n";
		
		
		//TODO:Evaluar la opcion 'Menor cantidad de dias', 'Mayor cantidad de dias'
	}
	
	//
	unsigned int Single::match(unsigned int countGroup,const Lessons& classroom)
	{
		unsigned int diff = ((Enviroment*)env)->get_data().groups.get_max_lessons() - classroom.size();
		if(diff > 0 and countGroup > 0)	return countGroup + (diff * WEEK_HOURS);
		return 0;
	}
	void Single::convertGamma(unsigned int count)
	{
		unsigned int gamma = std::pow(count,2);
		fitness += ((Enviroment*)env)->getGammaPortion() - (real(gamma) * ((Enviroment*)env)->getGamma());
	}
	void Single::overlap_by_teacher()
	{
		unsigned int count = 0;
		unsigned int countClass = 0;
		WeekHours week_actual;
		for(const Lessons& classroom : *this)
		{
			count = 0;
			for(unsigned int i = 0; i < classroom.size() - 1; i++)
			{
				if(classroom[i].week.count_hours() == 0) 
				{
					continue;
				}				
				for(unsigned int j = i + 1; j < classroom.size(); j++)
				{
					if(classroom[i].week.count_hours() == 0) 
					{
						continue;
					}
					else
					{
						week_actual.inters(classroom[i].week,classroom[j].week);
						count += week_actual.count_hours();
						week_actual.clear();
					}
				}
			}
			countClass += match(count,classroom) + count;
		}
		convertGamma(countClass);
	}
			
	//Deve dar una mejor califacion al horaio que se acerca mas 
	//a la hora exacta de clases por semana,deve cubir las hora de materia por semana sin pasarse o flatarle
	void Single::cover()
	{		
		unsigned int count = 0;
		unsigned int countClass = 0;
		for(const Lessons& classroom : *this)
		{
			for(unsigned int i = 0; i < classroom.size(); i++)
			{
				for(const Day day : classroom[i].week)
				{
					//la diferencia entre las horas disponibles y las necesesrias
					if(day.size() > 0) 
					{
						count += std::abs((int)classroom[i].subject->get_time() - (int)day.size());			
					}
				}
			}
			countClass += match(count,classroom) + count;
		}
		convertGamma(countClass);
	}
	void Single::not_empty()
	{
		unsigned int count = 0;
		for(const Lessons& classroom : *this)
		{
			for(unsigned int i = 0; i < classroom.size(); i++)
			{
				if(classroom[i].week.count_hours() == 0)
				{
					count += WEEK_HOURS;
				}
			}
		}
		convertGamma(count);
	}
}

