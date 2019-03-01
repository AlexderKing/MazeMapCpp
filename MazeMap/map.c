#include "stdafx.h"

map* CreateMap(void) {  
    map* temp_map = (map*)malloc(sizeof(map));
    
    temp_map->max_number = 1;
    temp_map->floor = NULL;
    temp_map->robot_tile = NULL;

    return temp_map;
}

void InitializeRobotTile(map* _map) {

    node *n = CreateMapNodeOnPosition( 0, 0);
    InsertNodeIntoFloor(_map, n);

    _map->robot_tile = n;
}

//node* CreateMapNodeOnPosition(map* _map, int x, int y) { //Why map is needed?????
//    tile* temp_tile = CreateMapTile();
//
//    temp_tile->X = x;
//    temp_tile->Y = y;
//    temp_tile->number = -1;
//
//    return CreateNode(standard_tile, temp_tile);
//}

node* CreateMapNodeOnPosition(int x, int y) {
    tile* temp_tile = CreateMapTile();

    temp_tile->X = x;
    temp_tile->Y = y;
    temp_tile->number = -1;

    return CreateNode(standard_tile, temp_tile);
}

boolean InsertNodeIntoFloor(map* _map, node* _node) {

    if(_map->floor == NULL) {
        _map->floor = CreateNodeList(_node);
        _node->tile->number = _map->max_number++;
        return b_true;
    }

    if(_node->tile->Y < _map->floor->currentIndex) {
        // Create new first pool
        node_list* temp_list = CreateNodeList(_node);
        temp_list->next = _map->floor;
        _map->floor = temp_list;
        _node->tile->number = _map->max_number++;
        return b_true;
    }

    node_list* current_row = _map->floor;
    node_list* previous_row = NULL;

    while(_node->tile->Y != current_row->currentIndex) {

        if(current_row->next == NULL) {
            current_row->next = CreateNodeList(_node);
            _node->tile->number = _map->max_number++;
            return b_true;
        }

        previous_row = current_row;
        current_row = current_row->next;

    }

    boolean return_value = b_false;

    node_list_element *inserted = InsertNodeIntoList(current_row, _node);
    if (inserted->node->tile->number == -1) {
        _node->tile->number = _map->max_number++;
        return_value = b_true;
    }
    
    if (previous_row != NULL) {
        previous_row->next = current_row;
    } else {
        _map->floor = current_row;
    }
    return return_value;
}

direction GetDirectionForRobot(map* _map) {
    // Starting from N go to the first unknown tile
    // If all are known go to the tile with the smallest number

    tile *robot = _map->robot_tile->tile;
    int smallest = 99999;
    direction proposed_direction = north;

    for (direction dir = north; dir<= west; dir++) {
        node *neighbor = robot->neighbors[dir];
        if (neighbor == NULL) {                         // UNKNOWN !!!
            return dir + override;
        }

        if (IsWall(neighbor) == b_false) {                // Not a wall?
            if (neighbor->tile->number<smallest) {
                smallest = neighbor->tile->number;
                proposed_direction = dir;
            }
        }
    }
    return proposed_direction;    
}

node *GetNodeAtPosition(map *_map, int x, int y) {
    node_list *current_row = _map->floor;

    if (current_row->currentIndex > y)
        return NULL;

    while (current_row->currentIndex<y) {
        current_row = current_row->next;
        if (current_row == NULL) {
            return NULL;
        }
    }

    // Now look into the row
    node_list_element *current_element = current_row->list;
    while (current_element->node->tile->X < x) {
        current_element = current_element->next;
        if (current_element == NULL) {
            return NULL;
        }
    }

    return current_element->node->tile->X == x ? current_element->node : NULL;
}

boolean AddTileInDirection(map *_map, direction _direction, node *node_to_add) {

    if ((_direction & override) == 0 || IsWall(node_to_add))
        return b_false;

    _direction &= ~override;

    tile *robot = _map->robot_tile->tile;

    node *node = GetNodeAtPosition(_map,
                                   XInDirection(robot->X, _direction),
                                   YInDirection(robot->Y, _direction));
    if (node == NULL) { // there is no node at this position
        node = node_to_add;
    }

    robot->neighbors[_direction] = node;
    node->tile->neighbors[GetOppositeDirection(_direction)] = _map->robot_tile;

    return InsertNodeIntoFloor(_map, node);
}
