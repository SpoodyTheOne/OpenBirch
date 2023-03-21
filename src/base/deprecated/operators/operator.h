#ifndef OPERATOR_H
#define OPERATOR_H


#include "base/expressionvalue.h"
#include <string>
#include <cassert>

struct Precedence {
    static inline int Parenthesis = 7;
};

enum OperatorAssociativity {
    Left = 0,
    Right = 1,
};

class Operator
{
public:
    Operator();
    ~Operator();
    virtual std::string getName() = 0;
    virtual std::string getSign() = 0;
    virtual int getPredecence() = 0;
    virtual int getArgumentCount() = 0;
    virtual OperatorAssociativity getAssociativity() { return OperatorAssociativity::Left; }

    virtual PreciseValue doOperation(std::vector<PreciseValue>) = 0;
};

#endif // OPERATOR_H
