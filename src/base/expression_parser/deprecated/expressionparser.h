#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <QString>

#include "parsertree.h"


class ExpressionParser
{
public:
    ExpressionParser();

    ParserTree tree;

    QString parseString(std::string str);
};

#endif // EXPRESSIONPARSER_H
