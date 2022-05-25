#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

OrgChart::OrgChart()
{
    this->root = nullptr;
}

OrgChart::OrgChart(const OrgChart &other) noexcept
{
    if (other.root != nullptr)
    {
        this->root = nullptr;
        root = new Node(other.root);

    }
    else
    {
        root = nullptr;
    }
}

OrgChart &OrgChart::operator=(const OrgChart &other) noexcept
{
    if (this == &other) 
    {
                return *this;
    }
    delete(this->root);
    root = new Node(other.root);
    return *this;
}

OrgChart::~OrgChart()
{
    Free(root);

} 

void OrgChart::Free(Node* root)
{
    if (root == nullptr) 
    {
        return;
    }

    for(size_t i = 0; i <root->children.size(); i++ )
    {
        Free(root->children.at(i));
    }
    delete root;
}


OrgChart& OrgChart::operator=(OrgChart &&other) noexcept
{
    *this = move(other);
    return *this;
}

OrgChart::OrgChart(OrgChart &&other) noexcept
{
    *this = move(other);  
}

OrgChart &OrgChart::add_root(const string &root)
{
    if (root.empty())
    {
        throw logic_error("empty string");
    }
    if (this->root != nullptr)
    {
        this->root->name = root;
    }
    else
    {
        this->root = new Node(root);
        this->root->name = root;
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const string &parent, const string &child)
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart");
    }
    if (child.empty())
    {
        throw logic_error("empty string");
    }
    Node *manager = findNode(parent);
    if (manager == NULL)
    {
        throw logic_error(parent + "is not in the chart");
    }
    Node *sub = new Node(child);
    manager->children.push_back(sub);
    return *this;
}

Node *OrgChart::findNode(const string &name)
{
    for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
    {
        if (*it == name)
        {
            return it.getNode();
        }
    }
    return NULL;
}

void OrgChart::LevelOrder()
{
    queue<Node *> que;
    vector<Node *> vec;
    
    que.push(this->root);
    while (!que.empty())
    {
        Node *curr = que.front();
        que.pop();
        vec.push_back(curr);
        for (unsigned long i = 0; i < curr->children.size(); i++)
        {
            que.push(curr->children[i]);
        }
    }

    for (unsigned long i = 0; i < vec.size() - 1; i++)
    {
        vec[i]->LO_Next = vec[i + 1];
    }
    vec[vec.size() - 1]->LO_Next = nullptr;
}

Node* OrgChart::ReverseOrder()
{
    queue<Node *> que;
    vector<Node *> vec;
    
    que.push(this->root);

    while (!que.empty())
    {
        Node *curr = que.front();
        que.pop();
        vec.push_back(curr);

        for (int i = (int)curr->children.size() - 1; i >= 0; i--)
        {
            que.push(curr->children[(unsigned long)i]);
        }
    }
    reverse(vec.begin(), vec.end());
    for (unsigned long i = 0; i < vec.size() - 1; i++)
    {
        vec[i]->RO_Next = vec[i + 1];
    }
    vec[vec.size() - 1]->RO_Next = nullptr;
    return vec[0];
}

void OrgChart::PreOrder()
{
    if (root == nullptr) 
    {
        return;
    }
    stack<Node*> stack;      
    vector<Node *> vec;
    stack.push(root);

    while (!stack.empty()) {

        Node* curr = stack.top();
        stack.pop();

        vec.push_back(curr);
        for ( int i =(int) curr->children.size() -1; i >= 0; i--) 
        {
            stack.push(curr->children.at((size_t)i));
        }
    } 
    for (unsigned long i = 0; i < vec.size() - 1; i++)
    {
        vec[i]->PO_Next = vec[i + 1];
    }
    vec[vec.size() - 1]->PO_Next = nullptr;    
}


Iterator OrgChart::begin_level_order()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    LevelOrder();
    return Iterator(this->root, Type::Level);
}

Iterator OrgChart::end_level_order()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    return Iterator(nullptr, Type::Level);
}

Iterator OrgChart::begin_reverse_order()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    Node* curr = ReverseOrder();
    return Iterator(curr, Type::Reverse);
}

Iterator OrgChart::reverse_order()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    return Iterator(nullptr, Type::Reverse);
}

Iterator OrgChart::begin_preorder()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    PreOrder();
    return Iterator(this->root, Type::Pre);
}

Iterator OrgChart::end_preorder()
{
    if (this->root == nullptr)
    {
        throw logic_error("empty chart!");
    }
    return Iterator(nullptr, Type::Pre);
}

Iterator OrgChart::begin()
{
    return begin_level_order();
}

Iterator OrgChart::end()
{
    return end_level_order();
}

static void print(Node* root , ostream& os)
{
        if(root == nullptr)
        {
            return;
        }
        
        os << root->name << "--";

        for(auto *child: root->children)
        {
            print(child, os);
        }
}

ostream& ariel::operator<<(ostream &output, OrgChart &org_chart)
{       
        print(org_chart.getRoot(), output);
        return output;
}

