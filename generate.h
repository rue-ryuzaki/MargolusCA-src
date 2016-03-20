#ifndef GENERATE_H
#define	GENERATE_H

#include "margolus.h"

enum generate_type {
    gen_random,
    gen_chess,
    gen_chess_l,
    gen_chess_ms,
    gen_nonsolid,
    gen_active
};

enum cube_location {
    cube_center,
    cube_upX,
    cube_downX,
    cube_upY,
    cube_downY,
    cube_upZ,
    cube_downZ
};

generate_type GenerateType(string value);

cube_location CubeLocation (string value);

class Generate {
public:
    Generate();
    ~Generate();
    
    void Generation(Margolus * CA);
    
    generate_type type; // -> private
    /* type = gen_cube */
    cube_location cube_loc; // -> private
    float x; // -> private
    float y; // -> private
    float z; // -> private
    
private:
    void Random(Margolus * CA, string name);
    void Random(Margolus * CA, SUBTYPE type);
    void Random(Margolus * CA, pSub sub);
    void Random(Margolus * CA, pSub sub, uint & count);
    void Adsorb(Margolus * CA, pSub sub, uint & count);
    void Chess(Margolus * CA);
    void ChessL(Margolus * CA);
    void RandomField(Margolus * CA);
    void Solid(Margolus * CA);
    void NonSolid(Margolus * CA);
    void Active(Margolus * CA);
    void setCube(Margolus * CA);
    
    uint xw;
    uint yw;
    uint zw; 
    uint x0;
    uint y0;
    uint z0;
};

#endif	/* GENERATE_H */
