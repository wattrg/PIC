#pragma once

#include<vector>
#include"setup.h"
#include <string>

#ifndef particle_H
#define particle_H

class particle {
private:
	std::string name;
	double q;
	double m;
	std::vector<double> pos;
	std::vector<double> vel;

public:
	particle();
	particle(char n, std::vector<double> x, std::vector<double> v);

	void print_pos();
	void print_vel();
};

#endif // !particle_H
