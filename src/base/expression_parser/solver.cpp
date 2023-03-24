#include "solver.h"
#include "base/nodes/constantnode.h"
#include "base/nodes/node.h"
#include "base/nodes/operatornode.h"
#include "base/nodes/variablenode.h"
#include <QRegExp>
#include <stack>

Solver::Solver(QString input, SymbolTable *symbolTable) : infix{input}, symbolTable{*symbolTable}
{

}

QString Solver::solve()
{
    QString preParsed = preParse(infix);
    QString parsed = parse(preParsed);

    compile(parsed);
    postCompile();

    QString evaluated = evaluate();
    QString postEvaluated = postEvaluate(evaluated);

    return postEvaluated;
}

QString Solver::preParse(QString input)
{
    // Replace aliases of operators with their true sign ( cdot -> *)
    // TOOD: once we add aliases

    // Replace functions with placeholders
    // TODO: add functions

    // Use symboltable to automatically turn 2x -> 2*x or xy -> x*y
    // TODO: remake symbol table

    // Factorial fix

    QString output = input;



    return input;
}

QString Solver::parse(QString input)
{
    return QString(PostFixParser::parseExpression(input.toStdString()).c_str());
}

void Solver::compile(QString postfix)
{
    std::stack<Node *> treeStack;
    size_t postfixLen = postfix.size();

    for (size_t i = 0; i < postfixLen; i++)
    {
        if (postfix.at(i) == ' ')
            continue;

        std::string tokenSequence = PostFixParser::getSequence(postfix, i, postfixLen - i);
        i += tokenSequence.size() - 1;

        try
        {
            // The token sequence is an operand, so just push a leaf node to the stack
            PreciseValue operand = PreciseValue(tokenSequence);
            Node* leafNode = new ConstantNode(operand);
            treeStack.push(leafNode);
            continue;
        }
        catch (const std::exception& e) { }

        Operator* op = OperatorFactory::create(tokenSequence);
        if (op == nullptr) {
            // The token sequence is a variable, so just push a leaf node to the stack
            Node* leafNode = new VariableNode(tokenSequence);
            treeStack.push(leafNode);
            continue;
        }

        Node* opNode = new OperatorNode(op);

       for (int i = 0; i < op->getArgumentCount(); i++) {
           // Insert child nodes so left is first index
           opNode->children.insert(opNode->children.begin(), treeStack.top());
           treeStack.top()->parent = opNode;
           treeStack.pop();
       }

       treeStack.push(opNode);
    }

    if (postfixLen > 0)
        this->compiledRoot = treeStack.top();
}

void Solver::postCompile()
{
    if (this->compiledRoot == nullptr)
        throw new std::runtime_error("nullptr tree root in post-compile!");

    // TODO: replace placeholder nodes with function nodes
}

QString Solver::evaluate()
{
    return this->compiledRoot->evaluate(&this->symbolTable);
}

QString Solver::postEvaluate(QString input)
{
    if (!isTrueEquation && input.startsWith("x="))
        return input.mid(2);

    return input;
}
