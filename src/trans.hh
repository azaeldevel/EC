
#ifndef AE_GA_TRANS_HH
#define AE_GA_TRANS_HH

#include <octetos/core/MD5sum.hh>
#include <list>
#include <vector>


#include "GA.hh"


namespace oct::ec::trans
{
class Enviroment;
typedef unsigned long Index;
typedef unsigned long ID;

namespace nodes
{
	class Node
	{

	};
}
class Chromosome : public oct::ec::Chromosome
{
public:
	Chromosome();
	virtual ~Chromosome();

	unsigned short getLengthPath()const;
	unsigned short getCountTagetsPath()const;

	const Chromosome& operator = (const Chromosome&);	
	
	virtual void print(std::ostream&) const;

private:
};


class Single : public oct::ec::Single
{
public:
	Single(const Single&);
	virtual ~Single();

	virtual void eval();
	virtual void randFill(bool favor = false);
	virtual Population juncting(std::list<oct::ec::Single*>& chils,const oct::ec::Single* single,unsigned short loglevel,void*);
	virtual void save(std::ofstream& fn);
	virtual void print(std::ostream&) const;
	unsigned int checkOrder()const;
	

private:
	Chromosome chromosome;
};

struct Targets : public std::list<nodes::Node*>
{

};

class Enviroment : public oct::ec::Enviroment
{
public:
	//
	
	//
	Enviroment();	
	Enviroment(const std::string& log);
	void init();
	virtual ~Enviroment();

	double getGammaLengthFront() const;
	double getGammaLengthBack() const;
	double getGammaTarget() const;
	const Targets& getTargets()const;
	double getFreactionQ()const;
	double getFreactionD()const;
	unsigned short getGenLengthMin() const;
	bool get_direction()const;
	
	void saveSolutions(const std::string& dir)const;
	void saveSolutions(std::ofstream& f)const;
	void creteRegion(std::list<nodes::Node*>& targets);

	virtual void initial();
	//virtual void selection();

protected:
	unsigned short threads;

private:
	void generate(nodes::Node* orig, unsigned short stop);
	void print(nodes::Node*);
	
	//	
	ID countID;
	double gammaLengthFront,gammaLengthBack,gammaTarget;
	Targets targets;
	double fractionQuality;
	double fractionDen;
	//nodes::Direction direction;
	unsigned short genLengthMin;
	/**
	*\brief true si la direccion es importante false si no
	*/
	bool direction;

};

}

#endif