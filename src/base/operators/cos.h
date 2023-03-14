#ifndef COS_H
#define COS_H

#include "operator.h"

class Cosine : public Operator
{
public:
    inline static const std::string name = "Cosine";
    inline static const std::string sign = "cos";
    inline static const int predecence = 5;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Cosine(); }

    ExpressionValue doOperation(ExpressionValue a, ExpressionValue b) { return std::cos(a+b); }
};


#endif // COS_H
