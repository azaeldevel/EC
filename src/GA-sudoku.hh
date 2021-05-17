

#ifndef AE_GA_EXT_HH
#define AE_GA_EXT_HH

#include <octetos/core/MD5sum.hh>

#include "GA.hh"


namespace ae::sudoku
{
class Enviroment;


class Chromosome : public ae::Chromosome
{
public:
	Chromosome();
	Chromosome(const Chromosome& obj);
	virtual ~Chromosome();
	geneUS getNumber(unsigned short i,unsigned short j) const;
	void setNumber(unsigned short i,unsigned short j,geneUS);

	const Chromosome& operator = (const Chromosome&);	
	
	virtual void combine(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void copy(const ae::Chromosome& P1);
	virtual void mutate(float p);
	virtual void randFill(bool favor = false);

	/*
	*\brief Busca un numero que no halla sido asignado.
	*/
	geneUS freeNumber()const;
	
	/*
	*\brief Detec colision
	*/
	void resetCollision();

	
private:
	geneUS numbers[3][3];
};

class Single : public ae::Single
{
public:
	Single(const Single&);
	Single(unsigned int id,Enviroment& e,Chromosome** init);
	Single(unsigned int id,Enviroment& e,Chromosome** newData,Chromosome** init, const Junction& junction);
	virtual ~Single();

	const Chromosome& getTalba(unsigned short i,unsigned short j)const;
		
	virtual void eval();
	virtual void randFill(bool favor = false);
	virtual void juncting(std::list<ae::Single*>& chils,ae::Single* single,unsigned short loglevel);
	virtual void save(std::ofstream& fn);
	const octetos::core::MD5sum& getMD5() const;
	
	void print(std::ostream&) const;
	void printInit(std::ostream&) const;
	unsigned int getErros()const;
	
private:
	Chromosome** tabla;
	Chromosome** intiVals;
	octetos::core::MD5sum md5;

	//
	void genMD5();
};

class Enviroment : public ae::Enviroment
{
public:
	//
	
	//
	Enviroment();	
	Enviroment(const std::string& initTable);
	Enviroment(const std::string& initTable,Iteration maxIteration);
	virtual ~Enviroment();
	void init(const std::string& initB);
	void initBoard(const std::string& initTable);

	unsigned short getFaltantes() const;
	double getGamma() const;
	ae::Single* getRandomSingleTop()const;
	ae::Single* getRandomSingle()const;
	//void saveSolutions(const std::string& dir)const;
	void saveSolutions(std::ofstream& f)const;
	
	virtual void selection();
	//virtual bool run();
	virtual void initial();
	virtual void evaluation();
	virtual void juncting();
	virtual void save();

private:

	/**
	*\brief valor estadistico de cada variable.
	*/
	double gamma;
	Chromosome** sudokuInit;
	std::string fnBoard;
	
};

}

#endif