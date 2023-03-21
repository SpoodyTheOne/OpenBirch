#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "base/deprecated/expression_parser/node.h"
#include "base/expressionvalue.h"

class ConstantNode : public Node
{
public:
    ConstantNode(ExpressionValue _value);

    ExpressionValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;
private:
    ExpressionValue value;
};

#endif // CONSTANTNODE_H
