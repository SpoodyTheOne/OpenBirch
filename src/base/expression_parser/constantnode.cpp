#include "constantnode.h"

ConstantNode::ConstantNode(Number _value)
{
    value = _value;
}

Number ConstantNode::evaluate() {
    return this->value;
}
