#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "operator.h"

class LParanthesis : public Operator
{
public:
    std::string name() { return std::string("Left Paranthesis"); }
    std::string sign() { return std::string("("); }
    int predecence() { return 5; }

    static Operator* create() { return new LParanthesis(); }
};

class RParanthesis : public Operator
{
public:
    std::string name() { return std::string("Right Paranthesis"); }
    std::string sign() { return std::string(")"); }
    int predecence() { return 5; }

    static Operator* create() { return new RParanthesis(); }
};

#endif // PARENTHESIS_H
