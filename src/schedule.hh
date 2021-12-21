

#ifndef EC_SCHEDULE_HH
#define EC_SCHEDULE_HH


#include "schedule-data.hh"



namespace oct::ec::sche
{
	
	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public oct::ec::Single, public Schedule
	{

	public:
		Single(ID id,Enviroment& env,const Junction& junction);
		/**
		*\brief Constructor que recive el ID del Individuo y el Ambiente
		*/
		Single(ID id,Enviroment& env, const Schedule&);
		Single(ID id,Enviroment& env);
		
		/**
		*\brief Evalua al individuo y asigna su valor de adaptabilidad(fitness)
		*/
		virtual void eval();		
		/**
		*\brief Crea un arcivo CSV con los datos relevantes del individuo
		*/
		virtual void save(std::ofstream& fn);		
		/**
		*\brief Realiza el apareo entre dos individuos
		*/
		virtual void juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single);
		/**
		*\brief Imprime los datos relevantes del individuo
		*/
		virtual void print(std::ostream&) const;

		virtual void mutate();
	private:
		/**
		*\brief Retorna la cantiad de traslapes que tiene los maestros
		*/
		unsigned int overlap_by_teacher()const;
		/**
		*\brief Retorna suma de la diferacia de horas entre los horasio asignados para cada materia y las horas de cada materia
		*/
		unsigned int diff_hour()const;
	private:
		//Schedule schedule;
		//const Data& data;
	};

	/**
	*\brief Variables de control y proceso
	*/
	class Enviroment : public oct::ec::Enviroment
	{
	public:

		/**
		*\brief Constructor que recive un directorio para guardar estadisticas
		*/
		Enviroment(const std::string& log,const std::string& dir);
		/**
		*\brief Inicia las variables
		*/
		void init();
		
		~Enviroment();
		
		/**
		*\brief Inicia el proceso de apareo, sobecragada devido a que deve distigir entre grupo para realizar el apareoa
		*/
		//virtual void juncting();

		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();

		unsigned int counter()const;

	private:
		std::string directory;
		Data data;
	};

}

#endif