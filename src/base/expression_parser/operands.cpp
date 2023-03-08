#include "operands.h"

std::unordered_map<std::string, OperandType> OperandKeywords = {
    {"+", OperandType::add},
    {"-", OperandType::subtract},
    {"*", OperandType::multiply},
    {"/", OperandType::divide},
    {"❌", OperandType::cross}
};
