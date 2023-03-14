#include "constantnode.h"

ConstantNode::ConstantNode(ExpressionValue _value)
{
    value = _value;
}

ExpressionValue ConstantNode::evaluate() {
    return this->value;
}
