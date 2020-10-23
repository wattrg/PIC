#include <iostream>
#include "particle.h"
#include "setup.h"
#include "ParmParse.h"
#include "io.h"
#include "mesh.h"
#include "EM.h"
#include <fstream>
#include "advance.h"
#include <mpi.h>

setup PIC;

int main(int argc, char* argv[])
{
    
    // Initialise the MPI environment
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "MPI initialised with " << world_size << " processors" << std::endl;



    // Initialise the simulation
    PIC.init(argv[1]);
    
    
    // I want to include this in PIC.init eventually
    particleContainer pc;
    for (int i = 0; i < PIC.nParticles; i++){
        particle p("electron",PIC.pos_init[i], PIC.vel_init[i], & pc.shpFncParam, -1.0, 0.01);
        pc.particles.push_back(p);
    }

    mesh grid (PIC.lo, PIC.hi, PIC.n_cells);
    std::cout << "Problem initialised \n";

    // run the simulation
    advance::run(grid, pc); 

    
    MPI_Finalize();
    
}
