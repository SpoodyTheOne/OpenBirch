#include "node.h"

Node::Node()
{

}

Node::~Node() {
    delete leftChild;
    delete rightChild;
}
