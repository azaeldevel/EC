

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
	void Node::add(Edge* e)
	{
		edges.push_back(e);
	}


	

	Edge::Edge(unsigned int d,Node* p, Node* n)
	{
		distance = d;
		prev = p;
		next = n;
		prev->add(this);
		next->add(this);
	}
	Edge::Edge(unsigned int t,unsigned int d,Node* p, Node* n)
	{
		time = t;
		distance = d;
		prev = p;
		next = n;
		prev->add(this);
		next->add(this);
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
	Edge* Region::newEdge(unsigned int d,Node* p, Node* n)
	{
		Edge* e = new Edge(d,p,n);
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
	nodes::Target* target1;
	nodes::Node* node1;
	nodes::Node* node2;
	nodes::Edge* edge;

	node1 = region->newStreet(++countID);//O
	node2 = region->newStreet(++countID);//66
	region->newEdge(600,node1,node2);

	node1 = node2;//66
	node2 = region->newStreet(++countID);//2
	region->newEdge(200,node1,node2);

	node1 = node2;//2
	node2 = region->newStreet(++countID);//3
	region->newEdge(500,node1,node2);
	
	node1 = node2;//3
	node2 = region->newStreet(++countID);//8
	region->newEdge(600,node1,node2);
	
	
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