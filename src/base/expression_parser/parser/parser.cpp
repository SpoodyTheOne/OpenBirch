#include "parser.h"
#include "base/openbirchstaticerror.h"

Expression* Parser::parse()
{
    Expression* expr = expression();

    if (!isAtEnd())
        throw OpenBirchStaticError(peek(), "Unfinished expression");

    return expr;
}

Expression* Parser::expression()
{
    return equality();
}

Expression* Parser::equality()
{
    Expression* expr = comparison();

    auto seq = {
        TokenType::BANG_EQUALS, // !=
        TokenType::EQUAL_EQUAL  // ==
    };

    while( match(seq) )
    {
        Token* op = previous();
        Expression* right = comparison();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::comparison()
{
    Expression* expr = term();

    auto seq = {
        TokenType::GREATER,         // >
        TokenType::GREATER_EQUAL,   // >=
        TokenType::LESS,            // <
        TokenType::LESS_EQUAL       // <=
    };

    while( match(seq) )
    {
        Token* op = previous();
        Expression* right = term();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::term()
{
    Expression* expr = factor();

    auto seq = {
        TokenType::MINUS,       // -
        TokenType::PLUS,        // +
    };

    while( match(seq) )
    {
        Token* op = previous();
        Expression* right = factor();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::factor()
{
    Expression* expr = unary();

    auto seq = {
        TokenType::SLASH,       // /
        TokenType::STAR,        // *
    };

    while( match(seq) )
    {
        Token* op = previous();
        Expression* right = unary();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::unary()
{
    auto seq = {
        TokenType::MINUS,       // -
    };

    if ( match( seq ) )
    {
        Token* op = previous();
        Expression* right = exponent();
        return new UnaryExpr(op,right);
    }

    return exponent();
}

Expression* Parser::exponent()
{
    Expression* expr = factorial();

    auto seq = {
        TokenType::EXPONENT,       // ^
    };

    while( match(seq) )
    {
        Token* op = previous();
        Expression* right = factorial();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::factorial()
{
    Expression* expr = primary();

    auto seq = {
        TokenType::BANG,       // ^
    };

    while( match(seq) )
    {
        Token* op = previous();
        expr = new UnaryExpr(op,expr);
    }

    return expr;
}

Expression* Parser::primary()
{
    if (match({TokenType::FALSE})) return new LiteralExpr(false);
    if (match({TokenType::TRUE})) return new LiteralExpr(true);

    if (match( {TokenType::STRING} )) return new LiteralExpr(previous()->getLiteral());

    if (match( {TokenType::INTEGER, TokenType::DECIMAL } ))
        return new LiteralExpr( Number(previous()->getLiteral()) );

    if (match( {TokenType::LPAREN} )) {
        Expression* expr = expression();
        expect(TokenType::RPAREN, "Expect ')' after expression.");
        return expr;
    }

    throw OpenBirchStaticError(peek(), "Expected token here");
}

/**
 * @brief Parser::match. Returns true if the next token is any in the given sequence
 * @param types
 * @return boolean
 */
bool Parser::match(std::initializer_list<TokenType> types, int index)
{
    for (TokenType type : types) // Loop over every token we recieved
    {
        if (check(type, index)) { // If we ever hit a token in the sequence
            advance();      // Consume token,
            return true;   // Then return true
        }
    }
    // Never met an expected token.
    return false;
}

bool Parser::check(TokenType type, int index)
{
    if (isAtEnd())
        return false;

    return peek(index)->type() == type;
}

bool Parser::isAtEnd()
{
    return peek()->type() == TokenType::END_OF_FILE;
}

Token* Parser::advance()
{
    if (!isAtEnd()) currentToken++;
    return previous();
}

Token* Parser::peek(int index)
{
    return tokens.at(currentToken + index);
}

Token* Parser::previous()
{
    return tokens.at(currentToken - 1);
}

Token* Parser::expect(TokenType type, std::string message)
{
    if (check(type)) return advance();

    throw OpenBirchStaticError(peek(), message);
}
