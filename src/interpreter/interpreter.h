#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "interpreter/scope.h"

namespace BirchLang {

class Interpreter
{
public:
    Interpreter();

    std::string interpretLine(std::string);

private:

    // Lexer tokenizer;
    // Parser parser;

    Scope GlobalScope;
};

}
#endif // INTERPRETER_H
