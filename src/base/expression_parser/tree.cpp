#include "tree.h"

Tree::Tree() {
    //m_Root = new Node();
}

Tree::~Tree() {
    delete m_Root;
}

const Node* Tree::getRoot() const { return m_Root; }
