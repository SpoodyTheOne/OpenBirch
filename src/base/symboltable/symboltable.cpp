#include "symboltable.h"
#include <iostream>

SymbolDefinition::SymbolDefinition(PreciseValue value)
{
    constantValue = value;
}

SymbolDefinition::~SymbolDefinition() {}

SymbolTable::SymbolTable()
{
}

SymbolTable::SymbolTable(SymbolTable *other)
{
    this->map = *other->getMap();
}

SymbolTable::~SymbolTable()
{
}

PreciseValue SymbolDefinition::getValue()
{
    if (this->type == SymbolType::Constant)
        return constantValue;

    return NULL;
}

void SymbolTable::defineSymbol(std::string symbol, SymbolDefinition definition)
{
    map.insert_or_assign(symbol,definition);
}

SymbolDefinition *SymbolTable::getSymbol(std::string symbol)
{
    std::cout << map.size() << std::endl;

    std::unordered_map<std::string,SymbolDefinition>::iterator it = map.find(symbol);

    if (it != map.end())
        return &(it->second);

    return nullptr;
}

bool SymbolTable::symbolExists(std::string symbol)
{
    std::unordered_map<std::string,SymbolDefinition>::iterator it = map.find(symbol);

    if (it != map.end())
        return true;

    return false;
}

SymbolMap *SymbolTable::getMap()
{
    return &map;
}
