#include "node.h"

Node::Node()
{

}

Node::~Node() {
    // destroys children
    children.clear();
    // clears memory
    std::vector<Node*>().swap(children);
}
