#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "base/deprecated/expression_parser/node.h"
#include "base/expressionvalue.h"

class ConstantNode : public Node
{
public:
    ConstantNode(PreciseValue _value);

    PreciseValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;
private:
    PreciseValue value;
};

#endif // CONSTANTNODE_H
