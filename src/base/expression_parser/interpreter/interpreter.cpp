#include "interpreter.h"
#include "base/openbirchstaticerror.h"

Number factorial(Number);
Number stirlingFactorial(Number);
Number optimizedFactorial(Number);

Interpreter::Interpreter()
{}

Interpreter::~Interpreter()
{}

std::string Interpreter::interpret(Expression* expr)
{
    Interpreter* i = new Interpreter();

    Expression* out = i->evaluate(expr);

    std::string result = out->getLiteral()->toUserString();

    delete out;

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

    bool two_strings = false;
    if (left->getLiteral()->type() == LiteralType::String || right->getLiteral()->type() == LiteralType::String)
        two_strings = true;

    switch(expr->m_Operator->type())
    {
    case TokenType::MINUS:
        return new LiteralExpr(left->getLiteral()->getNumberValue() - right->getLiteral()->getNumberValue());
    case TokenType::PLUS:
        if (two_strings)
            return new LiteralExpr(left->getLiteral()->toString() + right->getLiteral()->toString());
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
        return new LiteralExpr( optimizedFactorial(right->getLiteral()->getNumberValue()) );
    default:
        return new LiteralExpr();
    }
}

Number optimizedFactorial(Number num)
{
    if (num > 10000)
        return stirlingFactorial(num);

    return factorial(num);
}

Number factorial(Number num)
{
    if (num <= 1)
        return 1;

    Number output{1};
    do
    {
        output = output * num;
        num = num - 1;
    } while (num > 0);
    return output;
}

Number stirlingFactorial(Number num)
{
    // n! ~ sqrt(2*pi*n) * pow((n/e), n)

    Number pi = Number::PI;
    Number e = Number::NATURAL_LOG;

    return ((Number(2)*pi*num)^Number(0.5)) * ((num/e)^num);
}
