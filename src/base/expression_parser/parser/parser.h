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

    /**
     * @brief The top level statement. Returns a varDeclaration if a
     * := is found, otherwise it just returns a statement
     * @return Statement*
     */
    std::shared_ptr<Statement> declaration();

    /**
     * @brief Constructs a declare statement from the given tokens
     * IDENTIFIER := EXPRESSION
     * @return Statement*
     */
    std::shared_ptr<Statement> varDeclaration();

    /**
     * @brief If the call keyword is found: creates a callStatement,
     * otherwise creates an expressionStatement.
     * @return Statement*
     */
    std::shared_ptr<Statement> statement();

    /**
     * @brief Creates an expressionStatement, which is just an expression
     * with extra steps
     * @return ExpressionStatement*
     */
    std::shared_ptr<ExpressionStatement> expressionStatement();

    /**
     * @brief Creates a call statement, which performs a C++ function defined
     * in Interpreter::visitCallStatement()
     * @return CallStatement*
     */
    std::shared_ptr<CallStatement> callStatement();

    /**
     * @brief Entry to expressions. Simply constructs an equality()
     * @return Expression*
     */
    std::shared_ptr<Expression> expression();

    /**
     * @brief Constructs an equality expression. eg. a = b, a /= b. Or a comparison
     * @return Expression*
     */
    std::shared_ptr<Expression> equality();

    /**
     * @brief Compares expressions. eg > < >= <=.
     * Constructs a term() otherwise.
     * @return Expression.
     */
    std::shared_ptr<Expression> comparison();


    /**
     * @brief Constructs a term, aka plus or minus. Otherise constructs a factor.
     * @return Expression*
     */
    std::shared_ptr<Expression> term();

    /**
     * @brief Constructs a factor, aka multiply or divide. Otherwise constructs a unary
     * @return Expression*
     */
    std::shared_ptr<Expression> factor();

    /**
     * @brief constructs a unary (eg. -3) or an exponent
      * @return Expression*
     */
    std::shared_ptr<Expression> unary();

    /**
     * @brief exponent (eg 2^3) or factorial
     * @return Expression*
     */
    std::shared_ptr<Expression> exponent();

    /**
     * @brief factorial
     * @return Expression*
     */
    std::shared_ptr<Expression> factorial();

    /**
     * @brief Highest order of precedence. Returns numbers, variables, parentheses
     * @return Expression*
     */
    std::shared_ptr<Expression> primary();

    /**
     * @brief Checks if the next token is one in the sequence
     * @param seq initializer list of matches. eg { TokenType::IDENTIFIER }
     * @param index, offset for where to look 0 is next token, -1 is previous, etc.
     * @param consume Whether or not to consume the token.
     * @return bool whether or not the token matches criteria.
     */
    bool match(std::initializer_list<TokenType> seq, int index = 0, bool consume = true);

    /**
     * @brief check if the next token is of the given type
     * @param offset for where to look. -1 is previous, etc.
     * @return bool whether or not token was found.
     */
    bool check(TokenType, int offset = 0);

    /**
     * @brief Checks if theres no more tokens.
     * @return true if the next token is END_OF_FILE, false otherwise
     */
    bool isAtEnd();

    /**
     * @brief Checks if the next token is a terminator
     * @return true if the next token is either ;, \n or END_OF_FILE. false othewise
     */
    bool terminator();

    /**
     * @brief Throws an error if the next token isnt a terminator
     */
    void expectTerminator();

    /**
     * @brief Consume the next token
     * @return the token that was consumed
     */
    std::shared_ptr<Token> advance();

    /**
     * @brief Get the next token without consuming it
     * @param offset for where to look. -1 for previous etc.
     * @return the token
     */
    std::shared_ptr<Token> peek(int offset = 0);

    /**
     * @brief previous token
     * @return returns the token that was most recently consumed
     */
    std::shared_ptr<Token> previous();

    /**
     * @brief Throws an error if the next token isnt the expected type
     * @return The next token
     */
    std::shared_ptr<Token> expect(TokenType, std::string);
};

#endif // PARSER_H
