#include "stdafx.h"
#include "Tools.h"


MapDirection Tools::GetOppositeDirection(MapDirection dir) {

    return static_cast<MapDirection>(GetOppositeDirection(static_cast<int>(dir)));
}

int Tools::GetOppositeDirection(int intDir) {
    const bool ov = (intDir & override) != 0;

    intDir &= ~MapDirection::override;

    if (intDir % 2 == 0) {
        intDir = 2 - intDir;
    }
    else {
        intDir = 4 - intDir;
    }
    return ov ? (intDir | override) : intDir;
}