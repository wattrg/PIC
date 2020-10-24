#include <iostream>
#include "particle.h"
#include "setup.h"
#include "ParmParse.h"
#include "io.h"
#include "mesh.h"
#include "EM.h"
#include <fstream>
#include "advance.h"

#ifdef _OPENMP
#include <omp.h>
#endif // OMP


setup PIC;

int main(int argc, char* argv[])
{
#ifdef _OPENMP
    omp_set_num_threads(2);
    std::cout << "Using openMP" << std::endl;
#endif // OMP
 

    // Initialise the simulation
    PIC.init(argv[1]);
    
    
    // I want to include this in PIC.init eventually
    particleContainer * pc = new particleContainer;
#ifdef _OPENMP
    #pragma omp parallel for
#endif // OMP
        for (int i = 0; i < PIC.nParticles; i++)
        {
            particle p("electron",PIC.pos_init[i], PIC.vel_init[i], &(*pc).shpFncParam, PIC.q, PIC.m);
            //pc.particles.push_back(p);
            (*pc).particles[i] = p;
        }

    mesh grid (PIC.lo, PIC.hi, PIC.n_cells);
    std::cout << "Problem initialised \n";

    // run the simulation
    advance::run(&grid, pc); 

    
    
}
