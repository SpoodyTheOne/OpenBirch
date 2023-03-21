#include "operatornode.h"

OperatorNode::OperatorNode(Operator *_op)
{
    op = _op;
}

ExpressionValue OperatorNode::evaluate(SymbolTable *table)
{
    // TODO don't use recursive because it can cause stack overflow
    Operator *op = this->op;
    int argumentCount = op->getArgumentCount();
    if ((unsigned long)argumentCount != this->children.size())
        throw std::runtime_error("Operand count and N-ary operator for '" + op->getName() + "' does not match: " + std::to_string(argumentCount) + " != " + std::to_string(this->children.size()));

    if (this->children.size() != op->getArgumentCount())
        throw std::runtime_error("Argument count mismatch, expected " + std::to_string(op->getArgumentCount()) + " got " + std::to_string(this->children.size()));

    std::vector<ExpressionValue> values;

    for (int i = 0; i < op->getArgumentCount(); i++)
        values.push_back(this->children[i]->evaluate(table));

    return op->doOperation(values);
}

QString OperatorNode::getInformation(SymbolTable *table)
{
    return QString(this->op->getSign().c_str());
}
