#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include "parsertree.h"
#include "operands.h"

class ExpressionParser
{
public:
    ExpressionParser();

    ParserTree tree;

    void parseString( std::string str );
};

#endif // EXPRESSIONPARSER_H
