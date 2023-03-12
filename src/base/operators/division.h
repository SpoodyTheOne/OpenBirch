#ifndef DIVISION_H
#define DIVISION_H

#include "operator.h"

class Division : public Operator
{
public:
    std::string name() { return std::string("Division"); }
    std::string sign() { return std::string("/"); }
    int predecence() { return 3; }

    static Operator* create() { return new Division(); }
};

#endif // DIVISION_H
