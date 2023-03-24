#ifndef TOKEN_H
#define TOKEN_H

#include "base/expression_parser/lexer/tokentypes.h"
#include <string>

class Token
{
public:
    Token(TokenType _type, std::string _literal, int _lineNo);
    std::string toString() const;
private:
    const TokenType tokenType;
    const std::string literal;
    const int lineNo;
};

#endif // TOKEN_H
