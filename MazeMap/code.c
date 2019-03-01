#include "map.h"
#include <stddef.h>


void CreateNewTileUnderRobot(map *map, int x, int y, direction direction) {

    tile *t = CreateMapTile();
    t->X = x;
    t->Y = y;

    node *n = CreateNode(standard_tile, t);
    const boolean result = AddTileInDirection(map, direction, n);
    if (result == b_false) {
        // Clean up the mess
        DestroyNode(n); n = NULL;
        DestroyTile(t); t = NULL;
    }
}

void MoveRobotIntoNewPosition(map *map, direction d) {

    d = (direction)(d & ~override);
    map->robot_tile = map->robot_tile->tile->neighbors[d];
}

void MoveRobotToNextPosition(map *map, boolean *current_walls) {
    
    tile* robot = map->robot_tile->tile;

    UpdateTile(robot, current_walls);
    direction new_direction = GetDirectionForRobot(map);

    int x = XInDirection(robot->X, new_direction & ~override);
    int y = YInDirection(robot->Y, new_direction & ~override);

    if ((new_direction & override) != 0) {

        CreateNewTileUnderRobot(map, x, y, new_direction);
    }
    MoveRobotIntoNewPosition(map, new_direction);

}