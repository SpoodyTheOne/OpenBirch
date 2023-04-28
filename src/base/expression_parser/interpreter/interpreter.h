#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "base/expression_parser/environment.h"
#include "base/expression_parser/parser/expression.h"
#include "base/expression_parser/statementvisitor.h"
#include "base/expression_parser/parser/statement.h"
#include <string>

class Interpreter : public ExpressionVisitor, public StatementVisitor
{
public:
    static std::vector<std::string> interpret(std::vector<Statement*>, Environment* = 0);
    Interpreter();
    Interpreter(Environment* globalEnvironment);
    ~Interpreter();

    Expression* visitLiteral(LiteralExpr*);
    Expression* visitBinary(BinaryExpr*);
    Expression* visitUnary(UnaryExpr*);
    Expression* visitVariable(VariableExpr*);
    Expression* visitUnknown(UnknownExpression*);

    void visitVariableStatement(VariableStatement*);
    void visitExpressionStatement(ExpressionStatement*);
    void visitCallStatement(CallStatement*);

private:
    Expression* evaluate(Expression*);
    void        execute(Statement *);
    std::vector<std::string> outputs;
    Environment* environment;
    bool localEnvironment = true;
};

#endif // INTERPRETER_H
