#include "stdafx.h"
#include "NodeList.h"

NodeListElement::~NodeListElement() {
    this->node = nullptr;
    this->next = nullptr;
}


NodeList::NodeList(Node *firstNode)
{
    list = new NodeListElement(firstNode);
    next = nullptr;
    index = firstNode->GetTile()->GetTileY();
 }


NodeList::~NodeList()
{
    auto list = this->list;
    while (list != nullptr) {
        list = list->GetNext();
        delete this->list;
    }
}

NodeListElement* NodeList::InsertNodeIntoList(Node* node) 
{
    NodeListElement* previousElement = nullptr;
    NodeListElement* currentElement = this->list;

    while (node->GetTile()->GetTileX() > currentElement->GetNode()->GetTile()->GetTileX()) 
    {
        previousElement = currentElement;
        currentElement = currentElement->GetNext();

        if (currentElement == nullptr) 
        {
            previousElement->AttachElement(new NodeListElement(node));
            return previousElement->GetNext();
        }
    }

    if (node->GetTile()->GetTileX() == currentElement->GetNode()->GetTile()->GetTileX()) {
        return currentElement;
    }

    if (previousElement == nullptr) {
        auto tempElement = new NodeListElement(node);
        tempElement->AttachElement(currentElement);
        this->list = tempElement;
        return tempElement;
    }

    previousElement->AttachElement(new NodeListElement(node));
    previousElement->GetNext()->AttachElement(currentElement);
    return previousElement->GetNext();
}

