#include "stdafx.h"

/* 
struct _node_list_element {
    node* node;
    node_list_element* next;
};

struct _node_list {
    node_list_element* list;
    node_list* next;
};
 */

node_list_element* CreateListElement(node* node) {
    node_list_element* element = (node_list_element*)malloc(sizeof(node_list_element));
    element->node = node;
    element->next = NULL;

    return element;
}

node_list* CreateNodeList(node* first_node) {
    node_list_element* element = CreateListElement(first_node);
    node_list* list = (node_list*)malloc(sizeof(node_list));

    list->list = element;
    list->next = NULL;
    list->currentIndex = first_node->tile->Y;

    return list;
}

node_list_element* InsertNodeIntoList(node_list* list, node* node) {
    
    node_list_element* previous_element = NULL;
    node_list_element* current_element = list->list;

    while(node->tile->X > current_element->node->tile->X) {
        previous_element = current_element;
        current_element = current_element->next;

        if(current_element == NULL) {
            previous_element->next = CreateListElement(node);
            return previous_element->next;
        }
    }

    if(node->tile->X == current_element->node->tile->X) {
        return current_element;
    } 
    
    if(previous_element == NULL) {
        node_list_element* temp_element = CreateListElement(node);
        temp_element->next = current_element;
        list->list = temp_element;
        return temp_element;
    }
    
    previous_element->next = CreateListElement(node);
    previous_element->next->next = current_element;
    return previous_element->next;
}