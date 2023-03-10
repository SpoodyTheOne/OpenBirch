#ifndef OPERANDS_H
#define OPERANDS_H

#include "base/expression_parser/types.h"
#include <string>
#include <unordered_map>


// PEMDAS
std::unordered_map<std::string, int> Operands {
    {"(", 0},
    {"^", 1},
    {"*", 2},
    {"/", 3},
    {"+", 4},
    {"-", 5}

};

class Operand {
public:
    Operand();
    std::string name;
    std::string sign;

    Number doOperation(Number a, Number b);

    int Priority;
};

class MultiplyOperand: public Operand {
public:
    std::string name = "Multiply";
    std::string sign = "*";
    int Priority = Operands[sign];

    Number doOperation(Number a, Number b) {
        return a*b;
    }
};

#endif // OPERANDS_H
