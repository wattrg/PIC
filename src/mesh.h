#include "setup.h"

#ifndef mesh_h
#define mesh_h

class mesh {
 
public:
    std::vector<std::vector<double>> cellCntr; // must be cartesian grid
    std::vector<double> dx;
    std::vector<int> nCells;
    std::vector<double> lo, hi;
    std::vector<double> data; // 1D only
    std::vector<double> source; // 1D only
    double V; // cartesian only

    mesh(std::vector<double> lo, std::vector<double> hi, std::vector<int> nCells);

    void CleanSource();
    void CleanData();
    void growGhost(); // implementation assumes periodic BC
    void shrinkGhost(); // implementation assumes periodic BC
};

#endif // mesh_h