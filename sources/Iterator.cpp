#include <string>
#include "Iterator.hpp"

using namespace std;

Iterator::Iterator(Node *root, Type type)
{
    this->currNode = root;
    this->type = type;
}

string& Iterator::operator*() const
{
    if(currNode == nullptr){
            throw std::invalid_argument("nullptr");
        }
    return currNode->name;
}

string *Iterator::operator->() const
{
    return &(currNode->name);
}

Node *Iterator::getNode()
{
    return this->currNode;
}

Iterator &Iterator::operator++()
{
    if (this->type == Type::Level)
    {
        this->currNode = this->currNode->LO_Next;
    }
    if (this->type == Type::Reverse)
    {
        this->currNode = this->currNode->RO_Next;
    }
    if (this->type == Type::Pre)
    {
        this->currNode = this->currNode->PO_Next;
    }
    return *this;
}

Iterator Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

bool Iterator::operator==(const Iterator &other) const
{
    return currNode == other.currNode;
}

bool Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}