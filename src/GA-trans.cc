

#include "GA-trans.hh"

namespace ae::ga
{


namespace nodes
{


	Node::Node(ID i) : id(i),type(NodeType::UNKNOW)
	{

	}
	Node::Node(ID i,NodeType t) : id(i),type(t)
	{

	}
	Node::~Node()
	{

	}

	//getters
	ID Node::getID() const
	{
		return id;
	}
	NodeType Node::getType()const
	{
		return type;
	}
	Edge* Node::getFront(Index index)
	{
		std::list<Edge*>::iterator it = edgesFront.begin();
		std::advance(it, index);
		return *it;
	}
	/*std::list<Edge*>& Node::getListFront()
	{
		return edgesFront;
	}*/
	Index Node::getFrontCount()const
	{
		return edgesFront.size();
	}
	Edge* Node::getBack(Index index)
	{
		std::list<Edge*>::iterator it = edgesBack.begin();
		std::advance(it, index);
		return *it;
	}
	Index Node::getBackCount()const
	{
		return edgesBack.size();
	}
	
	//setters
	void Node::setType(NodeType t)
	{
		type = t;
	}


	//
	bool Node::isTrunk()const
	{
		return edgesFront.size() > 1 or edgesBack.size() > 1 ? true : false;
	}

	//
	void Node::addFront(Edge* e)
	{
		edgesFront.push_back(e);
	}
	void Node::addBack(Edge* e)
	{
		edgesBack.push_back(e);
	}
	Edge* Node::operator[](Index index)
	{
		std::list<Edge*>::iterator it = edgesFront.begin();
		std::advance(it, index);
		return *it;
	}	
	Edge* Node::nextLessTrans(bool direction)
	{
		std::list<Edge*>* edgeList;
		edgeList = direction? &edgesFront : &edgesBack;
		
		if(edgeList->size() == 0) return NULL;
		Edge* less = *edgeList->begin();
		if(less->getNextCount() == 0) return less;
		
		for(Edge* e : *edgeList)
		{
			if(e->getNextCount() == 0) return e;
			if(e->getNextCount() < less->getNextCount()) return less = e;
		}

		//std::cout << "TransEnviroment::nextLessTrans " << e->getID() << "\n";
		return less;
	}
	Edge* Node::nextLessTrans(Explored max,bool direction)
	{		
		std::list<Edge*>* edgeList;
		edgeList = direction? &edgesFront : &edgesBack;
		
		//std::cout << "TransEnviroment::nextLessTrans Step 1 node " << getID() << "\n";
		if(edgeList->empty()) return NULL;
		//std::cout << "TransEnviroment::nextLessTrans Step 2\n";
		for(Edge* e : *edgeList)
		{
			if(e->getNextCount() <  max) return e;
		}
		//std::cout << "TransEnviroment::nextLessTrans Step 3\n";
		return NULL;
	}








	


	

	Edge::Edge(unsigned int d,Node* a, Node* n)
	{
		distance = d;
		node = a;
		next = n;
		//node->addFront(this);
		//next->add(this);
		nextCount = 0 ;
		//prevCount = 0 ;
	}

	//getter
	Node* Edge::getNext()
	{
		return next;
	}
	Node* Edge::getNode()
	{
		return node;
	}
	
	Node* Edge::transNext()
	{
		nextCount++;
		return next;
	}
	/*Node* Edge::transPrev()
	{
		prevCount++;
		return prev;
	}*/
	unsigned short Edge::getNextCount()
	{
		return nextCount;
	}
	/*unsigned short Edge::getPrevCount()
	{
		return prevCount;
	}*/




	

	







	Region::Region(ID id, const std::string& name) : Node(id,NodeType::REGION),origin(NULL)
	{
		
	}
	Region::~Region()
	{
		for(Node* n : toDeleteNodes)
		{
			delete n;
		}		
		for(Edge* e : toDeleteEdges)
		{
			delete e;
		}
	}

	/*Street* Region::newStreet(ID id)
	{
		Street* n = new Street(id);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}*/
	/*Street* Region::newStreet(ID id,NodeType t)
	{
		Street* n = new Street(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}*/
	Node* Region::newNode(ID id)
	{
		Node* n = new Node(id);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}
	Node* Region::newNode(ID id,NodeType t)
	{
		Node* n = new Node(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}
	Edge* Region::newEdge(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		toDeleteEdges.push_back(e);
		return e;
	}
	void Region::newEdgeBi(unsigned int d,Node* a, Node* n)
	{
		Edge* e1 = new Edge(d,a,n);
		Edge* e2 = new Edge(d,n,a);
		a->addFront(e1);
		n->addBack(e2);
		toDeleteEdges.push_back(e1);
		toDeleteEdges.push_back(e2);
	}
	Node* Region::getOrigin()
	{
		return origin;
	}
}





TransChromosome::TransChromosome(const Path& p) : Chromosome("TransChromosome"),path(p)
{

}
TransChromosome::TransChromosome(const TransChromosome& obj) : Chromosome("TransChromosome"),path(obj.path)
{
	path = obj.path;
}
TransChromosome::~TransChromosome()
{
}

const TransChromosome& TransChromosome::operator = (const TransChromosome& obj)
{
	path = obj.path;

	return *this;
}

void TransChromosome::combine(const ae::Chromosome& P1,const ae::Chromosome& P2)
{

}
void TransChromosome::copy(const ae::Chromosome& P1)
{

}
void TransChromosome::mutate(float p)
{

}
void TransChromosome::randFill()
{

}
















TransSingle::TransSingle(const TransSingle& s) : Single(s),puntos(s.puntos),chromosome(s.chromosome)
{
}
TransSingle::TransSingle(ID id,Enviroment& e,const Junction& j, const Path& p) : Single(id,e,j),chromosome(p),puntos(0)
{
}
TransSingle::TransSingle(ID id,Enviroment& e, const Path& p) : Single(id,e),chromosome(p),puntos(0)
{
}

void TransSingle::eval()
{
	
}
void TransSingle::randFill()
{
}
void TransSingle::juncting(std::list<ae::Single*>& chils,ae::Single* single,unsigned short loglevel)
{
	
}
void TransSingle::save(std::ofstream& fn)
{
}
void TransSingle::print(std::ostream&) const
{

}







TransEnviroment::TransEnviroment()
{
	countID = 0;//contador de nodos
}
TransEnviroment::~TransEnviroment()
{
	if(region) delete region;
}


void TransEnviroment::generate(nodes::Node* n,unsigned short stop,bool direction)
{
	//std::cout << "TransEnviroment::generate Step 1\n";
	nodes::Edge* eN = n->nextLessTrans(stop);
	
	while(eN)
	{
		//std::cout << "TransEnviroment::generate Step 2\n";
		Path* newPath = new Path();
		//std::cout << "TransEnviroment::generate Step 3\n";
		eN->transNext();
		//std::cout << "TransEnviroment::generate Step 4\n";
		newPath->push_back(eN);
		//std::cout << "TransEnviroment::generate Step 5\n";
		lstPaths.push_back(newPath);
		//std::cout << "TransEnviroment::generate Step 6\n";		
		generate(newPath,eN,stop,direction);

		//net iteration
		eN = n->nextLessTrans(stop,direction);
	}
}
void TransEnviroment::generate(Path* path, nodes::Edge* eprev, unsigned short stop,bool direction)
{
	//std::cout << "TransEnviroment::generate2 Step 1\n";
	nodes::Node* n = eprev->getNext();
	nodes::Edge* eN = n->nextLessTrans(stop);
	//std::cout << "n = " << n->getID() << "\n";
	//std::cout << "TransEnviroment::generate2 Step 2 eN = " << eN << "\n";
	do
	{
		//std::cout << "TransEnviroment::generate2 Step 3\n";
		Path* newPath = NULL;
		if(eN)
		{
			newPath = new Path(*path);
			eN->transNext();
			newPath->push_back(eN);
			lstPaths.push_back(newPath);
			//std::cout << "TransEnviroment::generate2 Step 4\n";
		}
		
		if(n->getType() == nodes::UNKNOW and eN and newPath) generate(newPath,eN,stop,direction);
		
		//next iteration
		eN = n->nextLessTrans(stop,direction);
	}
	while(eN);
}
void TransEnviroment::initial()
{	
	std::cout << "Poblacion inicial..\n";
	std::vector<nodes::Node*> targets;
	creteRegion(targets);

	//
	for(nodes::Node* n : targets)
	{
		generate(n,1,true);
		generate(n,1,false);
	}
	
	//filtrar las rutas
	filterPaths();
	
	//generado individuos
	for(Path* path : lstPaths)
	{
 		TransSingle* s = new TransSingle(next(),*this,*path);
		push_back(s);
	}
	
	//liberando memoria de paths
	for(Path* path : lstPaths)
	{
		delete path;
	}
	lstPaths.clear();	
}
void TransEnviroment::selection()
{

}
/*bool TransEnviroment::run()
{
	initial();

	

	
	return true;
}*/

void TransEnviroment::print(nodes::Node* n)
{
	switch(n->getType())
	{
		case nodes::NodeType::TARGET:
			std::cout << "Target(" << n->getID() << ")" ;
			break;
		case nodes::NodeType::END:
			std::cout << "End("<< n->getID() << ")" ;
			break;
		case nodes::NodeType::ORIGIN:
			std::cout << "O("<< n->getID() << ")" ;
			break;
		default:
			std::cout << "(" << n->getID() << ")" ;
			break;
	}
}
void TransEnviroment::filterPaths()
{
	std::list<Path*> forDelete;
	for(Path* path : lstPaths)
	{
		nodes::Node* node = path->back()->getNode();
		
		//aceptar objetivos
		if(node->getType () != nodes::UNKNOW) continue;
		
		//aceptar esquinas,glorietas,
		if(node->isTrunk()) continue;

		//
		forDelete.push_back(path);
	}
	for(Path* path : forDelete)
	{
		delete path;
		lstPaths.remove(path);
	}
}
void TransEnviroment::evaluation()
{	
	std::cout << "Evaluacion..\n";
	TransSingle* single;
	for(ae::Single* s : *this)
	{
		single = (TransSingle*) s;
		std::cout << "ID : " << single->getID() << "\n";
		single->eval();
	}
}
void TransEnviroment::juncting()
{

}
void TransEnviroment::save()
{

}
}