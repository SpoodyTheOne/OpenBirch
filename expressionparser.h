#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include "parsertree.h"
#include <string>
#include <vector>

typedef double T;

enum ExpressionDataType {
    number = 0,
    vector = 1,
    matrix = 2,
    list = 3
};

struct ExpressionData {
    std::vector<std::vector<T>> data;
    ExpressionDataType type;
};

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
};

struct Operand {
    OperandType type;

    std::vector<std::vector<T>> part0;
    std::vector<std::vector<T>> part1;
    T parameter;
};

std::unordered_map<std::string, OperandType> CharToOperand = {
    {"+", OperandType::add},
    {"-", OperandType::subtract},
    {"*", OperandType::multiply},
    {"/", OperandType::divide},
    {"❌", OperandType::cross}
};

class ExpressionParser
{
public:
    ExpressionParser();

    ParserTree tree;

    void parseString( std::string str );
};

#endif // EXPRESSIONPARSER_H
