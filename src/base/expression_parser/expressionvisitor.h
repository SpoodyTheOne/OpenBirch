#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H

class LiteralExpr;
class BinaryExpr;
class UnaryExpr;
class Expression;

class ExpressionVisitor
{
public:
    virtual Expression* visitLiteral(LiteralExpr*) = 0;
    virtual Expression* visitBinary(BinaryExpr*) = 0;
    virtual Expression* visitUnary(UnaryExpr*) = 0;
};

#endif // EXPRESSIONVISITOR_H
