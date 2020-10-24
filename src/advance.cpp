#include "advance.h"
#include "setup.h"
#include "io.h"
#include "EM.h"

std::vector<double> advance::multiplyVecConstant(std::vector<double> & vec, double & c)
{
    std::vector<double> result;
    int length = vec.size();
    result.resize(length);
#ifdef _OPENMP
    #pragma omp parallel for
#endif
        for (int i = 0; i < length; i++){
            result[i] = (vec[i] * c);
        }
    return result;
}

std::vector<double> advance::addVecVec (std::vector<double>  vec1, std::vector<double>  vec2){
    std::vector<double> result;
    int length = vec1.size();
    result.resize(length);
#ifdef _OPENMP
    #pragma omp parallel for
#endif
        for (int i = 0; i < length; i++){
            result[i] = (vec1[i] + vec2[i]);
        }
    return result;
}

void advance::RK (std::vector<double> & S, std::vector<double> & dSdt, double dt)
{
    S = addVecVec(S, multiplyVecConstant(dSdt, dt));
}

void advance::run (mesh  * grid, particleContainer * pc)
{

    std::cout << "Beginning Simulation" << std::endl;
    while (PIC.t < PIC.max_time && PIC.step < PIC.max_steps){
        // PIC step 1: update particle position
        (*pc).moveParticles();



        // PIC step 2: project particles onto the grid
        // (calculating charge density)
        
        (*pc).particlesToGrid(*grid); // grid.source now stores charge density
        
        //PIC_IO::printVec(grid.source);
        //pc.printPos();

        // PIC step 3: compute electric field
        (*grid).growGhost();
        (*grid).CleanData();
        EM::poisson1D((*grid).data, (*grid).source, PIC.dx[0]); //grid.data now stores electric potential
        (*grid).shrinkGhost();
        (*grid).growGhost();
        EM::phiToE((*grid).data, PIC.dx[0]); // grid.data now stores electric field
        (*grid).shrinkGhost();


        // PIC step 4: compute forces and update velocity
        (*pc).applyParticleForces(*grid);

        

        // some book keeping
        PIC.t += PIC.dt;
        PIC.step += 1;

        if (PIC.step % PIC.print_int == 0){
            std::cout << "    Step: " << PIC.step << ",   Time: " << PIC.t <<std::endl;
        }

        if (PIC.step % PIC.plot_int == 0 || PIC.step == 1){
            PIC_IO::writeFile((*grid).source);
        }
    
    }
    std::cout << "Complete" << std::endl;
}