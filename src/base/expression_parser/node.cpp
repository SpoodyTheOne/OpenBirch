#include "node.h"

Node::Node(NodeType nodeType)
{
    m_NodeType = nodeType;
}

NodeType Node::GetNodeType() const
{
    return m_NodeType;
}

bool Node::isDeepestOperandNode() const
{
    // If node doesn't have two children, it can't be the deepest
    if (m_LeftChild == nullptr || m_RightChild == nullptr)
        return false;

    // If both child nodes are of type NodeType::Constant,
    // then this must be the deepest operand node (next deepest node).
    if (    m_LeftChild->GetNodeType() == NodeType::Constant
            && m_RightChild->GetNodeType() == NodeType::Constant)
        return true;

    return false;
}
