
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
	/*std::list<Edge*>& Node::getListFront()
	{
		return edgesFront;
	}*/
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
		
		//std::cout << "TransEnviroment::nextLessTrans Step 1 node " << getID() << "\n";
		if(edgeList->empty()) return NULL;
		//std::cout << "TransEnviroment::nextLessTrans Step 2\n";
		for(Edge* e : *edgeList)
		{
			if(e->getNextCount() <  max) return e;
		}
		//std::cout << "TransEnviroment::nextLessTrans Step 3\n";
		return NULL;
	}








	


	

	Edge::Edge(unsigned int d,Node* a, Node* n)
	{
		distance = d;
		node = a;
		next = n;
		//node->addFront(this);
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
		for(Node* n : toDeleteNodes)
		{
			delete n;
		}
		for(Edge* e : toDeleteEdges)
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

	/*Street* Region::newStreet(ID id)
	{
		Street* n = new Street(id);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}*/
	/*Street* Region::newStreet(ID id,NodeType t)
	{
		Street* n = new Street(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		
		return n;
	}*/
	Node* Region::newNode(ID id)
	{
		Node* n = new Node(id);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		countNodes++;
		
		return n;
	}
	Node* Region::newNode(ID id,NodeType t)
	{
		Node* n = new Node(id,t);
		toDeleteNodes.push_back(n);
		if(origin == NULL) origin = n;//si no hay nodo origne registrado
		countNodes++;
		
		return n;
	}
	Edge* Region::newEdge(unsigned int d,Node* a, Node* n)
	{
		Edge* e = new Edge(d,a,n);
		toDeleteEdges.push_back(e);
		countEdges++;
		
		return e;
	}
	void Region::newEdgeBi(unsigned int d,Node* a, Node* n)
	{
		Edge* e1 = new Edge(d,a,n);
		Edge* e2 = new Edge(d,n,a);
		a->addFront(e1);
		n->addBack(e2);
		toDeleteEdges.push_back(e1);
		toDeleteEdges.push_back(e2);
		countEdges++;
	}
	Node* Region::getOrigin()
	{
		return origin;
	}
	void Region::resetTrans()
	{
		for(Edge* e : toDeleteEdges)
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

void Chromosome::combine(const ec::Chromosome& P1,const ec::Chromosome& P2)
{

}
void Chromosome::copy(const ec::Chromosome& P1)
{

}
void Chromosome::mutate(float p)
{

}
void Chromosome::randFill(bool favor)
{

}
/*const Path& Chromosome::getPath() const
{
	return *path;
}*/

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
	//std::cout << "Step 1.1.1.1.1.3.1\n";
	if(pb->size() == 0) throw octetos::core::Exception("La Path de incio esta vacia.",__FILE__,__LINE__);
	if(pe->size() == 0) throw octetos::core::Exception("La Path de fin esta vacia.",__FILE__,__LINE__);
	if(pb->back()->getNode() != pe->front()->getNode())
	{
		std::string msg = "El node final no coincide con el nodo inicial.\n\t";
		for(nodes::Edge* eb : *pb)
		{
			msg += std::to_string(eb->getNode()->getID());
			msg += "->";
		}
		msg += "\n\t";
		for(nodes::Edge* ee : *pe)
		{
			msg += std::to_string(ee->getNode()->getID());
			msg += "->";
		}
		throw octetos::core::Exception(msg,__FILE__,__LINE__);
	}
	/*if(pb->back() != pe->front())
	{
		std::string msg = "Union (";
		msg += std::to_string(pb->back()->getNode()->getID()) + ") ->> (" + std::to_string(pe->front()->getNode()->getID()) + ")\n";
		throw octetos::core::Exception(msg,__FILE__,__LINE__);
	}*/
	//std::cout << "Step 1.1.1.1.1.3.2\n";
	//
	Path::const_iterator last = pb->begin();
	std::advance(last,pb->size()-1);
	for(nodes::Edge* e : *pb)
	{
		if(e == *last) break;
		push_back(e);
	}
	//std::cout << "Step 1.1.1.1.1.3.3\n";
	for(nodes::Edge* e : *pe)
	{
		push_back(e);
	}
}
Path::Path(const Path* p) : std::list<nodes::Edge*>(*p)
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
	//std::cout << "Step 1.1.1\n";
	for(nodes::Edge* e1 : *this)
	{
		//std::cout << "Step 1.1.1.1\n";
		for(nodes::Edge* e2 : *p)
		{
			if(p->front()->getNode() == front()->getNode()) continue;
			if(p->back()->getNode() == back()->getNode()) continue;
			
			//std::cout << "Step 1.1.1.1.1\n";
			if(e1->getNode() == e2->getNode() and e1->getNext() != e2->getNext())
			{
				//std::cout << "Step 1.1.1.1.1.1\n";
				Path pB(*this);
				Path pE(*p);
				//std::cout << "Step 1.1.1.1.1.2\n";		
				pB.cutAfther(e1->getNode());
				if(pB.size() < 3) continue;
				pE.cutBefore(e2->getNode());
				if(pE.size() < 3) continue;	
				//if(pB.back()->getNode() == pE.front()->getNext()) continue;
				//std::cout << "Step 1.1.1.1.1.3\n";
				std::string msg = "paths : \n\t";
				msg += "On(" + std::to_string(e1->getNode()->getID()) + ")\n\t";
				for(nodes::Edge* eb : *this)
				{
					msg += std::to_string(eb->getNode()->getID());
					msg += "->";
				}
				msg += "\n\t";
				for(nodes::Edge* ee : *p)
				{
					msg += std::to_string(ee->getNode()->getID());
					msg += "->";
				}
				msg += "\n\t";
				Path*  newp = new Path(&pB,&pE);
				for(nodes::Edge* res : *newp)
				{
					msg += std::to_string(res->getNode()->getID());
					msg += "->";
				}
				//std::cout << msg << "\n";
				//std::cout << "Step 1.1.1.1.1.4\n";
				lstp.push_back(newp);
			}
		}
	}
	//std::cout << "Step 1.1.2\n";
	return lstp.size();
}
bool Path::cutBefore(nodes::Node* n)
{
	std::list<nodes::Edge*> toDelete;
	for(nodes::Edge* e : *this)
	{
		if(e->getNode() == n)
		{
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
		if(e->getNode() != n)
		{
			if(cut)
			{
				toDelete.push_back(e);
			}			
		}
		else
		{
			cut = true;
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
unsigned short Path::CountTarget()const
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













Single::Single(const Single& s) : ec::Single(s),puntos(s.puntos),chromosome(s.chromosome)
{
}
Single::Single(ID id,Enviroment& e,const Junction& j, Path* p) : ec::Single(id,e,j),chromosome(p),puntos(0)
{
}
Single::Single(ID id,Enviroment& e, Path* p) : ec::Single(id,e),chromosome(p),puntos(0)
{
}

void Single::eval()
{
	double flength = 0.5 - (((Enviroment*)env)->getGammaLength() * double(chromosome.getLengthPath()));
	//std::cout << "l : " << double(chromosome.getPath().size()) << "\n";
	double fTarget = ((Enviroment*)env)->getGammaTarget() * double(chromosome.getCountTagetsPath());
	fitness = flength + fTarget;
	//if(flength > 1.0) print(std::cout);
	
}
void Single::randFill(bool favor)
{
}
Population Single::juncting(std::list<ec::Single*>& chils,const ec::Single* single,unsigned short loglevel,void* node) const
{
	Population counNew = 0;
	
	std::list<Path*> lstp;
	ec::Single* newchild;
	if(juncting((const Single*)single,lstp))
	{
		//std::cout << "\t(" << getID() << ") with (" << single->getID() << ")\n";
		//std::cout << "\t\t" << lstp.size() << " hijos\n";
		for(Path* p : lstp)
		{
			newchild = new Single(env->nextID(),(Enviroment&)*env,p);
			chils.push_back(newchild);
		}
		counNew++;
	}
	
	return counNew;
}
void Single::save(std::ofstream& fn)
{
	fn << getID();
	fn << ",";
	fn << getFitness();	
	//fn << ",";
	//fn << getMD5();
	fn << ",";
	fn << getAge();
	fn << "\n";
}
/*void Single::print(std::ostream& p) const
{
	Path::const_iterator actual, post;
	
	actual = chromosome.getPath().begin();
	post = chromosome.getPath().begin();
	do
	{
		std::advance(post,1);
		(*actual)->getNext();
		//(*post)->getNode();
		p << (*actual)->getNode()->getID() << "->";
		std::advance(actual,1);
	}
	while(post != chromosome.getPath().end());
	//p << (*post)->getNode()->getID() << "\n";	
}*/
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











Enviroment::Enviroment()
{
	countID = 0;//contador de nodos
	maxPopulation = 250;
	enableMaxIterations = true;
}
Enviroment::Enviroment(const std::string& log)
{
	countID = 0;//contador de nodos
	maxPopulation = 250;
	enableMaxIterations = true;
	logDirectory = log;
	maxIteration = 10;
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
void Enviroment::generate(Path* path, nodes::Edge* eprev, unsigned short stop,nodes::Direction direction)
{
	//if(path->size() > region->getCountEdges()/targets.size() ) return;
	
	nodes::Node* n = eprev->getNext();
	nodes::Edge* eN = n->nextLessTrans(stop,direction);
	do
	{
		Path* newPath = NULL;
		if(eN)
		{
			newPath = new Path(*path);
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
	//std::cout << "Poblacion inicial..\n";
	creteRegion(targets);
	gammaLength = 0.5 / double(region->getCountEdges());
	//std::cout << "Count : " << region->getCountEdges() << "\n";
	//std::cout << "gammaLength : " << gammaLength << "\n";
	gammaTarget = 0.5 / double(targets.size());
	//std::cout << "Count : " << targets.size() << "\n";
	//std::cout << "gammaTarget : " << gammaTarget << "\n";
	//ec::Enviroment::epsilon = gammaLength;

	//
	for(nodes::Node* n : targets)
	{
		region->resetTrans();
		generate(n,1,nodes::Direction::FRONT);
		region->resetTrans();
		generate(n,1,nodes::Direction::BACK);
	}
		
	//filtrar las rutas
	//filterPaths();
	
	//generado individuos
	for(Path* path : lstPaths)
	{
 		Single* s = new Single(nextID(),*this,path);
		push_back(s);
	}
	//liberando memoria de paths
	lstPaths.clear();
	
	//selection();
}

/*
bool Enviroment::run()
{
	//std::cout << "Initial : " << size() << "\n";
	initial();
	//std::cout << "Initial : " << size() << "\n";
	for(unsigned short i = 0; i < 10; i++)
	{
		std::cout << "Initial : " << size() << "\n";
		eval();
		sort(cmpStrength);
		Single* single;
		for(ec::Single* s : *this)
		{
			single = (Single*) s;
			//std::cout << "ID : " << single->getID() << " => " << single->getFitness() << "\n";
			//single->print(std::cout);
			//std::cout << "\n";
		}
		
		selection();
		
		juncting();
		for(ec::Single* s : newschils)
		{
			push_back(s);
		}
		newschils.clear();
	}
	
	return true;
}*/


void Enviroment::selection()
{
	if(maxPopulation > size()) return;//si no hay mas de la poblocion maxima continuar
	
	std::list<Single*> forDelete;
	Single* single;
	Population countPass = 0;
	//std::cout << "Step 1\n";
	for(ec::Single* s : *this)
	{
		//std::cout << ".";
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
		
		if(single->getChromosome()->getPath()->CountTarget() > 0 and nodeF->getType() != nodes::ORIGIN and nodeB->getType() != nodes::ORIGIN) continue;
		
		if(single->getFitness() > media) continue;
		
		//
		forDelete.push_back(single);
	}
	//std::cout << "Step 2\n";
	for(ec::Single* s : forDelete)
	{
		//std::cout << "Step 2.1\n";
		single = (Single*)s;
		//std::cout << "Step 2.2\n";
		delete single;
		//std::cout << "Step 2.3\n";
		remove(single);
		//std::cout << "Step 2.4\n";
	}
}
void Enviroment::eval()
{
	//std::cout << "Evaluacion..\n";
	Single* single;
	for(ec::Single* s : *this)
	{
		single = (Single*) s;
		single->eval();
		//std::cout << "ID : " << single->getID() << " = " << single->getFitness() << "\n";
	}
}

void Enviroment::juncting()
{
	Single *single1,*single2;
	for(ec::Single* s1 : *this)
	{
		single1 = (Single*) s1;
		for(ec::Single* s2 : *this)
		{
			single2 = (Single*) s2;
			if(s1 == s2) continue;
			s1->juncting(newschils,s2,echolevel,NULL);
			//single2->growUp();
		}
		//single1->growUp();
	}
}

void Enviroment::save()
{
	std::string strfn = logSubDirectory +  "/solutions-" + std::to_string(actualIteration) + ".csv";
	std::ofstream fn(strfn);
	for(ec::Single* s : *this)
	{
		if(1.0 - s->getFitness () < Enviroment::epsilon)
		{
			s->save(fn);
		}
	}
	fn.flush();
	fn.close();
}




}