#include "operatornode.h"

OperatorNode::OperatorNode(Operator *_op)
{
    op = _op;
}

Number OperatorNode::evaluate()
{
    // TODO don't use recursive because it can cause stack overflow
    Operator *op = this->op;
    int argumentCount = op->getArgumentCount();
    if ((unsigned long)argumentCount != this->children.size())
        throw std::runtime_error("Operand count and N-ary operator for '" + op->getName() + "' does not match: " + std::to_string(argumentCount) + " != " + std::to_string(this->children.size()));

    switch(argumentCount)
    {
    case 2:
    {
        Number a = this->children[0]->evaluate();
        Number b = this->children[1]->evaluate();

        Number out = op->doOperation(b, a);

        return out;
    }
    case 1:
    {
        Number a = this->children[0]->evaluate();
        return op->doOperation(a,0);
    }
    default: {
        throw std::runtime_error("Unsupported argument count " + std::to_string(argumentCount));
    }
    }
}
