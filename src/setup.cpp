#include "setup.h"

void setup::readLua(char const * file){
		ParmParse pp (file);

		pp.readVariable<int>(dim, "dim");
		pp.readVariable<std::vector<int>>(n_cells, "n_cells");
		pp.readVariable<int>(nParticles, "nParticles");
		pp.readVariable<std::vector<double>>(lo, "lo");
		pp.readVariable<std::vector<double>>(hi,"hi");
		pp.readVariable<double>(freq_plasma, "freq_plasma");
		pp.readVariable<double>(m, "m");
		pp.readVariable<double>(q,"q");
		pp.readVariable<int>(verbose, "verbose");
		pp.readVariable<std::vector<std::vector<double>>> (pos_init, "pos_init");
		pp.readVariable<std::vector<std::vector<double>>> (vel_init, "vel_init");
		pp.readVariable<char const *>(particle_step, "particle_step");
		pp.readVariable<char const *>(fieldss_step, "fields_step");
		pp.readVariable<double> (dt, "dt");
		pp.readVariable<double> (start_time, "start_time");
		pp.readVariable<double> (max_time, "stop_time");
		pp.readVariable<int> (max_steps, "max_steps");
		pp.readVariable<double> (rho_back, "rho_back");
		pp.readVariable<int> (print_int, "print_int");
		pp.readVariable<int> (plot_int, "plot_int");
}

void setup::init(char const * file){
    setup();
    if (file != NULL)
    {
        std::cout << "Initialising from " << file << "...   ";
        readLua(file);
    }
    else
    {
        std::cout << "No input file, terminating\n";
        exit(0);
    }
    
    t = start_time;
    step = 0;
    dx.resize(dim);
    for (int idim = 0; idim < dim; idim++){
        dx[idim] = (hi[idim]-lo[idim])/n_cells[idim];
    }
}