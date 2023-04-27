#include "environment.h"

Environment::Environment()
{

}

void Environment::define(std::string name, ExpressionStatement* value)
{
    if (stackframes.empty())
        return;

    // Define variable in current stackframe (top of stack)
    Stackframe currentStackframe = stackframes.back();
    currentStackframe.variables[name] = value;
}

bool Environment::isDefined(std::string name)
{
    for (std::vector<Stackframe>::iterator it = stackframes.begin(); it != stackframes.end(); it++)
    {
        auto variable = it->variables.find(name);
        if (variable == it->variables.end())
            continue;

        // The var was found in this stackframe
        return true;
    }

    // All stackframes was searched and no var was found
    return false;
}

ExpressionStatement* Environment::get(std::string name)
{
    for (std::vector<Stackframe>::iterator it = stackframes.begin(); it != stackframes.end(); it++)
    {
        auto variable = it->variables.find(name);
        if (variable == it->variables.end())
            continue;

        // The var was found in this stackframe
        return variable->second;
    }

    // All stackframes was searched and no var was found
    return nullptr;
}


