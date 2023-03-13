#ifndef EXPONENT_H
#define EXPONENT_H

#include "operator.h"

class Exponent : public Operator
{
public:
    inline static const std::string name = "Exponent";
    inline static const std::string sign = "^";
    inline static const int predecence = 4;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Exponent(); }

    Number doOperation(Number a, Number b) { return std::pow(b,2); }
};


#endif // EXPONENT_H
