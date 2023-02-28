#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "exprtk.hpp"


typedef float T;

typedef exprtk::symbol_table<T> symbol_table_t;
typedef exprtk::expression<T>   expression_t;
typedef exprtk::parser<T>       parser_t;


struct parsedExpression {
    bool isError;
    std::string message;
    T value;

    parsedExpression(bool _isError,std::string _message) {
        value = 0;
        isError = _isError;
        message = _message;
    }

    parsedExpression(T _value) {
        value = _value;
        isError = false;
        message = "";
    }
};

class Expressions
{
public:
    Expressions();

    static void initialize();

    static parsedExpression parseExpression(std::string input);

    static std::string parseExpressionToString(std::string input);

    static void resetSymbolTable();
};

#endif // EXPRESSIONS_H
