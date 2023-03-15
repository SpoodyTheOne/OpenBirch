#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "base/expression_parser/node.h"
#include "base/expression_parser/types.h"

class ConstantNode : public Node
{
public:
    ConstantNode(ExpressionValue _value);

    ExpressionValue evaluate() override;
    QString getInformation() override;
private:
    ExpressionValue value;
};

#endif // CONSTANTNODE_H
