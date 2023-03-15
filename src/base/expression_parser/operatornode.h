#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);

    ExpressionValue evaluate() override;
    QString getInformation() override;
private:
    Operator* op = nullptr;
};

#endif // OPERATORNODE_H
