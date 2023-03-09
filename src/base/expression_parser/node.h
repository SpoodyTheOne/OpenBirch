#ifndef NODE_H
#define NODE_H

#include <memory>
#include "types.h"
#include "node_type.h"

class Node
{
public:
    Node(NodeType nodeType);

    /**
     * @brief Checks whether or not this node is the deepest operand node.
     * @return True if it's the deepest. False if not.
     */
    bool isDeepestOperandNode() const;

    void replaceChild(Node *child, Node *newChild) {
        auto left_ptr = m_LeftChild.get();
        auto right_ptr = m_LeftChild.get();

        if (left_ptr == child) {
            left_ptr = newChild;
        } else if ()
    }

private:
    std::unique_ptr<Node> m_LeftChild{};
    std::unique_ptr<Node> m_RightChild{};
    std::unique_ptr<Node> m_ParentNode;
    NodeType m_NodeType;
    Number m_Value;
};

#endif // NODE_H
