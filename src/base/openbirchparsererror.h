#ifndef OPENBIRCHPARSERERROR_H
#define OPENBIRCHPARSERERROR_H


#include "base/expression_parser/lexer/token.h"
#include <stdexcept>
#include <cstring>

class OpenBirchParserError : public std::runtime_error
{
public:
    OpenBirchParserError(int _where, std::string _what): std::runtime_error(_what),  where(_where), end(_where), err(_what)
    {}

    OpenBirchParserError(int _where, int _end, std::string _what): std::runtime_error(_what),  where(_where), end(_end), err(_what)
    {}

    OpenBirchParserError(Token* _where, std::string _what): std::runtime_error(_what),  where(_where->charStart()), end(_where->charEnd()), err(_what)
    {}

    const char * what() const noexcept override  {
        std::string msg = std::to_string(where) + ": " + err;
        char *test = (char*) malloc(msg.size()*sizeof(char));

        strcpy(test, msg.c_str());
        return test;
    }

private:
    int where;
    int end;
    std::string err;

};

#endif // OPENBIRCHPARSERERROR_H
