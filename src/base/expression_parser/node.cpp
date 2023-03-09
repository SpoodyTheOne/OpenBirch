#include "node.h"

Node::Node()
{

}

Node::~Node() {
    delete m_LeftChild;
    delete m_RightChild;
    m_ParentNode = nullptr;
}

int Node::replaceChild(Node *child, Node *newChild) {

    if (m_ParentNode->m_LeftChild == child) {
        m_ParentNode->m_LeftChild = newChild;
        return 1;
    }
    else if (m_ParentNode->m_RightChild == child) {
        m_ParentNode->m_RightChild = newChild;
        return 1;
    }

    return 1;
}

void Node::setChild(Node *value, bool right) {
    if (right)
        m_RightChild = value;
    else
        m_LeftChild = value;
}
