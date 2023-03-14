#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "base/expression_parser/node.h"
#include "base/expression_parser/types.h"
#include <map>
#include <string>

class SymbolDefinition
{
public:
    SymbolDefinition(ExpressionValue value);
    SymbolDefinition(Node *rootFunctionNode);

    ExpressionValue getValue();
    ExpressionValue getValue(std::vector<ExpressionValue> args);
};

class SymbolTable
{
public:
    SymbolTable();

    static std::string defineSymbol(std::string symbol, SymbolDefinition definition);

private:
    static inline std::map<std::string, SymbolDefinition> map;
};

#endif // SYMBOLTABLE_H
