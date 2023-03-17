#ifndef EQUALS_H
#define EQUALS_H

#include "operator.h"

class Equals : public Operator
{
public:
    inline static const std::string name = "Equals";
    inline static const std::string sign = "=";
    inline static const int predecence = 0;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Equals(); }

    ExpressionValue doOperation(ExpressionValue a, ExpressionValue b) { return a == b ? 1 : 0; }
};

#endif // EQUALS_H
