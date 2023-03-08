#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <string>
#include <unordered_map>
#include "operands.h"

struct ParserTreeBranch {
    OperandType operand;

    ParserTreeBranch *part0;
    ParserTreeBranch *part1;

    std::vector<std::vector<T>> power;
    std::vector<std::vector<T>> num0;
    std::vector<std::vector<T>> num1;
};

class ParserTree
{
public:
    ParserTree();

    void splitString ( std::string input );

    ParserTreeBranch root;
};

#endif // PARSERTREE_H
