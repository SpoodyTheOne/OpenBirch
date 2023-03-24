#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "base/expressionvalue.h"
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
    SymbolDefinition(PreciseValue value);
    SymbolDefinition(Node *rootFunctionNode);

    ~SymbolDefinition();

    PreciseValue getValue();
    PreciseValue getValue(std::vector<PreciseValue> args);

    SymbolType type = SymbolType::Constant;

    PreciseValue constantValue;
};

typedef std::unordered_map<std::string, SymbolDefinition> SymbolMap;

class SymbolTable
{
public:
    SymbolTable();
    SymbolTable(SymbolTable const&);

    ~SymbolTable();

    void defineSymbol(std::string symbol, SymbolDefinition definition);
    SymbolDefinition *getSymbol(std::string symbol);
    bool symbolExists(std::string symbol);

    const SymbolMap *getMap() const;

private:
    SymbolMap* map{};
};

#endif // SYMBOLTABLE_H
