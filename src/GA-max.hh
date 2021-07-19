

#ifndef AE_GA_MAX_HH
#define AE_GA_MAX_HH

#include "GA.hh"


namespace ec::max
{
	class Enviroment;

	/**
	*\brief Representa nuestro conjunto de variables
	*/
	class Chromosome : public ec::Chromosome
	{
	public:
		Chromosome();
		geneUS getNumber() const;
		void mutate();

	private:
		geneUS gennumber;
		geneUS (*_combine)(const geneUS& gene);

	private:	
		geneUS combine1(const geneUS& gene);
		geneUS combine2(const geneUS& gene);
		geneUS combine3(const geneUS& gene);
		geneUS combine4(const geneUS& gene);
	};

	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public ec::Single
	{
	public:
		/**
		*\brief Constructor recive el ID del Individuo y el Ambiente
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
		virtual Population juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*);
		/**
		*\brief Imprime los datos relevantes del individuo
		*/
		virtual void print(std::ostream&) const;
	private:
		Chromosome chromo;
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

		virtual bool run();//temp for develop
		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();
	private:

	};

}

#endif