#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <stack>
#include "base/expression_parser/interpreter/stackframe.h"

class ExpressionStatement;

class Environment
{
public:
    Environment();

    /**
     * @brief define a variable
     * throws an error if the variable already exists
     */
    void define(std::string, ExpressionStatement* = 0);

    /**
     * @brief Returns true if the variable is defined
     * @return boolean
     */
    bool isDefined(std::string);

    /**
     * @brief Gets a variable by its lexeme
     * @return ExpressionStatement or null if it wasn't found
     */
    ExpressionStatement* get(std::string);

private:
    std::vector<Stackframe> stackframes;
};

#endif // ENVIRONMENT_H
