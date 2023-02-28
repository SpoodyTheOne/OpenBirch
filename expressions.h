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

    static parser_t *parser;
    static symbol_table_t *symbol_table;

    static parsedExpression parseExpression(std::string string) {
        expression_t expression;
        expression.register_symbol_table(*symbol_table);

        if (!parser->compile(string,expression)) {
            return *new parsedExpression(true,parser->error());
        }

        T result = expression.value();

        return *new parsedExpression(result);
    }

    static void resetSymbolTable() {
        symbol_table->clear();
    }
};

#endif // EXPRESSIONS_H
