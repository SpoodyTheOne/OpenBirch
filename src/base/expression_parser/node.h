#ifndef NODE_H
#define NODE_H

#include <memory>
#include "types.h"

class Node
{
public:
    Node();
    ~Node();

    Node* leftChild;
    Node* rightChild;
};

#endif // NODE_H
