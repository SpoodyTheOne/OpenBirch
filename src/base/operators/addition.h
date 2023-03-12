#ifndef ADDITION_H
#define ADDITION_H

#include "operator.h"

class Addition : public Operator
{
public:
    inline static const std::string name = "Addition";
    inline static const std::string sign = "+";
    inline static const int predecence = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new Addition(); }
};

#endif // ADDITION_H
