#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "base/operators/operator.h"
#include "node.h"

class OperatorNode : public Node
{
public:
    OperatorNode(Operator* _op);

    PreciseValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;
private:
    Operator* op = nullptr;
};

#endif // OPERATORNODE_H
