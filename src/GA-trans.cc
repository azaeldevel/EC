
#include <octetos/core/Error.hh>
#include <fstream>


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
		std::advance(it, index);
		return *it;
	}

	Index Node::getFrontCount()const
	{
		return edgesFront.size();
	}
	Edge* Node::getBack(Index index)
	{
		std::list<Edge*>::iterator it = edgesBack.begin();
		std::advance(it, index);
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
		std::advance(it, index);
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
	
	
	
	

	







	Region::Region(ID id, const std::string& name) : Node(id,NodeType::REGION),origin(NULL)
	{
		countNodes = 0;
		countEdges = 0;
	}
	Region::~Region()
	{
		for(Node* n : nodes)
		{
			delete n;
		}
		for(Edge* e : edges)
		{
			delete e;
		}
	}
	
	unsigned int Region::getCountNodes()const
	{
		return countNodes;
	}
	unsigned int Region::getCountEdges()const
	{
		return countEdges;
	}


	Node* Region::newNode(ID id)
	{
		Node* n = new Node(id);
		nodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		countNodes++;
		
		return n;
	}
	Node* Region::newNode(ID id,NodeType t)
	{
		Node* n = new Node(id,t);
		nodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		countNodes++;
		
		return n;
	}
	Edge* Region::newEdge(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		edges.push_back(e);
		countEdges++;
		
		return e;
	}
	void Region::newEdgeBi(unsigned int d,Node* a, Node* n)
	{
		Edge* e1 = new Edge(d,a,n);
		Edge* e2 = new Edge(d,n,a);
		a->addFront(e1);
		n->addBack(e2);
		edges.push_back(e1);
		edges.push_back(e2);
		countEdges++;
	}
	Node* Region::getOrigin()
	{
		return origin;
	}
	void Region::resetTrans()
	{
		for(Edge* e : edges)
		{
			e->resetNextCount();
		}
	}
}





Chromosome::Chromosome(Path* p) : ec::Chromosome("trans::Chromosome"),path(p)
{

}
Chromosome::Chromosome(const Chromosome& obj) : ec::Chromosome("TransChromosome"),path(obj.path)
{
	path = obj.path;
}
Chromosome::~Chromosome()
{
}

const Chromosome& Chromosome::operator = (const Chromosome& obj)
{
	path = obj.path;

	return *this;
}




Population Chromosome::juncting(const Chromosome* c,std::list<Path*>& p)const
{
	//std::cout << "Step 1.1\n";
	return path->juncting(c->path,p);
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
bool Chromosome::growUp()
{
	return path->growUp();
}






Path::Path(nodes::Direction d) : direction(d)
{	
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
}
Path::Path(const Path* p,nodes::Direction d) : std::list<nodes::Edge*>(*p), direction(d)
{
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
Population Path::juncting(const Path* p,std::list<Path*>& lstp)const
{
	for(nodes::Edge* e1 : *this)
	{
		for(nodes::Edge* e2 : *p)
		{
			if(p->front()->getNode() == front()->getNode()) continue;
			if(p->back()->getNode() == back()->getNode()) continue;
			
			if(e1->getNode() == e2->getNode() and e1->getNext() != e2->getNext())
			{//
				Path pB(*this);
				Path pE(*p);		
				pB.cutAfther(e1->getNode());
				if(pB.size() < 3) continue;
				pE.cutBefore(e2->getNode());
				if(pE.size() < 3) continue;
				Path*  newp = new Path(&pB,&pE);
				lstp.push_back(newp);
			}
		}
	}
	
	return lstp.size();
}
bool Path::cutBefore(nodes::Node* n)
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
bool Path::cutAfther(nodes::Node* n)
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
	return size();
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
bool Path::growUp()
{
	nodes::Edge* e = randNext();
	if(e) 
	{
		push_back(e);
		return true;
	}	

	return false;
}
nodes::Edge* Path::randNext()
{
	nodes::Node* n = back()->getNode();
	float rand = randNumber();
	std::list<nodes::Edge*>* randEdge;
	if(direction == nodes::Direction::FRONT) 
	{
		rand = randNumber(0.0,float(n->getFrontCount() - 1.0));
		return n->getFront(rand);
	}
	else if(direction == nodes::Direction::BACK)
	{
		rand = randNumber(0.0,float(n->getFrontCount() - 1.0));
	 	return n->getBack(rand);
	}
	
	return NULL;	
}













Single::Single(const Single& s,const std::list<nodes::Node*>& t) : ec::Single(s),puntos(s.puntos),chromosome(s.chromosome),lstTargets(t)
{
}
Single::Single(ID id,Enviroment& e,const Junction& j, Path* p,const std::list<nodes::Node*>& t) : ec::Single(id,e,j),chromosome(p),puntos(0),lstTargets(t)
{
}
Single::Single(ID id,Enviroment& e, Path* p,const std::list<nodes::Node*>& t) : ec::Single(id,e),chromosome(p),puntos(0),lstTargets(t)
{
}

void Single::eval()
{
	//double minfl = (Enviroment*)env)->getGammaLength() * ((Enviroment*)env)->getTargets().size());
	double maxfl = ((Enviroment*)env)->getGammaLength() * double(((Enviroment*)env)->getRegion()->getCountEdges());
	double flength = ((Enviroment*)env)->getGammaLength() * double(getLengthPath());
	flength = std::abs(maxfl - flength)/((((Enviroment&)getEnviroment()).getFreactionD()) * maxfl);
	flength = ((Enviroment&)getEnviroment()).getFreactionQ() - flength;
	
	double fTarget = ((Enviroment*)env)->getGammaTarget() * double(getCountTagetsPath());
	if(fTarget > ((Enviroment&)getEnviroment()).getFreactionQ())
	{
		fTarget = ((Enviroment&)getEnviroment()).getFreactionQ()/fTarget;
	}
	//std::cout << "(" << getID() << ") : ";
	//std::cout << "\tflength = " << flength << "\n";
	//std::cout << "\tfTarget = " << fTarget << "\n";
	fitness = flength + fTarget;	
}
void Single::randFill(bool favor)
{
	
}
/*Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void* node) const
{
	Population counNew = 0;
	
	std::list<Path*> lstp;
	ec::Single* newchild;
	if(juncting((const Single*)single,lstp))
	const std::list<nodes::Node*>& lsTargets = ((Enviroment*)env)->getTargets();
	for(ec::geneUS i = 0; i < getJunction().get_number(); i++)
	{
		for(Path* p : lstp)
		{
			if(lstp.size() + env->size() >= env->getMaxPopulation()) break;
			newchild = new Single(env->nextID(),(Enviroment&)*env,p,lstTargets);
			chils.push_back(newchild);
		}
		counNew++;
		counNew += juncting((const Single*)single,lstp);
	}
	for(Path* p : lstp)
	{
		newchild = new Single(env->nextID(),(Enviroment&)*env,p,lstTargets);
		chils.push_back(newchild);
		counNew++;	
	}
		
	return counNew;
}*/
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void* node) const
{
	Population counNew = 0;	
	
	//buscar un empate entre this y single
	std::list<nodes::Edge*>::const_iterator it = chromosome.getPath()->begin();
	for(nodes::Edge* e : *chromosome.getPath())
	{
		//it = std::find(((Single*)single)->chromosome.getPath()->begin(),((Single*)single)->chromosome.getPath()->end(),e);
	}
	//si existe tal empate realizar una usarlos como para union
		
	for(ec::geneUS i = 0; i < getJunction().get_number(); i++)
	{
		
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
	fn << "\n";
}

void Single::print(std::ostream& p) const
{
	chromosome.print(p);
}
void Single::print(nodes::Node&) const
{

}
Population Single::juncting(const Single* s,std::list<Path*>& p)const
{
	//std::cout << "Step 1\n";
	return chromosome.juncting(&s->chromosome,p);
}
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
	return chromosome.growUp();
}

unsigned short Single::checkOrder(const Path* p)const
{
	unsigned short count = 0;
	std::list<nodes::Node*>::const_iterator it = lstTargets.begin();
	for(nodes::Edge* e : *p)
	{
		if(e->getNode() == *it) 
		{
			count++;		
			it++;
			if(it == lstTargets.end()) break;
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
	maxPopulation = 250;
	stopperMaxIterations(1000);
	stopperNotDiference(1.0e-20);
	comparer = &cmpStrength1;
	fractionDen = 2.0;
	fractionQuality = 1.0/fractionDen;
	genLengthMin = 4;
}
Enviroment::~Enviroment()
{
	if(region) delete region;
}

double Enviroment::getGammaLength() const
{
	return gammaLength;
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


void Enviroment::generate(nodes::Edge* e,unsigned short stop,nodes::Direction direction)
{
	if(stop == 0) return;
	
	Path* newPath = new Path(direction);		
	nodes::Edge* edge = e;
	nodes::Node* node;
	
	unsigned short i = 0;
	do
	{
		node = edge->getNext();
		edge->transNext();
		newPath->push_back(edge);
		
		//next iteration
		i++;
		edge = node->nextLessTrans(stop,direction);		
	}
	while( i < stop and edge != NULL);
	lstPaths.push_back(newPath);
	//std::cout << "Generating ..";
	//newPath->print(std::cout);
	//std::cout << "\n";
}

void Enviroment::generate(nodes::Node* n,unsigned short stop,nodes::Direction direction)
{
	nodes::Edge* eN = n->nextLessTrans(stop,direction);	
	
	while(eN)
	{
		Path* newPath = new Path(direction);
		eN->transNext();
		newPath->push_back(eN);
		lstPaths.push_back(newPath);	
		generate(newPath,eN,stop,direction);

		//next iteration
		eN = n->nextLessTrans(stop,direction);
	}
}
void Enviroment::generate(Path* path, nodes::Edge* eprev, unsigned short stop,nodes::Direction direct)
{
	nodes::Node* n = eprev->getNext();
	nodes::Edge* eN = n->nextLessTrans(stop,direction);
	do
	{
		Path* newPath = NULL;
		if(eN)
		{
			newPath = new Path(path,direct);
			eN->transNext();
			newPath->push_back(eN);
			lstPaths.push_back(newPath);
		}
		
		if(n->getType() == nodes::UNKNOW and eN and newPath) generate(newPath,eN,stop,direction);
		
		//next iteration
		eN = n->nextLessTrans(stop,direction);
	}
	while(eN);
}
void Enviroment::initial()
{
	creteRegion(targets);
	/*for(nodes::Node* node : targets)
	{
		std::cout << node->getID() << "\n";
	}*/
	//
	gammaLength = fractionQuality/double(region->getCountEdges());
	gammaTarget = fractionQuality/double(targets.size());
	
	//
	for(nodes::Node* node : targets)
	{
		//std::cout << node->getID() << "\n";
		for(nodes::Edge* edge : node->edgesFront)
		{
			region->resetTrans();
			generate(edge,genLengthMin,nodes::Direction::FRONT);
		}
		for(nodes::Edge* edge : node->edgesBack)
		{
			region->resetTrans();
			generate(edge,genLengthMin,nodes::Direction::BACK);
		}
	}
	region->resetTrans();
	//generado individuos
	for(Path* path : lstPaths)
	{
 		Single* s = new Single(nextID(),*this,path,targets);
 		//s->print(std::cout);
 		//std::cout << "\n";
		push_back(s);
	}
	//liberando memoria de paths
	lstPaths.clear();
	
}


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
}



void Enviroment::save()
{
	std::string strfn = logSubDirectory +  "/solutions-" + std::to_string(actualIteration) + ".csv";
	std::ofstream fn(strfn);
	for(ec::Single* s : *this)
	{
		s->save(fn);
	}
	fn.flush();
	fn.close();
}

std::list<nodes::Node*> Enviroment::getTargets()const
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