#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);

    Number evaluate() override;
private:
    Operator* op = nullptr;
};

#endif // OPERATORNODE_H
