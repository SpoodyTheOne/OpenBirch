#ifndef STACKFRAME_H
#define STACKFRAME_H

#include <string>
#include <unordered_map>
#include "base/expression_parser/parser/statement.h"

struct Stackframe
{
    std::unordered_map<std::string, std::shared_ptr<Expression>> variables {};

    // TODO return address etc.

    std::shared_ptr<Statement> returnTo;
};

#endif // STACKFRAME_H
