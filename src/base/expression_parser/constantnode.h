#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "base/expression_parser/node.h"
#include "base/expression_parser/types.h"

class ConstantNode : public Node
{
public:
    ConstantNode(Number _value);

    Number getValue();

    Operator *getOperator() {
        return nullptr;
    }
private:
    Number value;
};

#endif // CONSTANTNODE_H
