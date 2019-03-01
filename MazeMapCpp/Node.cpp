#include "stdafx.h"
#include "Node.h"

Node *Node::wall = nullptr;
Node *Node::virtual_wall = nullptr;

Node::Node(TileType tileType, Tile *tileData)
{
    this->tileType = tileType;
    this->tile = tileData;
}


Node::~Node()
{
    tileType = TileType::standard_tile;
    tile = nullptr;
}
