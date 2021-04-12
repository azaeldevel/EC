

#include "GA-trans.hh"

namespace ae::ga
{


namespace nodes
{



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








	


	

	Edge::Edge(unsigned int d,Node* a, Node* n)
	{
		distance = d;
		node = a;
		next = n;
		node->add(this);
		//next->add(this);
		nextCount = 0 ;
		//prevCount = 0 ;
	}
	Edge::Edge(unsigned int t,unsigned int d,Node* a, Node* n)
	{
		time = t;
		distance = d;
		node = a;
		next = n;
		node->add(this);
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






	Street::Street(ID id,NodeType t) : Node(id,t)
	{

	}
	Street::~Street()
	{

	}










	Region::Region(ID id, const std::string& name) : Node(id,nodes::NodeType::Group),origin(NULL)
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

	
	Street* Region::newStreet(ID id,NodeType t)
	{
		Street* n = new Street(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
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
	//std::cout << "TransEnviroment::generate Step 0\n";	
	nodes::Node* n;
	//std::cout << "TransEnviroment::generate Step 0.1\n";
	std::list<nodes::Edge*>::iterator itE = l->end();
	//std::cout << "TransEnviroment::generate Step 0.2\n";
	itE--;
	//std::cout << "TransEnviroment::generate Step 0.3\n";
	n = (*itE)->getNext();//ultimo nodo
	//std::cout << "TransEnviroment::generate Step 0.4\n";
	nodes::Edge* newE;
	std::list<nodes::Edge*>* newL;
	//std::cout << "TransEnviroment::generate Step 1\n";
	
nextAdd:
	//std::cout << "TransEnviroment::generate Step 2\n";
	newE = n->nextLessTrans();//siguiente arista menos utilizado	
	if(newE)
	{
		std::cout << "TransEnviroment::generate Step 2.1 ID =" << n->getID() << "\n";
		if(newE->getNextCount() < stop)
		{
			//std::cout << "TransEnviroment::generate Step 2.1.1\n";
			newL = new std::list<nodes::Edge*>(*l);
			newL->push_back(newE);
			lstPaths.push_back(newL);//se crea neeva ruta
			newE->transNext();
			//std::cout << "TransEnviroment::generate Step 2.1.2\n";
			goto nextAdd;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}		
}
void TransEnviroment::init()
{
	//std::cout << "TransEnviroment::init Step 1\n";
	//crea la ciudad de pruebas
	creteRegion();

	//std::cout << "TransEnviroment::init Step 2\n";
	std::list<nodes::Edge*>* pthO = new std::list<nodes::Edge*>();		
	//std::cout << "TransEnviroment::init Step 2.1\n";
	nodes::Edge* e0 = (*region->getOrigin())[0];
	//std::cout << "TransEnviroment::init Step 2.2\n";
	pthO->push_back(e0);
	lstPaths.push_back(pthO);
	//std::cout << "TransEnviroment::init Step 2.3\n";
	e0->transNext();
	//std::cout << "TransEnviroment::init Step 3\n";
	
	//
	for(unsigned int i = 0; i < 10; i++)
	{
		for(std::list<nodes::Edge*>* ls : lstPaths)
		{
			generate(ls,1);
		}
	}
	for(std::list<nodes::Edge*>* ls : lstPaths)
	{
		std::list<nodes::Edge*>::iterator itB = ls->begin();
		nodes::Edge* eB = *itB;
		nodes::Node* nB = eB->getNode();
		std::cout << "Node : " << nB->getID();
		if(ls->size() > 1)
		{
			std::list<nodes::Edge*>::iterator itE = ls->end();
			nodes::Edge* eE = *(itE--);
			nodes::Node* nE = eE->getNode();
			std::cout << " --> " << nE->getID() << "\n";
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


}