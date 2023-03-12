#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "operator.h"

class Multiply : public Operator
{
public:
    inline static const std::string name = "Multiply";
    inline static const std::string sign = "*";
    inline static const int predecence = 3;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new Multiply(); }
};

#endif // MULTIPLY_H
