#ifndef PARSER_H
#define PARSER_H

#include <QString>

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
};

#endif // PARSER_H
