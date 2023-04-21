#ifndef STATEMENTVISITOR_H
#define STATEMENTVISITOR_H

class ExpressionStatement;
class CallStatement;

class StatementVisitor
{
public:
    virtual void visitExpressionStatement(ExpressionStatement*) = 0;
    virtual void visitCallStatement(CallStatement*) = 0;


    virtual ~StatementVisitor() {};
};

#endif // STATEMENTVISITOR_H
