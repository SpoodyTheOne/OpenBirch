#include "expressions.h"

expressionResult Expressions::parseExpression(std::string input) {
    symbol_table_t symbol_table;
    parser_t parser;
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    if (!parser.compile(input,expression)) {
        return *new expressionResult(true,parser.error());
    }

    T result = expression.value();

    return *new expressionResult(result);
}

std::string Expressions::parseExpressionToString(std::string input) {
    expressionResult parsed = parseExpression(input);

    if (parsed.isError)
        return parsed.message;

    return std::to_string(parsed.value);
}

void Expressions::resetSymbolTable() {
    symbol_table_t symbol_table;
    symbol_table.clear();
}

