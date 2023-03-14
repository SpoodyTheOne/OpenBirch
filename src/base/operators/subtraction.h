#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "operator.h"

class Subtraction : public Operator
{
public:
    inline static const std::string name = "Subtraction";
    inline static const std::string sign = "-";
    inline static const int predecence = 2;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Subtraction(); }

    ExpressionValue doOperation(ExpressionValue a, ExpressionValue b) { return b - a; }
};

#endif // SUBTRACTION_H
