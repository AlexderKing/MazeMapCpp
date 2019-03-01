#pragma once
#ifndef MAP_H_
#define MAP_H_

#include "node.h"
#include "node_list.h"

#ifdef MAZEMAP_EXPORT
#    define EXPORT __declspec(dllexport) 
#else
#    define EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Map {
        node* robot_tile;
        int max_number;

        node_list* floor;

    } map;

    EXPORT map* CreateMap(void);
    EXPORT void InitializeRobotTile(map* _map);
    EXPORT node* CreateMapNodeOnPosition(int x, int y);
    EXPORT direction GetDirectionForRobot(map* _map);
    EXPORT boolean AddTileInDirection(map *_map, direction _direction, node *node_to_add);

    EXPORT void MoveRobotToNextPosition(map *map, boolean *current_walls);

    boolean InsertNodeIntoFloor(map* _map, node* _node);
    node *GetNodeAtPosition(map *_map, int x, int y);

#ifdef __cplusplus
}
#endif

#endif // MAP_H_
