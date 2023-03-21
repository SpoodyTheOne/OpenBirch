#include "node.h"
#include <iostream>

Node::Node()
{

}

Node::~Node() {

    for (auto node : children) {
        delete node;
    }

    // destroys children
    children.clear();
    // clears memory
    std::vector<Node*>().swap(children);

    std::cout << "Node destroyed" << std::endl;
}
