#include "mesh.h"
#include "setup.h"
#include "io.h"

// data stored in the mesh is only 1D for the moment
mesh::mesh(std::vector<double> lo, std::vector<double> hi, std::vector<int> nCells)
{
    this->nCells = nCells;
    this->lo = lo;
    this->hi = hi;

    this->cellCntr.resize(PIC.dim);
    this->dx.resize(PIC.dim);


    for (int idim = 0; idim < PIC.dim; idim++){
        this->dx[idim] = (hi[idim] - lo[idim])/nCells[idim];
        data.resize(nCells[idim]);
        source.resize(nCells[idim]);
        for (int i = 0; i < this->nCells[idim]; i++){
            this->cellCntr[idim].push_back(this->lo[idim] + (i+0.5)*this->dx[idim]);
        }
        
    }

    V = 1.0;
	for (int i = 0; i < PIC.dim; i++){
		V = V * dx[i];
	}

}

void mesh::CleanSource(){
    std::fill(source.begin(), source.end(), 0.0);
}
void mesh::CleanData(){
    std::fill(data.begin(), data.end(), 0.0);
}

void mesh::growGhost(){
    source.insert(source.begin(), source.back());
    source.push_back(source[1]);
    data.insert(data.begin(), data.back());
    data.push_back(data[1]);
}
void mesh::shrinkGhost(){
    source.erase(source.begin());
    source.pop_back();
    data.erase(data.begin());
    data.pop_back();

}


