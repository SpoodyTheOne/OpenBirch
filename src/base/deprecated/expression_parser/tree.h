#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.h"


class Tree
{
public:
    Tree();
    ~Tree();

    /**
     * @brief Adds a node to the tree
     * @param node
     * The node to be added
     * @param parent
     * The node to add under
     * @param right_child
     * If true, m_RighChild of parent is set, otherwise its m_LeftChild
     */
    void addNode(Node *node, Node *parent, bool right_child);
    const Node* getRoot() const;
private:
    Node *m_Root;
};

#endif // TREE_H
