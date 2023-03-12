#ifndef ADDITION_H
#define ADDITION_H

#include "operator.h"

class Addition : public Operator
{
public:
    std::string name() { return std::string("Addition"); }
    std::string sign() { return std::string("+"); }
    int predecence() { return 2; }

    static Operator* create() { return new Addition(); }
};

#endif // ADDITION_H
