#pragma once

#ifndef NODE_LIST_H_
#define NODE_LIST_H_

#include "node.h"

#ifdef MAZEMAP_EXPORT
#    define EXPORT __declspec(dllexport)
#else
#    define EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

// Forward definitions
typedef struct _node_list_element node_list_element;
typedef struct _node_list node_list;

struct _node_list_element {
    node* node;
    node_list_element* next;
};

struct _node_list {
    int currentIndex;

    node_list_element* list;
    node_list* next;
};

node_list* CreateNodeList(node* first_node);
node_list_element* CreateListElement(node* node);
node_list_element* InsertNodeIntoList(node_list* list, node* node);

#ifdef __cplusplus
}
#endif

#endif // NODE_LIST_H_
