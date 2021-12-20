

#ifndef AE_GA_MAX_HH
#define AE_GA_MAX_HH

#include "GA.hh"


namespace oct::ec::max
{
	class Enviroment;

	/**
	*\brief Representa nuestro conjunto de variables
	*/
	class Chromosome : public oct::ec::Chromosome
	{
	public:
		typedef geneUS (Chromosome::*pfnCombine)(const geneUS&);

	public:
		Chromosome();
		Chromosome(geneUS,pfnCombine);
		geneUS getNumber() const;
		pfnCombine getCombine()const;

		
		geneUS combination(const geneUS& gene);
		static geneUS mutate(const geneUS& gene);
		static geneUS randGenNumber();
		static pfnCombine randCombine();

	private:
		geneUS gennumber;
		pfnCombine combine;

	private:	
		geneUS combine1(const geneUS& gene);
		geneUS combine2(const geneUS& gene);
		geneUS combine3(const geneUS& gene);
		geneUS combine4(const geneUS& gene);

	};

	/**
	*\brief Representa una posible solucion a nuestro problema
	*/
	class Single : public oct::ec::Single
	{
	public:
		//Single(const Chromosome& ch);
		Single(ID, Enviroment&, geneUS g,Chromosome::pfnCombine f);
		/**
		*\brief Constructor recive el ID del Individuo y el Ambiente
		*/
		Single(ID id,Enviroment& e);
		
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
		Chromosome chromo;
	};

	/**
	*\brief Variables de control y proceso
	*/
	class Enviroment : public oct::ec::Enviroment
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

		Enviroment(int argc, const char* argv[]);
		/**
		*\brief Inicia las variables
		*/
		void init();
		~Enviroment();

		//virtual bool run();//temp for develop
		/**
		*\brief Crea la poblacion inicial
		*/
		virtual void initial();
	private:

	};

}

#endif