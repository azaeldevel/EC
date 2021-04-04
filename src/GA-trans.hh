
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
		ID getID() const;
		//setter

		//funtions


	private:
		ID id; 
	};

	class Edge
	{
	public:
		Edge(unsigned int time,unsigned int distence,Node* prev, Node* next);

		//getters
		unsigned int getExplored() const;

		//funtions
		//void setNext(Node* n);
		//void setPrevius(Node* n);

	private:
		unsigned int explored;
		Node* next;
		Node* prev;
		unsigned int time;//in minutes
		unsigned int distance;//in meters
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
		Street* newStreet(ID id);
		Target* newTarget();
		Edge* newEdge(unsigned int time,unsigned int distence,Node* prev, Node* next);
	private: 
		std::string name;
		std::list<Node*> toDeleteNodes;
		std::list<Edge*> toDeleteEdges;
		
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


class TransEnviroment : public Enviroment
{
public:
	//
	
	//
	TransEnviroment();	
	TransEnviroment(const std::string& log);
	virtual ~TransEnviroment();
	void init();
	double getGamma() const;
	ae::Single* getRandomSingleTop()const;
	ae::Single* getRandomSingle()const;
	void saveSolutions(const std::string& dir)const;
	void saveSolutions(std::ofstream& f)const;
	void creteRegion();
	virtual void selection();
	virtual bool run();
private:
	nodes::Region* region;
	static ID countID;
};

}

#endif