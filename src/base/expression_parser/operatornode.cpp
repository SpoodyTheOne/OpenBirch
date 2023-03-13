#include "operatornode.h"

OperatorNode::OperatorNode(Operator *_op)
{
    op = _op;
}

Operator *OperatorNode::getOperator() {
    return op;
}
