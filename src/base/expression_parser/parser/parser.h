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

    std::shared_ptr<Expression> expression();
    std::shared_ptr<Expression> equality();
    std::shared_ptr<Expression> comparison();
    std::shared_ptr<Expression> term();
    std::shared_ptr<Expression> factor();
    std::shared_ptr<Expression> unary();
    std::shared_ptr<Expression> exponent();
    std::shared_ptr<Expression> factorial();
    std::shared_ptr<Expression> primary();

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
