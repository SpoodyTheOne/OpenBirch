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

    void accept(StatementVisitor* visitor) { visitor->visitExpressionStatement(*this); }

    const std::shared_ptr<Expression> expression;
};

class CallStatement : public Statement
{
public:
    CallStatement(std::shared_ptr<Expression> f, std::vector<std::shared_ptr<Expression>> a) : function(f), arguments(a) {};

    void accept(StatementVisitor* visitor) { visitor->visitCallStatement(*this); }

    const std::shared_ptr<Expression> function;
    const std::vector<std::shared_ptr<Expression>> arguments;
};

class DeclareStatement : public Statement
{
public:
    DeclareStatement(const Token& n) : name(n) {};
    DeclareStatement(const Token& n, std::shared_ptr<Expression> i) : name(n), value(i) {};


    void accept(StatementVisitor* visitor) { visitor->visitDeclareStatement(*this); };

    const Token& getName()
    {
        return name;
    }

    std::shared_ptr<Expression> getValue()
    {
        return value;
    }

private:
    const Token& name;
    std::shared_ptr<Expression> value;

};

#endif // STATEMENT_H
