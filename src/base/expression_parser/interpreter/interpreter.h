#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "base/expression_parser/parser/expression.h"
#include <string>

class Interpreter : public ExpressionVisitor
{
public:
    static std::string interpret(Expression*);

    Interpreter();
    ~Interpreter();

    Expression* visitLiteral(LiteralExpr*);
    Expression* visitBinary(BinaryExpr*);
    Expression* visitUnary(UnaryExpr*);

private:
    Expression* evaluate(Expression*);
};

#endif // INTERPRETER_H
