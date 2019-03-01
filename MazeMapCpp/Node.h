#pragma once
#include "Enums.h"

class Node;

class Tile final {
private :
    Node *neighbors[4];
    int number;
    int x, y;

public:
    Tile();
    Tile(int x, int y);
    ~Tile();

    void UpdateTile(const bool *wallInfo);

    //Node ** GetNeighbors() { return neighbors; }
    Node *GetNeighbor(int index) { return neighbors[index]; }
    void SetNeighbor(int index, Node *neighbor) { neighbors[index] = neighbor; }
    int GetNumber() { return number; }
    void SetNumber(int value) { if (number == -1) number = value; }

    int GetTileX() { return x; }
    int GetTileY() { return y; }

    int GetUnknowns();
};

class Node final {
private:
    Tile *tile;
    TileType tileType;

    static Node *wall;
    static Node *virtual_wall;

public:
    Node(TileType tileType, Tile *tileData);
    ~Node();

    static Node* CreateWall(void) { return wall == nullptr ? wall = new Node(TileType::wall, nullptr) : wall; }
    static Node* CreateVirtualWall(void) { return virtual_wall == nullptr ? virtual_wall = new Node(TileType::virtual_wall, nullptr) : virtual_wall; }

    bool IsWall() const { return tileType == TileType::wall || tileType == TileType::virtual_wall; }

    Tile *GetTile() { return tile; }
    TileType GetType() { return tileType; }
};

