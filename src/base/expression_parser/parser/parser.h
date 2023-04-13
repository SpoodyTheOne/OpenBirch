#ifndef PARSER_H
#define PARSER_H


#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/parser/expression.h"
#include <vector>
class Parser
{
public:
    Parser(std::vector<Token *> _tokens) : tokens(_tokens)
    {};

private:
    std::vector<Token *> tokens;
    int currentToken = 0;

    Expression expression();
    Expression equality();
    Expression comparison();
    Expression term();
    Expression factor();
    Expression unary();
    Expression exponent();
    Expression factorial();
    Expression primary();

    bool match(std::initializer_list<TokenType>);
    bool check(TokenType);
    Token advance();
};

#endif // PARSER_H
