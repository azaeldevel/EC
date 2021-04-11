
#ifndef AE_GA_TRANS_HH
#define AE_GA_TRANS_HH

#include <octetos/core/MD5sum.hh>
#include <list>


#include "GA.hh"


namespace ae::ga
{

namespace nodes
{
	class Edge;
	typedef unsigned long ID;
	typedef unsigned long Index;

	enum NodeType
	{
		Normal,
		Origin,
		Out,
		Group
	};
	class Node
	{
	friend class Edge;
	public:
		Node(ID id,NodeType type);
		virtual ~Node();

		//getters
		ID getID() const;
		
		//setter

		//funtions
		/**
		*\brief Agrega un arista al nodo.
		*/
		void add(Edge* edge);
		Edge* operator[] (Index index);
		Edge* nextLessTrans();
		
	private:
		ID id; 
		std::list<Edge*> edges;
		NodeType type;
	};

	class Edge
	{
	public:
		Edge(unsigned int distence,Node* prev, Node* next);
		Edge(unsigned int time,unsigned int distence, Node* prev, Node* next);

		//getters
		unsigned int getExplored() const;

		//funtions
		//void setNext(Node* n);
		//void setPrevius(Node* n);
		Node* transNext();
		Node* transPrev();
		Node* getNext();
		Node* getPrev();
		unsigned short getNextCount();
		unsigned short getPrevCount();

	private:
		unsigned int explored;
		Node* next;
		Node* prev;
		unsigned int time;//in minutes
		unsigned int distance;//in meters
		unsigned short nextCount;
		unsigned short prevCount;
	};

	class Street : public Node
	{
	public:
		Street(ID id,NodeType type);
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
		Street* newStreet(ID id,NodeType type);
		Target* newTarget();
		Edge* newEdge(unsigned int time,unsigned int distence,Node* prev, Node* next);
		Edge* newEdge(unsigned int distence,Node* prev, Node* next);
		Node* getOrigin();
		
	private: 
		std::string name;
		std::list<Node*> toDeleteNodes;
		std::list<Edge*> toDeleteEdges;
		Node* origin;
		
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
	void generate(std::list<nodes::Edge*>*,unsigned short stop);
	void generate(std::list<nodes::Edge*>*,nodes::Edge*,unsigned short stop);
	
	//	
	nodes::Region* region;
	static ID countID;
	std::list<std::list<nodes::Edge*>*> lstPaths;
};

}

#endif