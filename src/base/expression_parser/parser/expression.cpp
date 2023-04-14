#include "expression.h"

LiteralExpr::LiteralExpr(std::string s)
{
    _type = LiteralType::String;
    this->StringValue = s;
}

LiteralExpr::LiteralExpr(Number n)
{
    _type = LiteralType::Num;
    this->NumberValue = n;
}

LiteralExpr::LiteralExpr(bool b)
{
    _type = LiteralType::Boolean;
    this->BooleanValue = b;
}

LiteralExpr::LiteralExpr()
{
    _type = LiteralType::Null;
}
