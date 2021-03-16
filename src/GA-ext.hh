

#ifndef AE_GA_EXT_HH
#define AE_GA_EXT_HH


#include "GA.hh"


namespace ae::ga
{

/*
class MaxMin_R : public Chromosome
{
public:
	MaxMin_R();
	MaxMin_R(geneF x2_mx,geneF x2_mn);
	geneF get_x2_mx()const;
	geneF get_x2_mn()const;
	virtual void combine(const Chromosome& P1,const Chromosome& P2);
	virtual void copycombine(const Chromosome& P1,const Chromosome& P2);
	virtual void copy(const Chromosome& P1,const Chromosome& P2);
	virtual void mutate();

private:
	geneF x2_mx;
	geneF x2_mn;
};


struct Notas
{
	float x2_max;//la tendecia hacia 0 es mejor
	float x2_min;//la tendecia hacia 0 es mejor

	float strength;
};
class MaxMin_x2 : public Single
{
public:
	MaxMin_x2(unsigned int id,geneF x2_mx,geneF x2_min,geneUS number,geneUS algorit);
	MaxMin_x2(unsigned int id,MaxMin_R mm,const Junction& j);

public:
	MaxMin_R& getMaxMin();

	virtual void junction(MaxMin_x2& single,std::vector<MaxMin_x2*>& chils,unsigned short& count);

	static void junction(std::vector<ae::ga::MaxMin_x2*>& p,std::map<ae::ga::MaxMin_x2*,Notas>& e,unsigned short& idCount);
	static void eval_x2(const std::vector<ae::ga::MaxMin_x2*>& population,std::map<ae::ga::MaxMin_x2*,Notas>& evaluation);
	static void saveEvals(const std::string& prefixfn, const std::map<ae::ga::MaxMin_x2*,Notas>& result, unsigned short iteration);
	static int main(int argc, const char* argv[]);
private:
	MaxMin_R maxmin;
	//Junction juntion;
};
struct MaxMin_By_Value
{
	ae::ga::MaxMin_x2* maxmin;
	float value;
};
*/


class SudokuChromosome : public Chromosome
{
public:
	SudokuChromosome();
	geneUS getNumber(unsigned short i,unsigned short j) const;
	
	geneUS& number(unsigned short i,unsigned short j);
	virtual void combine(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void copycombine(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void copy(const ae::Chromosome& P1,const ae::Chromosome& P2);
	virtual void mutate(float p);
	virtual void randFill();
private:
	geneUS numbers[3][3];
};

class SudokuSingle : public Single
{
public:
	SudokuSingle(unsigned int id,const SudokuChromosome[3][3]);
	SudokuSingle(unsigned int id,const SudokuChromosome[3][3],const Junction& junction);
	const SudokuChromosome& getTalba(unsigned short i,unsigned short j)const;
	
	static int main(int argc, const char* argv[]);
	virtual void eval();
	virtual void randFill();
	virtual void juncting(ID& idCount,std::list<ae::Single*>& chils,ae::Single* single);
	virtual void saveEval(const std::string& prefixfn, const std::list<ae::Single*>& result, unsigned short iteration);
private:
	SudokuChromosome tabla[3][3];
};


}

#endif