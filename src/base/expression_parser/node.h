#ifndef NODE_H
#define NODE_H

#include "base/operators/operator.h"
#include <memory>
#include <vector>

class Node
{
public:
    Node();
    ~Node();

    std::vector<Node*> children;

    virtual Operator *getOperator() = 0;

    virtual Number getValue() = 0;
};

#endif // NODE_H
