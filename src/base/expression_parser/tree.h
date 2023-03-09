#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.h"


class Tree
{
public:
    Tree();
    void insertNode(Node* node);
private:
    std::unique_ptr<Node> m_Root{};
    std::unique_ptr<Node> m_CurrentWorkingNode{};
};

#endif // TREE_H
