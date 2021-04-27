#include "GA-trans.hh"

namespace ae::ga
{

void TransEnviroment::creteRegion()
{
	//std::cout << "TransEnviroment::creteRegion Step 1\n";
	region = new nodes::Region(++countID,"Tesing");
	nodes::Target* target1;
	nodes::Node* nodeA;
	nodes::Node* nodeB;
	nodes::Edge* edge;

	//std::cout << "TransEnviroment::creteRegion Step 2\n";
	nodeA = region->newNode(++countID,nodes::NodeType::ORIGIN);//O
	nodeB = region->newNode(++countID);//66, ID = 3
	region->newEdgeBi(600,nodeA,nodeB);
	nodes::Node* node_66 = nodeB;
	nodes::Node* node_O = nodeA;

	//std::cout << "TransEnviroment::creteRegion Step 3\n";
	nodeA = nodeB;//66
	nodeB = region->newNode(++countID);//2, ID = 4
	region->newEdgeBi(200,nodeA,nodeB);

	nodeA = nodeB;//2
	nodeB = region->newNode(++countID);//3
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//3
	nodeB = region->newNode(++countID);//8
	region->newEdgeBi(600,nodeA,nodeB);
	
	nodeA = nodeB;//8
	nodeB = region->newNode(++countID);//9
	region->newEdgeBi(400,nodeA,nodeB);
	
	nodeA = nodeB;//9
	nodeB = region->newNode(++countID);//10
	region->newEdgeBi(300,nodeA,nodeB);
	nodes::Node* node_10 = nodeB;
	
	nodeA = nodeB;//10
	nodeB = region->newNode(++countID);//11
	region->newEdgeBi(400,nodeA,nodeB);
	nodes::Node* node_11 = nodeB;
	
	nodeA = nodeB;//11
	nodeB = region->newNode(++countID);//41
	region->newEdgeBi(300,nodeA,nodeB);
		
	nodeA = node_66;//66
	nodeB = region->newNode(++countID);//67
	region->newEdgeBi(300,nodeA,nodeB);	
		
	nodeA = nodeB;//67
	nodeB = region->newNode(++countID);//69
	region->newEdgeBi(300,nodeA,nodeB);
		
	nodeA = nodeB;//69
	nodeB = region->newNode(++countID);//73,ID = 13
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_73 = nodeB;
		
	nodeA = nodeB;//73
	nodeB = region->newNode(++countID);//72
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_72 = nodeB;
	
	nodeA = node_73;//73
	nodeB = region->newNode(++countID);//83
	region->newEdgeBi(800,nodeA,nodeB);
	nodes::Node* node_83 = nodeB;
	
	nodeA = nodeB;//83
	nodeB = region->newNode(++countID);//84
	region->newEdgeBi(300,nodeA,nodeB);

	nodeA = node_83;//83
	nodeB = region->newNode(++countID);//85
	region->newEdgeBi(200,nodeA,nodeB);

	nodeA = nodeB;//85
	nodeB = region->newNode(++countID);//86
	region->newEdgeBi(300,nodeA,nodeB);
	//std::cout << "TransEnviroment::creteRegion Step n\n";
	
	nodeA = node_11;//11
	nodeB = region->newNode(++countID);//41
	region->newEdgeBi(300,nodeA,nodeB);
	
	nodeA = nodeB;//41
	nodeB = region->newNode(++countID);//42
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//42
	nodeB = region->newNode(++countID);//14
	region->newEdgeBi(300,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
	
	nodeA = nodeB;//14
	nodeB = region->newNode(++countID);//58
	region->newEdgeBi(400,nodeA,nodeB);
	
	nodeA = nodeB;//58
	nodeB = region->newNode(++countID);//13
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB;//13
	nodeB = region->newNode(++countID);//19
	region->newEdgeBi(200,nodeA,nodeB);
	
	nodeA = nodeB;//19
	nodeB = region->newNode(++countID);//20
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB;//20
	nodeB = region->newNode(++countID);//21
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB;//21
	nodeB = region->newNode(++countID);//63
	region->newEdgeBi(200,nodeA,nodeB);
	
	nodeA = nodeB;//63
	nodeB = region->newNode(++countID);//24
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//24
	nodeB = region->newNode(++countID);//23
	region->newEdgeBi(200,nodeA,nodeB);
	
	nodeA = nodeB;//23
	nodeB = region->newNode(++countID);//25
	region->newEdgeBi(200,nodeA,nodeB);
	
	nodeA = nodeB;//25
	nodeB = region->newNode(++countID);//27
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//27
	nodeB = region->newNode(++countID);//31
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//31
	nodeB = region->newNode(++countID);//30
	region->newEdgeBi(700,nodeA,nodeB);
	
	nodeA = nodeB;//30
	nodeB = region->newNode(++countID);//32
	region->newEdgeBi(300,nodeA,nodeB);
			
	nodeA = nodeB;//32
	nodeB = region->newNode(++countID);//33
	region->newEdgeBi(300,nodeA,nodeB);
	
	nodeA = nodeB;//33
	nodeB = region->newNode(++countID);//43
	region->newEdgeBi(800,nodeA,nodeB);
	
	region->newEdgeBi(500,nodeB,node_O);//43 -> O

	nodeA = node_10; //10
	nodeB = region->newNode(++countID); //36
	region->newEdgeBi(200,nodeA,nodeB);
	
	nodeA = nodeB; //36
	nodeB = region->newNode(++countID); //12
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB; //12
	nodeB = region->newNode(++countID); //58
	region->newEdgeBi(200,nodeA,nodeB);

	
	
}

}