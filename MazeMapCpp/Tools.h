#pragma once
#include "Enums.h"

class Tools
{
public:
    static int XInDirection(int x, MapDirection dir) { return dir == west ? x - 1 : dir == east ? x + 1 : x; }
    static int YInDirection(int y, MapDirection dir) { return dir == north ? y - 1 : dir == south ? y + 1 : y; }

    static int XInDirection(int x, int dir) { return dir == west ? x - 1 : dir == east ? x + 1 : x; }
    static int YInDirection(int y, int dir) { return dir == north ? y - 1 : dir == south ? y + 1 : y; }

    static  MapDirection GetOppositeDirection(MapDirection dir);
    static  int GetOppositeDirection(int dir);
};

