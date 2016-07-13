#ifndef MARGOLUS_QUASI_H
#define MARGOLUS_QUASI_H

#include "margolus_base.h"

class MargolusQuasi : public Margolus {
public:
    MargolusQuasi();
    explicit MargolusQuasi(Sizes sizes);
    MargolusQuasi(cuint& sizeX, cuint& sizeY, cuint sizeZ = 1);
    ~MargolusQuasi();
    
    void QuasiCalculation(cuint& dx, cuint& dy);
    void QuasiCalculation(cuint& dx, cuint& dy, cuint& dz);
    
private:
    double CalculationBlockEnergy(const Block& block, cuint& ix, cuint& iy);
    double CalculationBlockEnergy(const Block3D& block, cuint& ix, cuint& iy, cuint& iz);
    double QuasiBlockEnergy(const Block& block);
    double QuasiBlockEnergy(const Block3D& block);
};

#endif /* MARGOLUS_QUASI_H */
