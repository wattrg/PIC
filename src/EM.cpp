#include "EM.h"
#include <vector>
#include "setup.h"
#include "io.h"

void EM::poisson1D (std::vector<double> & phi, std::vector<double> & rho, double dx)
{
    int n = rho.size();
    std::vector<double> row (n, -1.0);
    std::vector<std::vector<double>> mat (n, row);

    // construct inverse poisson matrix
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                mat[i][j] = 1.0;
            }
            else if (j == i+1 || j == i-1){
                mat[i][j] = -2.0;
            }
        }
    }
    
    // perform the matrix multiplication
    // to calculate the electric potential
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            phi[i] += mat[i][j] * rho[i] * -1*dx*dx;
        }
    }
    
}

// 1D implementation
void EM::phiToE (std::vector<double> & data, double dx){
    std::vector<double> phi (data);
    for (unsigned int i = 1; i < data.size()+1; i++){
        data[i] = -(phi[i+1] - phi[i-1])/(2 * dx);
    }
    
}