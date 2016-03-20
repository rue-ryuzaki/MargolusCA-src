#ifndef MARGOLUS_QUASI_X_H
#define MARGOLUS_QUASI_X_H

#include <vector>
#include "margolus_base.h"

struct CellX {
    CellX(Cell cell) : central(cell) { }
    
    Cell central;
    vector<Cell> neighbours;
};

class MargolusQuasiX : public Margolus {
public:
    MargolusQuasiX();
    MargolusQuasiX(Sizes sizes);
    MargolusQuasiX(cuint& sizeX, cuint& sizeY, cuint sizeZ = 1);
    ~MargolusQuasiX();
    
    void QuasiCalculation();
    
private:
    void QuasiCalculation2D();
    void QuasiCalculation3D();
    double NeighbourEnergy(cuint& ix, cuint& iy, cuint& iz = 0);
    double CalculationBlockEnergy(const Block& block, cuint& ix, cuint& iy);
    double CalculationBlockEnergy(const Block3D& block, cuint& ix, cuint& iy, cuint& iz);
};

#endif /* MARGOLUS_QUASI_X_H */
