#include "advance.h"
#include "setup.h"
#include "io.h"

std::vector<double> advance::multiplyVecConstant(std::vector<double> & vec, double & c)
{
    std::vector<double> result;
    int length = vec.size();
    for (int i = 0; i < length; i++){
        result.push_back(vec[i] * c);
    }
    return result;
}

std::vector<double> advance::addVecVec (std::vector<double>  vec1, std::vector<double>  vec2){
    std::vector<double> result;
    int length = vec1.size();
    for (int i = 0; i < length; i++){
        result.push_back(vec1[i] + vec2[i]);
    }
    // PIC_IO::printVec(vec1); std::cout << "+" << std::endl;
    // PIC_IO::printVec(vec2); std::cout << "=" << std::endl;
    // PIC_IO::printVec(result);
    return result;
}

void advance::RK (std::vector<double> & S, std::vector<double> & dSdt, double dt)
{
    //std::cout << "before move"; PIC_IO::printVec(S);
    S = addVecVec(S, multiplyVecConstant(dSdt, dt));
    //std::cout << "after move"; PIC_IO::printVec(S);
}