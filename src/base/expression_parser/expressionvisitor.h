#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

#include <memory>

class LiteralExpr;
class BinaryExpr;
class UnaryExpr;
class VariableExpr;
class UnknownExpression;
class Expression;

class ExpressionVisitor
{
public:
    virtual std::shared_ptr<Expression> visitLiteral(LiteralExpr&) = 0;
    virtual std::shared_ptr<Expression> visitBinary(BinaryExpr&) = 0;
    virtual std::shared_ptr<Expression> visitUnary(UnaryExpr&) = 0;
    virtual std::shared_ptr<Expression> visitVariable(VariableExpr&) = 0;
    virtual std::shared_ptr<Expression> visitUnknown(UnknownExpression&) = 0;

    virtual ~ExpressionVisitor() {};
};

#endif // EXPRESSIONVISITOR_H
