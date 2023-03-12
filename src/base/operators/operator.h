#ifndef OPERATOR_H
#define OPERATOR_H


#include "base/expression_parser/types.h"
#include <string>

class Operator
{
public:
    Operator();
    virtual std::string name() = 0;
    virtual std::string sign() = 0;
    virtual int predecence() = 0;
    Number doOperation(Number a, Number b);
};

#endif // OPERATOR_H
