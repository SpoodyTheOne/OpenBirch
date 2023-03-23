#ifndef LEXER_H
#define LEXER_H

#include "interpreter/token.h"
#include <vector>

namespace BirchLang {

class Lexer
{
public:
    Lexer(std::string);

    void tokenize();

    std::vector<Token> tokenList;
    std::string source;
};

}
#endif // LEXER_H
