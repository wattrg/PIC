#include <iostream>
#include "particle.h"
#include "setup.h"
#include "ParmParse.h"
#include "io.h"
#include "mesh.h"
#include "EM.h"
#include <fstream>


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

    

    std::cout << "Beginning Simulation" << std::endl;
    while (PIC.t < PIC.max_time && PIC.step < PIC.max_steps){
        // PIC step 1: update particle position
        pc.moveParticles();



        // PIC step 2: project particles onto the grid
        // (calculating charge density)
        
        pc.particlesToGrid(grid); // grid.source now stores charge density
        
        //PIC_IO::printVec(grid.source);
        //pc.printPos();

        // PIC step 3: compute electric field
        grid.growGhost();
        grid.CleanData();
        EM::poisson1D(grid.data, grid.source, PIC.dx[0]); //grid.data now stores electric potential
        grid.shrinkGhost();
        grid.growGhost();
        //PIC_IO::printVec(grid.source);
        //PIC_IO::printVec(grid.data);
        EM::phiToE(grid.data, PIC.dx[0]); // grid.data now stores electric field
        grid.shrinkGhost();


        // PIC step 4: compute forces and update velocity
        pc.applyParticleForces(grid);

        

        // some book keeping
        PIC.t += PIC.dt;
        PIC.step += 1;

        if (PIC.step % PIC.print_int == 0){
            std::cout << "    Step: " << PIC.step << ",   Time: " << PIC.t <<std::endl;
        }

        if (PIC.step % PIC.plot_int == 0 || PIC.step == 1){
            PIC_IO::writeFile(grid.source);
        }
    
    }
    std::cout << "Complete" << std::endl;
    

    
}
