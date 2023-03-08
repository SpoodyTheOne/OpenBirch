#include "expressionparser.h"
#include <cctype>
#include <algorithm>
#include <QString>

ExpressionParser::ExpressionParser()
{

}

QString ExpressionParser::parseString(std::string str) {
    // Remove spaces from string
    str.erase(remove(str.begin(),str.end(),' '),str.end());

    this->tree = ParserTree();
    this->tree.splitString(str);
    return QString("out");
}
