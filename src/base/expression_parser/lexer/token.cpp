#include "token.h"

#include <string>

Token::Token(TokenType _tokenType, std::string _literal, int _lineNo) :
    tokenType{_tokenType}, literal{_literal}, lineNo{_lineNo}
{

}

std::string Token::toString() const
{
    return tokenType2String.at(tokenType) + "(" + literal + ")";
}
