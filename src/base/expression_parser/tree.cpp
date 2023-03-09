#include "tree.h"

Tree::Tree() {
    m_Root = new Node();
}

Tree::~Tree() {
    delete m_Root;
}
