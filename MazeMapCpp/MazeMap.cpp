#include "stdafx.h"
#include "MazeMap.h"
#include "Tools.h"


MazeMap::MazeMap()
{
    maxNumber = 1;
    floor = nullptr;
    robotTile = nullptr;
}

MazeMap::~MazeMap()
{
    this->robotTile = nullptr;

    if (this->floor != nullptr)
    {
        delete this->floor;
        this->floor = nullptr;
    }
}

void MazeMap::InitializeRobotTile() {
    const auto node = CreateMapNodeOnPosition(0, 0);
    InsertNodeIntoFloor(node);

    robotTile = node;
}

Node* MazeMap::CreateMapNodeOnPosition(int x, int y) 
{
    auto const tempTile = new Tile(x,y);

    return new Node(TileType::standard_tile, tempTile);
}

bool MazeMap::InsertNodeIntoFloor(Node* node) 
{

    if (this->floor == NULL) {
        this->floor = new NodeList (node);
        node->GetTile()->SetNumber(this->maxNumber++);
        return true;
    }

    if (node->GetTile()->GetTileY() < this->floor->GetIndex()) {
        // Create new first pool
        auto tempList = new NodeList(node);
        tempList->AttachList(this->floor);
        this->floor = tempList;
        node->GetTile()->SetNumber(this->maxNumber++);
        return true;
    }

    auto current_row = this->floor;
    NodeList* previous_row = nullptr;

    while (node->GetTile()->GetTileY() != current_row->GetIndex()) {

        if (current_row->IsLast()) {
            current_row->AttachList(new NodeList(node));
            node->GetTile()->SetNumber(this->maxNumber++);
            return true;
        }

        previous_row = current_row;
        current_row = current_row->GetNext();

    }

    bool return_value = false;

    auto *inserted = current_row->InsertNodeIntoList(node);
    if (inserted->GetNode()->GetTile()->GetNumber() == -1) {
        node->GetTile()->SetNumber(this->maxNumber++);
        return_value = true;
    }

    if (previous_row != nullptr) {
        previous_row->AttachList(current_row);
    }
    else {
        this->floor = current_row;
    }
    return return_value;
}

MapDirection MazeMap::GetDirectionForRobot() const {
    auto robot = robotTile->GetTile();
    int smallest = 99999;
    MapDirection proposed_direction = north;

    for (int dir = MapDirection::north; dir <= MapDirection::west; dir++) {
        auto neighbor = robot->GetNeighbor(dir);
        if (neighbor == nullptr) {                         // UNKNOWN !!!
            return static_cast<MapDirection>(dir + MapDirection::override);
        }

        if (! neighbor->IsWall() ) {                // Not a wall?
            if (neighbor->GetTile()->GetNumber() < smallest) {
                smallest = neighbor->GetTile()->GetNumber();
                proposed_direction = static_cast<MapDirection>(dir);
            }
        }
    }
    return proposed_direction;
}

Node* MazeMap::GetNodeAtPosition(int x, int y) {
    auto current_row = this->floor;

    if (current_row->GetIndex() > y)
        return nullptr;

    while (current_row->GetIndex()< y) {
        current_row = current_row->GetNext();
        if (current_row == nullptr) {
            return nullptr;
        }
    }

    // Now look into the row
    auto current_element = current_row->GetList();
    while (current_element->GetNode()->GetTile()->GetTileX() < x) {
        current_element = current_element->GetNext();
        if (current_element == nullptr) {
            return nullptr;
        }
    }

    return current_element->GetNode()->GetTile()->GetTileX() == x ? current_element->GetNode() : nullptr;
}

bool MazeMap::AddTileInDirection(MapDirection direction, Node* node_to_add) 
{
    int _direction = direction;

    if ((_direction & MapDirection::override) == 0 || node_to_add->IsWall())
        return false;

    _direction &= ~override;

    auto robot = robotTile->GetTile();

    auto node = GetNodeAtPosition(
        Tools::XInDirection(robot->GetTileX(), _direction),
        Tools::YInDirection(robot->GetTileY(), _direction));
    if (node == nullptr) { // there is no node at this position
        node = node_to_add;
    }

    robot->SetNeighbor(_direction, node);
    node->GetTile()->SetNeighbor(Tools::GetOppositeDirection(_direction), robotTile);

    return InsertNodeIntoFloor(node);
}

void MazeMap::MoveRobotToNextPosition(bool* current_walls) {
    auto robot = robotTile->GetTile();

    robot->UpdateTile(current_walls);
    UpdateNodeNeighbors(robotTile);
    auto new_direction = GetDirectionForRobot();

    int x = Tools::XInDirection(robot->GetTileX(), new_direction & ~override);
    int y = Tools::YInDirection(robot->GetTileY(), new_direction & ~override);

    if ((new_direction & override) != 0) {

        CreateNewTileUnderRobot(x, y, new_direction);
    }
    MoveRobotIntoNewPosition(new_direction);
}

void MazeMap::UpdateNodeNeighbors(Node* node) 
{
    auto tile = node->GetTile();
    for (int i=0; i<4; i++) {
        if (tile->GetNeighbor(i) != nullptr)
            continue;

        int x = Tools::XInDirection(tile->GetTileX(), i);
        int y = Tools::YInDirection(tile->GetTileY(), i);

        auto neighbor = GetNodeAtPosition(x, y);
        if (neighbor == nullptr || 
            neighbor->IsWall()          // Error in code?
            )
            continue;

        tile->SetNeighbor(i, neighbor);
        neighbor->GetTile()->SetNeighbor(Tools::GetOppositeDirection(i), node);
    }   
}


void MazeMap::CreateNewTileUnderRobot(int x, int y, MapDirection direction) {

    auto t = new Tile(x, y);

    auto n = new Node(standard_tile, t);
    const bool result = AddTileInDirection(direction, n);
    if (result == false) {
        // Clean up the mess
        delete n; n = NULL;
        delete t; t = NULL;
    }
}

void MazeMap::MoveRobotIntoNewPosition(MapDirection d) {

    const int dir = static_cast<int>(d) & ~MapDirection::override;
    this->robotTile = robotTile->GetTile()->GetNeighbor(dir);
}


