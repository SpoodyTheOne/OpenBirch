#ifndef NODE_H
#define NODE_H

#include "types.h"
#include <memory>
#include <vector>

class Node
{
public:
    Node();
    ~Node();

    std::vector<Node*> children;
    virtual ExpressionValue evaluate() = 0;
};

#endif // NODE_H
