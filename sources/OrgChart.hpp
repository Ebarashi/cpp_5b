#include <stdlib.h>
#include <vector>
#include <iostream>

#include "Iterator.hpp"

using namespace std;

namespace ariel
{
    class OrgChart
    {
        private:
            Node *root = nullptr;
            Node *findNode(const std::string &name);
            void LevelOrder();
            Node* ReverseOrder();
            void PreOrder();


        public:
            
            OrgChart();
            ~OrgChart();
            void Free(Node* root);

            OrgChart(const OrgChart &other) noexcept;
            OrgChart& operator=(const OrgChart &other) noexcept;
            
            OrgChart & operator=(OrgChart &&other) noexcept;
            OrgChart(OrgChart &&other) noexcept;

            OrgChart &add_root(const std::string &root);
            OrgChart &add_sub(const std::string &parent, const std::string &child);
            
            Iterator begin();
            Iterator end();
            Iterator begin_level_order();
            Iterator end_level_order();
            Iterator begin_reverse_order();
            Iterator reverse_order();
            Iterator begin_preorder();
            Iterator end_preorder();

            Node* getRoot(){return root;}
            friend ostream &operator<<(ostream &output, OrgChart &org_chart);

    };
}