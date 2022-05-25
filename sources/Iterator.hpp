#include <string>

#include "Node.hpp"

using namespace std;
using namespace ariel;

enum class Type{Level,Reverse,Pre};

class Iterator
        {
        private:
            Node *currNode;
            Type type;

        public:
            Iterator();
            Iterator(Node *root, Type type);
            string &operator*() const;
            string *operator->() const;
            Node *getNode();
            Iterator &operator++();   
            Iterator operator++(int); 
            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;
        };