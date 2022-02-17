

#ifndef AE_GA_MAX_HH
#define AE_GA_MAX_HH

#include "ec.hh"


namespace oct::ec::prog
{

	class Enviroment;

	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public oct::ec::Single
	{
	public:
		/**
		*\brief Constructor que recive el ID del Individuo y el Ambiente
		*/
		Single(Enviroment& env);

		/**
		*\brief Evalua al individuo y asigna su valor de adaptabilidad(fitness)
		*/
		virtual void eval();
		/**
		*\brief Crea un arcivo CSV con los datos relevantes del individuo
		*/
		virtual void save(Save&);
		/**
		*\brief Realiza el apareo entre dos individuos
		*/
		virtual void juncting(std::list<ec::Single*>& chils,const ec::Single* single);
		/**
		*\brief Imprime los datos relevantes del individuo
		*/
		virtual void print(std::ostream&) const;

		virtual void mutate();
	private:

	};

	/**
	*\brief Variables de control y proceso
	*/
	class Enviroment : public ec::Enviroment
	{
	public:
		/**
		*\brief Constructor que solomante llama a init
		*/
		Enviroment();
		/**
		*\brief Constructor que recive un directorio para guardar estadisticas
		*/
		Enviroment(const std::string& log);
		/**
		*\brief Inicia las variables
		*/
		void init();
		~Enviroment();


		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();
	private:

	};

}

#endif
