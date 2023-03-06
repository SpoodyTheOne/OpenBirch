#ifndef OPERANDS_H
#define OPERANDS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "typedef.h"

enum OperandType {
    add = 0,
    subtract = 1,
    multiply = 2,
    divide = 3,

    cross = 4,
    dot = 5,
    squareroot = 6,
    nth_root = 7,
    log = 8,
    nth_log = 9,
    parenthesis = 10,
};

struct Operand {
    OperandType type;

    std::vector<std::vector<T>> part0;
    std::vector<std::vector<T>> part1;
    T parameter;
};

extern std::unordered_map<std::string, OperandType> OperandKeywords;

#endif // OPERANDS_H
