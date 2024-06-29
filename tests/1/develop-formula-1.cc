#include <iostream>

#include "nodes.hh"

namespace core = oct::core::v3;



int main(int argc, char *argv[])
{
    core::Number<float> num1(5.0f);
    core::Number<float> num2(1.9f);
    core::Number<float> num3(3.9f);
    core::Addition<float> op1(num1,num2);
    core::Addition<float> op2(op1,num3);
    core::Subtration<float> op3(op2,num2);
    std::cout <<"Developing...\n";
    float result = op1;
    float result2 = op2;
    float result3 = op3;
    std::cout <<"Result 1 : " << result << "\n";
    std::cout <<"Result 2 : " << result2 << "\n";
    std::cout <<"Result 3 : " << result3 << "\n";


    return EXIT_SUCCESS;
}
