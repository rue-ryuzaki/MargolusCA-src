#include <iostream>
#include <vector>
#include "cell.h"

Cell::Cell() { }

Cell::Cell(pSub sub) {
    subs.push_back(sub);
}

Cell::~Cell() {
    subs.clear();
}

bool Cell::AddSub(pSub newSub) {
    bool haveActive = false;
    bool haveModifier = false;
    bool haveSolid = false;
    
    for (pSub & sub : subs) {
        switch (sub->GetType()) {
            case ACTIVE:
                haveActive = true;
                break;
            case MODIFIER:
                haveModifier = true;
                break;
            case SOLID:
                haveSolid = true;
                break;
            default:
                return false;
                break;
        }
    }
    
    if (haveSolid){
        return false;
    }
    
    if (haveActive) {
        if (newSub->GetType() == MODIFIER && !haveModifier) {
            subs.push_back(newSub);
            return true;
        }
        return false;
    }
    
    if (haveModifier) {
        if (newSub->GetType() == ACTIVE){// != SOLID) {
            subs.push_back(newSub);
            return true;
        }
        return false;
    }
    subs.push_back(newSub);
    return true;
}

uint Cell::GetSubCount() const {
    return subs.size();
}

void Cell::RemoveSub(int i) {
    subs.erase(subs.begin() + i);
}

void Cell::Clear() {
    subs.clear();
}

bool Cell::HaveActive() {
    for (pSub & sub : subs) {
        if (sub->GetType() == ACTIVE) {
            return true;
        }
    }
    return false;
}

bool Cell::HaveLiquid() {
    for (pSub & sub : subs) {
        return sub->GetType() != SOLID;// ? false : true;
    }
    return false;
}

bool Cell::HaveModifier() {
    for (pSub & sub : subs) {
        if (sub->GetType() == MODIFIER) {
            return true;
        }
    }
    return false;
}

bool Cell::HaveSolid() {
    for (pSub & sub : subs) {
        return sub->GetType() == SOLID;// ? true : false;
    }
    return false;
}

bool Cell::IsEmpty() const {
    return subs.size() == 0 ? true : false;
}

vector<pSub> Cell::GetSubs() const {
    return subs;
}

pSub Cell::GetSub(uint i) const {
    return subs[i];
}
