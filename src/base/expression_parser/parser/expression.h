#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/number.h"

class Expression
{};

class BinaryExpr : public Expression
{
public:
    BinaryExpr(Expression* l, Token* o, Expression* r) : m_Left(l), m_Operator(o), m_Right(r) {}

    Expression * m_Left;
    Token *m_Operator;
    Expression *m_Right;
};

class UnaryExpr : public Expression
{
public:
    UnaryExpr(Token* o, Expression* r) : m_Operator(o), m_Right(r) {}

    Token *m_Operator;
    Expression *m_Right;
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

private:
    std::string StringValue;
    Number NumberValue;
    bool BooleanValue;

    LiteralType _type;
};

#endif // EXPRESSION_H
