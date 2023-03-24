#ifndef LEXER_H
#define LEXER_H

#include "base/expression_parser/lexer/token.h"

#include <vector>

class Lexer
{
public:
    Lexer(std::string _source);
    std::vector<Token *> tokenize();
private:
    std::string source;
    std::vector<Token *> tokens;

    size_t start{0};
    size_t currentCharIdx{0};
    int currentLine{0};

    bool isAtEnd() const;
    void scanToken();
    char peek() const;
    char advance();
    void addToken(TokenType tokenType);
    void addToken(TokenType tokenType, std::string literal);
    bool match(char expected);

    void lexString();
};

#endif // LEXER_H
