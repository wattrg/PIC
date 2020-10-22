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
	
	// Data read from lua
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
	void readLua(char const * file);

	// performs the initial setup
	void init(char const * file);
};

extern setup PIC;


#endif // !setup_H





