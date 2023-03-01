#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "expressionparser.h"
#include <string>
#include <unordered_map>

class SymbolTable
{
public:
    static SymbolTable& instance()
    {
        static SymbolTable instance;
        return instance;
    }
    std::unordered_map<std::string, ExpressionData> table;

    static void setSymbol( std::string symbol, ExpressionData data ) {
        instance()._setSymbol(symbol, data);
    }

    static ExpressionData getSymbol( std::string symbol ) {
        return instance()._getSymbol(symbol);
    }

private:
    SymbolTable();

    void _setSymbol( std::string symbol, ExpressionData data );
    ExpressionData _getSymbol( std::string symbol );
};

#endif // SYMBOLTABLE_H
