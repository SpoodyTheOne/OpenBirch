#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "base/expression_parser/expressionvisitor.h"
#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/number.h"
#include "base/openbirchparsererror.h"
#include <iostream>


class LiteralExpr;

enum ExprType {
    Binary,
    Unary,
    Literal,
    Variable,
    None
};

class Expression
{
public:
    Expression * m_Left = 0;
    Token *m_Operator = 0;
    Expression *m_Right = 0;

    virtual LiteralExpr* getLiteral() = 0;

    ExprType expressionType = ExprType::None;

    virtual Expression* accept(ExpressionVisitor*) = 0;

    virtual std::string toExpressionString() = 0;

    virtual ~Expression() {};

protected:
    Expression(Expression* left, Token* op, Expression* right, ExprType t) : m_Left(left), m_Operator(op), m_Right(right), expressionType(t) {}
    Expression(ExprType t) : expressionType(t) {}
};

class BinaryExpr : public Expression
{
public:
    BinaryExpr(Expression* l, Token* o, Expression* r) : Expression(l, o, r, ExprType::Binary) {}

    virtual Expression* accept(ExpressionVisitor* visitor) { return visitor->visitBinary(this); };

    LiteralExpr* getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Binary foo!"); };

    std::string toExpressionString();

    ~BinaryExpr() {
        std::cout << "Deleted BinaryExpr" << std::endl;

        delete m_Left;
        delete m_Right;
    }
};

class UnaryExpr : public Expression
{
public:
    UnaryExpr(Token* o, Expression* r) : Expression(0, o, r, ExprType::Unary) {}

    virtual Expression* accept(ExpressionVisitor* visitor) { return visitor->visitUnary(this); };

    LiteralExpr* getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Unary foo!"); };

    std::string toExpressionString()
    {
        if (m_Operator->type() != TokenType::BANG)
            return "(" + m_Operator->getLiteral() + m_Right->toExpressionString() + ")";

        return "(" + m_Right->toExpressionString() + ")" + m_Operator->getLiteral();
    };

    ~UnaryExpr() {
        std::cout << "Deleted UnaryExpr" << std::endl;

        delete m_Right;
    }
};

enum LiteralType
{
    String,
    Num,
    Boolean,
    Null
};

class LiteralExpr : public Expression
{
public:
    LiteralType type() { return _type; };

    std::string getStringValue()    { return StringValue; };
    Number getNumberValue()         { return NumberValue; };
    bool getBooleanValue()          { return BooleanValue; };

    LiteralExpr(std::string);
    LiteralExpr(Number);
    LiteralExpr(bool);
    LiteralExpr();

    virtual Expression* accept(ExpressionVisitor* visitor) { return visitor->visitLiteral(this); };

    LiteralExpr* getLiteral();

    std::string toExpressionString() { return toString(); };

    ExprType expressionType = ExprType::Literal;

    std::string toString();
    std::string toUserString();

    ~LiteralExpr();

private:
    std::string StringValue = "";
    Number NumberValue = 0;
    bool BooleanValue = 0;

    LiteralType _type;
};

class VariableExpr : public Expression
{
public:
    VariableExpr(Token* n) : Expression(ExprType::Variable), name(n) {};

    LiteralExpr* getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Variable foo!"); };

    virtual Expression* accept(ExpressionVisitor* visitor) { return visitor->visitVariable(this); };

    std::string toExpressionString();
    Token* getName()
    {
        return name;
    }

private:
    Token* name;
};

class UnknownExpression : public Expression
{
public:
    UnknownExpression() : Expression(ExprType::None) {};

    virtual Expression* accept(ExpressionVisitor* visitor) { return visitor->visitUnknown(this); };

    std::string toExpressionString() { return "null"; };

    LiteralExpr* getLiteral() { return new LiteralExpr(); };
};


#endif // EXPRESSION_H
