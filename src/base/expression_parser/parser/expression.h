#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "base/expression_parser/lexer/token.h"

class Expression
{};

class Equality : public Expression
{
    Expression * m_Left;
    Token *m_Operator;
    Expression *m_Right;
};

#endif // EXPRESSION_H
