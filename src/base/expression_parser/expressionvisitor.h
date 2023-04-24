#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

class LiteralExpr;
class BinaryExpr;
class UnaryExpr;
class VariableExpr;
class UnknownExpression;
class Expression;

class ExpressionVisitor
{
public:
    virtual Expression* visitLiteral(LiteralExpr*) = 0;
    virtual Expression* visitBinary(BinaryExpr*) = 0;
    virtual Expression* visitUnary(UnaryExpr*) = 0;
    virtual Expression* visitVariable(VariableExpr*) = 0;
    virtual Expression* visitUnknown(UnknownExpression*) = 0;

    virtual ~ExpressionVisitor() {};
};

#endif // EXPRESSIONVISITOR_H
