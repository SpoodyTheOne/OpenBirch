#include "lexer.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

Lexer::Lexer(std::string _source) : source{_source}
{

}

std::vector<Token *> Lexer::tokenize()
{
    while (!isAtEnd())
    {
        // Scan next token
        start = currentCharIdx;

        scanToken();
    }

    // Source is scanned, lastly append EOL token and return
    addToken(TokenType::EOL);
    return tokens;
}

void Lexer::scanToken()
{
    std::cout << "current char idx: " << currentCharIdx << std::endl;
    char c = advance();
    switch(c)
    {
    // Single char tokens
    case '(': addToken(TokenType::LPAREN); break;
    case ')': addToken(TokenType::RPAREN); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '*': addToken(TokenType::STAR); break;
    case '/': addToken(TokenType::SLASH); break;

    // Ignore comments
    case '#':
        while(peek() != '\n' && !isAtEnd()) advance();
        break;

    // One or two char tokens
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUALS : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;

    // Ignore whitespace and tabs.
    case ' ':
    case '\r':
    case '\t':
      break;

    // String literals
    case '"': lexString(); break;


    case '\n':
      currentLine++;
      break;

    default:
        if (std::isdigit(c)) {
            // Number literals
            lexNumber();
        }
        else if (std::isalpha(c)) {
            // Identifiers
            lexIdentifier();
        }
        else {
            // TODO custom lexer exception
            throw std::runtime_error("Unexpected character");
        }

    }
}

bool Lexer::isAtEnd() const
{
    return currentCharIdx >= source.size();
}

char Lexer::advance()
{
    return source[currentCharIdx++];
}

char Lexer::peek(int ahead) const
{
    if (currentCharIdx + ahead >= source.size()) return '\0';
    return source[currentCharIdx + ahead];
}

void Lexer::addToken(TokenType tokenType)
{
    tokens.push_back(new Token(tokenType, "", currentLine));
}

void Lexer::addToken(TokenType tokenType, std::string literal)
{
    tokens.push_back(new Token(tokenType, literal, currentLine));
}

bool Lexer::match(char expected)
{
    if (isAtEnd()) return false;
    if (source[currentCharIdx] != expected) return false;

    // It's match - consume the char
    currentCharIdx++;
    return true;
}

void Lexer::lexString()
{
    // Consume all characters between the quotes
    while (peek() != '"' && !isAtEnd())
    {
        // There can be newlines in the string literal
        if (peek() == '\n') currentLine++;

        advance();
    }

    // Check for unterminated string
    if (isAtEnd())
        throw std::runtime_error("Unterminated string");

    // Consume the last quote
    advance();

    // Trim the start and end quote from the token
    std::cout << source << std::endl;
    std::string literal = source.substr(start + 1, currentCharIdx - 1 - (start + 1));
    addToken(TokenType::STRING, literal);
}

void Lexer::lexNumber()
{
    // Look for first part of the number
    while (std::isdigit(peek())) advance();

    bool isFractional{false};

    // Look for fractional part
    if (peek() == delimeter && std::isdigit(peek(1)))
    {
        isFractional = true;

        // Consume the delimiter
        advance();

        while (std::isdigit(peek())) advance();
    }

    TokenType tokenType{isFractional ? TokenType::DECIMAL : TokenType::INTEGER};
    addToken(tokenType, source.substr(start, currentCharIdx - start));
}

void Lexer::lexIdentifier()
{
    while(std::isalnum(static_cast<unsigned char>(peek()))) advance();

    std::string identifier = source.substr(start, currentCharIdx - start);

    // Check if identifier is a reserved keyword
    std::unordered_map<std::string, TokenType>::const_iterator it = keywords.find(identifier);
    if (it != keywords.end())
    {
        // The identifier is a keyword
        addToken(it->second);
        return;
    }

    // The identifier is user defined
    addToken(TokenType::IDENTIFIER, identifier);
}

