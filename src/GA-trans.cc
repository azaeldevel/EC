
#include <octetos/core/Error.hh>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "GA-trans.hh"

namespace ec::trans
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
		if(index > 0)std::advance(it, index);
		return *it;
	}

	Index Node::getFrontCount()const
	{
		return edgesFront.size();
	}
	Edge* Node::getBack(Index index)
	{
		std::list<Edge*>::iterator it = edgesBack.begin();
		if(index > 0)std::advance(it, index);
		return *it;
	}
	Index Node::getBackCount()const
	{
		return edgesBack.size();
	}
	
	//setters
	void Node::setType(NodeType t)
	{
		type = t;
	}


	//
	bool Node::isTrunk()const
	{
		return edgesFront.size() > 1 or edgesBack.size() > 1 ? true : false;
	}

	//
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
		if(index > 0) std::advance(it, index);
		return *it;
	}	
	Edge* Node::nextLessTrans(Direction direction)
	{
		std::list<Edge*>* edgeList;
		if (direction == Direction::FRONT) edgeList = &edgesFront;
		if (direction == Direction::BACK) edgeList = &edgesBack;
		
		if(edgeList->size() == 0) return NULL;
		Edge* less = *edgeList->begin();
		if(less->getNextCount() == 0) return less;
		
		for(Edge* e : *edgeList)
		{
			if(e->getNextCount() == 0) return e;
			if(e->getNextCount() < less->getNextCount()) return less = e;
		}

		//std::cout << "TransEnviroment::nextLessTrans " << e->getID() << "\n";
		return less;
	}
	Edge* Node::nextLessTrans(Explored max,Direction direction)
	{		
		std::list<Edge*>* edgeList;
		
		if (direction == Direction::FRONT) edgeList = &edgesFront;
		if (direction == Direction::BACK) edgeList = &edgesBack;
		
		if(edgeList->empty()) return NULL;
		for(Edge* e : *edgeList)
		{
			if(e->getNextCount() <  max) return e;
		}
		return NULL;
	}

	const std::list<Edge*>& Node::getListFront()const
	{
		return edgesFront;
	}
	const std::list<Edge*>& Node::getListBack()const
	{
		return edgesBack;
	}
	Edge* Node::randFront()
	{		
		if(edgesFront.size() == 0) return NULL;
		if(edgesFront.size() == 1) return *edgesFront.begin();

		double rand = randNumber (0.0,double(edgesFront.size()));
		
		std::list<Edge*>::iterator it = edgesFront.begin();
		std::advance(it,rand);
		return *it;		
	}
	Edge* Node::randBack()
	{		
		if(edgesBack.size() == 0) return NULL;
		if(edgesBack.size() == 1) return *edgesBack.begin();

		double rand = randNumber (0.0,double(edgesBack.size()));
		
		std::list<Edge*>::iterator it = edgesBack.begin();
		std::advance(it,rand);
		return *it;		
	}
	
	unsigned short Node::countFront()const
	{
		return edgesFront.size();
	}
	unsigned short Node::countBack()const
	{
		return edgesBack.size();
	}





	


	

	Edge::Edge(unsigned int d,Node* a, Node* n)
	{
		distance = d;
		node = a;
		next = n;
		nextCount = 0 ;
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
	const Node* Edge::getNode() const
	{
		return node;
	}
	
	Node* Edge::transNext()
	{
		nextCount++;
		return next;
	}
	unsigned short Edge::getNextCount()
	{
		return nextCount;
	}

	
	void Edge::resetNextCount()
	{
		nextCount = 0;
	}
	unsigned int Edge::getDistence()const
	{
		return distance;
	}
	
	
	

	







	Region::Region(ID id, const std::string& name) : Node(id,NodeType::REGION),origin(NULL)
	{
		//countNodes = 0;
		lengthFront = 0;
		lengthBack = 0;
	}
	Region::~Region()
	{
		for(Node* n : nodes)
		{
			for(Edge* e : n->edgesFront)
			{
				delete e;
			}
			for(Edge* e : n->edgesBack)
			{
				delete e;
			}
			delete n;
		}
	}
	
	unsigned int Region::getCountNodes()const
	{
		return nodes.size();
	}
	/*unsigned int Region::getCountEdgesFront()const
	{
		return countEdgesFront;
	}
	unsigned int Region::getCountEdgesBack()const
	{
		return countEdgesBack;
	}*/
	unsigned int Region::getLengthFront()const
	{
		return lengthFront;
	}
	unsigned int Region::getLengthBack()const
	{
		return lengthBack;
	}

	Node* Region::newNode(ID id)
	{
		Node* n = new Node(id);
		nodes.push_back(n);
		//if(origin == NULL) origin = n;//si no hay nodo origne registrado
		//countNodes++;
		
		return n;
	}
	Node* Region::newNode(ID id,NodeType t)
	{
		Node* n = new Node(id,t);
		nodes.push_back(n);
		if(t == NodeType::ORIGIN) origin = n;//si no hay nodo origne registrado
		//countNodes++;
		
		return n;
	}
	Edge* Region::newEdgeFront(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		a->addFront(e);
		lengthFront += d;
		
		return e;
	}
	Edge* Region::newEdgeBack(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		//std::cout << "(" << a->getID() << ")-->(" << n->getID() << ")\n";
		a->addBack(e);
		lengthBack += d;
		
		return e;
	}

	Node* Region::getOrigin()
	{
		return origin;
	}

}





Chromosome::Chromosome(Path* p) : ec::Chromosome("trans::Chromosome")
{
	path = p;
}
Chromosome::Chromosome(const Path& p) : ec::Chromosome("trans::Chromosome")
{
	path = new Path(p);
}
Chromosome::Chromosome(const Chromosome& obj) : ec::Chromosome("trans::Chromosome")
{
	path = new Path(*obj.path);
}
Chromosome::~Chromosome()
{
	delete path;
}

const Chromosome& Chromosome::operator = (const Chromosome& obj)
{
	path = obj.path;

	return *this;
}

void Chromosome::print(std::ostream& p) const
{
	path->print(p);
}
unsigned short Chromosome::getLengthPath()const
{
	return path->getLength();
}
unsigned short Chromosome::getCountTagetsPath()const
{
	return path->getCountTargets();
}
const Path* Chromosome::getPath()const
{
	return path;
}
Path* Chromosome::getPath()
{
	return path;
}





Path::Path(nodes::Direction d) : direction(d)
{	
}
Path::Path() : direction(nodes::Direction::NOTDIRECT)
{	
}
Path::Path(const Path& obj)
{
	operator =(obj);	
}
Path::Path(const Path* pb,const Path* pe)
{
	if(pb->size() == 0) throw octetos::core::Exception("La Path de incio esta vacia.",__FILE__,__LINE__);
	if(pe->size() == 0) throw octetos::core::Exception("La Path de fin esta vacia.",__FILE__,__LINE__);

	for(nodes::Edge* e : *pb)
	{
		push_back(e);
	}
	for(nodes::Edge* e : *pe)
	{
		push_back(e);
	}
	genMD5();
}
Path::Path(const Path* p,nodes::Direction d) : std::list<nodes::Edge*>(*p), direction(d)
{
	genMD5();
}
const Path& Path::operator = (const Path& obj)
{
	for(nodes::Edge* e : obj)
	{
		push_back(e);
	}
	direction = obj.direction;
	md5 = obj.md5;
	
	return *this;
}
unsigned short Path::getCountTargets()const
{
	unsigned short count  = 0;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode()->getType() != nodes::NodeType::UNKNOW) count++;
	}
		
	return count;
}
nodes::Direction Path::getDirection()const
{
	return direction;
}
const oct::core::StringMD5& Path::getMD5()const
{
	return md5;
}

bool Path::juncting(const Path* pB,const Path* pE,unsigned short offset)
{	
	std::list<nodes::Edge*>::const_iterator itB = pB->begin();
	std::list<nodes::Edge*>::const_iterator itE = pE->begin();
	std::advance(itB,offset);
	std::advance(itE,offset);
	nodes::Edge* eB = *itB;
	nodes::Edge* eE = *itE;
	if(eB->getNode() == eE->getNode() and eB->getNext() != eE->getNext())
	{
		Path pB(pB);
		Path pE(pE);	
		if(offset > 1)
		{
			pB.cutAfther(eB->getNode());
			pE.cutBefore(eB->getNode());
		}
		Path(&pB,&pE);
		genMD5();
		return true;
	}
	else
	{
		throw octetos::core::Exception("Los Paths indicado no tiene la coincidencia indicada",__FILE__,__LINE__);
	}
}
bool Path::juncting(const Path* pB,const Path* pE,const nodes::Edge* e)
{	
	std::list<nodes::Edge*>::const_iterator itB = std::find(pB->begin(),pB->end(),e);
	std::list<nodes::Edge*>::const_iterator itE = std::find(pE->begin(),pE->end(),e);
	
	if(itB == pB->end()) return false;
	if(itE == pE->end()) return false;
		
	if((*itB)->getNode() == (*itE)->getNode() and (*itB)->getNext() != (*itE)->getNext())
	{
		Path tempB(*pB);
		Path tempE(*pE);	
		tempB.cutAfther(e->getNode());
		tempE.cutBefore(e->getNode());
		Path(&tempB,&tempE);
		genMD5();
		return true;
	}
	else
	{
		throw octetos::core::Exception("Los Paths indicado no tiene la coincidencia indicada",__FILE__,__LINE__);
	}
}
bool Path::cutBefore(const nodes::Node* n)
{
	std::list<nodes::Edge*> toDelete;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode() == n)
		{
			toDelete.push_back(e);
			break;
		}
		else
		{
			toDelete.push_back(e);
		}
	}	
	for(nodes::Edge* e : toDelete)
	{
		remove(e);
	}
	
	return true;
}
bool Path::cutAfther(const nodes::Node* n)
{
	std::list<nodes::Edge*> toDelete;
	bool cut = false;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode() == n)
		{
			cut = true;
		}
		else
		{
			if(cut) toDelete.push_back(e);
		}
	}
	for(nodes::Edge* e : toDelete)
	{
		remove(e);
	}
	return true;
}
void Path::print(std::ostream& p) const
{
	const_iterator last = end();
	last--;
	for(const_iterator it = begin();it != end();it++)
	{
		print((*it)->getNode(),p);
		if(last != it) p << "->";
	}
}
unsigned short Path::getLength()const
{
	unsigned short length = 0;
	for(nodes::Edge* e : *this)
	{
		length += e->getDistence();
	}
	
	return length;
}
void Path::print(const nodes::Node* n,std::ostream& out)
{
	switch(n->getType())
	{
		case nodes::NodeType::TARGET:
			out << "Target(" << n->getID() << ")" ;
			break;
		case nodes::NodeType::END:
			out << "End("<< n->getID() << ")" ;
			break;
		case nodes::NodeType::ORIGIN:
			out << "O("<< n->getID() << ")" ;
			break;
		default:
			out << "(" << n->getID() << ")" ;
			break;
	}
}
unsigned short Path::countTarget()const
{
	unsigned short count = 0;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode()->getType() != nodes::NodeType::UNKNOW) count++;
	}
	
	return count;
}	

void Path::genMD5()
{
	std::string strmd5;
	if(size() == 0) return;

	for(std::list<nodes::Edge*>::iterator it = begin(); it != end(); it++)
	{
		strmd5 += std::to_string((*it)->getNode()->getID());
	}
	
	md5 = strmd5;
}
void Path::push_back(nodes::Edge* e)
{
	std::list<nodes::Edge*>::push_back(e);
	genMD5();
}
void Path::reverse(const Path* p)
{
	for(nodes::Edge* e : *p)
	{
		push_front(e);
	}
	if(p->direction == nodes::Direction::FRONT)
	{
		direction = nodes::Direction::BACK;
	}
	else if(p->direction == nodes::Direction::BACK)
	{
		direction = nodes::Direction::FRONT;
	}
	genMD5();
}
nodes::Edge* Path::find(nodes::Edge* e)
{
	iterator it;
	it = std::find(begin(),end(),e);
	if(it == end()) return NULL;
	return *it;
}
unsigned short Path::countCorners() const
{
	unsigned short count = 0 ;
	for(nodes::Edge* e : *this)
	{
		if(direction == nodes::Direction::FRONT)
		{
			if(e->getNode()->countFront() > 2) count++;
		}
		else if(direction == nodes::Direction::BACK)
		{
			if(e->getNode()->countBack() > 2) count++;
		}
		else
		{
			throw octetos::core::Exception("Direccion desconocida",__FILE__,__LINE__);
		}
	}
	
	return count;
}
nodes::Edge* Path::findCorner(unsigned short i)
{
	if(i == 0 ) return NULL;
	unsigned short count = 0 ;
	for(nodes::Edge* e : *this)
	{
		if(direction == nodes::Direction::FRONT)
		{
			if(e->getNode()->countFront() > 2) count++;			
		}
		else if(direction == nodes::Direction::BACK)
		{
			if(e->getNode()->countBack() > 2) count++;
		}
		else
		{
			throw octetos::core::Exception("Direccion desconocida",__FILE__,__LINE__);
		}
		if(count == i) return e;
	}
	
	return NULL;
}
nodes::Edge* Path::findTarget(unsigned short i)
{
	unsigned short count = 0 ;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode()->getType() != nodes::NodeType::UNKNOW) count++;
		if(count == i) return e;
	}
	
	return NULL;
}








Single::Single(const Single& s) : ec::Single(s),chromosome(s.chromosome)
{
}
Single::Single(ID id,Enviroment& e,const Junction& j, Path* p) : ec::Single(id,e,j),chromosome(p)
{
}
Single::Single(ID id,Enviroment& e, Path* p) : ec::Single(id,e),chromosome(p)
{
}
Single::~Single()
{

}

void Single::eval()
{
	double flength = 0.0;
	if(getCountTagetsPath() >= ((Enviroment*)env)->getTargets().size())
	{
		if(chromosome.getPath()->getDirection() == nodes::Direction::FRONT)
		{
			flength = ((Enviroment*)env)->getFreactionQ() - ((Enviroment*)env)->getGammaLengthFront() * double(getLengthPath());
		}
		else if(chromosome.getPath()->getDirection() == nodes::Direction::BACK)
		{
			flength = ((Enviroment*)env)->getFreactionQ() - ((Enviroment*)env)->getGammaLengthBack() * double(getLengthPath());
		}
	}
	
	double fTarget = ((Enviroment*)env)->getGammaTarget() * double(getCountTagetsPath());
	if(fTarget > ((Enviroment&)getEnviroment()).getFreactionQ())
	{
		fTarget = ((Enviroment&)getEnviroment()).getFreactionQ()/(((Enviroment*)env)->getFreactionD() * fTarget);
	}
	
	double fDirection;
	if(((Enviroment*)env)->get_direction())	
	{
		if(chromosome.getPath()->getDirection() == nodes::Direction::FRONT) fDirection = ((Enviroment*)env)->getFreactionQ();
	}
	else
	{
		fDirection = ((Enviroment*)env)->getFreactionQ();
	}

	
	//std::cout << "(" << getID() << ") : \n";
	//std::cout << "\tflength = " << flength << "\n";
	//std::cout << "\tfTarget = " << fTarget << "\n";
	fitness = fTarget + flength + fDirection;	
}
void Single::randFill(bool favor)
{
	
}

Population Single::juncting(std::list<ec::Single*>& chils,unsigned short loglevel,void* node)
{
	if(getJunction().get_type() != ec::Junction::TypeJuntion::UNARY) throw octetos::core::Exception("Metodo de reproduccion incorrrecto",__FILE__,__LINE__);
	Population counNew = 0;
	
	for(ec::geneUS i = 1; i < getJunction().get_number(); i++)
	{
		unsigned short corners = chromosome.getPath()->countCorners();
		nodes::Edge* pe = NULL;
		if(corners > 1)
		{
			double randCorner = randNumber(0.0,double(corners - 1));
			pe = chromosome.getPath()->findCorner(randCorner + 1);
			if(pe != NULL)
			{
				Path* newPath = new Path(chromosome.getPath()->getDirection());
				if(newPath->cutAfther(pe->getNode()))
				{					
					if(newPath->getDirection() == nodes::Direction::FRONT)
					{
						if(newPath->getLength() > ((Enviroment*)env)->getRegion()->getLengthFront())
						{
							delete newPath;
							continue;
						}
					}
					else if(newPath->getDirection() == nodes::Direction::BACK)
					{
						if(newPath->getLength() > ((Enviroment*)env)->getRegion()->getLengthBack())
						{
							delete newPath;
							continue;
						}
					}					
					if(newPath->countTarget() > ((Enviroment*)env)->getTargets().size())
					{
						delete newPath;
						continue;
					}
					counNew++;
					Single* newSingle = new Single(env->nextID(),*((Enviroment*)env),getJunction(),newPath);
					//newSingle->eval();
					
					chils.push_back(newSingle);
				}
			}
		}
		else
		{
			pe = chromosome.getPath()->findCorner(1);
			if(pe != NULL)
			{
				Path* newPath = new Path(chromosome.getPath()->getDirection());
				if(newPath->cutAfther(pe->getNode()))
				{
					if(newPath->getDirection() == nodes::Direction::FRONT)
					{
						if(newPath->getLength() > ((Enviroment*)env)->getRegion()->getLengthFront())
						{
							delete newPath;
							continue;
						}
					}
					else if(newPath->getDirection() == nodes::Direction::BACK)
					{
						if(newPath->getLength() > ((Enviroment*)env)->getRegion()->getLengthBack())
						{
							delete newPath;
							continue;
						}
					}					
					if(newPath->countTarget() > ((Enviroment*)env)->getTargets().size())
					{
						delete newPath;
						continue;
					}
					counNew++;
					Single* newSingle = new Single(env->nextID(),*((Enviroment*)env),getJunction(),newPath);
					chils.push_back(newSingle);
				}
			}
		}
	}	
	
	return counNew;
}
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void* node)
{
	Population counNew = 0;	
	if(getJunction().get_type() != ec::Junction::TypeJuntion::BINARY) throw octetos::core::Exception("Metodo de reproduccion incorrrecto",__FILE__,__LINE__);
	
	//std::cout << "Single::juncting Juntion 1\n";
	for(ec::geneUS i = 1; i < getJunction().get_number(); i++)
	{
		//std::cout << "Single::juncting 1.1\n";
		//std::cout << "Apareo : " << i << "/" << getJunction().get_number() << "\n";
		if(env->getEchoSteps())
		{
			print(std::cout);
			std::cout << "\n";
		}
		
		unsigned short nodepos = 0;
		
		//std::cout << "Single::juncting 1.1.1\n";
		bool flsingleP = false;
		Path *singleP = NULL;
		//std::cout << "Single::juncting 1.1.1.a\n";
		nodes::Edge* pe = NULL;
		nodes::Edge* singleE = NULL;
		unsigned short edgecount = chromosome.getPath()->countCorners();
		for(unsigned short i = 1; i <= edgecount; i++)
		{
			if(edgecount > 0) 
			{
				if(edgecount > 1)
				{
					double randEdge = randNumber(0.0,double(edgecount - 1));
					pe = chromosome.getPath()->findCorner(randEdge + 1);
				}
				else
				{
					pe = chromosome.getPath()->findCorner(1);				
				}			
			}
			
			singleE = ((Single*)single)->chromosome.getPath()->find(pe);
			if(singleE != NULL) break;//si no hay coinciendia con single regres al inicio
		}
		
		if(chromosome.getPath()->getDirection() != ((Single*)single)->chromosome.getPath()->getDirection()) 
		{
			singleP = new Path();
			singleP->reverse(((Single*)single)->chromosome.getPath());
			flsingleP = true;
		}
		else
		{
			singleP = ((Single*)single)->chromosome.getPath();
		}
			
		Path *newP = new Path(chromosome.getPath()->getDirection());
		if(newP->juncting(chromosome.getPath(),singleP,singleE)) 
		{
			if(newP->getDirection() == nodes::Direction::FRONT)
			{
				if(newP->getLength() > ((Enviroment*)env)->getRegion()->getLengthFront())
				{
					delete newP;
					continue;
				}
			}
			else if(newP->getDirection() == nodes::Direction::BACK)
			{
				if(newP->getLength() > ((Enviroment*)env)->getRegion()->getLengthBack())
				{
					delete newP;
					continue;
				}
			}
			if(newP->countTarget() > ((Enviroment*)env)->getTargets().size())
			{
				delete newP;
				continue;
			}
			counNew++;
			double randJ = randNumber(0.0,1.0);
			const Junction* genJ;
			if(randJ < 0.5)
			{
				genJ = &getJunction();
			}
			else
			{
				genJ = &((Single*)single)->getJunction();
			}
			Single* newSingle = new Single(env->nextID(),*((Enviroment*)env),*genJ,newP);
			chils.push_back(newSingle);
		}	
		else
		{
			delete newP;
		}
		if(flsingleP) delete singleP;
		
	}

	//if(chils.size() == counNew) 
	{
		Single* newSingle = new Single(*this);
		newSingle->growUp();
		chils.push_back(newSingle);
		counNew++;
	}
			
	return counNew;
}
void Single::save(std::ofstream& fn)
{
	fn << getID();
	fn << ",";
	fn << getFitness();
	fn << ",";
	fn << getAge();
	fn << ",";
	chromosome.getPath()->print(fn);
}

void Single::print(std::ostream& p) const
{
	p << chromosome.getPath()->getMD5() << " : ";
	chromosome.print(p);
}
void Single::print(nodes::Node&) const
{

}
/*Population Single::juncting(const Single* s,std::list<Path*>& p)const
{
	//std::cout << "Step 1\n";
	return chromosome.juncting(&s->chromosome,p);
}*/
unsigned short Single::getLengthPath()const
{
	return chromosome.getLengthPath();
}
unsigned short Single::getCountTagetsPath()const
{
	return chromosome.getCountTagetsPath();
}
const Chromosome* Single::getChromosome()const
{
	return &chromosome;
}
bool Single::growUp()
{
	nodes::Edge* e = NULL;
	nodes::Direction direct = chromosome.getPath()->getDirection();
	if(direct == nodes::Direction::FRONT)
	{
		if(chromosome.getPath()->back() != NULL) if(chromosome.getPath()->back()->getNext() != NULL) e = chromosome.getPath()->back()->getNext()->randFront();
		if(e != NULL) chromosome.getPath()->push_back(e);			
	}
	else if(direct == nodes::Direction::BACK)
	{
		if(chromosome.getPath()->back() != NULL) if(chromosome.getPath()->back()->getNext() != NULL) e = chromosome.getPath()->back()->getNext()->randBack();
		if(e != NULL) chromosome.getPath()->push_back(e);			
	}
	//print(std::cout);
	//std::cout << "\n";
	return e != NULL? true : false;
}
unsigned short Single::checkOrder(const Path* p)const
{
	unsigned short count = 0;
	std::list<nodes::Node*>::const_iterator it = ((Enviroment*)env)->getTargets().begin();
	for(nodes::Edge* e : *p)
	{
		if(e->getNode() == *it) 
		{
			count++;		
			it++;
			if(it == ((Enviroment*)env)->getTargets().end()) break;
		}
		
	}
	
	return count;
}










Enviroment::Enviroment()
{
	init();
}
Enviroment::Enviroment(const std::string& log)
{
	init();
	logDirectory = log;
}
void Enviroment::init()
{
	countID = 0;//contador de nodos
	initPopulation = 10000;
	maxPopulation = 1000;
	maxProgenitor = 500;
	stopperMaxIterations(2000);
	//stopperNotDiference(1.0e-20);
	//comparer = &cmpStrength1;
	fractionDen = 3.0;
	fractionQuality = 1.0/fractionDen;
	genLengthMin = 5;
	threads = 40;
	region = NULL;
	//echoSteps = true;
	
	//
	direction = true;
}
Enviroment::~Enviroment()
{
	if(region) delete region;
}

double Enviroment::getGammaLengthFront() const
{
	return gammaLengthFront;
}
double Enviroment::getGammaLengthBack() const
{
	return gammaLengthBack;
}
double Enviroment::getGammaTarget() const
{
	return gammaTarget;
}
const nodes::Region* Enviroment::getRegion()const
{
	return region;
}

unsigned short Enviroment::getGenLengthMin() const
{
	return genLengthMin;
}
bool Enviroment::get_direction()const
{
	return direction;
}


void Enviroment::generate(nodes::Node* n,unsigned short stop,nodes::Direction direction)
{
	if(lstPaths.size() >= initPopulation) return;
	
	//std::cout << "Step 1\n";
	Path* newPath = new Path(direction);
	if(direction == nodes::Direction::FRONT)
	{
		nodes::Edge* e = n->randFront();
		//std::cout << "Step 1.1 (" << e << ")\n";
		if(e != NULL) 
		{
			//std::cout << "Step 1.1.1 (" << e->getNode()->getID() << ")\n";
			newPath->push_back(e);
		}
	}
	else if(direction == nodes::Direction::BACK)
	{
		nodes::Edge* e = n->randBack();
		//std::cout << "Step Back 1.1 (" << e << ")\n";
		if(e != NULL) 
		{
			//std::cout << "Step Back 1.1.1 (" << e->getNode()->getID() << ")\n";
			newPath->push_back(e);
		}
	}
	else throw octetos::core::Exception("Direccion no asignada",__LINE__,__FILE__);

	//std::cout << "Step 2\n";
	for(unsigned short i = 0; i < stop; i++)
	{
		if(direction == nodes::Direction::FRONT)
		{
			//std::cout << "Step 2.1\n";
			nodes::Edge* e = NULL;
			if(newPath->back() != NULL) if(newPath->back()->getNext() != NULL) e = newPath->back()->getNext()->randFront();
			if(e != NULL) newPath->push_back(e);			
		}
		else if(direction == nodes::Direction::BACK)
		{
			//std::cout << "Step 2.1\n";
			nodes::Edge* e = NULL;
			if(newPath->back() != NULL)
			{
				//std::cout << "Step Back 2.1.1 (" << newPath->back()->getNext()->getID() << ")\n";
				if(newPath->back()->getNext() != NULL) 
				{
					e = newPath->back()->getNext()->randBack();
					//std::cout << "Step Back 2.1.1.1 (" << e->getNode()->getID() << ")\n";					
				}
			}
			if(e != NULL) newPath->push_back(e);			
		}
	}
	//std::cout << "Step 3\n";
	if(newPath->size() > 1) lstPaths.push_back(newPath);
}
void Enviroment::initial()
{
	creteRegion(targets);
	
	//
	gammaLengthFront = fractionQuality/double(region->getLengthFront());
	gammaLengthBack = fractionQuality/double(region->getLengthBack());
	gammaTarget = fractionQuality/double(targets.size());
	
	//
	std::cout << "Targets : \n";
	for(nodes::Node* node : targets)
	{
		std::cout << "\t" << node->getID() << "\n";
	}
	for(unsigned short i = 0; i < threads; i++)
	{
		for(nodes::Node* node : targets)
		{
			generate(node,genLengthMin,nodes::Direction::FRONT);
			generate(node,genLengthMin,nodes::Direction::BACK);
		}
	}
	
	//std::list<octetos::core::MD5sum> lsmd5;
	for(Path* path : lstPaths)
	{
		//if(std::find(lsmd5.begin(),lsmd5.end(),path->getMD5()) == lsmd5.end())
		{
			//lsmd5.push_back(path->getMD5());
			ec::Junction juntion;
			juntion.randFill(ec::Junction::randType());
	 		Single* s = new Single(nextID(),*this,juntion,path);
	 		//s->print(std::cout);
	 		//std::cout << "\n";
			push_back(s);
			/*if(path->getDirection() == nodes::Direction::BACK)
			{
				Path* reverPath = new Path();
				reverPath->reverse(path);
				std::cout << "reversed : ";
				reverPath->print(std::cout);
	 			std::cout << "\n";
			}*/
		}
	}
	
	lstPaths.clear();	
}

/*
void Enviroment::selection()
{
	if(maxPopulation > size()) return;//si no hay mas de la poblocion maxima continuar
	
	std::list<Single*> forDelete;
	Single* single;
	Population countPass = 0;
	//std::cout << "Step 1\n";
	for(ec::Single* s : *this)
	{
		//std::cout << "Step 1.1\n";
		countPass++;		
		single = (Single*)s;
		if(countPass > maxPopulation)
		{//eliminar a partir de que se alcance la maxima poblacion
			forDelete.push_back(single);
			continue;
		}
		
		nodes::Node* nodeF = single->getChromosome()->getPath()->front()->getNode();
		nodes::Node* nodeB = single->getChromosome()->getPath()->back()->getNode();
				
		//aceptar esquinas,glorietas,
		//if(nodeB->isTrunk()) continue;
		
		//aceptar los que ban del origne a los extremos
		if(nodeF->getType() == nodes::ORIGIN and nodeB->getType() == nodes::END and single->getChromosome()->getPath()->size() > 1) continue;
		
		//aceptar los que ban del origne a los target
		if(nodeF->getType() == nodes::ORIGIN and nodeB->getType() == nodes::TARGET and single->getChromosome()->getPath()->size() > 1) continue;
		
		//aceptar los que ban del target a los target
		if(nodeF->getType() == nodes::TARGET and nodeB->getType() == nodes::TARGET and single->getChromosome()->getPath()->size() > 1) continue;
		
		//aceptar los que ban del extremo al origen
		if(nodeF->getType() == nodes::END and nodeB->getType() == nodes::ORIGIN and single->getChromosome()->getPath()->size() > 1) continue;

		//aceptar los teinet un target en un extremo
		if(nodeF->getType() == nodes::END and nodeB->getType() == nodes::TARGET and single->getChromosome()->getPath()->size() > 1) continue;
		
		if(single->getChromosome()->getPath()->countTarget() > 0 and nodeF->getType() != nodes::ORIGIN and nodeB->getType() != nodes::ORIGIN) continue;
		
		if(single->getFitness() > media) continue;
		
		//
		forDelete.push_back(single);
	}
	//std::cout << "Step 2\n";
	for(ec::Single* s : forDelete)
	{
		single = (Single*)s;
		delete single;
		remove(single);
	}
}*/




const std::list<nodes::Node*>& Enviroment::getTargets()const
{
	return targets;
}

double Enviroment::getFreactionQ()const
{
	return fractionQuality;
}

double Enviroment::getFreactionD()const
{
	return fractionDen;
}


}