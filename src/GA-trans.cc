

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
	std::list<Edge*>& Node::getListFront()
	{
		return edgesFront;
	}
		
	//setters
	void Node::setType(NodeType t)
	{
		type = t;
	}
		
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
	Edge* Node::nextLessTrans()
	{
		if(edgesFront.size() == 0) return NULL;
		Edge* less = operator[](0);
		if(less->getNextCount() == 0) return less;
		
		for(Edge* e : edgesFront)
		{
			if(e->getNextCount() == 0) return e;
			if(e->getNextCount() < less->getNextCount()) return less = e;
		}

		//std::cout << "TransEnviroment::nextLessTrans " << e->getID() << "\n";
		return less;
	}
	Edge* Node::nextLessTrans(Explored max)
	{
		//std::cout << "TransEnviroment::nextLessTrans Step 1 node " << getID() << "\n";
		if(edgesFront.empty()) return NULL;
		//std::cout << "TransEnviroment::nextLessTrans Step 2\n";
		for(Edge* e : edgesFront)
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



TransEnviroment::TransEnviroment()
{
	init();
}
TransEnviroment::~TransEnviroment()
{
	if(region) delete region;
}


void TransEnviroment::generate(nodes::Node* n,unsigned short stop)
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
		generate(newPath,eN,stop);

		//net iteration
		eN = n->nextLessTrans(stop);
	}
}
void TransEnviroment::generate(Path* path, nodes::Edge* eprev, unsigned short stop)
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
		
		if(n->getType() != nodes::END and n->getType() != nodes::ORIGIN and eN) generate(newPath,eN,stop);
		
		//next iteration
		eN = n->nextLessTrans(stop);
	}
	while(eN);
}
void TransEnviroment::init()
{
	countID = 0;
	creteRegion();


	generate(region->getOrigin(),1);
	
	//std::cout << "TransEnviroment::init Step 3\n";
	for(Path* ls : lstPaths)
	{
		if(ls->size() > 0)
		{
			for(nodes::Edge* e : *ls)
			{				
				print(e->getNode());
				std::cout << " --> ";
			}
			if(ls->back()->getNext()) 
			{
				print(ls->back()->getNext());
			}
		}
		std::cout << "\n";
	}
	
}
void TransEnviroment::selection()
{

}
bool TransEnviroment::run()
{

	return true;
}

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
}