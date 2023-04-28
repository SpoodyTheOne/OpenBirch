#ifndef STATEMENT_H
#define STATEMENT_H

#include "base/expression_parser/lexer/token.h"
#include "base/expression_parser/statementvisitor.h"
#include <string>
#include <vector>

class Expression;

class Statement
{
public:
    virtual void accept(StatementVisitor*) = 0;
};

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expression* e) : expression(e) {};

    void accept(StatementVisitor* visitor) { visitor->visitExpressionStatement(this); }

    const Expression* expression;
};

class CallStatement : public Statement
{
public:
    CallStatement(std::string f, std::vector<Expression*> a) : function(f), arguments(a) {};

    void accept(StatementVisitor* visitor) { visitor->visitCallStatement(this); }

    const std::string function;
    const std::vector<Expression*> arguments;
};

class DeclareStatement : public Statement
{
public:
    DeclareStatement(Token* n) : name(n) {};
    DeclareStatement(Token* n, Expression* i) : name(n), value(i) {};

    void accept(StatementVisitor* visitor) { visitor->visitDeclareStatement(this); };

    Token* getName()
    {
        return name;
    }

    Expression* getValue()
    {
        return value;
    }

private:
    Token* name;
    Expression* value;
};

#endif // STATEMENT_H
