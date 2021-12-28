

#include "schedule.hh"

//#include <octetos/core/MD5sum.hh>

namespace oct::ec::sche
{
	
	const unsigned int Single::WEEK_HOURS = 168;
	const unsigned int Single::WEEK_HOURS2 = std::pow(Single::WEEK_HOURS,2);
	const unsigned int Single::WEEK_HOURS3 = std::pow(Single::WEEK_HOURS,3);

	
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
		//std::cout << "\tfiteness = " << fitness << "\n";
		cover();		
		//std::cout << "\tfiteness = " << fitness << "\n";
		not_empty();//un horarion con 0 horas no es util.
		//std::cout << "\tfiteness = " << fitness << "\n";
		//std::cout << "\tfiteness = " << fitness << "\n";
		
		
		//TODO:Evaluar la opcion 'Menor cantidad de dias', 'Mayor cantidad de dias'
	}

	//se puede interseta un maximo de WEEK_HOURS/2
	void Single::overlap_by_teacher()
	{
		unsigned int count = 0;
		WeekHours week_actual;
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < at(i).size() - 1; j++)
			{			
				for(unsigned int k = 1; k < size(); k++)
				{
					for(unsigned int l = 0; l < at(k).size(); l++)
					{
						week_actual.inters(at(i)[j].week,at(k)[l].week);
						count += week_actual.count_hours();
						week_actual.clear_days();
					}
				}
			}
		}
		if(count >  ((Enviroment&)*env).get_overlap_max()) throw oct::core::Exception("El conteo de horas no deve exceder WEEK_OVERLAP_MAX",__FILE__,__LINE__);
		//if(count > ((Enviroment&)*env).get_schedule_max_hours()) throw oct::core::Exception("El conteo de horas errones execdio el maximo esperado",__FILE__,__LINE__);
		if(count == 0) 
		{
			std::cout << "\toverlap_by_teacher count = " << count << "\n";
			fitness += 1.0/((Enviroment&)*env).get_criterion();
		}
		else
		{
			count =  ((Enviroment&)*env).get_overlap_max() - count;
			fitness += real(count)/ real(((Enviroment&)*env).get_criterion() * ((Enviroment&)*env).get_overlap_max());
		}
	}
			
	//Deve dar una mejor califacion al horaio que se acerca mas 
	//a la hora exacta de clases por semana,deve cubir las hora de materia por semana sin pasarse o flatarle
	void Single::cover()
	{		
		unsigned int count = 0;
		unsigned int countClass = 0;
		for(const ClassRoom& classroom : *this)
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
		}
		
		if(count >  ((Enviroment&)*env).get_cover_max()) throw oct::core::Exception("El conteo de horas no deve exceder SCHEDULE_COVER_MAX",__FILE__,__LINE__);
		if(count == 0)
		{
			std::cout << "\tcover count = " << count << "\n";
			fitness += 1.0/((Enviroment&)*env).get_criterion();
		}
		else
		{
			count =  ((Enviroment&)*env).get_cover_max() - count;
			fitness += real(count)/ real(((Enviroment&)*env).get_criterion() * ((Enviroment&)*env).get_cover_max());
		}
	}
	void Single::not_empty()
	{
		unsigned int count = 0;
		for(const ClassRoom& classroom : *this)
		{
			for(unsigned int i = 0; i < classroom.size(); i++)
			{
				if(classroom[i].week.count_hours() == 0)
				{
					count += WEEK_HOURS;
				}
			}
		}
		
		//
		if(count >  ((Enviroment&)*env).get_empty_max()) throw oct::core::Exception("El conteo de horas no deve exceder SCHEDULE_EMPTY_MAX",__FILE__,__LINE__);
		if(count == 0) 
		{
			std::cout << "\tnot empty count = " << count << "\n";
			fitness += 1.0/((Enviroment&)*env).get_criterion();
		}
		else
		{
			count =  ((Enviroment&)*env).get_empty_max() - count;
			fitness += real(count)/ real(((Enviroment&)*env).get_criterion() * ((Enviroment&)*env).get_empty_max());
		}
	}

}

