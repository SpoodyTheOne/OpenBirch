#include "token.h"

#include <string>

Token::Token(TokenType _tokenType, std::string _literal, int _lineNo, int _charNo, int _length) :
    tokenType{_tokenType}, literal{_literal}, lineNo{_lineNo}, charNo(_charNo), length(_length)
{

}

std::string Token::toString() const
{
    return tokenType2String.at(tokenType) + "(" + literal + ")";
}
