#include "symboltable.h"

SymbolDefinition::SymbolDefinition(PreciseValue value)
{
    constantValue = value;
}

SymbolDefinition::~SymbolDefinition() {}

SymbolTable::SymbolTable() {
    map = {};
}

SymbolTable::SymbolTable(SymbolTable &table) {
    this->map = *table.getMap();
}

SymbolTable::~SymbolTable()
{
    map.clear();
    SymbolMap().swap(map);
}

PreciseValue SymbolDefinition::getValue()
{
    if (this->type == SymbolType::Constant)
        return constantValue;

    return NULL;
}

void SymbolTable::defineSymbol(std::string symbol, SymbolDefinition definition)
{
    std::unordered_map<std::string,SymbolDefinition>::iterator it = map.find(symbol);

    map.insert_or_assign(symbol,definition);
}

SymbolDefinition *SymbolTable::getSymbol(std::string symbol)
{
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

const SymbolMap *SymbolTable::getMap() const
{
    return (const SymbolMap*)&map;
}
