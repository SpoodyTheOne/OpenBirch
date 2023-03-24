#include "symboltable.h"
#include <iostream>

SymbolDefinition::SymbolDefinition(PreciseValue value)
{
    constantValue = value;
}

SymbolDefinition::~SymbolDefinition() {}

SymbolTable::SymbolTable() : map{new SymbolMap()}
{
}

SymbolTable::SymbolTable(SymbolTable const& other)
{
    this->map = (SymbolMap*)other.getMap();
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
    ((SymbolMap*)map)->insert_or_assign(symbol,definition);
}

SymbolDefinition *SymbolTable::getSymbol(std::string symbol)
{
    std::cout << map->size() << std::endl;

    std::unordered_map<std::string,SymbolDefinition>::iterator it = ((SymbolMap*)map)->find(symbol);

    if (it != map->end())
        return &(it->second);

    return nullptr;
}

bool SymbolTable::symbolExists(std::string symbol)
{
    std::unordered_map<std::string,SymbolDefinition>::iterator it = ((SymbolMap*)map)->find(symbol);

    if (it != map->end())
        return true;

    return false;
}

const SymbolMap *SymbolTable::getMap() const
{
    return (const SymbolMap*) map;
}
