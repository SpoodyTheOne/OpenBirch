#include "parser.h"

Expression Parser::expression()
{
    return equality();
}

Expression Parser::equality()
{

}

Expression Parser::comparison()
{

}

Expression Parser::term()
{

}

Expression Parser::factor()
{

}

Expression Parser::unary()
{

}

Expression Parser::exponent()
{

}

Expression Parser::factorial()
{

}

Expression Parser::primary()
{

}

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (TokenType type : types) // Loop over every token we recieved
    {
        if (!check(type)) { // If we ever hit an incorrect token in the sequence
            advance();      // Consume token,
            return false;   // Then return false
        }
        advance();
    }
    // Never met an unexpected token.
    return true;
}
