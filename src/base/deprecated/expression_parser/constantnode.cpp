#include "constantnode.h"
#include <QString>

ConstantNode::ConstantNode(PreciseValue _value)
{
    value = _value;
}

PreciseValue ConstantNode::evaluate(SymbolTable *table) {
    return this->value;
}

QString ConstantNode::getInformation(SymbolTable *table)
{
    return QString(this->value.get_str().c_str());
}
