
#include "Node.hpp"

using namespace ariel;

Node::Node(const std::string &name)
{
    this->name = name;
    this->LO_Next = nullptr;
    this->PO_Next = nullptr;
    this->RO_Next = nullptr;
}

Node::Node(const Node *other)
{
    this->name = other->name;
    this->LO_Next = other->LO_Next;
    this->PO_Next = other->PO_Next;
    this->RO_Next = other->RO_Next;
    for (Node *child : other->children)
    {
        Node *temp = new Node(child);
        this->children.push_back(temp);
    }
}
