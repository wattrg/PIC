
#include<vector>

#ifndef advance_h
#define advance_h

namespace advance
{
    void RK (std::vector<double> & S, std::vector<double> & dSdt, double dt);  
    std::vector<double> multiplyVecConstant (std::vector<double> & vec, double & c);
    std::vector<double> addVecVec (std::vector<double> vec1, std::vector<double> vec2);
}

#endif