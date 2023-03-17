#ifndef OPERATOR_H
#define OPERATOR_H


#include "base/expression_parser/types.h"
#include <string>
#include <cassert>

class Operator
{
public:
    Operator();
    virtual std::string getName() = 0;
    virtual std::string getSign() = 0;
    virtual int getPredecence() = 0;
    virtual int getArgumentCount() = 0;

    virtual ExpressionValue doOperation(std::vector<ExpressionValue>) = 0;
};

#endif // OPERATOR_H
