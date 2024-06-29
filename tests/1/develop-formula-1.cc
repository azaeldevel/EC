

#include "nodes.hh"

namespace ec = oct::ec::v1;

int main(int argc, char *argv[])
{
    ec::Number<float> num1(5.0f);
    ec::Number<float> num2(1.9f);
    ec::Number<float> num3(3.9f);
    ec::Addition<float> op1(num1,num2);
    ec::Addition<float> op2(op1,num3);
    ec::Subtration<float> op3(op2,num2);
    ec::Divition<float> op4(op1,num2);
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


    return EXIT_SUCCESS;
}
