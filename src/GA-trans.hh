
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
	enum Direction
	{
		NOTDIRECT,
		FRONT,
		BACK
	};
	
	class Node
	{
	friend class Edge;
	friend class ec::trans::Enviroment;

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
		const std::list<Edge*>& getListFront()const;
		const std::list<Edge*>& getListBack()const;

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
		Edge* nextLessTrans(Direction direction);
		Edge* nextLessTrans(Explored max,Direction direction);
		
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
		void resetNextCount();
		
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
		void resetTrans();
		
	private: 
		std::string name;
		std::list<Node*> nodes;
		std::list<Edge*> edges;
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
	Path(nodes::Direction dir);
	Path(const Path*);
	Path(const Path*,nodes::Direction);
	Path(const Path*,const Path*);

	unsigned short getCountTargets()const;
	unsigned short getLength()const;
	nodes::Direction getDirection()const;

	//const nodes::Node* checkJunct(const Path*)const;
	//Population juncting(const Path*,std::list<Path*>& lp)const;
	bool juncting(Path*,Path*, unsigned short offset);
	virtual void print(std::ostream&) const;
	static void print(const nodes::Node* n,std::ostream&);
	unsigned short countTarget()const;
	bool growUp();
	nodes::Edge* randNext();
	
private:
	bool cutBefore(nodes::Node*);
	bool cutAfther(nodes::Node*);
	nodes::Direction direction;
};

class Chromosome : public ec::Chromosome
{
public:
	Chromosome(Path* path);
	Chromosome(const Chromosome& obj);
	virtual ~Chromosome();

	unsigned short getLengthPath()const;
	unsigned short getCountTagetsPath()const;
	const Path* getPath() const;
	Path* getPath();

	const Chromosome& operator = (const Chromosome&);	
	
	//Population juncting(const Chromosome*,std::list<Path*>& p)const;
	virtual void print(std::ostream&) const;
	bool growUp();

private:
	Path* path;
	bool reduce;
};


class Single : public ec::Single
{
public:
	Single(const Single&, const std::list<nodes::Node*>& targets);
	Single(ID id,Enviroment&, const Junction& junction, Path*, const std::list<nodes::Node*>& targets);
	Single(ID id,Enviroment&, Path*, const std::list<nodes::Node*>& targets);

	unsigned short getLengthPath()const;
	unsigned short getCountTagetsPath()const;
	const Chromosome* getChromosome()const;

	virtual void eval();
	virtual void randFill(bool favor = false);
	virtual Population juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*);
	virtual void save(std::ofstream& fn);
	virtual void print(std::ostream&) const;
	void print(nodes::Node&) const;	
	//Population juncting(const Single*,std::list<Path*>& p)const;
	bool growUp();
	
	bool checkRepitTarget(const Path* p)const;
	unsigned short checkOrder(const Path* p)const;
	nodes::Edge* find(nodes::Edge*);

private:
	unsigned short puntos;
	Chromosome chromosome;
	const std::list<nodes::Node*>& lstTargets;
};


class Enviroment : public ec::Enviroment
{
public:
	//
	
	//
	Enviroment();	
	Enviroment(const std::string& log);
	void init();
	virtual ~Enviroment();

	double getGammaLength() const;
	double getGammaTarget() const;
	const nodes::Region* getRegion()const;
	std::list<nodes::Node*> getTargets()const;
	double getFreactionQ()const;
	double getFreactionD()const;
	unsigned short getGenLengthMin() const;
	
	void saveSolutions(const std::string& dir)const;
	void saveSolutions(std::ofstream& f)const;
	void creteRegion(std::list<nodes::Node*>& targets);

	virtual void initial();
	virtual void selection();
	virtual void save();
private:
	void generate(nodes::Node* orig, unsigned short stop,nodes::Direction direction);
	void generate(nodes::Edge* orig, unsigned short stop,nodes::Direction direction);
	void generate(Path* path,nodes::Edge* e, unsigned short stop,nodes::Direction direction);
	void print(nodes::Node*);
	
	//	
	nodes::Region* region;
	std::list<Path*> lstPaths;
	nodes::ID countID;
	double gammaLength,gammaTarget;
	std::list<nodes::Node*> targets;
	double fractionQuality;
	double fractionDen;
	nodes::Direction direction;
	unsigned short genLengthMin;
};

}

#endif