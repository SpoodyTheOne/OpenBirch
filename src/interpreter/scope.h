#ifndef SCOPE_H
#define SCOPE_H

#include "interpreter/variable.h"
#include <unordered_map>
#include <string>

namespace BirchLang {

typedef std::unordered_map<std::string, Variable> SymbolMapDef;

class Scope
{
public:
    Scope(Scope *parent = nullptr);

    Variable getVariable(std::string name);

    template<typename T>
    void setVariable(std::string, T);

    bool isDefined(std::string, bool traverse = true);

private:
    Scope *parentScope = nullptr;
    SymbolMapDef SymbolMap;
};

}
#endif // SCOPE_H
