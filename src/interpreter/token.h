#ifndef TOKEN_H
#define TOKEN_H

#include <string>
namespace BirchLang {

enum TokenType {
    Id,
    Operator,
    Statement,
    Number,
    String,
    Terminator
};

class Token
{
public:
    Token();

    TokenType type;
    int charPlacement;
    std::string value;
};

}
#endif // TOKEN_H
