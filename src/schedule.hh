

#ifndef EC_SCHEDULE_HH
#define EC_SCHEDULE_HH

#include "GA.hh"

#include "schedule-data.hh"



namespace oct::ec::sche
{	
	


	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public oct::ec::Single
	{
	public:
		/**
		*\brief Constructor que recive el ID del Individuo y el Ambiente
		*/
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
		virtual Population juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single,unsigned short loglevel,void*);
		/**
		*\brief Imprime los datos relevantes del individuo
		*/
		virtual void print(std::ostream&) const;
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
		void init();
		
		~Enviroment();
	
		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();

		void pulverize_hours(core::DataTime& t1,core::DataTime& t2,std::vector<core::DataTime>& out);

		void testing();
	private:
		std::string directory;
		Pile pile;
		Data data;
	};

}

#endif