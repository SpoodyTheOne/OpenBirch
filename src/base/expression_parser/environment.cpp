#include "environment.h"
#include "base/expression_parser/number.h"
#include "base/expression_parser/parser/expression.h"


Environment::Environment()
{
    Stackframe* global = new Stackframe();
    global->variables = {};
    global->returnTo = 0;
    this->stackframes.push_back(global);

    define("pi", std::make_shared<LiteralExpr>(Number::PI));
    define("e", std::make_shared<LiteralExpr>(Number::NATURAL_LOG));
    define("euler", std::make_shared<LiteralExpr>(Number::EULER));

}

Environment::~Environment()
{
    // Delete every item
    for (Stackframe* s : stackframes)
        delete s;

    // Free memory or something
    std::vector<Stackframe*>().swap(stackframes);

    std::cout << "Environment destructed" << std::endl;
}

void Environment::define(std::string name, std::shared_ptr<Expression> value)
{
    if (stackframes.empty())
        return;

    // Define variable in current stackframe (top of stack)
    Stackframe* currentStackframe = stackframes.back();
    currentStackframe->variables.insert_or_assign(name, value);
}

bool Environment::isDefined(std::string name)
{
    for (std::vector<Stackframe*>::iterator it = stackframes.begin(); it != stackframes.end(); it++)
    {
        auto variable = (*it)->variables.find(name);
        if (variable == (*it)->variables.end())
            continue;

        // The var was found in this stackframe
        return true;
    }

    // All stackframes was searched and no var was found
    return false;
}

std::shared_ptr<Expression> Environment::get(std::string name)
{
    for (std::vector<Stackframe*>::iterator it = stackframes.begin(); it != stackframes.end(); it++)
    {
        auto variable = (*it)->variables.find(name);
        if (variable == (*it)->variables.end())
            continue;

        // The var was found in this stackframe
        return variable->second;
    }

    // All stackframes was searched and no var was found
    return nullptr;
}


