#include "lexer.h"
#include "base/openbirchstaticerror.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

Lexer::Lexer(std::string _source) : source{_source}
{

}

Lexer::~Lexer() {

}

std::vector<std::shared_ptr<Token>> Lexer::tokenize()
{
    while (!isAtEnd())
    {
        // Scan next token
        start = currentCharIdx;

        scanToken();
    }

    // Source is scanned, lastly append EOL token and return
    addToken(TokenType::END_OF_FILE);
    return tokens;
}

void Lexer::scanToken()
{
    std::cout << "current char idx: " << currentCharIdx << std::endl;
    char c = advance();
    switch(c)
    {
    // Single char tokens
    case '(': addToken(TokenType::LPAREN, std::string(1,c)); break;
    case ')': addToken(TokenType::RPAREN, std::string(1,c)); break;
    case ',': addToken(TokenType::COMMA, std::string(1,c)); break;
    case '.': addToken(TokenType::DOT, std::string(1,c)); break;
    case '-': addToken(TokenType::MINUS, std::string(1,c)); break;
    case '+': addToken(TokenType::PLUS, std::string(1,c)); break;
    case ';': addToken(TokenType::SEMICOLON, std::string(1,c)); break;
    case '*': addToken(TokenType::STAR, std::string(1,c)); break;

    // Ignore comments
    case '#':
        while(peek() != '\n' && !isAtEnd()) advance();
        break;

    // One or two char tokens
    case ':':
        if (match('='))
            addToken(TokenType::COLON_EQUALS, ":=");
        else
            addToken(TokenType::COLON, std::string(1,c));
        break;

    case '/':
        if (match('='))
            addToken(TokenType::SLASH_EQUALS, "/=");
        else
            addToken(TokenType::SLASH, std::string(1,c));
        break;

    case '!':
        if (match('='))
            addToken(TokenType::BANG_EQUALS, "!=");
        else
            addToken(TokenType::BANG, std::string(1,c));
        break;

    case '=':
        if (match('='))
            addToken(TokenType::EQUAL_EQUAL, "==");
        else
            addToken(TokenType::EQUAL, std::string(1,c));
        break;

    case '<':
        if (match('='))
            addToken(TokenType::LESS_EQUAL, "<=");
        else
            addToken(TokenType::LESS, std::string(1,c));
        break;

    case '>':
        if (match('='))
            addToken(TokenType::GREATER_EQUAL, ">=");
        else
            addToken(TokenType::GREATER, std::string(1,c));
        break;

    // Ignore whitespace and tabs.
    case '\r':
        break;

    case '\t':
        addToken(TokenType::TAB);
        break;

    case ' ': lexSpaces(); break;

    // String literals
    case '"': lexString(); break;

    case '^': addToken(TokenType::EXPONENT, std::string(1,c)); break;

    case '\n':
      currentLine++;
      break;

    default:
        if (std::isdigit(c)) {
            // Number literals
            lexNumber();
        }
        else if (isalpha(c)) {
            // Identifiers
            lexIdentifier();
        }
        else {
            // TODO custom lexer exception
            throw OpenBirchStaticError(start,currentCharIdx,"Unexpected character");
        }

    }
}

bool Lexer::isalpha(char c)
{
    if (std::isalpha(c))
        return true;

    switch (c)
    {
    case '_':
        return true;
    }

    return false;
}

bool Lexer::isalnum(char c)
{
    return std::isdigit(c) || isalpha(c);
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


void Lexer::addToken(TokenType tokenType, std::string literal)
{
    tokens.push_back(std::make_shared<Token>(tokenType, literal, currentLine, start, currentCharIdx));
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
        throw OpenBirchStaticError(start,currentCharIdx,"Unterminated string");

    // Consume the last quote
    advance();

    // Trim the start and end quote from the token
    std::cout << source << std::endl;
    std::string literal = source.substr(start + 1, currentCharIdx - 1 - (start + 1));
    addToken(TokenType::STRING, literal);
}

void Lexer::lexSpaces() {
    int spaces = 1;
    while (peek() == ' ' && !isAtEnd())
    {
        spaces++;
        advance();
        if (spaces == 4) {
            addToken(TokenType::TAB);
            break;
        }
    }
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
    } else if (peek() == delimeter)
    {
        throw OpenBirchStaticError(currentCharIdx, "Unfinished delimeter");
    }

    TokenType tokenType{isFractional ? TokenType::DECIMAL : TokenType::INTEGER};
    addToken(tokenType, source.substr(start, currentCharIdx - start));
}

void Lexer::lexIdentifier()
{
    while(isalnum(static_cast<unsigned char>(peek()))) advance();

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


