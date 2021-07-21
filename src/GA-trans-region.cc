

#include "GA-trans.hh"

namespace ec::trans
{

void Enviroment::creteRegion(std::list<nodes::Node*>& targets)
{
	//std::cout << "TransEnviroment::creteRegion Step 1\n";
	region = new nodes::Region(++countID,"Tesing");
	
	//front
	nodes::Node* node_2 = region->newNode(++countID,nodes::NodeType::ORIGIN);//O ID:2
	nodes::Node* node_3 = region->newNode(++countID);//ID:3
	region->newEdgeFront(250,node_2,node_3);
	nodes::Node* node_O = node_2;
	targets.push_back(node_O);

	nodes::Node* node_4 = region->newNode(++countID);
	region->newEdgeFront(200,node_3,node_4);//ID:4
	
	nodes::Node* node_5 = region->newNode(++countID);
	region->newEdgeFront(100,node_4,node_5);//ID:5
	
	nodes::Node* node_6 = region->newNode(++countID);
	region->newEdgeFront(300,node_5,node_6);//ID:6
	
	nodes::Node* node_7 = region->newNode(++countID);
	region->newEdgeFront(150,node_6,node_7);//ID:7
	
	nodes::Node* node_8 = region->newNode(++countID);
	region->newEdgeFront(250,node_7,node_8);//ID:8
	
	nodes::Node* node_9 = region->newNode(++countID);
	region->newEdgeFront(200,node_8,node_9);//ID:9
	
	nodes::Node* node_10 = region->newNode(++countID);
	region->newEdgeFront(150,node_9,node_10);//ID:10
	
	nodes::Node* node_11 = region->newNode(++countID);
	region->newEdgeFront(100,node_10,node_11);//ID:11
	
	nodes::Node* node_12 = region->newNode(++countID);
	region->newEdgeFront(50,node_11,node_12);//ID:12
	
	nodes::Node* node_13 = region->newNode(++countID);
	region->newEdgeFront(150,node_12,node_13);//ID:13
	
	nodes::Node* node_14 = region->newNode(++countID);
	region->newEdgeFront(100,node_13,node_14);//ID:14
	
	nodes::Node* node_15 = region->newNode(++countID);
	region->newEdgeFront(200,node_14,node_15);//ID:15
	
	nodes::Node* node_16 = region->newNode(++countID);
	region->newEdgeFront(200,node_15,node_16);//ID:16
	
	nodes::Node* node_17 = region->newNode(++countID);
	region->newEdgeFront(200,node_16,node_17);//ID:17
	
	nodes::Node* node_18 = region->newNode(++countID);
	region->newEdgeFront(250,node_17,node_18);//ID:18
	
	nodes::Node* node_19 = region->newNode(++countID);
	region->newEdgeFront(100,node_18,node_19);//ID:19
	
	nodes::Node* node_20 = region->newNode(++countID);
	region->newEdgeFront(200,node_19,node_20);//ID:20
	
	nodes::Node* node_21 = region->newNode(++countID);
	region->newEdgeFront(150,node_20,node_21);//ID:21
	
	nodes::Node* node_22 = region->newNode(++countID);
	region->newEdgeFront(200,node_21,node_22);//ID:22
	
	//nodes::Node* node_23 = region->newNode(++countID);
	//region->newEdgeFront(150,node_22,node_23);//ID:23
	++countID;//mantener la soncornizacion con los nombres c++

	nodes::Node* node_24 = region->newNode(++countID);
	region->newEdgeFront(150,node_22,node_24);//ID:24
	
	nodes::Node* node_25 = region->newNode(++countID);
	region->newEdgeFront(300,node_24,node_25);//ID:25
	
	nodes::Node* node_26 = region->newNode(++countID);
	region->newEdgeFront(100,node_25,node_26);//ID:26
	
	nodes::Node* node_27 = region->newNode(++countID);
	region->newEdgeFront(200,node_26,node_27);//ID:27
	
	nodes::Node* node_28 = region->newNode(++countID);
	region->newEdgeFront(150,node_27,node_28);//ID:28
	
	nodes::Node* node_29 = region->newNode(++countID);
	region->newEdgeFront(250,node_28,node_29);//ID:29
	
	nodes::Node* node_30 = region->newNode(++countID);
	region->newEdgeFront(150,node_29,node_30);//ID:30
	std::cout << "node_30 = " << node_30->getID() << "\n";
	
	region->newEdgeFront(100,node_30,node_O);
	
	nodes::Node* node_31 = region->newNode(++countID);
	region->newEdgeFront(100,node_O,node_31);//ID:31
	
	nodes::Node* node_32 = region->newNode(++countID);
	region->newEdgeFront(100,node_31,node_32);//ID:32
	
	nodes::Node* node_33 = region->newNode(++countID);
	region->newEdgeFront(100,node_32,node_33);//ID:33
	
	nodes::Node* node_34 = region->newNode(++countID);
	region->newEdgeFront(105,node_33,node_34);//ID:34
	
	nodes::Node* node_35 = region->newNode(++countID);
	region->newEdgeFront(110,node_34,node_35);//ID:35
	
	nodes::Node* node_36 = region->newNode(++countID);//ID:36
	region->newEdgeFront(188,node_35,node_36);
	
	region->newEdgeFront(188,node_36,node_19);
	
	nodes::Node* node_37 = region->newNode(++countID);//ID:37
	region->newEdgeFront(250,node_31,node_37);
	
	nodes::Node* node_38 = region->newNode(++countID);//ID:38
	region->newEdgeFront(100,node_37,node_38);
	
	nodes::Node* node_39 = region->newNode(++countID);//ID:39
	region->newEdgeFront(150,node_38,node_39);
	
	nodes::Node* node_40 = region->newNode(++countID);//ID:40
	region->newEdgeFront(200,node_39,node_40);
	
	nodes::Node* node_41 = region->newNode(++countID);//ID:41
	region->newEdgeFront(200,node_40,node_41);
	
	region->newEdgeFront(200,node_41,node_17);
	
	nodes::Node* node_42 = region->newNode(++countID);//ID:42
	region->newEdgeFront(150,node_39,node_42);
	
	nodes::Node* node_43 = region->newNode(++countID);//ID:43
	region->newEdgeFront(100,node_42,node_43);
	
	nodes::Node* node_44 = region->newNode(++countID);//ID:44
	region->newEdgeFront(150,node_43,node_44);
	
	nodes::Node* node_45 = region->newNode(++countID);//ID:45
	region->newEdgeFront(447,node_44,node_45);
	node_45->setType(nodes::NodeType::TARGET);
	targets.push_back(node_45);
	
	nodes::Node* node_46 = region->newNode(++countID);//ID:46
	region->newEdgeFront(200,node_44,node_46);
	
	nodes::Node* node_47 = region->newNode(++countID);//ID:47
	region->newEdgeFront(150,node_46,node_47);
	
	nodes::Node* node_48 = region->newNode(++countID);//ID:48
	region->newEdgeFront(150,node_47,node_48);
	
	region->newEdgeFront(100,node_45,node_11);
	
	
	//back
	region->newEdgeBack(200,node_O,node_30);
	
	region->newEdgeBack(150,node_30,node_29);
	
	region->newEdgeBack(250,node_29,node_28);
	
	region->newEdgeBack(150,node_28,node_27);
	
	region->newEdgeBack(200,node_27,node_26);
	
	region->newEdgeBack(100,node_26,node_25);
	
	region->newEdgeBack(300,node_25,node_24);
	
	region->newEdgeBack(150,node_24,node_22);
	
	//region->newEdgeBack(100,node_23,node_22);
	
	region->newEdgeBack(200,node_22,node_21);
	
	region->newEdgeBack(150,node_21,node_20);
	
	region->newEdgeBack(200,node_20,node_19);
	
	region->newEdgeBack(100,node_19,node_18);
	
	region->newEdgeBack(250,node_18,node_17);
	
	region->newEdgeBack(200,node_17,node_16);
	
	region->newEdgeBack(200,node_16,node_15);
	
	region->newEdgeBack(200,node_15,node_14);
	
	region->newEdgeBack(100,node_14,node_13);
	
	region->newEdgeBack(150,node_13,node_12);
	
	region->newEdgeBack(50,node_12,node_11);
	
	region->newEdgeBack(100,node_11,node_10);
	
	region->newEdgeBack(150,node_10,node_9);
	
	region->newEdgeBack(200,node_9,node_8);
	
	region->newEdgeBack(250,node_8,node_7);
	
	region->newEdgeBack(150,node_7,node_6);
	
	region->newEdgeBack(300,node_6,node_5);
	
	region->newEdgeBack(100,node_5,node_4);
	
	region->newEdgeBack(200,node_4,node_3);
	
	region->newEdgeBack(250,node_3,node_O);
	
	region->newEdgeBack(100,node_31,node_O);
	
	region->newEdgeBack(100,node_32,node_31);
	
	region->newEdgeBack(100,node_33,node_32);
	
	region->newEdgeBack(105,node_34,node_33);
	
	region->newEdgeBack(110,node_35,node_34);
	
	region->newEdgeBack(188,node_36,node_35);
	
	region->newEdgeBack(200,node_19,node_36);
	
	region->newEdgeBack(100,node_37,node_3);
	region->newEdgeBack(100,node_3,node_37);
	
	region->newEdgeBack(100,node_38,node_37);
	
	region->newEdgeBack(150,node_39,node_38);
	
	region->newEdgeBack(200,node_40,node_39);
	
	region->newEdgeBack(200,node_41,node_40);
	
	region->newEdgeBack(200,node_17,node_41);
	
	region->newEdgeBack(150,node_42,node_39);
	
	region->newEdgeBack(100,node_43,node_42);
	
	region->newEdgeBack(150,node_44,node_43);
	
	region->newEdgeBack(447,node_45,node_44);
	
	region->newEdgeBack(200,node_46,node_44);
	
	region->newEdgeBack(150,node_47,node_46);
	
	region->newEdgeBack(150,node_48,node_47);
	
	region->newEdgeBack(100,node_45,node_48);
	
	region->newEdgeBack(100,node_11,node_45);
	
	//region->newEdgeFront(250,node_31,node_37);
	region->newEdgeBack(250,node_37,node_31);
	
	region->newEdgeFront(250,node_32,node_38);
	region->newEdgeBack(250,node_38,node_32);
	
	region->newEdgeFront(300,node_33,node_39);
	region->newEdgeBack(2300,node_39,node_33);
	
}

}