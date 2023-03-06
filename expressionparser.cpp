#include "expressionparser.h"
#include <cctype>
#include <algorithm>

ExpressionParser::ExpressionParser()
{

}

void ExpressionParser::parseString(std::string str) {
    // Remove spaces from string
    str.erase(remove(str.begin(),str.end(),' '),str.end());

    this->tree = ParserTree();
    this->tree.splitString(str);
}
