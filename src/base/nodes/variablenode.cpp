#include "variablenode.h"

VariableNode::VariableNode(std::string _value)
{
    value = _value;
}

PreciseValue VariableNode::evaluate(SymbolTable *table)
{
    if (!table)
        throw std::runtime_error("Can't use variable nodes with null symboltable");

    SymbolDefinition *sd = table->getSymbol(this->value);

    if (!sd)
        throw std::runtime_error("Unknown variable " + this->value);

    if (sd->type != SymbolType::Constant)
        throw std::runtime_error("Cant do not number variabels");

    return sd->getValue();
}

QString VariableNode::getInformation(SymbolTable *table)
{
    if (!table)
        return QString((value + "(unknown)").c_str());

    PreciseValue val = evaluate(table);
    std::string name = value + " (";
    return QString(name.c_str()) + QString(val.get_str().c_str()) + ")";
}

std::string VariableNode::getName()
{
    return this->value;
}
