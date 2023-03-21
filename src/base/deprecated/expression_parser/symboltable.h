#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "base/expression_parser/types.h"
#include <unordered_map>
#include <string>

enum SymbolType {
    Constant,
    Func
};

class Node;

class SymbolDefinition
{
public:
    SymbolDefinition(ExpressionValue value);
    SymbolDefinition(Node *rootFunctionNode);

    ~SymbolDefinition();

    ExpressionValue getValue();
    ExpressionValue getValue(std::vector<ExpressionValue> args);

    SymbolType type = SymbolType::Constant;

    ExpressionValue constantValue;
};

typedef std::unordered_map<std::string, SymbolDefinition> SymbolMap;

class SymbolTable
{
public:
    SymbolTable();
    SymbolTable(SymbolTable&);

    ~SymbolTable();

    void defineSymbol(std::string symbol, SymbolDefinition definition);
    SymbolDefinition *getSymbol(std::string symbol);
    bool symbolExists(std::string symbol);

    const SymbolMap *getMap() const;

private:
    SymbolMap map;
};

#endif // SYMBOLTABLE_H
