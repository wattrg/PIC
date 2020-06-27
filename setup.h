#pragma once


#ifndef setup_H
#define setup_H

class setup {
public:
	int dim;
	std::vector<double> lo, hi;
	std::vector<double> dx;
	int nParticles;

	setup() {
		dim = 1;
		nParticles = 0;
		for (int i = 0; i < dim; i++) {
			lo.push_back(0.0);
			hi.push_back(0.0);
			dx.push_back(0.0);
		}

	}
};

extern setup PIC;


#endif // !setup_H





