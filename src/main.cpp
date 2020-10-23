#include <iostream>
#include "particle.h"
#include "setup.h"
#include "ParmParse.h"
#include "io.h"
#include "mesh.h"
#include "EM.h"
#include <fstream>
#include "advance.h"

setup PIC;

int main(int argc, char* argv[])
{
    // Initialise the simulation
    std::cout << "Initialising from " << argv[1] << "...    ";
    PIC.init(argv[1]);
    
    
    // I want to include this in PIC.init eventually
    particleContainer pc;
    for (int i = 0; i < PIC.nParticles; i++){
        particle p("electron",PIC.pos_init[i], PIC.vel_init[i], & pc.shpFncParam, -1.0, 0.01);
        pc.particles.push_back(p);
    }

    mesh grid (PIC.lo, PIC.hi, PIC.n_cells);
    std::cout << "Complete\n";

    // run the simulation
    advance::run(grid, pc); 

    
    
}
