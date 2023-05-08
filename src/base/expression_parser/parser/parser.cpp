#include "parser.h"
#include "base/openbirchstaticerror.h"

Parser::Parser(std::vector<std::shared_ptr<Token>> _tokens) : tokens{_tokens}
{

}

std::vector<Statement *> Parser::parse()
{
    std::vector<Statement *> statements = {};

    while ( !terminator() )
        statements.push_back(declaration());

    if (!isAtEnd())
        throw OpenBirchStaticError(peek(), "Unfinished expression");

    return statements;
}

Statement* Parser::declaration()
{
    if (peek()->type() == TokenType::IDENTIFIER)
        if (peek(1)->type() == TokenType::COLON_EQUALS)
            return varDeclaration();

    return statement();
}

Statement* Parser::varDeclaration()
{
    std::shared_ptr<Token> name = expect(TokenType::IDENTIFIER, "Unreachable error :) how tf");
    advance();

    Expression* value = expression();

    expectTerminator();

    return new DeclareStatement(name,value);
}

Statement* Parser::statement()
{
    if ( match({TokenType::CALL}) )
    {
        return callStatement();
    }

    return expressionStatement();
}

ExpressionStatement* Parser::expressionStatement()
{
    Expression* expr = expression();

    expectTerminator();
    return new ExpressionStatement(expr);
}

CallStatement* Parser::callStatement()
{
    Expression* callIdentifier = primary();
    std::string i = callIdentifier->getLiteral()->toString();

    if (!match( { TokenType::COMMA } ))
    {
        expectTerminator();
        return new CallStatement(i, std::vector<Expression*>{});
    }

    std::vector<Expression*> expressions;

    while ( !terminator() )
    {
        expressions.push_back(expression());
    }

    return new CallStatement(i, expressions);
}

Expression* Parser::expression()
{
    return equality();
}

Expression* Parser::equality()
{
    Expression* expr = comparison();

    auto seq = {
        TokenType::EQUAL,       // ==
        TokenType::SLASH_EQUALS // /=
    };

    while( match(seq) )
    {
        std::shared_ptr<Token> op = previous();
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
        std::shared_ptr<Token> op = previous();
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
        std::shared_ptr<Token> op = previous();
        Expression* right = factor();
        expr = new BinaryExpr(expr,op,right);
    }

    return expr;
}

Expression* Parser::factor()
{
    if (match( {TokenType::INTEGER, TokenType::DECIMAL, TokenType::IDENTIFIER }, 0, false))
    {
        if (match( {TokenType::INTEGER, TokenType::DECIMAL, TokenType::IDENTIFIER }, 1, false ))
        {
            Expression* e = unary();

            std::shared_ptr<Token> multiplyToken = std::make_shared<Token>(TokenType::STAR,"*",-1,-1,0);

            return new BinaryExpr(e, multiplyToken, unary());
        }
    }

    Expression* expr = unary();

    auto seq = {
        TokenType::SLASH,       // /
        TokenType::STAR,        // *
    };

    while( match(seq) )
    {
        std::shared_ptr<Token> op = previous();
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
        std::shared_ptr<Token> op = previous();
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

    if( match(seq) )
    {
        std::shared_ptr<Token> op = previous();
        Expression* right = exponent();
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
        std::shared_ptr<Token> op = previous();
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

    if (match( {TokenType::IDENTIFIER} ))
    {
        std::cout << "VARIVLE" << std::endl;
        return new VariableExpr(previous());
    }

    throw OpenBirchStaticError(peek(), "Expected expression here");
}

/**
 * @brief Parser::match. Returns true if the next token is any in the given sequence
 * @param types
 * @return boolean
 */
bool Parser::match(std::initializer_list<TokenType> types, int index, bool consume)
{
    for (TokenType type : types) // Loop over every token we recieved
    {
        if (check(type, index)) { // If we ever hit a token in the sequence
            if (consume)
                advance(); // Consume token,

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

bool Parser::terminator()
{
    auto seq = {
        TokenType::SEMICOLON,
        TokenType::NEWLINE,
        TokenType::END_OF_FILE
    };

    if (!match(seq) && !isAtEnd())
        return false;

    return true;
}

void Parser::expectTerminator()
{
    if (!terminator())
        throw OpenBirchStaticError(currentToken, "Expected ; or newline before next expression");
}

std::shared_ptr<Token> Parser::advance()
{
    if (!isAtEnd()) currentToken++;
    return previous();
}

std::shared_ptr<Token> Parser::peek(int index)
{
    return tokens.at(currentToken + index);
}

std::shared_ptr<Token> Parser::previous()
{
    return tokens.at(currentToken - 1);
}

std::shared_ptr<Token> Parser::expect(TokenType type, std::string message)
{
    if (check(type)) return advance();

    throw OpenBirchStaticError(peek(), message);
}
