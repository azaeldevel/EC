

#ifndef EC_SCHEDULE_HH
#define EC_SCHEDULE_HH


#include "schedule-data.hh"



namespace oct::ec::sche
{
	class Enviroment;


	typedef unsigned int Child;

	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public oct::ec::Single, public Schedule
	{

	public:
		Single(Enviroment& env,unsigned int);
		/**
		*\brief Constructor que recive el ID del Individuo y el Ambiente
		*/
		//Single(ID id,Enviroment& env, const Schedule&);
		Single(Enviroment& env);

		/**
		*\brief Evalua al individuo y asigna su valor de adaptabilidad(fitness)
		*/
		virtual void eval();


		/**
		*\brief Crea un arcivo CSV con los datos relevantes del individuo
		*/
		virtual void save(Save& fn);
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
		static unsigned int jump_saver;

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
		void sigma_hours();
		real sigma_hours(const ClassRoom&);
		real sigma_hours(const Lesson&);


		/**
		*\brief Asegura que si la clase es de mas de una horas sean continuas
		*/
		void unique_class();//TODO: implementar

		/**
		*\brief Cuando los horaios no son continuos la interseccion no produce los resutados esperados, esta funcion esta pensada realizar una verificacion de esta situacion
		*/
		// un ejemplo seria el horario de un salon con una hora de receso difernete al la hora de una clase nommal,
		// en esta caso al asignar un profeso que puede cubir desde el inico del dia hasta un horario cualquiere que sobrepase el recreo
		// el horario del maestro despues de recreo no coincidira con el horario del salon despues del recreo al no condicerar en el horario
		// del maestro este salto en el tiempo.
		bool bound_schedule()const; //TODO:implemetar


		/*void juncting_mesh_lessons(const Single&,const Single&);
		void juncting_mesh_classroom(const Single&,const Single&);
		void juncting_half(const Single&,const Single&);
		void juncting_choose_one_lesson(const Single&,const Single&);
		void juncting_choose_random_lesson(const Single&,const Single&);*/

	private:
		typedef void (Schedule::*algorit)(const Schedule&,const Schedule&);

		algorit random_algorit();
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
		Enviroment(const std::string& log,const std::string& dir,const std::string& out_dir);
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

		void select_times(Lesson&,const WeekHours&);
		//void random_complete_times(Lesson&,const WeekOptions&);

		//unsigned int counter()const;

	private:
		std::string input_directory;
		Data data;
		std::string strid;

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
