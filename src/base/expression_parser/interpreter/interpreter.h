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
    static std::vector<std::string> interpret(std::vector<std::shared_ptr<Statement>>, Environment* = 0);
    Interpreter();
    Interpreter(Environment* globalEnvironment);
    ~Interpreter();

    std::shared_ptr<Expression> visitLiteral(LiteralExpr&);
    std::shared_ptr<Expression> visitBinary(BinaryExpr&);
    std::shared_ptr<Expression> visitUnary(UnaryExpr&);
    std::shared_ptr<Expression> visitVariable(VariableExpr&);
    std::shared_ptr<Expression> visitUnknown(UnknownExpression&);

    void visitDeclareStatement(DeclareStatement&);
    void visitExpressionStatement(ExpressionStatement&);
    void visitCallStatement(CallStatement&);

private:
    std::shared_ptr<Expression> evaluate(std::shared_ptr<Expression>);
    void        execute(std::shared_ptr<Statement>);
    std::vector<std::string> outputs;
    Environment* environment;
    bool localEnvironment = true;
};

#endif // INTERPRETER_H
