#ifndef TOKEN_H
#define TOKEN_H

#include "base/expression_parser/lexer/tokentypes.h"
#include <string>

class Token
{
public:
    Token(TokenType _type, std::string _literal, int _lineNo, int _charNo, int _length);
    std::string toString() const;
    int charStart() { return charNo; };
    int charEnd() { return charNo + length; };
private:
    const TokenType tokenType;
    const std::string literal;
    const int lineNo;
    const int charNo;
    const int length;
};

#endif // TOKEN_H
