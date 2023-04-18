#include "expression.h"
#include <iostream>

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

std::string LiteralExpr::toString()
{
    switch (_type)
    {
    case LiteralType::String:
        return this->getStringValue();
        break;
    case LiteralType::Boolean:
        return this->getBooleanValue() ? "true" : "false";
    case LiteralType::Num:
        return this->getNumberValue().toString();
    default:
        return "null";
    }
}
