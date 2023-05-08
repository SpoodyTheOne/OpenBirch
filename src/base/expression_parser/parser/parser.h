#ifndef PARSER_H
#define PARSER_H


#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/parser/expression.h"
#include "base/expression_parser/parser/statement.h"
#include <vector>
class Parser
{
public:
    Parser(std::vector<Token *> _tokens) : tokens(_tokens)
    {};

    std::vector<Statement *> parse();

private:
    std::vector<Token *> tokens;
    int currentToken = 0;

    Statement* declaration();
    Statement* varDeclaration();

    Statement* statement();

    ExpressionStatement* expressionStatement();
    CallStatement* callStatement();

    Expression* expression();
    Expression* equality();
    Expression* comparison();
    Expression* term();
    Expression* factor();
    Expression* unary();
    Expression* exponent();
    Expression* factorial();
    Expression* primary();

    bool match(std::initializer_list<TokenType>, int index = 0, bool consume = true);
    bool check(TokenType, int index = 0);
    bool isAtEnd();
    bool terminator();

    void expectTerminator();

    Token* advance();
    Token* peek(int index = 0);
    Token* previous();
    Token* expect(TokenType, std::string);
};

#endif // PARSER_H
