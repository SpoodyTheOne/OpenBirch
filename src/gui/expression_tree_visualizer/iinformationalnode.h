#ifndef IINFORMATIONALNODE_H
#define IINFORMATIONALNODE_H

#include "base/deprecated/expression_parser/symboltable.h"
#include <QString>

class IInformationalNode
{
public:
    virtual QString getInformation(SymbolTable *table) = 0;
    int absolutePosition{0};
};

#endif // IINFORMATIONALNODE_H
