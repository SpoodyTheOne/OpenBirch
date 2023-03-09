#ifndef PARSER_H
#define PARSER_H

#include "base/expression_parser/tree.h"
#include <QString>

enum ParserState {
    Idle,
    Working,
    Error,
};

class Parser
{
public:
    Parser(QString input);
    Parser(std::string input);
    ~Parser();

    /**
     * @brief Compiles the input expression into a tree structure
     * representing the expression. Can later be used to evaluate
     * the expression with Parser::evaluate() method.
     */
    void compile();

    /**
     * @brief Evaluates the expression tree structure to a value.
     * @return Returns the value of the evaluated expression.
     */
    QString evaluate();

private:
    std::string m_Expression;
    Tree *m_expressionTree;
    ParserState state = ParserState::Idle;
    std::string err_msg = "";
};

#endif // PARSER_H
