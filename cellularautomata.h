#ifndef CELLULARAUTOMATA_H
#define	CELLULARAUTOMATA_H

#include "cell.h"
#include "types.h"

struct Sizes {
    Sizes(uint x = 0, uint y = 0, uint z = 0) : x(x), y(y), z(z) { }
    
    uint x;
    uint y;
    uint z;
};

class CellularAutomata {
public:
    CellularAutomata();
    CellularAutomata(Sizes sizes);
    CellularAutomata(cuint& sizeX, cuint& sizeY, cuint sizeZ = 1);
    
    ~CellularAutomata();
    
    void ReSize(cuint& sizeX, cuint& sizeY, cuint sizeZ = 1);
    inline uint GetSizeX() const { return size.x; }
    inline uint GetSizeY() const { return size.y; }
    inline uint GetSizeZ() const { return size.z; }
    inline uint GetVolume() const { return size.x * size.y * size.z; }
    Cell GetCell(uint x, uint y, uint z = 0) const { return cells[x][y][z]; }
    void SetCell(const Cell& cell, uint x, uint y, uint z = 0) 
        { cells[x][y][z] = cell; }
        
    void ClearAllBorders();
    void ClearUpX();
    void ClearUpY();
    void ClearUpZ();
    void ClearDownX();
    void ClearDownY();
    void ClearDownZ();
    void SetEmptyField();
    uint SolidCount();
    uint Count(SUBTYPE type);
    uint Count(const string& name);
    uint SidesCount();
    uint SidesCount(SUBTYPE type);
    uint SidesCount(const string& name);
    vector<pSub> GetSubs() const { return subs; }
    pSub GetSub(cuint& i) const { return subs[i]; }
    pSub GetSub(const string& name);
    int GetSubI(const string& name);
    void ClearSubs() { subs.clear(); }
    bool AddToCell(pSub sub, int x, int y, int z = 0);
    void AddSub(pSub newSub);
    void AddSub(const SUBTYPE type, const string& name, const XColor color = XColor(),
        const vector<locate>& locations = vector<locate>());
    
    inline uint GetSubCount() const { return subs.size(); }
    void SaveFieldBin(const char* path);
    void SaveFieldText(const char* path);
    void LoadFieldBin(const char* path);
    void LoadFieldText(const char* path);
    void LoadFieldTextOld(const char* path);
    void LoadFieldTextXYZN(const char* path);
    void LoadFieldTextXY_M(const char* path, string sol, string mod);
    void LoadFieldTextXYZM(const char* path, string sol, string mod);
    void LoadFieldTextXYZX(const char* path);
    void LoadFieldTextXYZ(const char* path, string name);
    void LoadFieldTextXYZR(const char* path, string name);
    void SaveToImage(const char* path, uchar* imageData);
    void SaveToImagePNG(const char* path, uchar* imageData);
    uint Layer();
    uint Adsorbed() const;
    void ImportSubs(CellularAutomata * CA);
    unsigned long long iteration = 0;
    
protected:
    uint adsorbLayer = 0;
    vector<pSub> subs;
    Cell ***cells;
    
private:
    Sizes size;
};

#endif	/* CELLULARAUTOMATA_H */