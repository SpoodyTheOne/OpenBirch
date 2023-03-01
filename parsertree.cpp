#include "parsertree.h"

ParserTree::ParserTree()
{

}

bool isNumber(char);

void ParserTree::splitString(std::string str) {
    // str is already trimmed of all whitespace.

    const char* expression = str.c_str();

    ParserTreeBranch currentBranch = root;

    std::string currentstring = "";
    // 0 = currently unsure
    // 1 = currently adding to a number
    // 2 = currently adding to an operand
    // 3 = currently adding to a symbol
    int currentMode = 0;

    for (uint i = 0; i < str.length(); i++) {
        //if (isNumber(*expression))
    }
}

bool isNumber(char c) {
    int ci = (int)c;
    return (ci <= 57) && (ci >= 48);
}
