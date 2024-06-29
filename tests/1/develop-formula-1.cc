

#include "nodes.hh"
#include "formule.hh"

namespace ec = oct::ec::v1;

int main(int argc, char *argv[])
{
    ec::Number<float> num1(5.0f);
    ec::Number<float> num2(1.9f);
    ec::Number<float> num3(3.9f);
    ec::Number<float> num4(3.0f);
    ec::Variable<float> var1("a");
    ec::Variable<float> var2("b");
    ec::Addition<float> op1(num1,num2);
    ec::Addition<float> op2(op1,num3);
    ec::Subtration<float> op3(op2,num2);
    ec::Divition<float> op4(op1,num2);
    ec::Pow<float> op5(num2,num4);
    ec::Product<float> op6(num1,num3);
    ec::Product<float> op7(var1,var2);
    std::cout <<"Developing...\n";
    float result = op1;
    float result2 = op2;
    float result3 = op3;
    std::cout <<"Result 1 : " << result << "\n";
    std::cout <<"Result 2 : " << result2 << "\n";
    std::cout <<"Result 3 : " << result3 << "\n";
    std::cout <<"\n";
    op3.print(std::cout);
    std::cout << "\n";
    op4.print(std::cout);
    std::cout << " = " << (float)op4 << "\n";
    std::cout << "\n";
    op7.print(std::cout);
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> numgen(0.0f,1.0f);
    size_t variables = 3;
    size_t deep = 5;
    //numgen(rng);
    ec::Formule fm1;
    fm1.generate(variables,deep,numgen,rng);
    //fm1.print(std::cout);


    return EXIT_SUCCESS;
}
