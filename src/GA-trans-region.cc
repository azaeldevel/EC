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
	nodeA = region->newNode(++countID,nodes::NodeType::ORIGIN);//O
	nodeB = region->newNode(++countID);//66, ID = 3
	region->newEdgeBi(600,nodeA,nodeB);
	nodes::Node* node_66 = nodeB;
	nodes::Node* node_O = nodeA;
	targets.push_back(node_O);

	//std::cout << "TransEnviroment::creteRegion Step 3\n";
	nodeA = nodeB;//66
	nodeB = region->newNode(++countID);//2, ID = 4
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_2 = nodeB;
	
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
	nodes::Node* node_42 = nodeB;
	
	nodeA = nodeB;//42
	nodeB = region->newNode(++countID);//14
	region->newEdgeBi(300,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
	targets.push_back(nodeB);
	
	nodeA = nodeB;//14
	nodeB = region->newNode(++countID);//58
	region->newEdgeBi(400,nodeA,nodeB);
	
	nodeA = nodeB;//58
	nodeB = region->newNode(++countID);//13
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB;//13
	nodeB = region->newNode(++countID);//19
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_19 = nodeB;
	
	nodeA = nodeB;//19
	nodeB = region->newNode(++countID);//20
	region->newEdgeBi(100,nodeA,nodeB);
	
	nodeA = nodeB;//20
	nodeB = region->newNode(++countID);//21
	region->newEdge(100,nodeA,nodeB);
	nodes::Node* node_21 = nodeB;
	
	nodeA = nodeB;//21
	nodeB = region->newNode(++countID);//63
	region->newEdge(200,nodeA,nodeB);
	nodes::Node* node_63 = nodeB;
	
	nodeA = nodeB;//63
	nodeB = region->newNode(++countID);//24
	region->newEdge(500,nodeA,nodeB);
	nodes::Node* node_24 = nodeB;
	
	nodeA = nodeB;//24
	nodeB = region->newNode(++countID);//23
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_23 = nodeB;
	
	nodeA = nodeB;//23
	nodeB = region->newNode(++countID);//25
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_25 = nodeB;
	
	nodeA = nodeB;//25
	nodeB = region->newNode(++countID);//27
	region->newEdgeBi(500,nodeA,nodeB);
	nodes::Node* node_27 = nodeB;
	
	nodeA = nodeB;//27
	nodeB = region->newNode(++countID);//31
	region->newEdgeBi(500,nodeA,nodeB);
	
	nodeA = nodeB;//31
	nodeB = region->newNode(++countID);//30
	region->newEdgeBi(700,nodeA,nodeB);
	nodes::Node* node_30 = nodeB;
	
	nodeA = nodeB;//30
	nodeB = region->newNode(++countID);//32
	region->newEdgeBi(300,nodeA,nodeB);
	nodes::Node* node_32 = nodeB;
			
	nodeA = nodeB;//32
	nodeB = region->newNode(++countID);//33
	region->newEdgeBi(300,nodeA,nodeB);
	nodes::Node* node_33 = nodeB;
	
	nodeA = nodeB;//33
	nodeB = region->newNode(++countID);//43
	region->newEdgeBi(800,nodeA,nodeB);
	nodes::Node* node_43 = nodeB;
	//print(node_43);
	
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

	nodeA = node_2; //2
	nodeB = region->newNode(++countID); //7
	region->newEdgeBi(600,nodeA,nodeB);
	nodes::Node* node_7 = nodeB;
	
	nodeA = nodeB; //7
	nodeB = region->newNode(++countID); //65
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_65 = nodeB;
	
	nodeA = nodeB; //65
	nodeB = region->newNode(++countID); //17
	region->newEdgeBi(400,nodeA,nodeB);
	nodes::Node* node_17 = nodeB;
		
	nodeA = nodeB; //17
	nodeB = region->newNode(++countID); //18
	region->newEdgeBi(200,nodeA,nodeB);
	nodes::Node* node_18 = nodeB;

	nodeA = nodeB; //18
	nodeB = region->newNode(++countID); //57
	region->newEdgeBi(100,nodeA,nodeB);
	nodes::Node* node_57 = nodeB;
	
	region->newEdgeBi(200,nodeB,node_24);
		
	nodeA = node_43; //43
	nodeB = region->newNode(++countID); //44
	region->newEdgeBi(1000,nodeA,nodeB);
		
	nodeA = nodeB; //44
	nodeB = region->newNode(++countID); //90
	region->newEdgeBi(300,nodeA,nodeB);
		
	nodeA = nodeB; //90
	nodeB = region->newNode(++countID); //45
	region->newEdgeBi(300,nodeA,nodeB);	
		
	nodeA = nodeB; //45
	nodeB = region->newNode(++countID); //46
	region->newEdgeBi(600,nodeA,nodeB);
		
	nodeA = nodeB; //46
	nodeB = region->newNode(++countID); //47
	region->newEdgeBi(1100,nodeA,nodeB);
		
	nodeA = nodeB; //47
	nodeB = region->newNode(++countID); //60
	region->newEdgeBi(400,nodeA,nodeB);
		
	nodeA = nodeB; //60
	nodeB = region->newNode(++countID); //61
	region->newEdgeBi(800,nodeA,nodeB);
		
	nodeA = nodeB; //61
	nodeB = region->newNode(++countID); //56
	region->newEdgeBi(500,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
		
	nodeA = nodeB; //56
	nodeB = region->newNode(++countID); //91
	region->newEdgeBi(1400,nodeA,nodeB);
		
	nodeA = nodeB; //91
	nodeB = region->newNode(++countID); //6
	region->newEdgeBi(200,nodeA,nodeB);
		
	nodeA = nodeB; //6
	nodeB = region->newNode(++countID); //5
	region->newEdgeBi(300,nodeA,nodeB);
		
	nodeA = nodeB; //5
	nodeB = region->newNode(++countID); //4
	region->newEdgeBi(200,nodeA,nodeB);
		
	region->newEdgeBi(200,nodeB,node_2);
		
	nodeA = node_7; //7
	nodeB = region->newNode(++countID); //37
	region->newEdgeBi(300,nodeA,nodeB);
		
	nodeA = node_65; //65
	nodeB = region->newNode(++countID); //35
	region->newEdgeBi(300,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
	targets.push_back(nodeB);
	
	nodeA = node_33; ///33
	nodeB = region->newNode(++countID); //34
	region->newEdgeBi(300,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
	targets.push_back(nodeB);
		
	nodeA = node_32; //32
	nodeB = region->newNode(++countID); //38
	region->newEdgeBi(300,nodeA,nodeB);
	nodeB->setType(nodes::NodeType::TARGET);
	targets.push_back(nodeB);
		
	nodeA = node_30;//30
	nodeB = region->newNode(++countID);//29
	region->newEdgeBi(500,nodeA,nodeB);
	nodes::Node* node_29 = nodeB;
		
	nodeA = nodeB; //29
	nodeB = region->newNode(++countID); //28
	region->newEdgeBi(300,nodeA,nodeB);
	
	region->newEdgeBi(300,nodeB,node_27);
	
	region->newEdgeBi(300,node_29,node_18);
		
	nodeA = node_42; //42
	nodeB = region->newNode(++countID); //92
	region->newEdgeBi(700,nodeA,nodeB);
		
	nodeA = nodeB; //92
	nodeB = region->newNode(++countID); //15
	region->newEdgeBi(400,nodeA,nodeB);
		
	nodeA = nodeB; //15
	nodeB = region->newNode(++countID); //26
	region->newEdgeBi(300,nodeA,nodeB);
	nodes::Node* node_26 = nodeB;
	
	region->newEdgeBi(900,node_26,node_25);
	
	nodeB = region->newNode(++countID);//62
	region->newEdge(900,node_57,nodeB);
	
	nodeA = nodeB; //62
	nodeB = region->newNode(++countID); //19
	region->newEdgeBi(400,nodeA,node_19);
	nodes::Node* node_62 = nodeB;
	
	nodeA = node_21;//21
	nodeB = region->newNode(++countID); //22
	region->newEdgeBi(100,nodeA,nodeB);
	nodes::Node* node_22 = nodeB;
	
	region->newEdgeBi(700,nodeB,node_23);

	region->newEdgeBi(141,node_26,node_22);

	region->newEdgeBi(141,node_22,node_63);

	region->newEdgeBi(141,node_63,node_62);

	region->newEdgeBi(173,node_62,node_17);
	
	
	
}

}