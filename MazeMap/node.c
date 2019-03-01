#include "stdafx.h"

static node* Wall = NULL;
static node* VWall = NULL;

node* CreateNode(const tile_type type, tile* data) {
    size_t size = sizeof(node);
    node* temp_node = (node*)malloc(size);
    temp_node->tile = data;
    temp_node->type = type;

    return  temp_node;
}

node* CreateMapWall(const tile_type type) {
    return CreateNode(type, NULL);
}

node* CreateWall(void) {
    return Wall == NULL ? (Wall = CreateNode(wall, NULL)) : Wall;
}

node* CreateVirtualWall(void) {
    return VWall == NULL ? (VWall = CreateNode(virtual_wall, NULL)) : VWall;
}

tile* CreateMapTile(void) {
    tile* temp_tile = (tile*)malloc(sizeof(tile));
    for (int i = 0; i < 4; i++) {
        temp_tile->neighbors[i] = NULL;
    }
    temp_tile->number = -1;
    temp_tile->X = 1234567;
    temp_tile->Y = 1234567;

    return  temp_tile;
} 

void UpdateTile(tile *tile, const boolean *wall_info) {
    for (int i = 0; i < 4; i++) {
        tile->neighbors[i] = wall_info[i] ? CreateWall() : tile->neighbors[i];
    }
}

direction GetOppositeDirection(direction dir) {
    const boolean ov = (dir & override) != 0;

    dir &= ~override;

    if (dir % 2 == 0) {
        dir = 2 - dir;
    } else {
        dir = 4 - dir;
    }
    return ov ? dir | override : dir;
}

void DestroyTile(tile *t) {
    free(t);
    t = NULL;
}

void DestroyNode(node *n) {
    free(n);
    n = NULL;
}

