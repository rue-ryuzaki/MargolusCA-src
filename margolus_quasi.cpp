#include "margolus_quasi.h"

MargolusQuasi::MargolusQuasi() : MargolusQuasi(1, 1, 1) { }

MargolusQuasi::MargolusQuasi(Sizes sizes) : Margolus(sizes.x, sizes.y, sizes.z) { }

MargolusQuasi::MargolusQuasi(cuint& sizeX, cuint& sizeY, cuint sizeZ)
        : Margolus(sizeX, sizeY, sizeZ) { }

MargolusQuasi::~MargolusQuasi() { }
    
void MargolusQuasi::QuasiCalculation(cuint& dx, cuint& dy, cuint& dz) {
//#pragma omp parallel for
    for (uint ix = dx; ix < GetSizeX() - 1; ix += 2) {
        for (uint iy = dy; iy < GetSizeY() - 1; iy += 2) {
            for (uint iz = dz; iz < GetSizeZ() - 1; iz += 2) {
                if (CheckEmpty(ix, iy, iz)) {
                    continue;
                }
                blockSize3D = 1;
                CreateRotateNotBlock3D(blocks3D[0], ix, iy, iz);
                if (modifierMove && CheckMod(ix, iy, iz)) {
                    if (CheckActive (ix, iy)) {
                        if (CheckCanRotate3D(ClockWiceX, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceX, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceX, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceX, ix, iy, iz);
                            ++blockSize3D;
                        }
                        if (CheckCanRotate3D(CounterClockWiceX, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceX, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceX, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceX, ix, iy, iz);
                            ++blockSize3D;
                        }
                        if (CheckCanRotate3D(ClockWiceY, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceY, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceY, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceY, ix, iy, iz);
                            ++blockSize3D;
                        }
                        if (CheckCanRotate3D(CounterClockWiceY, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceY, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceY, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceY, ix, iy, iz);
                            ++blockSize3D;
                        }
                        if (CheckCanRotate3D(ClockWiceZ, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceZ, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceZ, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceZ, ix, iy, iz);
                            ++blockSize3D;
                        }
                        if (CheckCanRotate3D(CounterClockWiceZ, ix, iy, iz)) {
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceZ, ix, iy, iz, false, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceZ, ix, iy, iz, true, true);
                            ++blockSize3D;
                            CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceZ, ix, iy, iz);
                            ++blockSize3D;
                        }
                    } else {
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceX, ix, iy, iz, false, true);
                        ++blockSize3D;
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceX, ix, iy, iz, false, true);
                        ++blockSize3D;
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceY, ix, iy, iz, false, true);
                        ++blockSize3D;
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceY, ix, iy, iz, false, true);
                        ++blockSize3D;
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceZ, ix, iy, iz, false, true);
                        ++blockSize3D;
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceZ, ix, iy, iz, false, true);
                        ++blockSize3D;
                    }
                } else {
                    if (CheckCanRotate3D(ClockWiceX, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceX, ix, iy, iz);
                        ++blockSize3D;
                    }
                    if (CheckCanRotate3D(CounterClockWiceX, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceX, ix, iy, iz);
                        ++blockSize3D;
                    }
                    if (CheckCanRotate3D(ClockWiceY, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceY, ix, iy, iz);
                        ++blockSize3D;
                    }
                    if (CheckCanRotate3D(CounterClockWiceY, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceY, ix, iy, iz);
                        ++blockSize3D;
                    }
                    if (CheckCanRotate3D(ClockWiceZ, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], ClockWiceZ, ix, iy, iz);
                        ++blockSize3D;
                    }
                    if (CheckCanRotate3D(CounterClockWiceZ, ix, iy, iz)) {
                        CreateRotateBlock3D(blocks3D[blockSize3D], CounterClockWiceZ, ix, iy, iz);
                        ++blockSize3D;
                    }
                }
                double Z = 0.0;
                // + Energy
                for (uint i = 0; i < blockSize3D; ++i) {
                    double energy = QuasiBlockEnergy(blocks3D[i]); //кДж/моль
                    blocks3D[i].energy = exp(-energy / (R * *T));
                    Z += blocks3D[i].energy;
                }
                //normalization
                double sumProbability = 0.0;
                double rnd = (double)(rand()) / RAND_MAX;
                for (uint i = 0; i < blockSize3D; ++i) {
                    sumProbability += blocks3D[i].energy / Z;
                    if (rnd <= sumProbability) {
                        ChangeBlock(blocks3D[i], ix, iy, iz);
                        break;
                    }
                }
            }
        }
    }
}

void MargolusQuasi::QuasiCalculation(cuint& dx, cuint& dy) {
//#pragma omp parallel for
    for (uint ix = dx; ix < GetSizeX() - 1; ix += 2) {
        for (uint iy = dy; iy < GetSizeY() - 1; iy += 2) {
            if (CheckEmpty(ix, iy)) {
                continue;
            }
            // 1
            blockSize = 1;
            CreateRotateNotBlock(blocks[0], ix, iy);
            if (modifierMove && CheckMod(ix, iy)) {
                if (CheckActive (ix, iy)) {
                    if (CheckCanClockWice(ix, iy)) {
                        CreateRotateBlock(blocks[blockSize], ClockWice, ix, iy, false, true);
                        ++blockSize;
                        CreateRotateBlock(blocks[blockSize], ClockWice, ix, iy, true, true);
                        ++blockSize;
                        CreateRotateBlock(blocks[blockSize], ClockWice, ix, iy);
                        ++blockSize;
                    }
                    if (CheckCanCounterClockWice(ix, iy)) {
                        CreateRotateBlock(blocks[blockSize], CounterClockWice, ix, iy, false, true);
                        ++blockSize;
                        CreateRotateBlock(blocks[blockSize], CounterClockWice, ix, iy, true, true);
                        ++blockSize;
                        CreateRotateBlock(blocks[blockSize], CounterClockWice, ix, iy);
                        ++blockSize;
                    }
                } else {
                    CreateRotateBlock(blocks[blockSize], ClockWice, ix, iy, false, true);
                    ++blockSize;
                    CreateRotateBlock(blocks[blockSize], CounterClockWice, ix, iy, false, true);
                    ++blockSize;
                }
            } else {
                if (CheckCanClockWice(ix, iy)) {
                    CreateRotateBlock(blocks[blockSize], ClockWice, ix, iy);
                    ++blockSize;
                }
                if (CheckCanCounterClockWice(ix, iy))  {
                    CreateRotateBlock(blocks[blockSize], CounterClockWice, ix, iy);
                    ++blockSize;
                }
            }
            
            double Z = 0.0;
            // + Energy
            for (uint i = 0; i < blockSize; ++i) {
                double energy = QuasiBlockEnergy(blocks[i]); //кДж/моль
                blocks[i].energy = exp(-energy / (R * *T));
                Z += blocks[i].energy;
            }
            //normalization
            double sumProbability = 0.0;
            double rnd = (double)(rand()) / RAND_MAX;
            for (uint i = 0; i < blockSize; ++i) {
                sumProbability += blocks[i].energy / Z;
                if (rnd <= sumProbability) {
                    ChangeBlock(blocks[i], ix, iy);
                    break;
                }
            }
        }
    }
}

double MargolusQuasi::CalculationBlockEnergy(const Block& block, cuint& ix, cuint& iy) {
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

double MargolusQuasi::CalculationBlockEnergy(const Block3D& block, cuint& ix,
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

double MargolusQuasi::QuasiBlockEnergy(const Block& block) {
    double sumEnergy = 0.0;
    
    if (!moveForward || block.move[movement] > 0) {
        sumEnergy += block.move[movement] * *steamEnergy_;
    }
        
    return sumEnergy;
}

double MargolusQuasi::QuasiBlockEnergy(const Block3D& block) {
    double sumEnergy = 0.0;
    
    if (!moveForward || block.move[movement] > 0) {
        sumEnergy += block.move[movement] * *steamEnergy_;
    }
    
    return block.move[movement] * *steamEnergy_;;
}
