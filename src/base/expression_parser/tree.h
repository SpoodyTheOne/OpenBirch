#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.h"


class Tree
{
public:
    Tree();
private:
    std::unique_ptr<Node> m_Root;
};

#endif // TREE_H
