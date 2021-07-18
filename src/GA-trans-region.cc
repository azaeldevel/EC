

#include "GA-trans.hh"

namespace ec::trans
{

void Enviroment::creteRegion(std::list<nodes::Node*>& targets)
{
	//std::cout << "TransEnviroment::creteRegion Step 1\n";
	region = new nodes::Region(++countID,"Tesing");
	nodes::Target* target1;
	nodes::Node* nodeA;
	nodes::Node* nodeB;
	nodes::Edge* edge;

	//std::cout << "TransEnviroment::creteRegion Step 2\n";
	nodeA = region->newNode(++countID,nodes::NodeType::ORIGIN);//O ID:2
	nodeB = region->newNode(++countID);//ID:3
	region->newEdge(250,nodeA,nodeB);
	nodes::Node* node_O = nodeA;
	targets.push_back(node_O);

	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:4
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:5
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(300,nodeA,nodeB);//ID:6
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:7
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(250,nodeA,nodeB);//ID:8
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:9
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:10
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:11
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(50,nodeA,nodeB);//ID:12
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:13
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:14
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:15
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:16
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:17
	nodes::Node* node_17 = nodeB;
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(250,nodeA,nodeB);//ID:18
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:19
	nodes::Node* node_19 = nodeB;
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:20
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:21
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:22
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:23

	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:24
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(300,nodeA,nodeB);//ID:25
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:26
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(200,nodeA,nodeB);//ID:27
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:28
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(250,nodeA,nodeB);//ID:29
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(150,nodeA,nodeB);//ID:30
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,node_O,nodeB);//ID:31
	nodes::Node* node_31 = nodeB;
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:32
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(100,nodeA,nodeB);//ID:33
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(105,nodeA,nodeB);//ID:34
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);
	region->newEdge(110,nodeA,nodeB);//ID:35
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:36
	region->newEdge(188,nodeA,nodeB);
	
	nodeA = nodeB;
	region->newEdge(188,nodeA,node_19);
	
	nodeB = region->newNode(++countID);//ID:37
	region->newEdge(250,node_31,nodeB);

	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:38
	region->newEdge(100,nodeA,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:39
	region->newEdge(150,nodeA,nodeB);
	nodes::Node* node_39 = nodeB;
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:40
	region->newEdge(200,nodeA,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:41
	region->newEdge(200,nodeA,nodeB);
	
	region->newEdge(200,nodeB,node_17);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:42
	region->newEdge(150,node_39,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:43
	region->newEdge(100,nodeA,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:44
	region->newEdge(150,nodeA,nodeB);
	nodes::Node* node_44 = nodeB;
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:45
	region->newEdge(447,nodeA,nodeB);
	targets.push_back(nodeB);
	
	nodeB = region->newNode(++countID);//ID:46
	region->newEdge(200,node_44,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:47
	region->newEdge(150,nodeA,nodeB);
	
	nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:48
	region->newEdge(150,nodeA,nodeB);
	
	/*nodeA = nodeB;
	nodeB = region->newNode(++countID);//ID:
	region->newEdge(,nodeA,nodeB);*/
}

}