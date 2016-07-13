#include "margolus_quasi_x.h"

MargolusQuasiX::MargolusQuasiX() : MargolusQuasiX(1, 1, 1) { }

MargolusQuasiX::MargolusQuasiX(Sizes sizes) : Margolus(sizes.x, sizes.y, sizes.z) { }

MargolusQuasiX::MargolusQuasiX(cuint& sizeX, cuint& sizeY, cuint sizeZ)
        : Margolus(sizeX, sizeY, sizeZ) { }

MargolusQuasiX::~MargolusQuasiX() { }

void MargolusQuasiX::QuasiCalculation() {
    if (GetSizeZ() == 1) {
        QuasiCalculation2D();
    } else {
        QuasiCalculation3D();
    }
}

void MargolusQuasiX::QuasiCalculation2D() {
    if (modifierMove) {
        // TODO
        
    } else {
        switch (movement) {
            case 1: // -x
                for (int ix = 1; ix < GetSizeX(); ++ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        if (cells[ix][iy][0].HaveActive() && !cells[ix - 1][iy][0].HaveSolid()) {
                            // curr
                            double currEn = exp(0);
                            // moved
                            double moveEn = exp(- *steamEnergy_ / (R * *T));
                            //normalization
                            double rnd = double(rand()) / RAND_MAX;
                            if (rnd >= (currEn / (currEn + moveEn))) {
                                // move!
                                Cell inCell = Cell();
                                for (pSub & sub : cells[ix][iy][0].GetSubs()) {
                                    if (sub->GetType() == ACTIVE) {
                                        cells[ix - 1][iy][0].AddSub(sub);
                                    } else {
                                        inCell.AddSub(sub);
                                    }
                                }
                                cells[ix][iy][0] = inCell;
                            }
                        }
                    }
                }
                break;
            case 2: // +x
                for (int ix = GetSizeX() - 2; ix >= 0; --ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        if (cells[ix][iy][0].HaveActive() && !cells[ix + 1][iy][0].HaveSolid()) {
                            // curr
                            double currEn = exp(0);
                            // moved
                            double moveEn = exp(- *steamEnergy_ / (R * *T));
                            //normalization
                            double rnd = double(rand()) / RAND_MAX;
                            if (rnd >= (currEn / (currEn + moveEn))) {
                                // move!
                                Cell inCell = Cell();
                                for (pSub & sub : cells[ix][iy][0].GetSubs()) {
                                    if (sub->GetType() == ACTIVE) {
                                        cells[ix + 1][iy][0].AddSub(sub);
                                    } else {
                                        inCell.AddSub(sub);
                                    }
                                }
                                cells[ix][iy][0] = inCell;
                            }
                        }
                    }
                }
                break;
            case 3: // -y
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = 1; iy < GetSizeY(); ++iy) {
                        if (cells[ix][iy][0].HaveActive() && !cells[ix][iy - 1][0].HaveSolid()) {
                            // curr
                            double currEn = exp(0);
                            // moved
                            double moveEn = exp(- *steamEnergy_ / (R * *T));
                            //normalization
                            double rnd = double(rand()) / RAND_MAX;
                            if (rnd >= (currEn / (currEn + moveEn))) {
                                // move!
                                Cell inCell = Cell();
                                for (pSub & sub : cells[ix][iy][0].GetSubs()) {
                                    if (sub->GetType() == ACTIVE) {
                                        cells[ix][iy + 1][0].AddSub(sub);
                                    } else {
                                        inCell.AddSub(sub);
                                    }
                                }
                                cells[ix][iy][0] = inCell;
                            }
                        }
                    }
                }
                break;
            case 4: // +y
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = GetSizeY() - 2; iy >= 0; --iy) {
                        if (cells[ix][iy][0].HaveActive() && !cells[ix][iy + 1][0].HaveSolid()) {
                            // curr
                            double currEn = exp(0);
                            // moved
                            double moveEn = exp(- *steamEnergy_ / (R * *T));
                            //normalization
                            double rnd = double(rand()) / RAND_MAX;
                            if (rnd >= (currEn / (currEn + moveEn))) {
                                // move!
                                Cell inCell = Cell();
                                for (pSub & sub : cells[ix][iy][0].GetSubs()) {
                                    if (sub->GetType() == ACTIVE) {
                                        cells[ix][iy - 1][0].AddSub(sub);
                                    } else {
                                        inCell.AddSub(sub);
                                    }
                                }
                                cells[ix][iy][0] = inCell;
                            }
                        }
                    }
                }
                break;
        }
    }
}

void MargolusQuasiX::QuasiCalculation3D() {
    if (modifierMove) {
        // TODO
        
    } else {
        switch (movement) {
            case 1: // -x
                for (int ix = 1; ix < GetSizeX(); ++ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        for (int iz = 0; iz < GetSizeZ(); ++iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix - 1][iy][iz].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix - 1][iy][iz].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
            case 2: // +x
                for (int ix = GetSizeX() - 2; ix >= 0; --ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        for (int iz = 0; iz < GetSizeZ(); ++iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix + 1][iy][iz].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix + 1][iy][iz].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
            case 3: // -y
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = 1; iy < GetSizeY(); ++iy) {
                        for (int iz = 0; iz < GetSizeZ(); ++iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix][iy - 1][iz].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix][iy - 1][iz].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
            case 4: // +y
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = GetSizeY() - 2; iy >= 0; --iy) {
                        for (int iz = 0; iz < GetSizeZ(); ++iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix][iy + 1][iz].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix][iy + 1][iz].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
            case 5: // -z
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        for (int iz = 1; iz < GetSizeZ(); ++iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix][iy][iz - 1].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix][iy][iz - 1].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
            case 6: // +z
                for (int ix = 0; ix < GetSizeX(); ++ix) {
                    for (int iy = 0; iy < GetSizeY(); ++iy) {
                        for (int iz = GetSizeZ() - 2; iz >= 0; --iz) {
                            if (cells[ix][iy][iz].HaveActive() && !cells[ix][iy][iz + 1].HaveSolid()) {
                                // curr
                                double currEn = exp(0);
                                // moved
                                double moveEn = exp(- *steamEnergy_ / (R * *T));
                                //normalization
                                double rnd = double(rand()) / RAND_MAX;
                                if (rnd >= (currEn / (currEn + moveEn))) {
                                    // move!
                                    Cell inCell = Cell();
                                    for (pSub & sub : cells[ix][iy][iz].GetSubs()) {
                                        if (sub->GetType() == ACTIVE) {
                                            cells[ix][iy][iz + 1].AddSub(sub);
                                        } else {
                                            inCell.AddSub(sub);
                                        }
                                    }
                                    cells[ix][iy][iz] = inCell;
                                }
                            }
                        }
                    }
                }
                break;
        }
    }
}

double MargolusQuasiX::NeighbourEnergy(cuint& ix, cuint& iy, cuint& iz) {
    double sumEnergy = 0.0;
    
    Cell cellIn = cells[ix][iy][iz];
    Cell cellOut;
    
    if (ix > 1) {
        cellOut = cells[ix - 1][iy][iz];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    if (ix < GetSizeX() - 2) {
        cellOut = cells[ix + 1][iy][iz];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    if (iy > 1) {
        cellOut = cells[ix][iy - 1][iz];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    if (iy < GetSizeY() - 2) {
        cellOut = cells[ix][iy + 1][iz];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    if (iz > 1) {
        cellOut = cells[ix][iy][iz - 1];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    if (iz < GetSizeZ() - 2) {
        cellOut = cells[ix][iy][iz + 1];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    
    for (pSub & subA : cellIn.GetSubs()) {
        if (subA->GetType() == ACTIVE) {
            for (pSub & subM : cellIn.GetSubs()) {
                if (subM->GetType() == MODIFIER) {
                    sumEnergy += GetEnergyCell(subA->GetName(), subM->GetName());
                }
            }
        }
    }
    
    return sumEnergy;
}

double MargolusQuasiX::CalculationBlockEnergy(const Block& block, cuint& ix, cuint& iy) {
    double sumEnergy = 0.0;
    
    Cell cellIn, cellOut;
    //x gran 1
    if (ix > 0) {
        cellIn = block.cells[0][1];
        cellOut = cells[ix - 1][iy + 1][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
        cellIn = block.cells[0][0];
        cellOut = cells[ix - 1][iy][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    //x gran 2
    if (ix < GetSizeX() - 2) {
        cellIn = block.cells[1][1];
        cellOut = cells[ix + 2][iy + 1][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
        cellIn = block.cells[1][0];
        cellOut = cells[ix + 2][iy][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    //y gran 1
    if (iy > 0) {
        cellIn = block.cells[1][0];
        cellOut = cells[ix + 1][iy - 1][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
        cellIn = block.cells[0][0];
        cellOut = cells[ix][iy - 1][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    //y gran 2
    if (iy < GetSizeY() - 2) {
        cellIn = block.cells[1][1];
        cellOut = cells[ix + 1][iy + 2][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
        cellIn = block.cells[0][1];
        cellOut = cells[ix][iy + 2][0];
        PareEnergy(cellIn, cellOut, sumEnergy);
    }
    //inside block
    for (uint i = 0; i < 4; ++i) {
        cellIn = block.cells[indexF[i][0]][indexF[i][1]];
        cellOut = block.cells[indexF[i + 1][0]][indexF[i + 1][1]];
        PareEnergyFull(cellIn, cellOut, sumEnergy);
    }
    
    return sumEnergy;
}

double MargolusQuasiX::CalculationBlockEnergy(const Block3D& block, cuint& ix,
        cuint& iy, cuint& iz) {
    double sumEnergy = 0.0;
    
    Cell cellIn, cellOut;
    
    //x gran 1
    if (ix > 0) {
        for (uint z = 0; z < 2; ++z) {
            cellIn = block.cells[0][1][z];
            cellOut = cells[ix - 1][iy + 1][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
            cellIn = block.cells[0][0][z];
            cellOut = cells[ix - 1][iy][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    //x gran 2
    if (ix < GetSizeX() - 2) {
        for (uint z = 0; z < 2; ++z) {
            cellIn = block.cells[1][1][z];
            cellOut = cells[ix + 2][iy + 1][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
            cellIn = block.cells[1][0][z];
            cellOut = cells[ix + 2][iy][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    //y gran 1
    if (iy > 0) {
        for (uint z = 0; z < 2; ++z) {
            cellIn = block.cells[1][0][z];
            cellOut = cells[ix + 1][iy - 1][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
            cellIn = block.cells[0][0][z];
            cellOut = cells[ix][iy - 1][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    //y gran 2
    if (iy < GetSizeY() - 2) {
        for (uint z = 0; z < 2; ++z) {
            cellIn = block.cells[1][1][z];
            cellOut = cells[ix + 1][iy + 2][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
            cellIn = block.cells[0][1][z];
            cellOut = cells[ix][iy + 2][iz + z];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    //z gran 1
    if (iz > 0) {
        for (uint i = 0; i < 4; ++i) {
            cellIn = block.cells[indexF[i][0]][indexF[i][1]][0];
            cellOut = cells[ix + indexF[i][0]][iy + indexF[i][1]][iz - 1];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    //z gran 2
    if (iz < GetSizeZ() - 2) {
        for (uint i = 0; i < 4; ++i) {
            cellIn = block.cells[indexF[i][0]][indexF[i][1]][1];
            cellOut = cells[ix + indexF[i][0]][iy + indexF[i][1]][iz + 2];
            PareEnergy(cellIn, cellOut, sumEnergy);
        }
    }
    
    //inside block
    for (uint i = 0; i < 4; ++i) {
        for (uint z = 0; z < 2; ++z) {
            cellIn = block.cells[indexF[i][0]][indexF[i][1]][z];
            cellOut = block.cells[indexF[i + 1][0]][indexF[i + 1][1]][z];
            PareEnergyFull(cellIn, cellOut, sumEnergy);
        }
        {
            cellIn = block.cells[indexF[i][0]][indexF[i][1]][0];
            cellOut = block.cells[indexF[i][0]][indexF[i][1]][1];
            PareEnergyFull(cellIn, cellOut, sumEnergy);
        }
    }
    
    return sumEnergy;
}
