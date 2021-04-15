

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
		if(edges.size() == 0) return NULL;
		Edge* less = operator[](0);
		if(less->getNextCount() == 0) return less;
		
		for(Edge* e : edges)
		{
			if(e->getNextCount() == 0) return e;
			if(e->getNextCount() < less->getNextCount()) return less = e;
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
	Edge* Region::newEdge(unsigned int t,unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(t,d,a,n);
		toDeleteEdges.push_back(e);
		return e;
	}
	Edge* Region::newEdge(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
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
void TransEnviroment::generate(Path* l,unsigned short stop)
{
	//std::cout << "TransEnviroment::generate Step 0\n";	
	nodes::Node* n = l->back()->getNext();
	//std::cout << "TransEnviroment::generate Step 0.1\n";
	//Path::iterator itE = l->end();
	//std::cout << "TransEnviroment::generate Step 0.2\n";
	//itE--;
	//std::cout << "TransEnviroment::generate Step 0.3\n";
	//n = (*itE)->getNext();//ultimo nodo
	//std::cout << "TransEnviroment::generate Step 0.4\n";
	nodes::Edge *newE = NULL, *newEtemp = NULL;
	Path* newL;
	//std::cout << "TransEnviroment::generate Step 1\n";
	
nextAdd:
	//std::cout << "TransEnviroment::generate Step 2 n =" << n << "\n";
	newEtemp = n->nextLessTrans();//siguiente arista menos utilizado
	if(newEtemp == newE) return;
	newE = newEtemp;
	//std::cout << "TransEnviroment::generate Step 2.1.1 newE =" << newE << ", ID = " << newE->getNode()->getID() << "\n";
	if(newE)
	{	
		//std::cout << "TransEnviroment::generate Step 2.1.2 \n";
		if(newE->getNextCount() < stop)
		{
			//std::cout << "TransEnviroment::generate Step 2.1.3\n";
			newL = new Path(*l);
			newL->push_back(newE);
			lstPaths.push_back(newL);//se crea neeva ruta
			newE->transNext();
			//std::cout << "TransEnviroment::generate Step 2.1.4 : " << newE << "," << newE->getNode() << "\n";
			goto nextAdd;
		}
		else
		{
			//std::cout << "TransEnviroment::generate Step 2.2\n";
			return;
		}
	}
	else
	{
		//std::cout << "TransEnviroment::generate Step 2.3\n";
		return;
	}
	//std::cout << "TransEnviroment::generate Step 2.4\n";
}
void TransEnviroment::init()
{
	//std::cout << "TransEnviroment::init Step 1\n";
	//crea la ciudad de pruebas
	creteRegion();

	//std::cout << "TransEnviroment::init Step 2\n";
	Path* pthO = new Path();		
	//std::cout << "TransEnviroment::init Step 2.1\n";
	nodes::Edge* e0 = (*region->getOrigin())[0];
	//std::cout << "TransEnviroment::init Step 2.2\n";
	pthO->push_back(e0);
	lstPaths.push_back(pthO);
	//std::cout << "TransEnviroment::init Step 2.3\n";
	e0->transNext();
	
	
	//
	for(unsigned int i = 0; i < 30; i++)
	{
		for(Path* ls : lstPaths)
		{
			generate(ls,1);
		}
	}
	//std::cout << "TransEnviroment::init Step 3\n";
	for(Path* ls : lstPaths)
	{
		/*Path::iterator itB = ls->begin();
		nodes::Edge* eB = *itB;
		nodes::Node* nB = eB->getNode();
		std::cout << "Node : " << nB->getID();
		if(ls->size() > 0)
		{
			//Path::const_iterator itE = ls->back();
			nodes::Edge* eE = ls->back();
			//std::cout << "eE --> " << eE << "\n";
			//std::cout << " count  " << ls->size() << "\n";
			nodes::Node* nE = eE->getNode();
			std::cout << " --> " << nE->getID();
		}*/
		std::cout << "| --> ";
		if(ls->size() > 0)
		{
			for(nodes::Edge* e : *ls)
			{
				std::cout << e->getNode()->getID()  << " --> " ;
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


}