#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "base/expression_parser/expressionvisitor.h"
#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/number.h"
#include "base/openbirchparsererror.h"
#include <memory>

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
    std::shared_ptr<Expression> m_Left = 0;
    const Token* m_Operator;
    std::shared_ptr<Expression> m_Right = 0;

    virtual LiteralExpr& getLiteral() = 0;

    ExprType expressionType = ExprType::None;

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor*) = 0;

    virtual std::string toExpressionString() = 0;

    virtual ~Expression() {};

protected:
    Expression(std::shared_ptr<Expression> left, const Token& op, std::shared_ptr<Expression> right, ExprType t) : m_Left(left), m_Operator(&op), m_Right(right), expressionType(t) {}
    Expression(ExprType t) : expressionType(t) {}
};

class BinaryExpr : public Expression
{
public:
    BinaryExpr(std::shared_ptr<Expression> l, const Token& o, std::shared_ptr<Expression> r) : Expression(l, o, r, ExprType::Binary) {}

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor* visitor) { return visitor->visitBinary(*this); };

    LiteralExpr& getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Binary foo!"); };

    std::string toExpressionString();

    ~BinaryExpr() {
        std::cout << "Deleted BinaryExpr" << std::endl;
    }
};

class UnaryExpr : public Expression
{
public:
    UnaryExpr(const Token& o, std::shared_ptr<Expression> r) : Expression(0, o, r, ExprType::Unary) {}

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor* visitor) { return visitor->visitUnary(*this); };

    LiteralExpr& getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Unary foo!"); };

    std::string toExpressionString()
    {
        if (m_Operator->type() != TokenType::BANG)
            return "(" + m_Operator->getLiteral() + m_Right->toExpressionString() + ")";

        return "(" + m_Right->toExpressionString() + ")" + m_Operator->getLiteral();
    };

    ~UnaryExpr() {
        std::cout << "Deleted UnaryExpr" << std::endl;
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

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor* visitor) { return visitor->visitLiteral(*this); };

    LiteralExpr& getLiteral();

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
    VariableExpr(const Token& n) : Expression(ExprType::Variable), name(n) {};

    LiteralExpr& getLiteral();

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor* visitor) { return visitor->visitVariable(*this); };

    std::string toExpressionString();
    const Token& getName()
    {
        return name;
    }

private:
    const Token& name;
};

class UnknownExpression : public Expression
{
public:
    UnknownExpression() : Expression(ExprType::None) {};

    virtual std::shared_ptr<Expression> accept(ExpressionVisitor* visitor) { return visitor->visitUnknown(*this); };

    std::string toExpressionString() { return "null"; };

    LiteralExpr& getLiteral() { return *new LiteralExpr(); };
};


#endif // EXPRESSION_H
