

#include "GA-trans.hh"

namespace ae::ga
{


namespace nodes
{



	Node::Node(ID i) : id(i)
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
		
	void Node::add(Edge* e)
	{
		edges.push_back(e);
	}
	Edge* Node::operator[](Index index)
	{
		std::list<Edge*>::iterator it = edges.begin();
		std::advance(it, index);
		return *it;
	}	
	Edge* Node::nextLessTrans()
	{
		Edge* less = operator[](0);
		for(Edge* e : edges)
		{
			if(e->getNextCount() == 0) return e;
			if(e->getNextCount() < less->getNextCount()) less = e;
		}

		return less;
	}








	


	

	Edge::Edge(unsigned int d,Node* p, Node* n)
	{
		distance = d;
		prev = p;
		next = n;
		prev->add(this);
		next->add(this);
		nextCount = 0 ;
		prevCount = 0 ;
	}
	Edge::Edge(unsigned int t,unsigned int d,Node* p, Node* n)
	{
		time = t;
		distance = d;
		prev = p;
		next = n;
		prev->add(this);
		next->add(this);
		nextCount = 0 ;
		prevCount = 0 ;
	}

	//getter
	Node* Edge::getNext()
	{
		return next;
	}
	Node* Edge::getPrev()
	{
		return prev;
	}
	
	Node* Edge::transNext()
	{
		nextCount++;
		return next;
	}
	Node* Edge::transPrev()
	{
		prevCount++;
		return prev;
	}
	unsigned short Edge::getNextCount()
	{
		return nextCount;
	}
	unsigned short Edge::getPrevCount()
	{
		return prevCount;
	}






	Street::Street(ID id) : Node(id)
	{

	}
	Street::~Street()
	{

	}










	Region::Region(ID id, const std::string& name) : Node(id),origin(NULL)
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

	
	Street* Region::newStreet(ID id)
	{
		Street* n = new Street(id);
		toDeleteNodes.push_back(n);
		if(!origin) origin = n;
		return n;
	}
	Edge* Region::newEdge(unsigned int t,unsigned int d,Node* p, Node* n)
	{
		Edge* e = new Edge(t,d,p,n);
		toDeleteEdges.push_back(e);
		return e;
	}
	Edge* Region::newEdge(unsigned int d,Node* p, Node* n)
	{
		Edge* e = new Edge(d,p,n);
		toDeleteEdges.push_back(e);
		return e;
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


ID TransEnviroment::countID = 0;
void TransEnviroment::generate(std::list<nodes::Edge*>* l,unsigned short stop)
{
	for(nodes::Edge* e : *l)
	{
		
	}
}
void TransEnviroment::generate(std::list<nodes::Edge*>* l, nodes::Edge* e,unsigned short stop)
{
	nodes::Node* n = e->getPrev();
	nodes::Edge* newE = n->nextLessTrans();
	
	if(newE->getNextCount() > stop) return;
	
	nodes::Node* newN = newE->transNext();
	std::list<nodes::Edge*>* newL = new std::list<nodes::Edge*>(*l);
	
}
void TransEnviroment::init()
{
	//crea la ciudad de pruebas
	creteRegion();

	//
	std::list<nodes::Edge*>* pthO = new std::list<nodes::Edge*>();
	pthO->push_back((*region->getOrigin())[0]);
	lstPaths.push_back(pthO);
	for(std::list<nodes::Edge*>* ls : lstPaths)
	{		
		std::list<nodes::Edge*>::iterator it = ls->begin();
		nodes::Edge* e = *it;
		nodes::Node* n = e->getPrev();
		std::cout << "Node : " << n->getID() << "\n";
		
		generate(ls,1);
	}
	
}
void TransEnviroment::selection()
{

}
bool TransEnviroment::run()
{

	return true;
}


}