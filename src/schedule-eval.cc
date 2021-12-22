

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
		
		//std::cout << "\tfiteness = " << fitness << "\n";
		//Evaluar la opcion 'Menor cantidad de dias', 'Mayor cantidad de dias'
	}
	
	//
	void Single::overlap_by_teacher()
	{
		unsigned int count = 0;
		WeekHours week_actual;
		for(const Lessons& lessons : *this)
		{
			for(unsigned int i = 0; i < lessons.size(); i++)
			{
				if(lessons[i].week.count_hours() == 0) 
				{
					count += WEEK_HOURS;
					continue;
				}				
				for(unsigned int j = i + 1; j < lessons.size(); j++)
				{
					if(lessons[i].week.count_hours() == 0) 
					{
						count += WEEK_HOURS;
					}
					else
					{
						week_actual.inters(lessons[i].week,lessons[j].week);
						count += week_actual.count_hours();
						week_actual.clear();
					}
				}
			}
		}
		unsigned int gamma = size() * WEEK_HOURS2;
		gamma = gamma - std::pow(count,2);
		fitness += real(gamma) * env->getGamma();
	}
			
	//Deve dar una mejor califacion al horaio que se acerca mas 
	//a la hora exacta de clases por semana,deve cubir las hora de materia por semana sin pasarse o flatarle
	void Single::cover()
	{
		unsigned int count = 0;
		for(const Lessons& lessons : *this)
		{
			for(unsigned int i = 0; i < lessons.size(); i++)
			{
				for(const Day day : lessons[i].week)
				{
					//la diferencia entre las horas disponibles y las necesesrias
					if(day.size() > 0) 
					{
						count += std::abs((int)lessons[i].subject->get_time() - (int)day.size());			
					}
				}
			}
		}
		unsigned int gamma = size() * WEEK_HOURS2;
		gamma = gamma - std::pow(count,2);
		fitness += real(gamma) * env->getGamma();
	}
	
}

