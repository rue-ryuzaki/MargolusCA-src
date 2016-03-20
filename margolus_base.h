#ifndef MARGOLUS_H
#define	MARGOLUS_H

#include <string.h>
#include <cmath>
#include "cellularautomata.h"

enum Rotate {
    UnMoved,
    ClockWice,
    CounterClockWice
};

enum Rotate3D {
    UnMoved3,
    ClockWiceX,
    CounterClockWiceX, 
    ClockWiceY,
    CounterClockWiceY,
    ClockWiceZ,
    CounterClockWiceZ
};

struct Energy {
    ~Energy() {
        /*delete energyH;
        energyH = 0;
        delete energyS;
        energyS = 0;*/
    }
    string name1;
    string name2;
    
    double* energyH;
    double* energyS;
    double energy;
    
    void UpdateEnergy(double T) {
        energy = *energyH - T * *energyS;
    }
};

struct simpleBlock {
    double energy;
    int move[7];
};

struct Block : public simpleBlock {
    Cell cells[2][2] = {{Cell(), Cell()},
                        {Cell(), Cell()}};
    Rotate rotate;
};

struct Block3D : public simpleBlock {
    Cell cells[2][2][2] = {{{Cell(), Cell()},
                        {Cell(), Cell()}},
                        {{Cell(), Cell()},
                        {Cell(), Cell()}}};
    Rotate3D rotate;
};

class Margolus : public CellularAutomata {
public:
    Margolus();
    Margolus(Sizes sizes);
    Margolus(cuint& sizeX, cuint& sizeY, cuint sizeZ = 1);
    ~Margolus();

    void Calculation(cuint& dx, cuint& dy);
    void Calculation(cuint& dx, cuint& dy, cuint& dz);
    void SetTempPtr(double* pointer) {
        if (T == 0 || T == nullptr) {
            T = pointer;
        }
        //return T;
    }
    void SetTemperature(double Temp) { *T = Temp; }
    inline double GetTemperature() const { return *T; }
    void SetEnergy(const string& name1, const string& name2, double* energyH,
        double* energyS);
    void AddEnergy(const string& name1, const string& name2, double* energyH,
        double* energyS);
    void AddEnergy(Energy & en) { energy.push_back(en); }
    
    vector<Energy> GetEnergies() const { return energy; }
    vector<Energy> GetEnergiesCell() const { return energyCell; }
    double GetEnergy(const string& name1, const string& name2);
    double GetEnergyH(const string& name1, const string& name2); 
    double GetEnergyS(const string& name1, const string& name2);

    void SetEnergyCell(const string& name1, const string& name2, double* energyH,
        double* energyS);
    void AddEnergyCell(const string& name1, const string& name2, double* energyH,
        double* energyS);
    void AddEnergyCell(Energy & en) { energyCell.push_back(en); }
    double GetEnergyCell(const string& name1, const string& name2);
    double GetEnergyHCell(const string& name1, const string& name2); 
    double GetEnergySCell(const string& name1, const string& name2);
    void ClearEnergy() { energy.clear(); energyCell.clear(); }
    void SetSteamPtr(double* pointer) {
        if (steamEnergy_ == 0 || steamEnergy_ == nullptr) {
            steamEnergy_ = pointer;
        }
        //return steamEnergy_;
    }
    void SetSteamEnergy(double steamEnergy) { *steamEnergy_ = steamEnergy; }
    inline double GetSteamEnergy() const { return *steamEnergy_; }
    void SetMoveModifier(bool value) { modifierMove = value; }
    void UpdateEnergies();
    void PrintParameters() const;
    uint movement = 0;
    bool finished = false;
    //void PrintBlocks();
    
protected:
    void PrintBlock(Block & block) const;
    bool CheckEmpty(cuint& ix, cuint& iy) const;
    bool CheckEmpty(cuint& ix, cuint& iy, cuint& iz) const;
    bool CheckMod(cuint& ix, cuint& iy) const;
    bool CheckMod(cuint& ix, cuint& iy, cuint& iz) const;
    bool CheckActive(cuint& ix, cuint& iy) const;
    bool CheckActive(cuint& ix, cuint& iy, cuint& iz) const;
    void PareEnergy(Cell& cellIn, Cell& cellOut, double& energy);
    void PareEnergyFull(Cell& cellIn, Cell& cellOut, double& energy);
    void CreateRotateNotBlock(Block & block, cuint& ix, cuint& iy);
    void CreateRotateNotBlock3D(Block3D & block, cuint& ix, cuint& iy, cuint& iz);
    void CreateRotateBlock(Block & block, Rotate rotate, cuint& ix, cuint& iy,
        bool act = true, bool mod = false);
    void CreateRotateBlock3D(Block3D & block, Rotate3D rotate, cuint& ix,
        cuint& iy, cuint& iz, bool act = true, bool mod = false);
    bool CheckCanClockWice(cuint& ix, cuint& iy) const;
    bool CheckCanCounterClockWice(cuint& ix, cuint& iy) const;
    bool CheckCanRotate3D(Rotate3D rotate, cuint& ix, cuint& iy,
        cuint& iz) const;
    //void CreateBlock(list<Block>(& block), int& ix, int& iy);
    void ChangeBlock(const Block& block, cuint& ix, cuint& iy);
    void ChangeBlock(const Block3D& block, cuint& ix, cuint& iy, cuint& iz);
    virtual double CalculationBlockEnergy(const Block& block, cuint& ix, cuint& iy);
    virtual double CalculationBlockEnergy(const Block3D& block, cuint& ix, cuint& iy, cuint& iz);
    int indexF[9][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, 1},
        {0, 1}, {0, 0}};
    int indexB[9][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1},
        {1, 0}, {0, 0}};
    //int shifts[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    Block blocks[7];
    Block3D blocks3D[19];
    uint blockSize = 0;
    uint blockSize3D = 0;
    double* steamEnergy_ = 0;
    vector<Energy> energy;
    vector<Energy> energyCell;
    const double R = 8.3144598;
    double* T = 0;
    bool modifierMove = false;
};

#endif	/* MARGOLUS_H */
