
#ifndef AE_GA_TRANS_HH
#define AE_GA_TRANS_HH

#include <octetos/core/MD5sum.hh>

#include "GA.hh"
#include <list>

namespace ae::ga
{

namespace nodes
{
	typedef unsigned long ID;
	
	class Node
	{
	public:
		Node(ID id);
		virtual ~Node();

		//getters
		unsigned int getExplored() const;
		//setter

		//funtions
		void setNext(Node* n);
		void setPrevius(Node* n);

	private:
		ID id; 
		unsigned int explored;
		Node* next;
		Node* prev;
	};

	class Street : public Node
	{
	public:
		Street(ID id);
		virtual ~Street();
	private: 

	};


	class Target : public Node
	{
	public:
		Target(ID id,const std::string& name);
		virtual ~Target();

		const std::string& getName()const;
	private: 
		std::string name;
	};

	class Region : public Node
	{
	public:
		Region(ID id, const std::string& name);
		virtual ~Region();

		//getters
		const std::string& getName()const;

		//funtions
		void connect(Node* from, Node* to);
		Node* newNode();
		Street* newStreet();
		Target* newTarget();
	private: 
		std::string name;
		std::list<Node*> toDelete;
	};

	class Colony : public Region
	{
	public:
		Colony(ID id, const std::string& name);
		virtual ~Colony();
		Region* newRegion();
	private: 
		std::list<Region*> toDelete;
	};


	class City : public Region
	{
	public:
		City(ID id, const std::string& name);
		virtual ~City();
		Colony* newColony();
		
	private: 
		std::list<Colony*> toDelete;
	};
}

class TransChromosome : public Chromosome
{
public:
	TransChromosome();
	TransChromosome(const TransChromosome& obj);
	virtual ~TransChromosome();

	const TransChromosome& operator = (const TransChromosome&);	
	
	virtual void combine(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void copy(const ae::Chromosome& P1);
	virtual void mutate(float p);
	virtual void randFill();
	
private:
	//std::list<Node*> path;
};


class TransSingle : public Single
{
public:
	TransSingle(const Single&);
	TransSingle(ID id,Enviroment&,const Junction& junction);
	TransSingle(ID id,Enviroment&);
};


}

#endif