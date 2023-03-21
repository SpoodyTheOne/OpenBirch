#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "base/deprecated/expression_parser/node.h"
#include "base/deprecated/expression_parser/symboltable.h"
#include "base/expressionvalue.h"

class VariableNode : public Node
{
public:
    VariableNode(std::string _value);

    PreciseValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;

    std::string getName();
private:
    std::string value;
};
#endif // VARIABLENODE_H
