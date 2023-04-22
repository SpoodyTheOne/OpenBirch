#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "base/expression_parser/parser/expression.h"
#include "base/expression_parser/statementvisitor.h"
#include "base/expression_parser/parser/statement.h"
#include <string>

class Interpreter : public ExpressionVisitor, public StatementVisitor
{
public:
    static std::vector<std::string> interpret(std::vector<Statement*>);

    Interpreter();
    ~Interpreter();

    Expression* visitLiteral(LiteralExpr*);
    Expression* visitBinary(BinaryExpr*);
    Expression* visitUnary(UnaryExpr*);

    void visitExpressionStatement(ExpressionStatement*);
    void visitCallStatement(CallStatement*);

private:
    Expression* evaluate(Expression*);
    void        execute(Statement *);
    std::vector<std::string> outputs;
};

#endif // INTERPRETER_H
