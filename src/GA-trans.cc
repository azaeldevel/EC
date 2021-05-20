
#include <octetos/core/Error.hh>



#include "GA-trans.hh"

namespace ec::trans
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
		countNodes = 0;
		countEdges = 0;
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
	
	unsigned int Region::getCountNodes()const
	{
		return countNodes;
	}
	unsigned int Region::getCountEdges()const
	{
		return countEdges;
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
		countNodes++;
		
		return n;
	}
	Node* Region::newNode(ID id,NodeType t)
	{
		Node* n = new Node(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		countNodes++;
		
		return n;
	}
	Edge* Region::newEdge(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		toDeleteEdges.push_back(e);
		countEdges++;
		
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
		countEdges++;
	}
	Node* Region::getOrigin()
	{
		return origin;
	}
}





Chromosome::Chromosome(Path* p) : ec::Chromosome("trans::Chromosome"),path(p)
{

}
Chromosome::Chromosome(const Chromosome& obj) : ec::Chromosome("TransChromosome"),path(obj.path)
{
	path = obj.path;
}
Chromosome::~Chromosome()
{
}

const Chromosome& Chromosome::operator = (const Chromosome& obj)
{
	path = obj.path;

	return *this;
}

void Chromosome::combine(const ec::Chromosome& P1,const ec::Chromosome& P2)
{

}
void Chromosome::copy(const ec::Chromosome& P1)
{

}
void Chromosome::mutate(float p)
{

}
void Chromosome::randFill(bool favor)
{

}
const Path& Chromosome::getPath() const
{
	return *path;
}











	Path::Path()
	{	
	}
	Path::Path(const Path* p) : std::list<nodes::Edge*>(*p)
	{
	
	}
unsigned short Path::getCountTargets()const
{
	unsigned short count  = 0;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode()->getType() != nodes::NodeType::UNKNOW) count++;
	}
		
	return count;
}
	
	
	
	
	

















Single::Single(const Single& s) : ec::Single(s),puntos(s.puntos),chromosome(s.chromosome)
{
}
Single::Single(ID id,Enviroment& e,const Junction& j, Path* p) : ec::Single(id,e,j),chromosome(p),puntos(0)
{
}
Single::Single(ID id,Enviroment& e, Path* p) : ec::Single(id,e),chromosome(p),puntos(0)
{
}

void Single::eval()
{
	double flength = ((Enviroment*)env)->getGammaLength() * double(chromosome.getPath().size());
	//std::cout << "l : " << double(chromosome.getPath().size()) << "\n";
	double fTarget = ((Enviroment*)env)->getGammaTarget() * double(chromosome.getPath().getCountTargets());
	fitness = flength + fTarget;
	//if(flength > 1.0) print(std::cout);
	
}
void Single::randFill(bool favor)
{
}
void Single::juncting(std::list<ec::Single*>& chils,ec::Single* single,unsigned short loglevel)
{
	
}
void Single::save(std::ofstream& fn)
{
}
void Single::print(std::ostream& p) const
{
	Path::const_iterator actual, post;
	
	actual = chromosome.getPath().begin();
	post = chromosome.getPath().begin();
	do
	{
		std::advance(post,1);
		(*actual)->getNext();
		//(*post)->getNode();
		p << (*actual)->getNode()->getID() << "->";
		std::advance(actual,1);
	}
	while(post != chromosome.getPath().end());
	//p << (*post)->getNode()->getID() << "\n";	
}
void Single::print(nodes::Node&) const
{

}






Enviroment::Enviroment()
{
	countID = 0;//contador de nodos
}
Enviroment::~Enviroment()
{
	if(region) delete region;
}

double Enviroment::getGammaLength() const
{
	return gammaLength;
}
double Enviroment::getGammaTarget() const
{
	return gammaTarget;
}

void Enviroment::generate(nodes::Node* n,unsigned short stop,bool direction)
{
	//std::cout << "TransEnviroment::generate Step 1\n";
	nodes::Edge* eN = n->nextLessTrans(stop,direction);
	
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
void Enviroment::generate(Path* path, nodes::Edge* eprev, unsigned short stop,bool direction)
{
	//std::cout << "TransEnviroment::generate2 Step 1\n";
	nodes::Node* n = eprev->getNext();
	nodes::Edge* eN = n->nextLessTrans(stop,direction);
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
void Enviroment::initial()
{	
	//std::cout << "Poblacion inicial..\n";
	creteRegion(targets);
	gammaLength = 0.5 / double(region->getCountEdges());
	//std::cout << "Count : " << region->getCountEdges() << "\n";
	//std::cout << "gammaLength : " << gammaLength << "\n";
	gammaTarget = 0.5 / double(targets.size());
	//std::cout << "Count : " << targets.size() << "\n";
	//std::cout << "gammaTarget : " << gammaTarget << "\n";
	//ec::Enviroment::epsilon = gammaLength;

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
 		Single* s = new Single(nextID(),*this,path);
		push_back(s);
	}
	
	//liberando memoria de paths
	lstPaths.clear();
	
		
}
void Enviroment::selection()
{

}

bool Enviroment::run()
{
	initial();
	std::cout << "Initial : " << size() << "\n";
	
	eval();
	
	return true;
}

void Enviroment::print(nodes::Node* n)
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
void Enviroment::filterPaths()
{
	std::list<Path*> forDelete;
	for(Path* path : lstPaths)
	{
		nodes::Node* nodeF = path->front()->getNode();
		nodes::Node* nodeB = path->back()->getNode();
				
		//aceptar esquinas,glorietas,
		//if(nodeB->isTrunk()) continue;
		
		//aceptar los que ban del origne a los extremos
		if(nodeF->getType() == nodes::ORIGIN and nodeB->getType() == nodes::END) continue;
		
		//aceptar los que ban del origne a los target
		if(nodeF->getType() == nodes::ORIGIN and nodeB->getType() == nodes::TARGET) continue;
		
		//aceptar los que ban del target a los target
		if(nodeF->getType() == nodes::TARGET and nodeB->getType() == nodes::TARGET) continue;
		
		//aceptar los que ban del extremo al origen
		if(nodeF->getType() == nodes::END and nodeB->getType() == nodes::ORIGIN) continue;

		//aceptar los teinet un target en un extremo
		if(nodeF->getType() == nodes::TARGET or nodeB->getType() == nodes::TARGET) continue;
		
		//
		forDelete.push_back(path);
	}
	for(Path* path : forDelete)
	{
		delete path;
		lstPaths.remove(path);
	}
}
void Enviroment::eval()
{
	//std::cout << "Evaluacion..\n";
	Single* single;
	for(ec::Single* s : *this)
	{
		single = (Single*) s;
		single->eval();
		//std::cout << "ID : " << single->getID() << " => " << single->getFitness() << "\n";
	}
}
void Enviroment::juncting()
{

}
void Enviroment::save()
{

}
}