#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "base/expression_parser/node.h"
#include "base/expression_parser/symboltable.h"
#include "base/expression_parser/types.h"

class VariableNode : public Node
{
public:
    VariableNode(std::string _value);

    ExpressionValue evaluate(SymbolTable *table = nullptr) override;
    QString getInformation(SymbolTable *table = nullptr) override;
private:
    std::string value;
};
#endif // VARIABLENODE_H
