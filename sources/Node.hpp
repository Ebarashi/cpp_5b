#include <stdlib.h>
#include <vector>
#include <iostream>

 using namespace std;
 
 namespace ariel
 {
    class Node
        {
        public:
            string name;
            Node *LO_Next;
            Node *RO_Next;
            Node *PO_Next;
            vector<Node *> children;
            Node(const string &name);
            Node(const Node *other);
        };
 }