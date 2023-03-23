#include "scope.h"

namespace BirchLang {

Scope::Scope(Scope *parent)
{
    this->parentScope = parent;
}

bool Scope::isDefined(std::string name, bool traverse)
{
    SymbolMapDef::iterator it = this->SymbolMap.find(name);

    if (it == this->SymbolMap.end())
    {
        if (!traverse || !this->parentScope)
            return false;

        return this->parentScope->isDefined(name);
    }

    return true;
}

Scope *Scope::variableDefinedIn(std::string name)
{
    if (isDefined(name,false))
        return this;
    else
        return this->parentScope->variableDefinedIn(name);

    return nullptr;
}

template<typename T>
void Scope::setVariable(std::string name, T value)
{
    Scope *scope = variableDefinedIn(name);

    if (scope == this || scope == nullptr) // Not defined
        this->SymbolMap.insert_or_assign(name,Variable(value));
    else
        scope->setVariable(name,value);
}

}
