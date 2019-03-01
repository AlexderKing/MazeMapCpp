#include "../MazeMap/node.h"
#include "../MazeMap/map.h"

#include <stdio.h>

int main() {
    for (int i = 0; i < 100; i++) {
        //node*n = CreateMapNodeOnPosition(0, 0);

        //if (n->tile->X != 0) {
        //    printf("Current run: %i", i);

        //}

        map *map = CreateMap();
        InitializeRobotTile(map);

        if (map->robot_tile->tile->X != 0)
            printf("Current run: %i", i);
    }

    printf("Finished");
    getchar();
}
