
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
	friend class Region;
	friend class ec::trans::Enviroment;

	public:
		Node(ID id);
		Node(ID id,NodeType type);
		virtual ~Node();

		//getters
		ID getID() const;
		NodeType getType()const;
		/**
		*\brief 0 base index
		*/
		Edge* getFront(Index index);
		//std::list<Edge*>& getListFront();
		Index getFrontCount()const;
		/**
		*\brief 0 base index
		*/
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
		/**
		*\brief 0 base index
		*/
		Edge* operator[] (Index index);
		Edge* nextLessTrans(Direction direction);
		Edge* nextLessTrans(Explored max,Direction direction);
		Edge* randFront();
		Edge* randBack();
		unsigned short countFront()const;
		unsigned short countBack()const;

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
		Node* getNext();
		Node* getNode();
		const Node* getNode()const;
		unsigned short getNextCount();
		//unsigned short getPrevCount();
		void resetNextCount();
		unsigned int getDistence()const;
		
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
		//unsigned int getCountEdgesFront()const;
		//unsigned int getCountEdgesBack()const;
		unsigned int getLengthFront()const;
		unsigned int getLengthBack()const;

		//funtions
		void connect(Node* from, Node* to);
		Node* newNode();
		Node* newNode(ID id);
		Node* newNode(ID id,NodeType type);
		//Street* newStreet(ID id);
		//Street* newStreet(ID id,NodeType type);
		Target* newTarget();
		Edge* newEdge(unsigned int time,unsigned int distence,Node* prev, Node* next);
		Edge* newEdgeFront(unsigned int distence,Node* prev, Node* next);
		Edge* newEdgeBack(unsigned int distence,Node* prev, Node* next);
		void newEdgeBi(unsigned int distence,Node* prev, Node* next);
		
	private: 
		std::string name;
		std::list<Node*> nodes;
		//std::list<Edge*> edges;
		//unsigned int countEdgesFront;
		//unsigned int countEdgesBack;
		unsigned int lengthFront;
		unsigned int lengthBack;
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
	Path(const Path&);
	Path(const Path*,nodes::Direction);
	Path(const Path*,const Path*);

	const Path& operator =(const Path& );

	unsigned short getCountTargets()const;
	unsigned short getLength()const;
	nodes::Direction getDirection()const;
	const oct::core::StringMD5& getMD5()const;

	//const nodes::Node* checkJunct(const Path*)const;
	//Population juncting(const Path*,std::list<Path*>& lp)const;
	bool juncting(const Path* pB,const Path* pE, unsigned short offset);
	bool juncting(const Path* pB,const Path* pE,const nodes::Edge* e);
	virtual void print(std::ostream&) const;
	static void print(const nodes::Node* n,std::ostream&);
	unsigned short countTarget()const;
	//bool growUp();
	//nodes::Edge* randNext();
	void genMD5();
	void push_back(nodes::Edge*);
	void reverse(const Path*);
	nodes::Edge* find(nodes::Edge*);
	unsigned short countCorners() const;
	/**
	*\brief 1-based index, get the i-esimo coners in path
	*\return NULL if index is 0 or not found
	*/
	nodes::Edge* findCorner(unsigned short);
	/**
	*\brief 1-based index,  get the i-esimo target in path
	*\return NULL if index is 0 or not found
	*/
	nodes::Edge* findTarget(unsigned short);
	
	bool cutBefore(const nodes::Node*);
	bool cutAfther(const nodes::Node*);
	bool cutAfther(unsigned short point);

private:
	nodes::Direction direction;
	oct::core::StringMD5 md5;
};

class Chromosome : public ec::Chromosome
{
public:
	Chromosome(Path* path);
	Chromosome(const Path& path);
	Chromosome(const Chromosome& obj);
	virtual ~Chromosome();

	unsigned short getLengthPath()const;
	unsigned short getCountTagetsPath()const;
	const Path* getPath() const;
	Path* getPath();

	const Chromosome& operator = (const Chromosome&);	
	
	//Population juncting(const Chromosome*,std::list<Path*>& p)const;
	virtual void print(std::ostream&) const;
	//bool growUp();

private:
	Path* path;
	//bool reduce;
};


class Single : public ec::Single
{
public:
	Single(const Single&);
	Single(ID id,Enviroment&, const Junction& junction, Path*);
	Single(ID id,Enviroment&, Path*);
	virtual ~Single();

	unsigned short getLengthPath()const;
	unsigned short getCountTagetsPath()const;
	const Chromosome* getChromosome()const;

	virtual void eval();
	virtual void randFill(bool favor = false);
	virtual Population juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void*);
	//virtual Population juncting(std::list<ec::Single*>& chils,unsigned short loglevel,void*);
	virtual void save(std::ofstream& fn);
	virtual void print(std::ostream&) const;
	void print(nodes::Node&) const;	
	//Population juncting(const Single*,std::list<Path*>& p)const;
	bool growUp();
	
	bool checkRepitTarget(const Path* p)const;
	unsigned short checkOrder(const Path* p)const;
	//nodes::Edge* findTarget(nodes::Edge*, unsigned short i);

private:
	//unsigned short puntos;
	Chromosome chromosome;
};

struct Targets : public std::list<nodes::Node*>
{

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

	double getGammaLengthFront() const;
	double getGammaLengthBack() const;
	double getGammaTarget() const;
	const nodes::Region* getRegion()const;
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
	void generate(nodes::Node* orig, unsigned short stop,nodes::Direction direction);
	void print(nodes::Node*);
	
	//	
	nodes::Region* region;
	std::list<Path*> lstPaths;
	nodes::ID countID;
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

	nodes::Node* origin;
};

}

#endif