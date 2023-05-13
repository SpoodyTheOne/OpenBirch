#include "parser.h"
#include "base/openbirchstaticerror.h"

Parser::Parser(std::vector<Token>&& _tokens) : tokens{std::move(_tokens)}
{

}

std::vector<std::shared_ptr<Statement>> Parser::parse()
{
    // list of statements to return after parsing
    std::vector<std::shared_ptr<Statement>> statements = {};

    // consume tokens and construct statements until we hit a terminator
    while ( !terminator() )
        statements.push_back(declaration());

    // throw an error if we have tokens left over
    if (!isAtEnd())
        throw OpenBirchStaticError(peek(), "Unfinished expression");

    return statements;
}

std::shared_ptr<Statement> Parser::declaration()
{
    // check for the pattern "var := expr"
    if (peek().type() == TokenType::IDENTIFIER)
        if (peek(1).type() == TokenType::COLON_EQUALS)
            return varDeclaration();

    // not declaring, so we construct a regular statement
    return statement();
}

std::shared_ptr<Statement> Parser::varDeclaration()
{
    // get the name of the new variable
    const Token& name = expect(TokenType::IDENTIFIER, "Unreachable error :) how tf");
    advance(); // consume := token

    // construct expression to get value of variable.
    std::shared_ptr<Expression> value = expression();

    // expect ; after declaration
    expectTerminator();

    return std::make_shared<DeclareStatement>(name,value);
}

std::shared_ptr<Statement> Parser::statement()
{
    if ( match({TokenType::CALL}) )
    {
        return callStatement();
    }

    return expressionStatement();
}

std::shared_ptr<ExpressionStatement> Parser::expressionStatement()
{
    std::shared_ptr<Expression> expr = expression();

    if (peek().type() == TokenType::COLON_EQUALS)
        throw OpenBirchStaticError(peek(), "Can't assign to an expression/temporary value");

    expectTerminator();
    return std::make_shared<ExpressionStatement>(expr);
}

std::shared_ptr<CallStatement> Parser::callStatement()
{
    std::shared_ptr<Expression> callIdentifier = primary();

    if (!match( { TokenType::COMMA } ))
    {
        expectTerminator();
        return std::make_shared<CallStatement>(callIdentifier, std::vector<std::shared_ptr<Expression>>{});
    }

    std::vector<std::shared_ptr<Expression>> expressions;

    while ( !terminator() )
    {
        expressions.push_back(expression());
    }

    return std::make_shared<CallStatement>(callIdentifier, expressions);
}

std::shared_ptr<Expression> Parser::expression()
{
    return equality();
}

std::shared_ptr<Expression> Parser::equality()
{
    std::shared_ptr<Expression> expr = comparison();

    auto seq = {
        TokenType::EQUAL,       // =
        TokenType::SLASH_EQUALS // /=
    };

    while( match(seq) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = comparison();
        expr = std::make_shared<BinaryExpr>(expr,op,right);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::comparison()
{
    std::shared_ptr<Expression> expr = term();

    auto seq = {
        TokenType::GREATER,         // >
        TokenType::GREATER_EQUAL,   // >=
        TokenType::LESS,            // <
        TokenType::LESS_EQUAL       // <=
    };

    while( match(seq) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = term();
        expr = std::make_shared<BinaryExpr>(expr,op,right);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::term()
{
    std::shared_ptr<Expression> expr = factor();

    auto seq = {
        TokenType::MINUS,       // -
        TokenType::PLUS,        // +
    };

    while( match(seq) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = factor();
        expr = std::make_shared<BinaryExpr>(expr,op,right);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::factor()
{
    if (match( {TokenType::INTEGER, TokenType::DECIMAL, TokenType::IDENTIFIER }, 0, false))
    {
        if (match( { TokenType::IDENTIFIER }, 1, false ))
        {
            std::shared_ptr<Expression> e = unary();

            std::shared_ptr<Token> multiplyToken = std::make_shared<Token>(TokenType::STAR,"*",-1,-1,0);

            return std::make_shared<BinaryExpr>(e, multiplyToken, unary());
        }
    }

    std::shared_ptr<Expression> expr = unary();

    auto seq = {
        TokenType::SLASH,       // /
        TokenType::STAR,        // *
    };

    while( match(seq) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = unary();
        expr = std::make_shared<BinaryExpr>(expr,op,right);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::unary()
{
    auto seq = {
        TokenType::MINUS,       // -
    };

    if ( match( seq ) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = exponent();
        return std::make_shared<UnaryExpr>(op,right);
    }

    return exponent();
}

std::shared_ptr<Expression> Parser::exponent()
{
    std::shared_ptr<Expression> expr = factorial();

    auto seq = {
        TokenType::EXPONENT,       // ^
    };

    if( match(seq) )
    {
        const Token& op = previous();
        std::shared_ptr<Expression> right = unary();
        expr = std::make_shared<BinaryExpr>(expr,op,right);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::factorial()
{
    std::shared_ptr<Expression> expr = primary();

    auto seq = {
        TokenType::BANG,       // ^
    };

    while( match(seq) )
    {
        const Token& op = previous();
        expr = std::make_shared<UnaryExpr>(op,expr);
    }

    return expr;
}

std::shared_ptr<Expression> Parser::primary()
{
    if (match({TokenType::FALSE})) return std::make_shared<LiteralExpr>(false);
    if (match({TokenType::TRUE})) return std::make_shared<LiteralExpr>(true);

    if (match( {TokenType::STRING} )) return std::make_shared<LiteralExpr>(previous().getLiteral());

    if (match( {TokenType::INTEGER, TokenType::DECIMAL } ))
        return std::make_shared<LiteralExpr>( Number(previous().getLiteral()) );

    if (match( {TokenType::LPAREN} )) {
        std::shared_ptr<Expression> expr = expression();
        expect(TokenType::RPAREN, "Expect ')' after expression.");
        return expr;
    }

    if (match( {TokenType::IDENTIFIER} ))
    {
        std::cout << "VARIVLE" << std::endl;
        return std::make_shared<VariableExpr>(previous());
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

    return peek(index).type() == type;
}

bool Parser::isAtEnd()
{
    return peek().type() == TokenType::END_OF_FILE;
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

const Token& Parser::advance()
{
    if (!isAtEnd()) currentToken++;
    return previous();
}

const Token& Parser::peek(int index)
{
    return tokens.at(currentToken + index);
}

const Token& Parser::previous()
{
    return tokens.at(currentToken - 1);
}

const Token &Parser::expect(TokenType type, std::string message)
{
    if (check(type)) return advance();

    throw OpenBirchStaticError(peek(), message);
}
