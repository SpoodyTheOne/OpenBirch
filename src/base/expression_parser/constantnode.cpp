#include "constantnode.h"
#include <QString>

ConstantNode::ConstantNode(ExpressionValue _value)
{
    value = _value;
}

ExpressionValue ConstantNode::evaluate(SymbolTable *table) {
    return this->value;
}

QString ConstantNode::getInformation(SymbolTable *table)
{
    return QString(this->value.print().c_str());
}
