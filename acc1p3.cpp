#define SOL_NUM 3

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>



typedef unsigned long long LL;

LL N, T;

std::vector<std::pair<LL, LL>> optionsBuffer;


struct Node
{
    std::pair<LL, LL> data; // a_i, b_i
    Node* right;
    Node* left;
    Node* parent;

    Node(std::pair<LL, LL> d = std::pair<LL, LL>())
    {
        data = d;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
};

struct BST_tree
{
    Node* root;
    Node* minValueNode(Node* node)
    {
        Node* current = node;
  
        /* loop down to find the leftmost leaf */
        while (current && current->left != nullptr)
            current = current->left;
  
        return current;
    }

    void deleteElement(Node* node)
    {
        if (node == nullptr)
            return;
        
        //no children
        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->parent)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                if (node->parent->right == node)
                {
                    node->parent->right = nullptr;
                }
            }
            else
            {
                //node is the head
                delete root;
                root = nullptr;
            }
            return;
        }

        if (node->right)
        {
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            
            if(temp->parent->left == temp)
            {
                temp->parent->left = nullptr;
            }
            if(temp->parent->right == temp)
            {
                temp->parent->right = nullptr;
            }
            delete temp;
        }

        if (node->right == nullptr && node->left != nullptr)
        {
            node->data = node->left->data;
            Node* OGLeft = node->left;
            Node* leftRight = node->left->right;
            if (node->left->left)
            {
                node->left->left->parent = node;
                node->left = node->left->left;
            }
            else
            {
                node->left = nullptr;
            }
            if (leftRight)
            {
                leftRight->parent = node;
                node->right = leftRight;
            }
            else
            {
                node->right = nullptr;
            }
            delete OGLeft;
            return;
        }
        if (node->left == nullptr && node->right != nullptr)
        {
            node->data = node->right->data;
            Node* OGRight = node->right;
            Node* rightLeft = node->right->left;
            if (node->right->right)
            {
                node->right->right->parent = node;
                node->right = node->right->right;
            }
            if (rightLeft)
            {
                rightLeft->parent = node;
                node->right = rightLeft;
            }
            delete OGRight;
            return;
        }
    }

    void insertElement(std::pair<LL, LL> data)
    {

        Node* node = new Node(data);
        if (root == nullptr)
        {
            root = node;
            return;
        }

        Node* prev = nullptr;
        Node* temp = root;
        
        while (temp)
        {
            if (temp->data.first > data.first)
            {
                prev = temp;
                temp = temp->left;
            }
            else if (temp->data.first <= data.first)
            {
                prev = temp;
                temp = temp->right;
            }
        }
        if (prev->data.first > data.first)
            prev->left = node;
        else
            prev->right = node;

        node->parent = prev;
    }


    Node* getMaxValueNode()
    {
        if (root == nullptr) 
        {
            return root;
        }
        Node *temp = root;
        while (temp->right)
        {
            temp = temp->right;
        }
         
        return temp;
    }

    std::pair<LL, LL> getMaxValueNodeAndDelete()
    {
        if (root == nullptr) 
        {
            return std::pair<LL, LL>();
        }
        Node *temp = root;
        while (temp->right)
        {
            temp = temp->right;
        }
        //if head root
        if (temp->parent == nullptr)
        {
            std::pair<LL, LL> ret = temp->data;
            //if no children -> delete entire tree
            if (temp->left == nullptr)
            {
                delete root;
                root = nullptr;
            }
            //reassign root
            else
            {
                root = temp->left;
                root->parent = nullptr;
                delete temp;
            }
            return ret;
        }
        //if no children and not head -> just remove node
        if(temp->left == nullptr && temp->right == nullptr)
        {
            temp->parent->right = nullptr;
            std::pair<LL, LL> ret = temp->data;
            delete temp;
            return ret;
        }
        //if one child to the left
        if (temp->left != nullptr)
        {
            temp->left->parent = temp->parent;
            temp->parent->right = temp->left;
            std::pair<LL, LL> ret = temp->data;
            delete temp;
            return ret;
        }
        return std::pair<LL, LL>();
    }

    void contruct()
    {
        std::sort(optionsBuffer.begin(), optionsBuffer.end(), [](std::pair<LL, LL> a, std::pair<LL, LL> b)
        {
            return a.first < b.first;
        });
        root = addNodesInConstruction(0, N - 1);
    }
    
    Node* addNodesInConstruction(long long l, long long r)
    {
        if (l > r)
        {
            return nullptr;
        }
        long long m = (l + r) / 2 + ((l + r) % 2 == 1);
        Node* constructRoot = new Node(optionsBuffer[m]);
        constructRoot->left = addNodesInConstruction(l, m - 1);
        if (constructRoot->left)
        {
            constructRoot->left->parent = constructRoot;
        }
        constructRoot->right = addNodesInConstruction(m + 1, r);
        if (constructRoot->right)
        {
            constructRoot->right->parent = constructRoot;
        }
        return constructRoot;
    }
};

BST_tree options;

struct solver
{
    std::vector<std::pair<LL, LL>> opt;

    void addElement(std::pair<LL, LL> in)
    {
        opt.push_back(in);
    }
    LL retrieveMaxElement()
    {
        if (opt.size() > 0)
        {
            auto it = std::max_element(opt.begin(), opt.end(), [](std::pair<LL, LL> a, std::pair<LL, LL> b)
            {
                return a.first < b.first;
            });
            LL ret = it->first;
            it->first = std::max(0LL, (long long) (it->first - it->second));
            return ret;
        }
        return 0ULL;
    }
};

solver options_vector;


void parseInput(std::string str);
void parseOption_BST(std::string str);
LL determineMaxHappiness_BST();
LL determineMaxHappiness_vector();
void parseOption_vector(std::string str);

int main()
{
    std::string in;
    std::getline(std::cin, in);

    parseInput(in);

    for (LL i = 0; i < N; i++)
    {
        std::string input;
        std::getline(std::cin, input);
        parseOption_vector(input);
    }
    //options.contruct();

    std::cout << determineMaxHappiness_vector() << '\n';
}

LL determineMaxHappiness_vector()
{
    LL max = 0ULL;

    for (LL i = 0; i < T; i++)
    {
        max += options_vector.retrieveMaxElement();
    }
    
    return max % 998244353;
}

LL determineMaxHappiness_BST()
{
    LL max = 0ULL;

    for (LL i = 0; i < T; i++)
    {
        // auto maxIt = options.getMaxValueNode();
        // max += maxIt->data.first;

        // std::pair<LL, LL> elemToInsert = {
        //     std::max(0LL, (long long) (maxIt->data.first - maxIt->data.second)),
        //     maxIt->data.second
        // };

        // options.deleteElement(maxIt);
        // options.insertElement(elemToInsert);
        auto maxVal = options.getMaxValueNodeAndDelete();
        max += maxVal.first;

        options.insertElement({
            std::max(0LL, (long long) (maxVal.first - maxVal.second)),
            maxVal.second
        });
    }


    return max % 998244353;
}


void parseInput(std::string str)
{
    LL lines[2] = {0ULL, 0ULL};
    LL j = 0;
    for (LL i = 0; i < str.length() && j < 2; i++)
    {
        if (str[i] == ' ')
        {
            lines[j] /= 10;
            j++;
        }
        else
        {
            lines[j] += str[i] - '0';
            lines[j] *= 10;
        }
    }
    lines[1] /= 10;

    N = lines[0];
    T = lines[1];
}

void parseOption_BST(std::string str)
{
    LL option[2] = {0ULL, 0ULL};
    LL j = 0;
    for (LL i = 0; i < str.length() && j < 2; i++)
    {
        if (str[i] == ' ')
        {
            option[j] /= 10;
            j++;
        }
        else
        {
            option[j] += str[i] - '0';
            option[j] *= 10;
        }
    }
    option[1] /= 10;

    optionsBuffer.push_back(std::pair<LL, LL>(option[0], option[1]));
}

void parseOption_vector(std::string str)
{
    LL option[2] = {0ULL, 0ULL};
    LL j = 0;
    for (LL i = 0; i < str.length() && j < 2; i++)
    {
        if (str[i] == ' ')
        {
            option[j] /= 10;
            j++;
        }
        else
        {
            option[j] += str[i] - '0';
            option[j] *= 10;
        }
    }
    option[1] /= 10;

    options_vector.addElement({
        option[0], option[1]
    });
}