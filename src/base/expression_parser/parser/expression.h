#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/number.h"
#include "base/openbirchparsererror.h"

class LiteralExpr;

enum ExprType {
    Binary,
    Unary,
    Literal,
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

protected:
    Expression(Expression* left, Token* op, Expression* right, ExprType t) : m_Left(left), m_Operator(op), m_Right(right), expressionType(t) {}
    Expression(ExprType t) : expressionType(t) {}
};

class BinaryExpr : public Expression
{
public:
    BinaryExpr(Expression* l, Token* o, Expression* r) : Expression(l, o, r, ExprType::Binary) {}

    LiteralExpr* getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Binary foo!"); };
};

class UnaryExpr : public Expression
{
public:
    UnaryExpr(Token* o, Expression* r) : Expression(0, o, r, ExprType::Unary) {}


    LiteralExpr* getLiteral() { throw std::runtime_error("You bitchass mf, cant getLiteral() if expressionType is Unary foo!"); };
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

    LiteralExpr* getLiteral();

    ExprType expressionType = ExprType::Literal;

private:
    std::string StringValue = "";
    Number NumberValue = 0;
    bool BooleanValue = 0;

    LiteralType _type;
};

#endif // EXPRESSION_H
