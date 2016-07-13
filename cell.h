#ifndef CELL_H
#define	CELL_H

#include <memory>
#include <vector>
#include "substance.h"
#include "types.h"

using namespace std;

class Cell {
public:
    Cell();
    explicit Cell(pSub sub);
    ~Cell();
    
    bool AddSub(pSub newSub);
    uint GetSubCount() const;
    void RemoveSub(int i);
    void Clear();
    
    bool HaveActive();
    bool HaveLiquid();
    bool HaveModifier();
    bool HaveSolid();
    bool IsEmpty() const;
    
    vector<pSub> GetSubs() const;
    pSub GetSub(uint i) const;
    
private:
    vector<pSub> subs;
};

#endif	/* CELL_H */
