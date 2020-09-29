#include "ParmParse.h"
#include <fstream>
#include <iostream>

#ifndef setup_H
#define setup_H

/*
Class to handle information about the sim
(e.g. information from the lua file)
*/
class setup {
public:
	
	//Data read from lua
	int                              dim;
	double                           dt;
	std::vector<int>                 n_cells;
	std::vector<double>              lo, hi;
	int                              nParticles;
	double                           freq_plasma;
	double                           m;
	double                           q;
	int                              verbose;
	double                           rho_back;
	std::vector<std::vector<double>> pos_init;
	std::vector<std::vector<double>> vel_init;
	char const *                     particle_step;
	char const *                     fieldss_step;
	double                           start_time;
	double                           max_time;
	int                              max_steps;
	int                              print_int;
	int                              plot_int;

	// other data stored
	double t;
	int step;
	std::vector<double> dx;
	std::ofstream outfile;

	
	// Sets defaults based on defaults file
	setup() {
		readLua("../src/defaults.lua");
	}

	// gets information from lua script
	void readLua(char const * file){
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

	// performs the initial setup
	void init(char const * file){
		readLua(file);
		t = start_time;
		step = 0;
		dx.resize(dim);
		for (int idim = 0; idim < dim; idim++){
			dx[idim] = (hi[idim]-lo[idim])/n_cells[idim];
		}
	}
};

extern setup PIC;


#endif // !setup_H





