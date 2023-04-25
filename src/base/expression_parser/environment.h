#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>

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

private:
    std::unordered_map<std::string, ExpressionStatement*> values = {};
};

#endif // ENVIRONMENT_H
