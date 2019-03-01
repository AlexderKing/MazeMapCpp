#pragma once

#include "Node.h"

class NodeListElement {
private:
    Node *node;
    NodeListElement *next;

public:
    NodeListElement(Node *node):  node(node), next(nullptr) {}
    ~NodeListElement();

    Node *GetNode() { return node; }
    NodeListElement *GetNext() { return next; }
    void AttachElement(NodeListElement *element) { next = element; }

    bool IsLast() { return next == nullptr; }
};

class NodeList
{
private:
    int index;
    NodeListElement *list;
    NodeList *next;

public:
    NodeList(Node *firstNode);
    ~NodeList();

    int GetIndex() { return index; }
    NodeListElement* InsertNodeIntoList(Node *node);

    void AttachList(NodeList *list) { next = list; }
    bool IsLast() { return next == nullptr; }

    NodeListElement* GetList() { return list; }
    NodeList* GetNext() { return next; }
};

