

#ifndef AE_GA_MAX_HH
#define AE_GA_MAX_HH

#include "GA.hh"


namespace ec::max
{
	
	class Enviroment;

	class Chromosome : public ec::Chromosome
	{
	public:
		geneUS combine(const geneUS& P1,const geneUS& P2);
		geneUS mutate(const geneUS& P1);

	private:
		geneUS gennumber;
	};

	class Single : public ec::Single
	{
	public:
		Single(ID id,Enviroment& env);

		virtual void eval();
		virtual void save(std::ofstream& fn);
		virtual Population juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*);
		virtual void print(std::ostream&) const;
	private:
		
	};

	class Enviroment : public ec::Enviroment
	{
	public:	
		Enviroment();
		Enviroment(const std::string& log);	
		void init();
		~Enviroment();

		virtual void selection();
		virtual void initial();
	private:

	};

}

#endif