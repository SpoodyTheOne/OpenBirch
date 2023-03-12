#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "operator.h"

class Multiply : public Operator
{
public:
    std::string name() { return std::string("Multiply"); }
    std::string sign() { return std::string("*"); }
    int predecence() { return 3; }

    static Operator* create() { return new Multiply(); }
};

#endif // MULTIPLY_H
