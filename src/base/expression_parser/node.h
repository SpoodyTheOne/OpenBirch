#ifndef NODE_H
#define NODE_H

#include <memory>
#include "types.h"

class Node
{
public:
    Node();
    ~Node();

    /**
     * @brief Replaces a child of this note with another
     * @param child : The node to replace, usually currentWorkingNode
     * @param newChild : The node that replaces the old one
     * @return Returns a number, 0 indicating success, 1 indicating error
     */
    int replaceChild(Node *child, Node *newChild);

    void setChild(Node *value,bool right = false);

    Number getValue() {
        return m_Value;
    }
protected:
    Node *m_LeftChild;
    Node *m_RightChild;
    Node *m_ParentNode;
    Number m_Value;
};

#endif // NODE_H
