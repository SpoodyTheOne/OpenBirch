#include "constantnode.h"
#include <QString>

ConstantNode::ConstantNode(ExpressionValue _value)
{
    value = _value;
}

ExpressionValue ConstantNode::evaluate() {
    return this->value;
}

QString ConstantNode::getInformation()
{
    return QString(this->value.print().c_str());
}
