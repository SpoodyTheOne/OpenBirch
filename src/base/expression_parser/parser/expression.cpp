#include "expression.h"

LiteralExpr::LiteralExpr(std::string s) : Expression(ExprType::Literal)
{
    _type = LiteralType::String;
    this->StringValue = s;
}

LiteralExpr::LiteralExpr(Number n) : Expression(ExprType::Literal)
{
    _type = LiteralType::Num;
    this->NumberValue = n;
}

LiteralExpr::LiteralExpr(bool b) : Expression(ExprType::Literal)
{
    _type = LiteralType::Boolean;
    this->BooleanValue = b;
}

LiteralExpr::LiteralExpr() : Expression(ExprType::Literal)
{
    _type = LiteralType::Null;
}

LiteralExpr* LiteralExpr::getLiteral()
{
    return this;
}
