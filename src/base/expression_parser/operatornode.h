#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);

    Operator *getOperator();

    Number getValue() {
        return Number(0,0,0);
    }
private:
    Operator* op = nullptr;
};

#endif // OPERATORNODE_H
