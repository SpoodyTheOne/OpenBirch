#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
/*
#include "exprtk.hpp"

typedef float T;

typedef exprtk::symbol_table<T> symbol_table_t;
typedef exprtk::expression<T>   expression_t;
typedef exprtk::parser<T>       parser_t;

struct expressionResult {
    bool isError;
    std::string message;
    T value;

    expressionResult(bool _isError,std::string _message) {
        value = 0;
        isError = _isError;
        message = _message;
    }

    expressionResult(T _value) {
        value = _value;
        isError = false;
        message = "";
    }
};

class Expressions
{
public:
    static Expressions& instance()
    {
       static Expressions instance;
       return instance;
    }

    inline static symbol_table_t symbol_table;

    void initialize();

    expressionResult parseExpression(std::string input);

    std::string parseExpressionToString(std::string input);

    void resetSymbolTable();

private:
    Expressions();
};
*/
#endif // EXPRESSIONS_H
