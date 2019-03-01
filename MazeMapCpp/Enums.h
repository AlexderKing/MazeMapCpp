#pragma once

#ifndef __ENUMS_H
#define __ENUMS_H

typedef enum TileType {
    virtual_wall = -2,
    wall = -1,
    standard_tile = 1,
    black_tile = 2,
    checkpoint = 3,
    ramp = 4
} tile_type;

typedef enum MapDirection {
    north = 0,
    east = 1,
    south = 2,
    west = 3,
    override = 128,
    override_north = 128,
    override_east = 129,
    override_south = 130,
    override_west = 131
} direction;


#endif
