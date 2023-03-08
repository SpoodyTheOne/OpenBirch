#include "parsertree.h"
#include "expressiondatatypes.h"

ParserTree::ParserTree()
{

}

bool isNumber(char);

void ParserTree::splitString(std::string str) {
    // str is already trimmed of all whitespace.

    const char* expression = str.c_str();

    ParserTreeBranch currentBranch = root;

    std::string workingRegister = "";
    std::string operandRegister = "";
    std::string saveRegister = "";

    for (uint i = 0; i < str.length(); i++) {
        if (isNumber(*expression))
            workingRegister = workingRegister + *expression++;
        else {
            operandRegister = operandRegister + *expression++;

            if (!saveRegister.empty()) {
                // Create operand between workingRegister and saveRegister

                ExpressionData data;

                data.type = ExpressionDataType::number;

                std::vector<std::vector<T>> vec;
                std::vector<T> fuck_me;
                fuck_me.push_back(std::atoi(workingRegister.c_str()));
                vec.push_back(fuck_me);

                root.num0 = vec;

                std::vector<std::vector<T>> vec2;
                std::vector<T> fuck_me2;

                fuck_me2.push_back(std::atoi(saveRegister.c_str()));
                vec2.push_back(fuck_me2);

                root.num1 = vec2;

                root.operand = OperandKeywords[operandRegister];

                workingRegister.clear();
                operandRegister.clear();
                saveRegister.clear();

                continue;
            }

            saveRegister = workingRegister;
        }
    }
}

bool isNumber(char c) {
    return (c <= 57) && (c >= 48);
}
