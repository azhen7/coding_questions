#define SOL_NUM 3

#include <iostream>
#include <string>
#include <algorithm>

#if SOL_NUM == 3

#include <list>
#include <utility>

#else

#include <vector>
#include <array>

#endif

typedef unsigned long long LL;

LL N, T;

#if SOL_NUM == 3

struct node
{
    std::pair<LL, LL> data;
    node* right;
    node* left;
    node* parent;

    node(std::pair<LL, LL> d = std::pair<LL, LL>())
    {
        data = d;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
    
    void deleteElement()
    {
        
    }

    void insertElement(std::pair<LL, LL> data)
    {
        node* it = this;
        while (it)
        {
            if (it->data.first <= data.first)
            {
                if (it->right)
                {
                    it = it->right;
                }
                else
                {
                    node* insert = new node(data);
                    it->right = insert;
                    insert->parent = it;
                    break;
                }
            }
            else
            {
                if (it->left)
                {
                    it = it->left;
                }
                else
                {
                    node* insert = new node(data);
                    it->left = insert;
                    insert->parent = it;
                    break;
                }
            }
        }
    }

    LL getMax()
    {
        LL max = 0ULL;

        node* it = this;
        max = this->data.first;
        while (it->right)
        {
            it = it->right;
            if (it->data.first > max)
            { 
                max = it->data.first;
            }
        }

        this->insertElement({std::max(0LL, (long long) (it->data.first - it->data.second)), it->data.second});

        if (it->left)
        {
            it->data = it->left->data;
            node* right = it->left->right;
            if (it->left->left)
            {
                it->left->left->parent = it;
                it->left = it->left->left;
            }
            else
            {
                it->left = nullptr;
            }
            if (right)
            {
                right->parent = it;
                it->right = right;
            }
        }
        else
        {
            if (it->parent)
            {
                it->parent->right = nullptr;
            }

            delete it;
            it = nullptr;
        }

        return max;
    }
};

node* options = nullptr;

//std::list<std::pair<LL, LL>> options;

#else

std::vector<std::array<LL, 2>> options;

#endif

void parseInput(std::string str);
void parseOption(std::string str);
LL determineMaxHappiness();

int main()
{
    std::string in;
    std::getline(std::cin, in);

    parseInput(in);

    for (LL i = 0; i < N; i++)
    {
        std::string input;
        std::getline(std::cin, input);
        parseOption(input);
    }

    std::cout << determineMaxHappiness() << '\n';
}

LL determineMaxHappiness()
{
    //auto test = options;
    LL max = 0ULL;


//SLOW - DON'T USE
#if SOL_NUM == 1

    std::sort(options.begin(), options.end(), [](std::array<LL, 2> a, std::array<LL, 2> b)
    {
        return a[0] < b[0];
    });
    for (LL i = 0; i < T; i++)
    {
        //add last elem (since it's largest)
        max += options[N - 1][0];

        std::array<LL, 2> maxVal = options[N - 1];
        maxVal[0] = std::max(0LL, (long long) (options[N - 1][0] - options[N - 1][1]));

        for (LL j = 0; j < options.size(); j++)
        {
            if (options[j][0] >= maxVal[0])
            {
                options.insert(options.begin() + j, maxVal);
                break;
            }
            if (j == options.size() - 1)
            {
                options.push_back(maxVal);
            }
        }

        options.erase(options.end() - 1);
    }

#elif SOL_NUM == 2

    for (LL i = 0; i < T; i++)
    {
        LL currentMaxIndex = 0ULL;
        for (LL j = 0; j < N; j++)
        {
            if (options[j][0] > options[currentMaxIndex][0])
            {
                currentMaxIndex = j;
            }
        }
        if (options[currentMaxIndex][0] == 0LL)
        {
            break;
        }
        max += options[currentMaxIndex][0];
        options[currentMaxIndex][0] = std::max(0LL, (long long) (options[currentMaxIndex][0] - options[currentMaxIndex][1]));
    }

#elif SOL_NUM == 3

    for (LL i = 0; i < T; i++)
    {
        //std::cout << options->getMax() << '\n';
        max += options->getMax();
        // auto it = options.end();
        // --it;
        // max += it->first;
        // it->first = std::max(0LL, (long long) (it->first - it->second));
    }

#endif

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

void parseOption(std::string str)
{

#if SOL_NUM == 3


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

    if (!options)
    {
        options = new node(std::pair<LL, LL>(option[0], option[1]));
    }
    else
    {
        options->insertElement(std::pair<LL, LL>(option[0], option[1]));
    }

#else

    std::array<LL, 2> option{0, 0};
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

    options.push_back(option);

#endif

}