#ifndef OPENBIRCHSTATICERROR_H
#define OPENBIRCHSTATICERROR_H

#include "base/expression_parser/lexer/token.h"
#include <stdexcept>

class OpenBirchStaticError : public std::runtime_error
{
public:
    OpenBirchStaticError(int _where, std::string _what): std::runtime_error(_what),  where(_where), end(_where), err(_what)
    {}

    OpenBirchStaticError(int _where, int _end, std::string _what): std::runtime_error(_what),  where(_where), end(_end), err(_what)
    {}

    OpenBirchStaticError(Token _where, std::string _what): std::runtime_error(_what),  where(_where.charStart()), end(_where.charEnd()), err(_what)
    {}

    std::string what() {
        return std::to_string(where) + ": " + err;
    }

private:
    int where;
    int end;
    std::string err;

};

#endif // OPENBIRCHSTATICERROR_H
