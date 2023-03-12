#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "operator.h"

class Subtraction : public Operator
{
public:
    std::string name() { return std::string("Subtraction"); }
    std::string sign() { return std::string("-"); }
    int predecence() { return 2; }

    static Operator* create() { return new Subtraction(); }
};

#endif // SUBTRACTION_H
