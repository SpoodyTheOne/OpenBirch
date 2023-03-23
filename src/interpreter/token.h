#ifndef TOKEN_H
#define TOKEN_H

namespace BirchLang {

enum TokenType {
    Id,
    Operator,
    Statement,
    Number,
    String
};

class Token
{
public:
    Token();

    TokenType type;
};

}
#endif // TOKEN_H
