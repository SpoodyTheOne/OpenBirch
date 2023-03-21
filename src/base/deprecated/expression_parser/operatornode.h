#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/deprecated/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);

    ExpressionValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;
private:
    Operator* op = nullptr;
};

#endif // OPERATORNODE_H
