#include "generate.h"

generate_type GenerateType(string value) {
    if (value == "random")   return gen_random;
    if (value == "chess")    return gen_chess;
    if (value == "chess_l")  return gen_chess_l;
    if (value == "chess_ms") return gen_chess_ms;
    return gen_random; // default
}

cube_location CubeLocation(string value) {
    if (value == "center")  return cube_center;
    if (value == "upX")     return cube_upX;
    if (value == "downX")   return cube_downX;
    if (value == "upY")     return cube_upY;
    if (value == "downY")   return cube_downY;
    if (value == "upZ")     return cube_upZ;
    if (value == "downZ")   return cube_downZ;
    //if (value == "point")   return gen_cube_point;
    return cube_center; // default
}

Generate::Generate() : type(gen_random), cube_loc(cube_center),
        x(0.0), y(0.0), z(0.0), xw(), yw(), zw(), x0(), y0(), z0() { }

Generate::~Generate() { }

void Generate::Generation(Margolus* CA) {
    switch (type) {
        case gen_random:
            RandomField(CA);
            break;
        case gen_chess:
            Chess(CA);
            NonSolid(CA);
            break;
        case gen_chess_l:
            ChessL(CA);
            NonSolid(CA);
            break;
        case gen_chess_ms:
            // gen right chess!
            Chess(CA);
            NonSolid(CA);
            break;
        case gen_nonsolid:
            NonSolid(CA);
            break;
        case gen_active:
            Active(CA);
            break;
        default:
            break;
    }
}

void Generate::Random(Margolus * CA, string name) {
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetName() == name) {
            Random(CA, sub);
        }
    }
}

void Generate::Random(Margolus * CA, SUBTYPE type) {
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() == type) {
            Random(CA, sub);
        }
    }
}

void Generate::Random(Margolus * CA, pSub sub) {
    for (uint k = 0; k < sub->GetFillCount();) {
        uint x = rand() % CA->GetSizeX();
        uint y = rand() % CA->GetSizeY();
        uint z = rand() % CA->GetSizeZ();

        if (CA->AddToCell(sub,x, y, z)) {
            ++k;
        }
    }
}

void Generate::Random(Margolus * CA, pSub sub, uint & count) {
    for (uint k = 0; k < count;) {
        uint x = rand() % CA->GetSizeX();
        uint y = rand() % CA->GetSizeY();
        uint z = rand() % CA->GetSizeZ();

        if (CA->AddToCell(sub,x, y, z)) {
            ++k;
        }
    }
}

void Generate::Solid(Margolus * CA) {
    setCube(CA);
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() == SOLID) {
            for (locate & loc : sub->GetLocations()) {
                if (loc.location == randomF) {
                    uint count = (uint)(*loc.consist * xw * yw * zw);
                    sub->SetFillCount(sub->GetFillCount() + count);
                    for (uint k = 0; k < count;) {
                        uint x = x0 + rand() % xw;
                        uint y = y0 + rand() % yw;
                        uint z = z0 + rand() % zw;

                        if (CA->GetCell(x, y, z).IsEmpty()) {
                            if (!CA->GetCell(x - 1, y - 1, z).HaveSolid() &&
                                    !CA->GetCell(x + 1, y - 1, z).HaveSolid() &&
                                    !CA->GetCell(x - 1, y + 1, z).HaveSolid() &&
                                    !CA->GetCell(x + 1, y + 1, z).HaveSolid()) {
                                if (CA->AddToCell(sub, x, y, z)) {
                                    ++k;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Generate::RandomField(Margolus * CA) {
    Solid(CA);
    NonSolid(CA);
}

void Generate::Adsorb(Margolus * CA, pSub sub, uint & count) {
    for (uint k = 0; k < count;) {
        uint x = rand() % CA->GetSizeX();
        uint y = rand() % CA->GetSizeY();
        uint z = rand() % CA->GetSizeZ();
        if (!CA->GetCell(x, y, z).HaveModifier()) {
            if ((x != 0 && CA->GetCell(x - 1, y, z).HaveSolid()) ||
                    (x != CA->GetSizeX() - 1 && CA->GetCell(x + 1, y, z).HaveSolid()) ||
                    (y != 0 && CA->GetCell(x, y - 1, z).HaveSolid()) ||
                    (y != CA->GetSizeY() - 1 && CA->GetCell(x, y + 1, z).HaveSolid()) ||
                    (z != 0 && CA->GetCell(x, y, z - 1).HaveSolid()) ||
                    (z != CA->GetSizeZ() - 1 && CA->GetCell(x, y, z + 1).HaveSolid())) {
                CA->AddToCell(sub, x, y, z);
                ++k;
            }
        }
    }
}

void Generate::Chess(Margolus* CA) {
    setCube(CA);
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() == SOLID) {
            for (locate & loc : sub->GetLocations()) {
                if (loc.location == randomF) {
                    uint count = (uint)(*loc.consist * xw * yw * zw);
                    sub->SetFillCount(sub->GetFillCount() + count);
                    for (uint k = 0; k < count;) {
                        uint x = x0 + 1 + 3 * (rand() % ((xw - 1) / 3));
                        uint y = y0 + 1 + 3 * (rand() % ((yw - 1) / 3));
                        uint z = zw < 3 ? (rand() % zw) :
                            z0 + 1 + 3 * (rand() % ((zw - 1) / 3));
                        if (CA->AddToCell(sub, x, y, z)) {
                            ++k;
                        }
                    }
                }
            }
        }
    }
}

void Generate::ChessL(Margolus* CA) {
    setCube(CA);
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() == SOLID) {
            for (locate & loc : sub->GetLocations()) {
                if (loc.location == randomF) {
                    uint count = (uint)(*loc.consist * xw * yw * zw);
                    sub->SetFillCount(sub->GetFillCount() + count);
                    for (uint k = 0; k < count;) {
                        uint x = x0 + 1 + 4 * (rand() % ((xw - 1) / 4));
                        uint y = y0 + 1 + 3 * (rand() % ((yw - 1) / 3));
                        uint z = zw < 3 ? (rand() % zw) :
                            z0 + 1 + 3 * (rand() % ((zw - 1) / 3));
                        if (CA->AddToCell(sub, x, y, z)) {
                            ++k;
                        }
                        if (CA->AddToCell(sub, x + 1, y, z)) {
                            ++k;
                        }
                    }
                }
            }
        }
    }
}

void Generate::NonSolid(Margolus* CA) {
    setCube(CA);
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() != SOLID) {
            for (locate & loc : sub->GetLocations()) {
                uint count = (loc.location == adsorbed ? ((uint)(*loc.consist * CA->Layer()))
                        : ((uint)(*loc.consist * (CA->GetSizeX() * CA->GetSizeY()
                        * CA->GetSizeZ()))));
                sub->SetFillCount(sub->GetFillCount() + count);
                uint k = 0;
                switch (loc.location) {
                    case outside:
                        while (k < count) {
                            uint ix = rand() % CA->GetSizeX();
                            uint iy = rand() % CA->GetSizeY();
                            uint iz = rand() % CA->GetSizeZ();

                            if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                    iz > z0 && iz <= (z0 + zw)) {
                                continue;
                            }

                            if (CA->AddToCell(sub, ix, iy, iz)) {
                                ++k;
                            }
                        }
                        break;
                    case randomF:
                        while (k < count) {
                            uint ix = rand() % CA->GetSizeX();
                            uint iy = rand() % CA->GetSizeY();
                            uint iz = rand() % CA->GetSizeZ();

                            if (CA->AddToCell(sub, ix, iy, iz)) {
                                ++k;
                            }
                        }
                        break;
                    case topX:
                        while (k < count) {
                            for (uint ix = CA->GetSizeX() - 1; ix >= 0; --ix) {
                                for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                    for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomX:
                        while (k < count) {
                            for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                    for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case topY:
                        while (k < count) {
                            for (uint iy = CA->GetSizeY() - 1; iy >= 0; --iy) {
                                for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                    for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomY:
                        while (k < count) {
                            for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                    for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case topZ:
                        while (k < count) {
                            for (uint iz = CA->GetSizeZ() - 1; iz >= 0; --iz) {
                                for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                    for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomZ:
                        while (k < count) {
                            for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                    for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case adsorbed:
                        Adsorb(CA, sub, count);
                        break;
                }
            }
        }
    }
}

void Generate::Active(Margolus* CA) {
    setCube(CA);
    for (pSub & sub : CA->GetSubs()) {
        if (sub->GetType() == ACTIVE) {
            for (locate & loc : sub->GetLocations()) {
                uint count = (loc.location == adsorbed ? ((uint)(*loc.consist * CA->Layer()))
                        : ((uint)(*loc.consist * (CA->GetSizeX() * CA->GetSizeY()
                        * CA->GetSizeZ()))));
                sub->SetFillCount(sub->GetFillCount() + count);
                uint k = 0;
                switch (loc.location) {
                    case outside:
                        while (k < count) {
                            uint ix = rand() % CA->GetSizeX();
                            uint iy = rand() % CA->GetSizeY();
                            uint iz = rand() % CA->GetSizeZ();

                            if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                    iz > z0 && iz <= (z0 + zw)) {
                                continue;
                            }

                            if (CA->AddToCell(sub, ix, iy, iz)) {
                                ++k;
                            }
                        }
                        break;
                    case randomF:
                        while (k < count) {
                            uint ix = rand() % CA->GetSizeX();
                            uint iy = rand() % CA->GetSizeY();
                            uint iz = rand() % CA->GetSizeZ();

                            if (CA->AddToCell(sub, ix, iy, iz)) {
                                ++k;
                            }
                        }
                        break;
                    case topX:
                        while (k < count) {
                            for (uint ix = CA->GetSizeX() - 1; ix >= 0; --ix) {
                                for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                    for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomX:
                        while (k < count) {
                            for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                    for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case topY:
                        while (k < count) {
                            for (uint iy = CA->GetSizeY() - 1; iy >= 0; --iy) {
                                for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                    for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomY:
                        while (k < count) {
                            for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                    for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case topZ:
                        while (k < count) {
                            for (uint iz = CA->GetSizeZ() - 1; iz >= 0; --iz) {
                                for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                    for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case bottomZ:
                        while (k < count) {
                            for (uint iz = 0; iz < CA->GetSizeZ(); ++iz) {
                                for (uint ix = 0; ix < CA->GetSizeX(); ++ix) {
                                    for (uint iy = 0; iy < CA->GetSizeY(); ++iy) {
                                        if (ix > x0 && ix <= (x0 + xw) &&  iy > y0 && iy <= (y0 + yw) &&
                                                iz > z0 && iz <= (z0 + zw)) {
                                            continue;
                                        }
                                        if (k >= count) {
                                            break;
                                        }
                                        if (CA->AddToCell(sub, ix, iy, iz)) {
                                            ++k;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case adsorbed:
                        Adsorb(CA, sub, count);
                        break;
                }
            }
        }
    }
}

void Generate::setCube(Margolus* CA) {
    xw = (uint)(x * CA->GetSizeX());
    yw = (uint)(y * CA->GetSizeY());
    zw = (uint)(z * CA->GetSizeZ()); 
    x0 = (CA->GetSizeX() - xw) / 2;
    y0 = (CA->GetSizeY() - yw) / 2;
    z0 = (CA->GetSizeZ() - zw) / 2;
    switch (cube_loc) {
        case cube_center:
            break;
        case cube_upX:
            x0 = CA->GetSizeX() - xw;
            break;
        case cube_downX:
            x0 = 0;
            break;
        case cube_upY:
            y0 = CA->GetSizeY() - yw;
            break;
        case cube_downY:
            y0 = 0;
            break;
        case cube_upZ:
            z0 = CA->GetSizeZ() - zw;
            break;
        case cube_downZ:
            z0 = 0;
            break;
    }
}
