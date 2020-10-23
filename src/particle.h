#include<vector>
#include"setup.h"
#include "mesh.h"


#ifndef particle_H
#define particle_H

/*
particle class
*/
class particle {
private:
	std::string name;
	double q;
	double m;
	std::vector<double> pos;
	std::vector<double> vel;
	std::vector<double> pExt;
	int * sfo;
	

public:
	
	particle();
	particle(char const* n, std::vector<double> x, std::vector<double> v, int * l, double charge, double mass);

	
	void print_pos(bool el);
	void print_vel(bool el);
	void moveParticle();
	double bspline(double zeta, int l);
	double shpFnc(std::vector<double> xPrime);
	double interpFnc(std::vector<double> xPrime);
	void particleToGrid(mesh & grid);
	void applyParticleForce(mesh & grid);
};


/*
container of particles
*/
class particleContainer {
public:
	int np;
	int shpFncParam;
	std::vector<particle> particles;
	

	particleContainer ();
	
	void moveParticles();
	void particlesToGrid(mesh & grid);
	void applyParticleForces(mesh & grid);
	void printPos();
	void printVel();
	
};







#endif // !particle_H
