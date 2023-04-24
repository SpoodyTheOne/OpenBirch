#ifndef STATEMENTVISITOR_H
#define STATEMENTVISITOR_H

class ExpressionStatement;
class CallStatement;
class VariableStatement;

class StatementVisitor
{
public:
    virtual void visitVariableStatement(VariableStatement*) = 0;
    virtual void visitExpressionStatement(ExpressionStatement*) = 0;
    virtual void visitCallStatement(CallStatement*) = 0;


    virtual ~StatementVisitor() {};
};

#endif // STATEMENTVISITOR_H
