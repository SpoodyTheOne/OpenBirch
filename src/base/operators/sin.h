#ifndef SIN_H
#define SIN_H

#include "operator.h"

class Sin : public Operator
{
public:
    inline static const std::string name = "Addition";
    inline static const std::string sign = "sin";
    inline static const int predecence = 5;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new Sin(); }
};


#endif // SIN_H
