#include "operatornode.h"

OperatorNode::OperatorNode(Operator *_op)
{
    op = _op;
}

Number OperatorNode::evaluate()
{
    Operator *op = this->op;
    int argumentCount = op->getArgumentCount();
    if ((unsigned long)argumentCount != this->children.size())
                throw std::runtime_error("Children do not match expected amount");

    switch(argumentCount)
    {
    case 2:
    {
        Number a = this->children[0]->evaluate();
        Number b = this->children[1]->evaluate();

        Number out = op->doOperation(b, a);

        return out;
        break;
    }
    case 1:
    {
        Number a = this->children[0]->evaluate();
        return op->doOperation(a,0);
        break;
    }
    default: {
        throw std::runtime_error("Unsupported argument count " + std::to_string(argumentCount));
        break;
    }
    }
}
