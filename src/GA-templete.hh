

#ifndef AE_GA_MAX_HH
#define AE_GA_MAX_HH

#include "GA.hh"


namespace ec::alg
{
	
	class Chromosome : public ec::Chromosome
	{
	public:
	
	private:
		geneUS gennumber;
	};

	class Single : public ec::Single
	{
	public:
		virtual void eval();
		virtual void save(std::ofstream& fn);
		virtual Population juncting(std::list<Single*>& chils,const Single* single,unsigned short loglevel,void*);
		virtual void print(std::ostream&) const;
	private:
		
	};

	class Enviroment : public ec::Enviroment
	{
	public:	
		Enviroment();
		Enviroment(const std::string& log);	
		virtual void selection();
		virtual void initial();
		virtual void save();
	private:

	};

}

#endif