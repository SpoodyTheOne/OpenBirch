#ifndef NODE_H
#define NODE_H

#include "base/deprecated/expression_parser/symboltable.h"
#include "gui/expression_tree_visualizer/iinformationalnode.h"
#include "base/expressionvalue.h"
#include <memory>
#include <vector>

class Node : public IInformationalNode
{
public:
    Node();
    virtual ~Node();

    Node* parent{this};
    std::vector<Node*> children;
    virtual ExpressionValue evaluate(SymbolTable *table = nullptr) = 0;
    virtual QString getInformation(SymbolTable *table = nullptr) = 0;
};

#endif // NODE_H
