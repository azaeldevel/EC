

#ifndef AE_GA_EXT_HH
#define AE_GA_EXT_HH

#include <octetos/core/MD5sum.hh>

#include "GA.hh"


namespace ae::ga
{

class SudokuChromosome : public Chromosome
{
public:
	SudokuChromosome();
	SudokuChromosome(const SudokuChromosome& obj);
	virtual ~SudokuChromosome();
	geneUS getNumber(unsigned short i,unsigned short j) const;
	void setNumber(unsigned short i,unsigned short j,geneUS);

	const SudokuChromosome& operator = (const SudokuChromosome&);	
	
	virtual void combine(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void copy(const ae::Chromosome& P1);
	virtual void mutate(float p);
	virtual void randFill();
	
private:
	geneUS numbers[3][3];
};

class SudokuSingle : public Single
{
public:
	SudokuSingle(const SudokuSingle&);
	SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome t[3][3]);
	SudokuSingle(unsigned int id,Enviroment& e,const SudokuChromosome t[3][3],const SudokuChromosome vi[3][3], const Junction& junction);
	virtual ~SudokuSingle();
	const SudokuChromosome& getTalba(unsigned short i,unsigned short j)const;
		
	virtual void eval();
	virtual void randFill();
	virtual void juncting(ID& idCount,std::list<ae::Single*>& chils,ae::Single* single,unsigned short loglevel);
	virtual void save(std::ofstream& fn);
	const octetos::core::MD5sum& getMD5() const;
	
	void print(std::ostream&) const;
	void printInit(std::ostream&) const;
	unsigned int getErros()const;
	
private:
	SudokuChromosome tabla[3][3];
	const SudokuChromosome (*intiVals)[3];
	octetos::core::MD5sum md5;

	//
	void genMD5();
};

class SudokuEnviroment : public Enviroment
{
public:
	//
	
	//
	SudokuEnviroment();	
	SudokuEnviroment(const std::string& log,const std::string& initTable);
	virtual ~SudokuEnviroment();
	void init(const std::string& initB);
	void initBoard(const std::string& initTable);
	unsigned short getFaltantes() const;
	double getGamma() const;
	ae::Single* getRandomSingleTop()const;
	ae::Single* getRandomSingle()const;
	void saveSolutions(const std::string& dir)const;
	
	virtual void selection();
	virtual bool run();
private:

	/**
	*\brief valor estadistico de cada variable.
	*/
	double gamma;
	SudokuChromosome sudokuInit[3][3];
	
};

}

#endif