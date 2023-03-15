#ifndef NODE_H
#define NODE_H

#include "gui/expression_tree_visualizer/iinformationalnode.h"
#include "types.h"
#include <memory>
#include <vector>

class Node : public IInformationalNode
{
public:
    Node();
    ~Node();

    Node* parent{this};
    std::vector<Node*> children;
    virtual ExpressionValue evaluate() = 0;
    virtual QString getInformation() = 0;
};

#endif // NODE_H
