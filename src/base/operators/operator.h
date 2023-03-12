#ifndef OPERATOR_H
#define OPERATOR_H


#include "base/expression_parser/types.h"
#include <string>

class Operator
{
public:
    Operator();
    virtual std::string getName() = 0;
    virtual std::string getSign() = 0;
    virtual int getPredecence() = 0;
    Number doOperation(Number a, Number b);
};

#endif // OPERATOR_H
