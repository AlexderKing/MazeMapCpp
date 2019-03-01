#pragma once

/************ Algorithm declaration ***************/
/*
 * 1.   Scan all 4 sides and update map by walls
 *
 * 2.   Drive to the left side when unknown if not drive to the left right
 * 2.1  Save your tile with number (from map) as neighbor and update robot location as well as number
 * 2.2  If all tiles are already known drive back (always to smallest number) to the first with unknown tiles
 *      and go back to 1.
 *
 * 3.   If all tiles are already passed you should be at tile number 1 => Finish
 * 3.1  (optional) check if there are no more unknown tiles
 *
 */

#ifndef NODE_H_
#define NODE_H_

#ifdef MAZEMAP_EXPORT
#    define EXPORT __declspec(dllexport) 
#else
#    define EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#pragma region enums

// Defining boolean type
typedef char boolean;
#define b_false (char)0
#define b_true (char)1

/* Definition of Enums */
typedef enum TileType{
    virtual_wall = -2, 
    wall = -1, 
    standard_tile = 1, 
    black_tile = 2, 
    checkpoint = 3, 
    ramp = 4
} tile_type;

typedef enum Direction {
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
#pragma endregion

typedef struct Tile tile;
typedef struct Node node;

struct Tile {

    node* neighbors[4]; // Neighbors should be 0123
                        //                     NESW
    int number;
    int X, Y;
};

struct Node {
    tile* tile;
    tile_type type;
};

EXPORT tile* CreateMapTile(void);
EXPORT node* CreateNode(const tile_type type, tile* data);

EXPORT void DestroyTile(tile *t);
EXPORT void DestroyNode(node *n);
        
    

// Walls
EXPORT node* CreateMapWall(const tile_type type);
EXPORT node* CreateWall(void);
EXPORT node* CreateVirtualWall(void);

EXPORT void UpdateTile(tile *tile, const boolean *wall_info);

inline boolean IsWall(node *n) { return n->type == wall || n->type == virtual_wall; }
inline int XInDirection(int x, direction dir) { return dir == west ? x - 1 : dir == east ? x + 1 : x; }
inline int YInDirection(int y, direction dir) { return dir == north ? y - 1 : dir == south ? y + 1 : y; }

direction GetOppositeDirection(direction direction);

#ifdef __cplusplus
}
#endif
#endif // NODE_H_
