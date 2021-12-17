

#include "schedule.hh"

#include <octetos/core/MD5sum.hh>


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
		//TODO:evaluar la opcion 'Menor cantidad de dias', 'Mayor cantidad de dias'
	}
	
	
	
}

