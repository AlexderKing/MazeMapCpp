#include "stdafx.h"
#include "Node.h"


Tile::Tile()
{
    for (int i = 0; i < 4; i++)
        neighbors[i] = nullptr;
    number = -1;
    x = 1234567;
    y = 1234567;
}

Tile::Tile(int x, int y):Tile()
{
    this->x = x;
    this->y = y;
}

Tile::~Tile()
{
    for (int i = 0; i < 4; i++)
        neighbors[i] = nullptr;
}

void Tile::UpdateTile(const bool* wallInfo) {
    for (int i = 0; i < 4; i++) {
        this->neighbors[i] = wallInfo[i] ? Node::CreateWall() : this->neighbors[i];
    }
}

int Tile::GetUnknowns()
{
    int cnt = 0;
    for (int i = 0; i < 4; i++)
        if (this->neighbors[i] == nullptr)
            cnt++;
    return cnt;
}
