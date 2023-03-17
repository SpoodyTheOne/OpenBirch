#ifndef PARSER_H
#define PARSER_H

#include "base/expression_parser/node.h"
#include <QString>

enum ParserState {
    Idle,
    Working,
    Error,
};

enum ParserOutputMode {
    Number,
    Variable,
    Function,
};

class Parser
{
public:
    Parser(QString input);
    Parser(std::string input);
    Parser();
    ~Parser();

    /**
     * @brief Compiles the input expression into a tree structure
     * representing the expression. Can later be used to evaluate
     * the expression with Parser::evaluate() method.
     * @return Returns an empty string if successful, otherwise this is the error encountered
     */
    QString compile(SymbolTable* = nullptr);

    /**
     * @brief Evaluates the expression tree structure to a value.
     * @param The symbol table context to evaluate in
     * @return Returns the value of the evaluated expression.
     */
    QString evaluate(SymbolTable* = nullptr, bool keepTree = false);

    void errorCompile(std::string err) {
        state = ParserState::Error;
        err_msg = err;
    }

    void setExpression(QString expression);
    Node* getTreeRoot() const;

private:
    std::string m_Expression = "";
    Node* treeRoot = nullptr;
    ParserState state = ParserState::Idle;
    std::string err_msg = "";

    ParserOutputMode outputMode = ParserOutputMode::Number;
    std::string outputSymbol = "";
};

#endif // PARSER_H
