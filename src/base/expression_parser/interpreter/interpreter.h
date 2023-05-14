#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "base/expression_parser/environment.h"
#include "base/expression_parser/parser/expression.h"
#include "base/expression_parser/statementvisitor.h"
#include "base/expression_parser/parser/statement.h"
#include <string>

class Interpreter : public ExpressionVisitor, public StatementVisitor
{
public:
    /**
     * @brief Interpreter constructor. Recieves a vector of statements to be exececuted and moves it into the interpreter.
     * @param _statements the statements that the interpreter will execute.
     * @param globalEnviroment the global enviroment the interpreter will use.
     */
    Interpreter(std::vector<std::shared_ptr<Statement>>&& _statements, Environment* globalEnvironment = 0);

    ~Interpreter();

    std::vector<std::string> interpret();

    std::shared_ptr<Expression> visitLiteral(LiteralExpr&);
    std::shared_ptr<Expression> visitBinary(BinaryExpr&);
    std::shared_ptr<Expression> visitUnary(UnaryExpr&);
    std::shared_ptr<Expression> visitVariable(VariableExpr&);
    std::shared_ptr<Expression> visitUnknown(UnknownExpression&);

    void visitDeclareStatement(DeclareStatement&);
    void visitExpressionStatement(ExpressionStatement&);
    void visitCallStatement(CallStatement&);

private:
    std::vector<std::shared_ptr<Statement>> statements;
    std::shared_ptr<Expression> evaluate(std::shared_ptr<Expression>);
    void execute(std::shared_ptr<Statement>);
    std::vector<std::string> outputs;
    Environment* environment;
    bool localEnvironment = true;
};

#endif // INTERPRETER_H
