#ifndef PARSER_H
#define PARSER_H


#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/parser/expression.h"
#include "base/expression_parser/parser/statement.h"
#include <memory>
#include <vector>

class Parser
{
public:
    Parser(std::vector<std::shared_ptr<Token>> _tokens);

    std::vector<std::shared_ptr<Statement>> parse();

private:
    std::vector<std::shared_ptr<Token>> tokens;
    int currentToken = 0;

    std::shared_ptr<Statement> declaration();
    std::shared_ptr<Statement> varDeclaration();

    std::shared_ptr<Statement> statement();

    std::shared_ptr<ExpressionStatement> expressionStatement();
    std::shared_ptr<CallStatement> callStatement();

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

    std::shared_ptr<Token> advance();
    std::shared_ptr<Token> peek(int index = 0);
    std::shared_ptr<Token> previous();
    std::shared_ptr<Token> expect(TokenType, std::string);
};

#endif // PARSER_H
