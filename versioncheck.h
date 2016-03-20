#ifndef VERSIONCHECK_H
#define VERSIONCHECK_H

#include <iostream>
#include <regex>
#include "program.h"

using namespace std;

struct ver {
    ver() { }
    ver(string v) : value(v) { }
    
    string value;
    int sub[4];
    
    bool update() {
        for (int i = 0; i < 4; ++i) {
            sub[i] = 0;
        }
        int dot = 0;
        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == '.') {
                ++dot;
            }
        }
        
        switch (dot) {
            case 1:
            {
                regex reg("([0-9]+).([0-9]+)");
                smatch match;
                if (regex_search(value, match, reg)) {
                    for (int i = 0; i <= dot; ++i) {
                        sub[i] = atoi(match[i + 1].str().c_str());
                    }
                } else {
                    cout << "Error 1 read application version!\n";
                    return false;
                }
            }
                break;
            case 2:
            {
                regex reg("([0-9]+).([0-9]+).([0-9]+)");
                smatch match;
                if (regex_search(value, match, reg)) {
                    for (int i = 0; i <= dot; ++i) {
                        sub[i] = atoi(match[i + 1].str().c_str());
                    }
                } else {
                    cout << "Error 2 read application version!\n";
                    return false;
                }
            }
                break;
            case 3:
            {
                regex reg("([0-9]+).([0-9]+).([0-9]+).([0-9]+)");
                smatch match;
                if (regex_search(value, match, reg)) {
                    for (int i = 0; i <= dot; ++i) {
                        sub[i] = atoi(match[i + 1].str().c_str());
                    }
                } else {
                    cout << "Error 3 read application version!\n";
                    return false;
                }
            }
                break;
            default:
                cout << "Unknown error read application version!\n";
                return false;
                break;
        }
        return true;
    }
};

void checkConfigVersion(string cfg, int &x) {
    ver thisVer(program_version);
    if (!thisVer.update()) {
        x = -2;
        return;
    }
    
    ver cfgVer(cfg);
    if (!cfgVer.update()) {
        x = -3;
        return;
    }
    
    for (int i = 0; i < 3; ++i) {
        if (thisVer.sub[i] < cfgVer.sub[i]) {
            x = 0;
            return;
        }
        if (thisVer.sub[i] > cfgVer.sub[i]) {
            x = 1;
            return;
        }
    }
    x = 2;
}

#endif /* VERSIONCHECK_H */
