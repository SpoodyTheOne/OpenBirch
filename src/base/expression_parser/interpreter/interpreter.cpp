#include "interpreter.h"
#include "base/openbirchstaticerror.h"

Number factorial(Number);
Number stirlingFactorial(Number);
Number optimizedFactorial(Number);
Number gammaFunctionApprox(Number);

Interpreter::Interpreter()
{
    environment = new Environment();
}

Interpreter::Interpreter(Environment* globalEnvironment)
{
    environment = globalEnvironment;
    localEnvironment = false;
}

Interpreter::~Interpreter()
{
    if (localEnvironment)
        delete environment;
}

std::vector<std::string> Interpreter::interpret(std::vector<std::shared_ptr<Statement>> statements, Environment* globalEnv)
{
    Interpreter* i;

    if (globalEnv == nullptr)
        i = new Interpreter();
    else
        i = new Interpreter(globalEnv);

    for (std::shared_ptr<Statement> statement : statements)
    {
        i->execute(statement);
    }

    std::vector<std::string> output = i->outputs;

    delete i;

    return output;
}


std::shared_ptr<Expression> Interpreter::evaluate(std::shared_ptr<Expression> expr)
{
    return expr->accept(this);
}

void Interpreter::execute(std::shared_ptr<Statement> statement)
{
    statement->accept(this);
}

void Interpreter::visitDeclareStatement(DeclareStatement& v)
{
    std::shared_ptr<Expression> value = v.getValue();
    bool canLiteral = true;

    try {
        value = evaluate(value);
        value->getLiteral();
    } catch (std::runtime_error e) {
        // Undefined variable
        canLiteral = false;
    }

    environment->define(v.getName()->getLiteral(), value);
//    outputs.push_back(v.getName()->getLiteral() + " := " + (canLiteral ? value->getLiteral().toString() : value->toExpressionString()));
}

void Interpreter::visitExpressionStatement(ExpressionStatement& e)
{
    try {
        std::shared_ptr<Expression> out = evaluate(e.expression);
        if (out->expressionType == ExprType::Literal)
            outputs.push_back(out->getLiteral().toUserString());
        else
            outputs.push_back(out->toExpressionString());
    } catch (OpenBirchStaticError) {
        outputs.push_back((e.expression)->toExpressionString());
    }
}

void Interpreter::visitCallStatement(CallStatement& e)
{
    std::string i = e.function;

    if (i == "cout")
    {
        if (e.arguments.size() == 0)
            throw OpenBirchStaticError(0,"cout expects at least 1 argument");

        for (const std::shared_ptr<Expression> &e : e.arguments)
        {
            std::cout << evaluate(e)->getLiteral().toUserString() << " ";
        }

        std::cout << std::endl;

        return;
    }

    throw OpenBirchStaticError(0, "Unknown internal function \"" + i + "\"");
}

std::shared_ptr<Expression> Interpreter::visitLiteral(LiteralExpr& expr)
{
    return std::make_shared<LiteralExpr>(expr.getLiteral());
}

std::shared_ptr<Expression> Interpreter::visitBinary(BinaryExpr& expr)
{
    std::shared_ptr<Expression> left = evaluate(expr.m_Left);
    std::shared_ptr<Expression> right = evaluate(expr.m_Right);

    bool two_strings = false;
    if (left->getLiteral().type() == LiteralType::String || right->getLiteral().type() == LiteralType::String)
        two_strings = true;

    if (left->getLiteral().type() == LiteralType::Null || right->getLiteral().type() == LiteralType::Null)
        return std::make_shared<BinaryExpr>(expr);

    switch(expr.m_Operator->type())
    {
    case TokenType::MINUS:
        return std::make_shared<LiteralExpr>(left->getLiteral().getNumberValue() - right->getLiteral().getNumberValue());
    case TokenType::PLUS:
        if (two_strings)
            return std::make_shared<LiteralExpr>(left->getLiteral().toString() + right->getLiteral().toString());
        return std::make_shared<LiteralExpr>(left->getLiteral().getNumberValue() + right->getLiteral().getNumberValue());
    case TokenType::STAR:
        return std::make_shared<LiteralExpr>(left->getLiteral().getNumberValue() * right->getLiteral().getNumberValue());
    case TokenType::SLASH:
        return std::make_shared<LiteralExpr>(left->getLiteral().getNumberValue() / right->getLiteral().getNumberValue());
    case TokenType::EXPONENT:
        return std::make_shared<LiteralExpr>(left->getLiteral().getNumberValue() ^ right->getLiteral().getNumberValue());
    default:
        return std::make_shared<LiteralExpr>();
    }
}

std::shared_ptr<Expression> Interpreter::visitUnary(UnaryExpr& expr)
{
    std::shared_ptr<Expression> right = evaluate(expr.m_Right);

    switch(expr.m_Operator->type())
    {
    case TokenType::MINUS:
        return std::make_shared<LiteralExpr>(right->getLiteral().getNumberValue() * -1);
    case TokenType::BANG:
        return std::make_shared<LiteralExpr>( optimizedFactorial(right->getLiteral().getNumberValue()) );
    default:
        return std::make_shared<LiteralExpr>();
    }
}

std::shared_ptr<Expression> Interpreter::visitVariable(VariableExpr& expr)
{
    // TODO get variable from enviroment

    if (environment->isDefined(expr.getName()->getLiteral()))
        return environment->get(expr.getName()->getLiteral());

    return std::make_shared<UnknownExpression>();
}

std::shared_ptr<Expression> Interpreter::visitUnknown(UnknownExpression& expr)
{
    return std::make_shared<LiteralExpr>(expr.getLiteral());
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
