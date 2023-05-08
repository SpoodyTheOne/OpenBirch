#ifndef STATEMENT_H
#define STATEMENT_H

#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/statementvisitor.h"
#include <string>
#include <vector>
#include <memory>

class Expression;

class Statement
{
public:
    virtual void accept(StatementVisitor*) = 0;
};

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(std::shared_ptr<Expression> e) : expression(e) {};

    void accept(StatementVisitor* visitor) { visitor->visitExpressionStatement(this); }

    const std::shared_ptr<Expression> expression;
};

class CallStatement : public Statement
{
public:
    CallStatement(std::string f, std::vector<std::shared_ptr<Expression>> a) : function(f), arguments(a) {};

    void accept(StatementVisitor* visitor) { visitor->visitCallStatement(this); }

    const std::string function;
    const std::vector<std::shared_ptr<Expression>> arguments;
};

class DeclareStatement : public Statement
{
public:
<<<<<<< HEAD
    DeclareStatement(Token* n) : name(n) {};
    DeclareStatement(Token* n, std::shared_ptr<Expression> i) : name(n), value(i) {};
=======
    DeclareStatement(std::shared_ptr<Token> n) : name(n) {};
    DeclareStatement(std::shared_ptr<Token> n, Expression* i) : name(n), value(i) {};
>>>>>>> origin/Interpreter

    void accept(StatementVisitor* visitor) { visitor->visitDeclareStatement(this); };

    std::shared_ptr<Token> getName()
    {
        return name;
    }

    std::shared_ptr<Expression> getValue()
    {
        return value;
    }

private:
<<<<<<< HEAD
    Token* name;
    std::shared_ptr<Expression> value;
=======
    std::shared_ptr<Token> name;
    Expression* value;
>>>>>>> origin/Interpreter
};

#endif // STATEMENT_H
