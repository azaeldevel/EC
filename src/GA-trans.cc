

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


	Edge::Edge(unsigned int t,unsigned int d,Node* p, Node* n)
	{
		time = t;
		distance = d;
		prev = p;
		next = n;
	}


	






	Street::Street(ID id) : Node(id)
	{

	}
	Street::~Street()
	{

	}










	Region::Region(ID id, const std::string& name) : Node(id)
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

		return n;
	}
	Edge* Region::newEdge(unsigned int t,unsigned int d,Node* p, Node* n)
	{
		Edge* e = new Edge(t,d,p,n);
		toDeleteEdges.push_back(e);
		return e;
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
void TransEnviroment::creteRegion()
{
	region = new nodes::Region(++countID,"Tesing");
	nodes::Node* node1;
	nodes::Node* node2;
	
	node1 = region->newStreet(++countID);
	node2 = region->newStreet(++countID);
	nodes::Edge* e = region->newEdge(5,1000,node1,node2);

	
	
}

ID TransEnviroment::countID = 0;
void TransEnviroment::init()
{
	region = NULL;
}

void TransEnviroment::selection()
{

}
bool TransEnviroment::run()
{

}


}