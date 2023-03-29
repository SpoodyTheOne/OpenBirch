#ifndef PARSER_H
#define PARSER_H


#include "base/expression_parser/lexer/token.h"
#include <vector>
class Parser
{
public:
    Parser(std::vector<Token *> _tokens) : tokens(_tokens)
    {};

private:
    std::vector<Token *> tokens;
    int currentToken = 0;
};

#endif // PARSER_H
