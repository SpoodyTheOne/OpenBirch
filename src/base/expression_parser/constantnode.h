#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H


#include "base/expression_parser/node.h"
class ConstantNode : public Node
{
public:
    ConstantNode(Number value);
};

#endif // CONSTANTNODE_H
