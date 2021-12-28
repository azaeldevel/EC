

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

	public:

		static const unsigned int WEEK_HOURS;
		static const unsigned int WEEK_HOURS2;
		static const unsigned int WEEK_HOURS3;

	private:
		
		/**
		*\brief Retorna la cantiad de traslapes que tiene los maestros
		*/
		void overlap_by_teacher();
		/**
		*\brief Retorna suma de la diferacia de horas entre los horasio asignados para cada materia y las horas de cada materia
		*/
		void cover();

		void not_empty();

		/**
		*\brief Asegura que las horas selecionas este dentro de un rango de desviacion esandar asignado
		*/
		void signam_hours();
		real signam_hours(const ClassRoom&);
		real signam_hours(const Lesson&);
	private:


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
		void init(const std::string&);
		
		~Enviroment();
		
		const Data& get_data()const;

		unsigned int get_criterion()const;
		unsigned int get_overlap_max() const;
		unsigned long get_overlap_max2() const;
		unsigned int get_cover_max() const;
		unsigned long get_cover_max2() const;
		unsigned int get_empty_max() const;
		unsigned int get_sigma_hours_max() const;
		unsigned int get_sigma_hours_max2() const;
		unsigned int get_sigma_hours_limit() const;

		//real get_gamma() const;
		//double get_portion() const;
		//unsigned int get_schedule_max_hours() const;
		

		/**
		*\brief Inicia el proceso de apareo, sobecragada devido a que deve distigir entre grupo para realizar el apareoa
		*/
		//virtual void juncting();

		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();

		void select_times(Lesson&,const WeekOptions&);

		//unsigned int counter()const;

	private:
		std::string directory;
		Data data;	
		
		unsigned int CRITERION;
		//real PORTION;
		//real GAMMA;
		//unsigned int schedule_max_hours;
		unsigned int schedule_overlap_max;
		unsigned long schedule_overlap_max2;
		unsigned int schedule_cover_max;
		unsigned long schedule_cover_max2;
		unsigned int SCHEDULE_EMPTY_MAX;
		//real SCHEDULE_ERROR;
		real schedule_sigma_hours_max;
		real schedule_sigma_hours_max2;
		real schedule_sigma_hours_limit;
	};

}

#endif