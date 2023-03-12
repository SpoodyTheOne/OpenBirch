#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);
private:
    Operator* op;
};

#endif // OPERATORNODE_H
