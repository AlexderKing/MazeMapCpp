#pragma once
#include "Node.h"
#include "NodeList.h"

class MazeMap
{
private:
    Node *robotTile;
    int maxNumber;
    NodeList *floor;

    bool InsertNodeIntoFloor(Node* _node);
    Node *GetNodeAtPosition(int x, int y);

    void CreateNewTileUnderRobot(int x, int y, MapDirection direction);
    void MoveRobotIntoNewPosition(MapDirection direction);
    void UpdateNodeNeighbors(Node *node);

public:
    MazeMap();
    ~MazeMap();

    static Node* CreateMapNodeOnPosition(int x, int y);

    void InitializeRobotTile();
    MapDirection GetDirectionForRobot() const;
    bool AddTileInDirection(MapDirection direction, Node *node_to_add);

    void MoveRobotToNextPosition(bool *current_walls);

};

