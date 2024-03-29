#ifndef LEXER_H
#define LEXER_H

#include "base/expression_parser/lexer/token.h"

#include <vector>

class Lexer
{
public:
    Lexer(std::string _source);
    ~Lexer();
    std::vector<Token *> tokenize();
private:
    const char delimeter{'.'};
    const std::unordered_map<std::string, TokenType> keywords{
        {"if", TokenType::IF},
        {"elif", TokenType::ELIF},
        {"else", TokenType::ELSE},
        {"then", TokenType::THEN},
        {"end", TokenType::END},
        {"while", TokenType::WHILE},
        {"for", TokenType::FOR},
        {"do", TokenType::DO},
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"InternalCall", TokenType::CALL},
    };
    std::string source;
    std::vector<Token *> tokens;

    size_t start{0};
    size_t currentCharIdx{0};
    int currentLine{0};

    /**
     * @brief checks whether or not the current character being
     * processed is at the end of the source.
     * @return true if at the end, else false
     */
    bool isAtEnd() const;

    /**
     * @brief scans the next token. Will go through every character
     * until a token has been identified or its the end of the source.
     * Finally it will push the token to the token list.
     */
    void scanToken();

    /**
     * @brief peeks at the lookahead character. It's a readonly
     * and will not advance.
     * @param ahead: optionally specify how far to peek into the source.
     * The next character is when ahead is set to 0 (default).
     * @return the character at the lookahead position in the source. If
     * the lookahead character is outside of the source '\0' is returned.
     */
    char peek(int ahead = 0) const;

    /**
     * @brief consumes the character currently being processed,
     * and advances the current char index, to point to the next
     * character from the source.
     * @return
     */
    char advance();

    /**
     * @brief adds a token of type tokenType to the token list
     * @param tokenType: the token type of the token to be added.
     */
    void addToken(TokenType tokenType);

    /**
     * @brief adds a token of type tokenType to the token list.
     * @param tokenType: the token type of the token to be added.
     * @param literal: the data about a literal token to be stored
     * with the token.
     */
    void addToken(TokenType tokenType, std::string literal);

    /**
     * @brief matches the lookahead character to the expected character.
     * If it's a match then consume the character.
     * @param expected: the character to expect the lookahead character
     * to be.
     * @return true if the lookahead character is what thats expeted,
     * else false
     */
    bool match(char expected);

    /**
     * @brief lexes a string literal. Will advance until a terminating
     * quote is found, and create a string token with the literal data
     * field set to be the content inside of the string.
     */
    void lexString();

    /**
     * @brief lexes spaces until 4 or another character is found. Adds 1 TAB token per
     * 4 spaces
     */
    void lexSpaces();

    /**
     * @brief lexes a number literal. Will create a integer or decimal
     * token depending on the type of number literal. The number will
     * be stored in the token's literal data field in string form.
     */
    void lexNumber();

    void lexIdentifier();
};

#endif // LEXER_H
