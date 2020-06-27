#include "particle.h"
#include <iostream>
#include "setup.h"
#include <string>



particle::particle() {
	name = "None";
	q = 0.0;
	m = 0.0;
	for (int i = 1; i <= PIC.dim; i++) {
		pos.push_back(0.0);
		vel.push_back(0.0);
	}
}

particle::particle(char n, std::vector<double> x, std::vector<double> v) {
	name = n;
	pos = x;
	vel = v;
}

void particle::print_pos() {
	std::cout << "[";
	for (int i = 0; i < PIC.dim; i++) {
		std::cout << pos[i];
		if (i < PIC.dim - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}


void particle::print_vel() {
	std::cout << "[";
	for (int i = 0; i < PIC.dim; i++) {
		std::cout << vel[i];
		if (i < PIC.dim - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}
