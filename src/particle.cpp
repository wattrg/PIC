#include "particle.h"
#include <iostream>
#include "io.h"
#include "advance.h"
#include "mesh.h"
#include <math.h>

particle::particle() {
	name = "None";
	q = 0.0;
	m = 0.0;
	for (int i = 1; i <= PIC.dim; i++) {
		pos.push_back(0.0);
		vel.push_back(0.0);
	}
	sfo = nullptr;
}

particle::particle(char const * n, std::vector<double> x, std::vector<double> v, int * l, double charge, double mass) {
	name = n;
	pos = x;
	vel = v;
	sfo = l;
	q = charge;
	m = mass;
	pExt.resize(PIC.dim);
	for (int idim = 0; idim < PIC.dim; idim++){
		pExt[idim] = PIC.dx[idim];
	}
}


void particle::print_pos(bool el = true){
	PIC_IO::printVec(pos, el);
}

void particle::print_vel(bool el = true){
	PIC_IO::printVec(vel, el);
}

void particle::moveParticle(){
	// step the particle forward
	advance::RK(this->pos, this->vel, PIC.dt);

	// temporary periodic bc while I don't have proper \
	boundary conditions
	for (int i = 0; i < PIC.dim; i++){
		if (pos[i] < PIC.lo[i]){
			pos[i] += PIC.hi[i] - PIC.lo[i];
		}
		else if (pos[i] > PIC.hi[i]) {
			pos[i] -= PIC.hi[i] - PIC.lo[i];
		}
	}
}

// 1D only
void particle::particleToGrid(mesh & grid){
	for (int idim = 0; idim < PIC.dim; idim ++){
		for (std::vector<double>::size_type i = 0; i != grid.data.size(); i++){
			std::vector<double> xprime = {grid.cellCntr[idim][i] - pos[idim]};
			grid.source[i] += q * interpFnc(xprime);
		}
	}
}

double particle::bspline(double zeta, int l){
	switch (l)
	{
	case 0:
		if (zeta < 0.5 && zeta > -0.5){
			return 1.0;
		}
		else{
			return 0.0;
		}
		break;

	case 1:
		if (zeta > -1.0 && zeta < 0.0){
			return (zeta + 1);
		}
		else if (zeta >= 0.0 && zeta < 1.0){
			return (1 - zeta);
		}
		else{
			return 0.0;
		}
	
	default:
		break;
	}
}

double particle::shpFnc(std::vector<double> xPrime){
	double V = 1;
	double S = 1;
	for (int idim = 0; idim < PIC.dim; idim++){
		V = V*this->pExt[idim];
		S = S * bspline(xPrime[idim]/this->pExt[idim], *this->sfo);
	}
	return (S/V);
}

double particle::interpFnc(std::vector<double> xPrime){
	double S = 1;
	for (int idim = 0; idim < PIC.dim; idim++){
		S = S * bspline(xPrime[idim]/this->pExt[idim], *this->sfo+1);
	}
	return S;
}

// 1D only
void particle::applyParticleForce(mesh & grid){
	// find the index of the cell the particle is in
	int indx = int ( (pos[0] - grid.lo[0])/grid.dx[0] );

	// electric field in the cell
	double E = grid.data[indx];

	// calculate acceleration
	std::vector<double> accel = {E * q / m};

	// update velocity
	advance::RK(vel, accel, PIC.dt);

}



particleContainer::particleContainer () {
	np = PIC.nParticles;
	shpFncParam = 0;
}

void particleContainer::moveParticles() {
	for (int i = 0; i < np; i++){
		particles[i].moveParticle();
	}
}

void particleContainer::particlesToGrid(mesh & grid){
	// first make sure the sources are zero
	grid.CleanSource();

	// now loop over the contribution of all the particles
	for (particle & p : particles){
		p.particleToGrid(grid);
	}

	// divide by the volume and add rho_back
	for (double & s : grid.source){
		s = s/grid.V + PIC.rho_back;
	}

}

void particleContainer::applyParticleForces(mesh & grid){
	for (particle & p : particles){
		p.applyParticleForce(grid);
	}
}

void particleContainer::printPos(){
	std::cout << "[";
	for (particle & p : particles){
		p.print_pos(false);
		std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

void particleContainer::printVel(){
	std::cout << "[";
	for (particle & p : particles){
		p.print_vel(false);
		std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

