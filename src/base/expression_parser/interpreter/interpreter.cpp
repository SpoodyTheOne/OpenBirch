#include "interpreter.h"
#include "base/openbirchstaticerror.h"

Number factorial(Number);
Number stirlingFactorial(Number);
Number optimizedFactorial(Number);
Number gammaFunctionApprox(Number);

Interpreter::Interpreter()
{}

Interpreter::~Interpreter()
{}

void Interpreter::interpret(std::vector<Statement *> statements)
{
    Interpreter* i = new Interpreter();

    for (Statement* statement : statements)
    {
        i->execute(statement);
    }

    delete i;
}

Expression* Interpreter::evaluate(Expression* expr)
{
    return expr->accept(this);
}

void Interpreter::execute(Statement* statement)
{
    statement->accept(this);
}

void Interpreter::visitExpressionStatement(ExpressionStatement* e)
{
    evaluate((Expression *) e->expression);
}

void Interpreter::visitCallStatement(CallStatement* e)
{
    std::string i = e->function;

    if (i == "cout")
    {
        for (Expression* e : e->arguments)
        {
            std::cout << evaluate(e)->getLiteral()->toUserString() << " ";
        }

        std::cout << std::endl;
    }
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
    if (num > 1000)
        return gammaFunctionApprox(num + 1);

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


Number gammaFunctionApprox(Number num)
{
    Number two_pi = Number::PI*2;
    Number e = Number::NATURAL_LOG;
    Number z = num;

    Number two_sqrt_pi = (two_pi/num)^Number(0.5);

    Number part2 = ( Number(1) / e ) * ( num + ( Number(1) / ( (Number(12) * num) - ( Number(1) / ( Number(10) * num ) ) ) ) );

    return two_sqrt_pi * ( part2^Number(num) );
}
