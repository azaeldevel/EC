

#ifndef AE_GA_EXT_HH
#define AE_GA_EXT_HH


#include "GA.hh"


namespace ae::ga
{


struct Notas
{
	float x2_max;//la tendecia hacia 0 es mejor
	float x2_min;//la tendecia hacia 0 es mejor

	float strength;
};
class MaxMin_x2 : public ae::ga::Single
{
public:
	MaxMin_x2(unsigned int id,geneF x2_mx,geneF x2_min,geneUS number,geneUS algorit);
	MaxMin_x2(unsigned int id,MaxMin_R mm,Junction j);

public:
	MaxMin_R& getMaxMin();

	virtual void junction(MaxMin_x2& single,std::vector<MaxMin_x2*>& chils,unsigned short& count);

	static void junction(std::vector<ae::ga::MaxMin_x2*>& p,std::map<ae::ga::MaxMin_x2*,Notas>& e,unsigned short& idCount);
	static void eval_x2(const std::vector<ae::ga::MaxMin_x2*>& population,std::map<ae::ga::MaxMin_x2*,Notas>& evaluation);
	static void saveEvals(const std::string& prefixfn, const std::map<ae::ga::MaxMin_x2*,Notas>& result, unsigned short iteration);
	static int main(int argc, const char* argv[]);
private:
	MaxMin_R maxmin;
	Junction juntion;
};
struct MaxMin_By_Value
{
	ae::ga::MaxMin_x2* maxmin;
	float value;
};

}

#endif