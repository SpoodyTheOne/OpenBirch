#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "base/expression_parser/parser/expression.h"
#include <string>

class Interpreter
{
public:
    static std::string interpret(Expression*);
};

#endif // INTERPRETER_H
