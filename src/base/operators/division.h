#ifndef DIVISION_H
#define DIVISION_H

#include "operator.h"

class Division : public Operator
{
public:
    inline static const std::string name = "Division";
    inline static const std::string sign = "/";
    inline static const int predecence = 3;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new Division(); }
};

#endif // DIVISION_H
