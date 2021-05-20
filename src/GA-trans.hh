
#ifndef AE_GA_TRANS_HH
#define AE_GA_TRANS_HH

#include <octetos/core/MD5sum.hh>
#include <list>
#include <vector>


#include "GA.hh"


namespace ec::trans
{
class Enviroment;

namespace nodes
{
	class Edge;
	typedef unsigned long ID;
	typedef unsigned long Index;
	typedef unsigned long Explored;

	enum NodeType
	{
		UNKNOW,
		//NORNAL,
		ORIGIN, /*Nodo de origen*/
		END,/*Hacia afuera del grafo*/
		REGION, /*Subnodo*/
		TARGET, /*Nodo objetivo*/
		//UNION,
	};
	
	class Node
	{
	friend class Edge;
	public:
		Node(ID id);
		Node(ID id,NodeType type);
		virtual ~Node();

		//getters
		ID getID() const;
		NodeType getType()const;
		Edge* getFront(Index index);
		//std::list<Edge*>& getListFront();
		Index getFrontCount()const;
		Edge* getBack(Index index);
		Index getBackCount()const;

		//setter
		void setType(NodeType type);

		//
		bool isTrunk()const;
		//funtions
		/**
		*\brief Agrega un arista al nodo.
		*/
		void addFront(Edge* edge);
		void addBack(Edge* edge);
		Edge* operator[] (Index index);
		Edge* nextLessTrans(bool direction);
		Edge* nextLessTrans(Explored max,bool direction);
		
	private:
		ID id; 
		std::list<Edge*> edgesFront;
		std::list<Edge*> edgesBack;
		NodeType type;
	};

	class Edge
	{
	public:
		Edge(unsigned int distence,Node* actual, Node* next);
		//Edge(unsigned int time,unsigned int distence, Node* actual, Node* next);

		//getters
		Explored getExplored() const;

		//funtions
		//void setNext(Node* n);
		//void setPrevius(Node* n);
		Node* transNext();
		//Node* transPrev();
		virtual Node* getNext();
		Node* getNode();
		unsigned short getNextCount();
		//unsigned short getPrevCount();
		
	private:
		Explored explored;
		Node* next;
		Node* node;
		unsigned int time;//in minutes
		unsigned int distance;//in meters
		unsigned short nextCount;
		//unsigned short prevCount;
	};

	

	class Target : public Node
	{
	public:
		Target(ID id);
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
		Node* getOrigin();
		unsigned int getCountNodes()const;
		unsigned int getCountEdges()const;

		//funtions
		void connect(Node* from, Node* to);
		Node* newNode();
		Node* newNode(ID id);
		Node* newNode(ID id,NodeType type);
		//Street* newStreet(ID id);
		//Street* newStreet(ID id,NodeType type);
		Target* newTarget();
		Edge* newEdge(unsigned int time,unsigned int distence,Node* prev, Node* next);
		Edge* newEdge(unsigned int distence,Node* prev, Node* next);
		void newEdgeBi(unsigned int distence,Node* prev, Node* next);
		
	private: 
		std::string name;
		std::list<Node*> toDeleteNodes;
		std::list<Edge*> toDeleteEdges;
		Node* origin;
		unsigned int countNodes,countEdges;
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


//typedef std::list<nodes::Edge*> Path;
class Path : public std::list<nodes::Edge*>
{
public:
	Path();
	Path(const Path*);
	unsigned short getCountTargets()const;
};

class Chromosome : public ec::Chromosome
{
public:
	Chromosome(Path* path);
	Chromosome(const Chromosome& obj);
	virtual ~Chromosome();

	const Path& getPath()const;

	const Chromosome& operator = (const Chromosome&);	
	
	virtual void combine(const ec::Chromosome& P1,const ec::Chromosome& P2);
	virtual void copy(const ec::Chromosome& P1);
	virtual void mutate(float p);
	virtual void randFill(bool favor = false);
	
private:
	Path* path;
};


class Single : public ec::Single
{
public:
	Single(const Single&);
	Single(ID id,Enviroment&, const Junction& junction, Path*);
	Single(ID id,Enviroment&, Path*);
	
	virtual void eval();
	virtual void randFill(bool favor = false);
	virtual void juncting(std::list<ec::Single*>& chils,ec::Single* single,unsigned short loglevel);
	virtual void save(std::ofstream& fn);
	virtual void print(std::ostream&) const;
	void print(nodes::Node&) const;

private:
	unsigned short puntos;
	Chromosome chromosome;
};


class Enviroment : public ec::Enviroment
{
public:
	//
	
	//
	Enviroment();	
	Enviroment(const std::string& log);
	virtual ~Enviroment();

	double getGammaLength() const;
	double getGammaTarget() const;
	ec::Single* getRandomSingleTop()const;
	ec::Single* getRandomSingle()const;

	
	void saveSolutions(const std::string& dir)const;
	void saveSolutions(std::ofstream& f)const;
	void creteRegion(std::list<nodes::Node*>& targets);

	virtual void initial();
	virtual void selection();
	virtual bool run();
	virtual void eval();
	virtual void juncting();
	virtual void save();
private:
	void generate(nodes::Node* orig, unsigned short stop,bool direction);
	void generate(Path* path,nodes::Edge* e, unsigned short stop,bool direction);
	void filterPaths();
	void print(nodes::Node*);
	//	
	nodes::Region* region;
	std::list<Path*> lstPaths;
	nodes::ID countID;
	double gammaLength,gammaTarget;
	std::list<nodes::Node*> targets;
};

}

#endif