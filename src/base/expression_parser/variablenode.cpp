#include "variablenode.h"

VariableNode::VariableNode(std::string _value)
{
    value = _value;
}

ExpressionValue VariableNode::evaluate(SymbolTable *table)
{
    if (!table)
        throw std::runtime_error("Can't use variable nodes with null symboltable");

    SymbolDefinition *sd = table->getSymbol(this->value);

    if (sd->type != SymbolType::Constant)
        throw std::runtime_error("Cant do not number vrabiels");

    return sd->getValue();
}

QString VariableNode::getInformation(SymbolTable *table)
{
    ExpressionValue val = evaluate(table);
    std::string name = value + " (";
    return QString(name.c_str()) + QString(val.print().c_str()) + ")";
}
