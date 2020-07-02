#include "mesh.h"
#include "particle.h"

#ifndef em_h
#define em_h

namespace EM
{
    void poisson1D (std::vector<double> & phi, std::vector<double>& rho, double dx);
    void phiToE (std::vector<double> & data, double dx);
}


#endif