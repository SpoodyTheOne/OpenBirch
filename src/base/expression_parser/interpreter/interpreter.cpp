#include "interpreter.h"
#include "base/openbirchstaticerror.h"

Number factorial(Number);

Interpreter::Interpreter()
{}

Interpreter::~Interpreter()
{}

std::string Interpreter::interpret(Expression* expr)
{
    Interpreter* i = new Interpreter();

    Expression* out = i->evaluate(expr);

    std::string result = out->getLiteral()->toString();

    delete i;
    return result;
}

Expression* Interpreter::evaluate(Expression* expr)
{
    return expr->accept(this);
}

Expression* Interpreter::visitLiteral(LiteralExpr* expr)
{
    return expr->getLiteral();
}

Expression* Interpreter::visitBinary(BinaryExpr* expr)
{
    Expression* left = evaluate(expr->m_Left);
    Expression* right = evaluate(expr->m_Right);

    switch(expr->m_Operator->type())
    {
    case TokenType::MINUS:
        return new LiteralExpr(left->getLiteral()->getNumberValue() - right->getLiteral()->getNumberValue());
    case TokenType::PLUS:
        return new LiteralExpr(left->getLiteral()->getNumberValue() + right->getLiteral()->getNumberValue());
    case TokenType::STAR:
        return new LiteralExpr(left->getLiteral()->getNumberValue() * right->getLiteral()->getNumberValue());
    case TokenType::SLASH:
        return new LiteralExpr(left->getLiteral()->getNumberValue() / right->getLiteral()->getNumberValue());
    case TokenType::EXPONENT:
        return new LiteralExpr(left->getLiteral()->getNumberValue() ^ right->getLiteral()->getNumberValue());
    default:
        return new LiteralExpr();
    }
}

Expression* Interpreter::visitUnary(UnaryExpr* expr)
{
    Expression* right = evaluate(expr->m_Right);

    switch(expr->m_Operator->type())
    {
    case TokenType::MINUS:
        return new LiteralExpr(right->getLiteral()->getNumberValue() * -1);
    case TokenType::BANG:
        return new LiteralExpr( factorial(right->getLiteral()->getNumberValue()) );
    default:
        return new LiteralExpr();
    }
}

Number factorial(Number num)
{
    if (num <= 1)
        return 1;

    return num * factorial( num - 1 );
}
